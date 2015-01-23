// VERSION: 1
/*
*  UPPAAAL2C (c) 2014 Ariel Eizenberg - arieleiz@seas.upenn.edu.
*
*    This file is part of UPPAAAL2C. You can redistribute it and/or modify
*    it under the terms of the Academic Free License 3.0
*	  (http://opensource.org/licenses/AFL-3.0).
*
*/

#include "uppaal2c.h"
#include "uppaal2c_platform.h"
#include "uppaal2c_types.h"
#include "uppaal2c_private.h"
#include "model.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#pragma warning(disable : 4127)
#endif

#ifdef DISPATCH_DEBUG
#define TRACE(str)	do { if(DISPATCHER._dbgout != NULL) {DISPATCHER._dbglock->lock(); DISPATCHER._dbgout->printf str ; DISPATCHER._dbglock->unlock(); } } while(0)
#else
#define TRACE(str)	do {} while(0)
#endif

// static assert to make sure code is 32-bit, since pointers are used as 32-bit callback IDs (fixable, but no reason yet)
static int __STATIC_ASSERT_64BIT[(sizeof(void*) == 4) ? 1 : -1];

U2C_DISPATCHER_STATE DISPATCHER;

///////////////////////

static void u2c_run_steps();
static void u2c_clear_signals();
static void u2c_clear_normal_step();
static void u2c_run_tasks(int types);

static U2C_TRANSITION* u2c_find_valid_transition(volatile U2C_TASK* process);
static U2C_BOOL u2c_can_take_transition(U2C_TRANSITION* transition);
static void u2c_take_transition(volatile U2C_TASK* process, U2C_TRANSITION* transition);
static void u2c_enter_state(volatile U2C_TASK* process, U2C_STATENODE* state);
static void u2c_leave_state(volatile U2C_TASK* process, U2C_STATENODE* state);

static void _u2c_task_main(void* arg);

static void _u2c_ticker_handler_cb(void* ctx);
static void _u2c_channel_irq_handler(U2C_GPIO_IRQ_HANDLER_PARAM_DECL);

static int u2c_add_time(int timecur, int timespan);
static int u2c_sub_time(int timecur, int timeprev);
static int u2c_wall_add(int timespan);
static int u2c_wall_diff(int timeprev);

//////////////////////

void u2c_init()
{
	int i, j;

	DISPATCHER._cnt_proc = 0;
	DISPATCHER._tick = 0;
	
	// init channels
	for (i = 0; i < TOTAL_CHANNEL_COUNT; ++i)
	{
		U2C_CHANNEL* chn = ALL_CHANNELS[i];
		for (j = 0; j < U2C_MAX_SEND_DATA; ++j)
		{
			U2C_SENDDATA* sd = &chn->send[j];
			sd->pin = NC;
			sd->mode = U2C_SendChannelModeNone;
			sd->last_write = 0;
			u2c_platform_gpio_clear(&sd->gpio);
		}

		U2C_RECVDATA* rv = &chn->recv;
		rv->mode = U2C_ReceiveChannelModeNone;
		u2c_platform_gpio_clear(&rv->gpio);
	}

}

void u2c_set_clock_multiplier(int multiplier)
{
	DISPATCHER._clock_multiplier = multiplier;
}

#ifdef DISPATCH_DEBUG
#ifdef DISPATCH_DEBUG
void u2c_init_debug(debug_print_cb_t cb);
#endif

void u2c_init_debug(Serial* serial, Mutex* dbgmutex)
{
	_dbgout = serial;
	_dbglock = dbgmutex;
	TRACE(("Dispatcher initializing.\r\n"));
}
#endif


void u2c_add_task(U2C_TASK* ps)
{
#ifdef DISPATCH_DEBUG
	if (DISPATCHER._cnt_proc >= U2C_TOTAL_TASK_COUNT)
	{
		TRACE(("Too many processes!\r\n"));
		return;
	}
#endif
	U2C_TASK_LIST[DISPATCHER._cnt_proc] = ps;
	++DISPATCHER._cnt_proc;
}

static void _u2c_ticker_handler_cb(void* ctx)
{
	++ DISPATCHER._tick;
}

static void _u2c_channel_irq_handler(U2C_GPIO_IRQ_HANDLER_PARAM_DECL)
{
	U2C_CHANNEL* channel = (U2C_CHANNEL*)U2C_GPIO_IRQ_HANDLER_PARAM_CTX;
	if (u2c_platform_is_interrupt_mode(channel->recv.mode, U2C_GPIO_IRQ_HANDLER_PARAM_EVTMODE))
		u2c_fire_channel(channel);
}

static void u2c_fire_channel_pulse_cb(void* context)
{
	U2C_SENDDATA* sd = (U2C_SENDDATA*)context;
	switch (sd->mode)
	{
	case U2C_SendChannelModePulseUp:
		u2c_platform_gpio_reset(&sd->gpio);
		break;
	case U2C_SendChannelModePulseDown:
		u2c_platform_gpio_set(&sd->gpio);
		break;
	}
}

void u2c_fire_channel(U2C_CHANNEL* channel)
{
	channel->cur_fired = U2C_TRUE;
	for (int i = 0; i < U2C_MAX_SEND_DATA; ++i)
	{
		U2C_SENDDATA* sd = &channel->send[i];
		if (sd->pin == NC)
			continue;
		switch (sd->mode)
		{
		case U2C_SendChannelModeNone:
			break;
		case U2C_SendChannelModeSet:
			u2c_platform_gpio_set(&sd->gpio);
			break;
		case U2C_SendChannelModeToggle:
			sd->last_write = 1 - sd->last_write;
			if (sd->last_write)
				u2c_platform_gpio_set(&sd->gpio);
			else
				u2c_platform_gpio_reset(&sd->gpio);
			break;
		case U2C_SendChannelModeReset:
			u2c_platform_gpio_reset(&sd->gpio);
			break;
		case U2C_SendChannelModePulseUp:
			u2c_platform_gpio_set(&sd->gpio);
			u2c_platform_ticker_set(&sd->ticker, sd->pulse_length_us, U2C_FALSE, u2c_fire_channel_pulse_cb, sd);
			break;
		case U2C_SendChannelModePulseDown:
			u2c_platform_gpio_reset(&sd->gpio);
			u2c_platform_ticker_set(&sd->ticker, sd->pulse_length_us, U2C_FALSE, u2c_fire_channel_pulse_cb, sd);
			break;
		}
	}
	if (channel->fired_cb != NULL)
		channel->fired_cb(channel);
	u2c_platform_signal_thread(DISPATCHER._main_disp_tid);
}

void u2c_set_channel_fire_cb(U2C_CHANNEL* channel, void(*func)(U2C_CHANNEL* me), void* context)
{
	channel->fired_cb = func;
	channel->context = context;
}

void u2c_set_channel_output(U2C_CHANNEL* channel, PinName pin, U2C_SendChannelMode mode, int pulse_length_us)
{
	for (int i = 0; i < U2C_MAX_SEND_DATA; ++i)
	{
		U2C_SENDDATA* sd = &channel->send[i];
		if (sd->pin != NC && sd->pin != pin)
			continue;

		u2c_platform_gpio_init_out(&sd->gpio, pin);
		sd->mode = mode;
		sd->pulse_length_us = pulse_length_us;
		sd->pin = pin;
	}
}

void u2c_disable_channel_outputs(U2C_CHANNEL* channel)
{
	for (int i = 0; i < U2C_MAX_SEND_DATA; ++i)
		channel->send[i].mode = U2C_SendChannelModeNone;
}

void u2c_set_channel_input(U2C_CHANNEL* channel, U2C_PLATFORM_PIN_NAME pin, U2C_PLATFORM_PIN_MODE pull, U2C_ReceiveChannelMode rcmode)
{
	if (channel->recv.mode != U2C_ReceiveChannelModeNone)
		u2c_platform_gpio_free(&channel->recv.gpio);

	channel->recv.mode = rcmode;
	u2c_platform_gpio_init_interrupt(&channel->recv.gpio, pin, pull, _u2c_channel_irq_handler, channel);
	u2c_platform_gpio_interrupt_set(&channel->recv.gpio, rcmode);
}

void u2c_set_state_enter_cb(U2C_STATENODE* state, void(*func)(U2C_STATENODE* me), void* context)
{
	state->state_enter = func;
	state->context = context;
}

void u2c_set_state_leave_cb(U2C_STATENODE* state, void(*func)(U2C_STATENODE* me), void* context)
{
	state->state_leave= func;
	state->context = context;
}

void u2c_transition_execute_cb(U2C_TRANSITION* transition, void(*func)(U2C_TRANSITION* me), void* context)
{
	transition->transition_execute_cb = func;
	transition->context = context;
}

void u2c_set_process_start_cb(U2C_TASK* entry, void(*func)(U2C_TASK* me), void* context)
{
	entry->process_start = func;
	entry->context = context;
}

void u2c_run()
{
	// we need the stack space, this is the only way to get it
	DISPATCHER._main_disp_tid = u2c_platform_get_cur_task_id();
	u2c_platform_ticker_set(&DISPATCHER._ticker, DISPATCHER._clock_multiplier, U2C_TRUE, _u2c_ticker_handler_cb, NULL);
	
	TRACE(("Dispatcher starting all threads.\r\n"));
	for (int i = 0; i < DISPATCHER._cnt_proc; ++i)
	{
		U2C_TASK* task = (U2C_TASK*)U2C_TASK_LIST[i];
		u2c_platform_mutex_init(&task->mutex);
		if (!u2c_platform_thread_create(_u2c_task_main, task, &task->thread_id, &task->thread_def))
		{
			TRACE(("Dispatcher failed initializing thread!\n"));
			return;
		}
	}

	TRACE(("Dispatcher starting.\r\n"));
	for (;;)
	{
		u2c_run_steps();
	}
}

void u2c_run_steps()
{
	u2c_platform_time_t now = u2c_platform_read_usec();
#ifdef DISPATCH_DEBUG
	int tick_before = get_tick();
#endif
	TRACE(("u2c_run_steps(): starting, now=%i.\r\n", now));

	u2c_clear_signals();
	u2c_clear_normal_step();
	u2c_run_tasks(U2C_StateCommited);

	// no commited nodes left, see if we have enough time for a normal loop
	for(;;)
	{
		int tdiff = u2c_platform_diff_now(now);
		if(tdiff >= DISPATCHER._clock_multiplier)
			break;

		u2c_run_tasks(U2C_StateNormal | U2C_StateUrgent);
		u2c_platform_signal_wait_timed(DISPATCHER._clock_multiplier - tdiff);
	}

	u2c_run_tasks(U2C_StateUrgent);

	TRACE(("Dispatcher wait end (diff=%i, tdiff=%i).\r\n", u2c_platform_diff_now(now), get_tick() - tick_before));
}

void u2c_clear_signals()
{
	for (int i = 0; i < TOTAL_CHANNEL_COUNT; ++i)
	{
		U2C_CHANNEL* chn = ALL_CHANNELS[i];
		// XXX am I sure?
		chn->prev_fired = chn->cur_fired;
		chn->cur_fired = U2C_FALSE;
	}
}

void u2c_clear_normal_step()
{
	for (int i = 0; i < DISPATCHER._cnt_proc; ++i)
	{
		U2C_TASK* task = (U2C_TASK*)U2C_TASK_LIST[i];
		u2c_platform_mutex_lock(&task->mutex);
		task->normal_stepped = U2C_FALSE;
		u2c_platform_mutex_unlock(&task->mutex);
	}
}

void u2c_run_tasks(int types)
{
	int prevmode = types;
	for (;;)
	{
		//TRACE(("u2c_run_tasks(): running types=%i loop.\r\n", types));
		U2C_BOOL anyfound = U2C_FALSE;
		U2C_BOOL restartloop = U2C_FALSE;
		const int cnt_proc = DISPATCHER._cnt_proc;
		for (int i = 0; i < cnt_proc; ++i)
		{
			U2C_TASK* task = (U2C_TASK*)U2C_TASK_LIST[i];

			if (!u2c_platform_mutex_trylock(&task->mutex))
			{
				//TRACE(("u2c_run_tasks(): could not lock mutex of to %s\r\n", task->name));
				anyfound = U2C_TRUE;
				continue;
			}

			U2C_STATENODE* current = task->current;
			if (current == NULL)
				continue;
			U2C_STATENODE_DATA* se = (U2C_STATENODE_DATA*)task->current->data;
			if (se == NULL)
				continue;

			if ((types != U2C_StateCommited) && se->mode == U2C_StateCommited)
			{
				// found commited step in middle of urgent/normal loop
				types = U2C_StateCommited;
				restartloop = U2C_TRUE;
				u2c_platform_mutex_unlock(&task->mutex);
				break;
			}

			se = (U2C_STATENODE_DATA*)task->current->data; // prevent race-condition
			if ((se->mode & types) != 0)
			{
				if (se->mode != U2C_StateNormal || !task->normal_stepped)
				{
					// we grabbed the lock, means its not running
					anyfound = U2C_TRUE;
					//TRACE(("u2c_run_tasks(): sending signal to %s\r\n", TASK_LIST[i]->data->name));
					u2c_platform_signal_thread(task->thread_id);
				}
			}
			u2c_platform_mutex_unlock(&task->mutex);
		}
		if (restartloop)
		{
			TRACE(("u2c_run_tasks(): found commited during normal loop, restarting in commited mode.\r\n"));
			continue;
		}

		if (!anyfound)
		{
			if (prevmode != types)
			{
				TRACE(("u2c_run_tasks(): done processing new commited nodes, resuming with normal/urgent\r\n"));
				types = prevmode;
				continue;
			}

			//TRACE(("u2c_run_tasks(                                                                                                                                                                                                                                                                                                                                                                                                                                                             ): did not find any process with types=%i.\r\n", types));
			break;
		}

		//TRACE(("u2c_run_tasks(): waiting\r\n"));
		u2c_platform_signal_wait();

		U2C_BOOL changed = U2C_FALSE;
		for (int i = 0; i < cnt_proc; ++i)
		{
			U2C_TASK* task = (U2C_TASK*)&U2C_TASK_LIST[i];
			if (u2c_platform_mutex_trylock(&task->mutex))
			{
				U2C_STATENODE* current = task->current;
				if (current != NULL
					&& current->data->mode == U2C_StateCommited
					&& task->stepped)
				{
					// we grabbed the lock, means it stopped running
					changed = U2C_TRUE;
				}
				u2c_platform_mutex_unlock(&task->mutex);
			}
			else
			{
				//TRACE(("u2c_run_tasks(): could not lock mutex of %s\n", TASK_LIST[i]->data->name));
				changed = U2C_TRUE; // still running
			}
		}
		if (!changed)
		{
			if (types == U2C_StateCommited)
			{
				TRACE(("u2c_run_steps(): nothing changed in commited loop!.\r\n"));
			}
			else
			{
				//TRACE(("u2c_run_steps(): nothing changed, done with step!.\r\n"));
				return;
			}
		}
	}
}

static void _u2c_task_main(const void* arg_)
{
	U2C_TASK* process = (U2C_TASK*)arg_;
	const U2C_TASK_DATA* pdata = process->data;

	TRACE(("[%s] u2c_task_main_imp(): starting\r\n", process->data->name));
	u2c_platform_mutex_lock(&process->mutex);
	if (process->process_start != NULL)
		process->process_start(process);

	U2C_STATENODE* state = pdata->initstate;
	u2c_enter_state(process, state);
	process->state = U2C_ProcessRunning;
	u2c_platform_mutex_unlock(&process->mutex);
	u2c_platform_signal_thread(DISPATCHER._main_disp_tid);

	for (;;)
	{
		//TRACE(("[%s] u2c_task_main_imp(): waiting for signal.\r\n", process->data->name));
		process->state = U2C_ProcessWaiting;
		u2c_platform_signal_wait();
		process->state = U2C_ProcessRunning;
		//TRACE(("[%s] u2c_task_main_imp(): woken up.\r\n", process->data->name));

		u2c_platform_mutex_lock(&process->mutex);
		//TRACE(("u2c_run_tasks(): locked\r\n"));

		do
		{
			//TRACE(("[%s:%s] u2c_task_main_imp(): current state type is %i.\r\n", process->data->name, process->current->data->name, process->current->data->mode));
			U2C_TRANSITION* transition = u2c_find_valid_transition(process);
			if (transition != NULL)
			{
				u2c_take_transition(process, transition);
			}
			else
			{
				process->stepped = U2C_FALSE;
				//TRACE(("[%s:%s] u2c_task_main_imp(): no transitions found.\r\n", process->data->name, process->current->data->name));
				break;
			}

		} while (process->current->data->mode == U2C_StateCommited);

		//TRACE(("u2c_run_tasks(): unlocking\r\n"));
		u2c_platform_mutex_unlock(&process->mutex);
		u2c_platform_signal_thread(DISPATCHER._main_disp_tid);
	}

}

U2C_TRANSITION* u2c_find_valid_transition(volatile U2C_TASK* process)
{
	U2C_STATENODE* state = process->current;
	U2C_TRANSITION* const* transitions = state->data->transitions;

	if (transitions == NULL)
		return NULL;

	for (int i = 0; transitions[i] != NULL; ++i)
	{
		if (u2c_can_take_transition(transitions[i]))
		{
			return transitions[i];
		}
	}

	return NULL;
}

U2C_BOOL u2c_can_take_transition(U2C_TRANSITION* transition)
{
	if (transition->data->receive != NULL)
	{
		U2C_CHANNEL* channel = transition->data->receive;
		if (!(channel->cur_fired || channel->prev_fired))
 			return U2C_FALSE;
	}
	if (transition->data->guard != NULL)
	{
		u2c_platform_mutex_lock(&DISPATCHER._lock);
		U2C_BOOL res = transition->data->guard();
		u2c_platform_mutex_unlock(&DISPATCHER._lock);
		if (!res)
			return U2C_FALSE;
	}

	return U2C_TRUE;
}

void u2c_take_transition(volatile U2C_TASK* process, U2C_TRANSITION* transition)
{
	if (process->current->data->mode == U2C_StateNormal)
		process->normal_stepped = U2C_TRUE;
	process->stepped = U2C_TRUE;

	TRACE(("[%s:%s!>%s] u2c_take_transition(): before\r\n", process->data->name, process->current->data->name, transition->data->name));
	u2c_leave_state(process, process->current);
		
	if (transition->data->update != NULL)
	{
		u2c_platform_mutex_lock(&DISPATCHER._lock);
		transition->data->update();
		u2c_platform_mutex_unlock(&DISPATCHER._lock);
	}

	if (transition->data->receive != NULL)
	{
		U2C_CHANNEL* channel = transition->data->receive;
		if (!channel->data->broadcast)
			channel->cur_fired = U2C_FALSE;
	}

	if (transition->data->send != NULL)
		u2c_fire_channel(transition->data->send);

	if (transition->transition_execute_cb != NULL)
		transition->transition_execute_cb(transition);
		
	u2c_enter_state(process, transition->data->target);

	TRACE(("[%s:%s!<%s] u2c_take_transition(): after\r\n", process->data->name, process->current->data->name, transition->data->name));
}

void u2c_enter_state(volatile U2C_TASK* process, U2C_STATENODE* state)
{
	process->current = state;
	TRACE(("[%s.>%s] entering_state(): entering\r\n", process->data->name, state->data->name));
	if (state->state_enter != NULL)
		state->state_enter(state);
}

void u2c_leave_state(volatile U2C_TASK* process, U2C_STATENODE* state)
{
	process->current = NULL;
	TRACE(("[%s.<%s] leaving_state(): leaving\r\n", process->data->name, state->data->name));
	if (state->state_leave != NULL)
		state->state_leave(state);
}

#ifdef __cplusplus
}
#endif

