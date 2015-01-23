// VERSION: 1
#include "uppaal2c_platform.h"
#include "uppaal2c.h"
#include <cmsis_os.h>

void u2c_platform_gpio_init_in(U2C_PLATFORM_GPIO* gpioptr, U2C_PLATFORM_PIN_NAME pin, U2C_PLATFORM_PIN_MODE mode) 
{ 
	gpio_init_in(&gpioptr->gpio, pin); 
	gpio_mode(&gpioptr->gpio, mode);
}

void u2c_platform_gpio_init_interrupt(U2C_PLATFORM_GPIO* gpioptr, U2C_PLATFORM_PIN_NAME pin, U2C_PLATFORM_PIN_MODE mode,
				u2c_gpio_irq_handler_cb_t cb, void* ctx)
{
	gpio_init_in(&(gpioptr)->gpio, pin);
	gpio_mode(&(gpioptr)->gpio, mode); 
	gpio_irq_init(&(gpioptr)->gpio_irq, pin, cb, (uint32_t)ctx); 
} 

void u2c_platform_gpio_interrupt_set(U2C_PLATFORM_GPIO* gpioptr, U2C_ReceiveChannelMode rcmode)
{
	gpio_irq_event evt = IRQ_NONE;
	switch (rcmode)
	{
	case U2C_ReceiveChannelInterruptRise:
		evt = IRQ_RISE;
		break;

	case U2C_ReceiveChannelInterruptFall:
		evt = IRQ_FALL;
		break;

	case U2C_ReceiveChannelModeNone:
		break;
	}

	if (evt != IRQ_NONE)
	{
		gpio_irq_set(&gpioptr->gpio_irq, evt, 1);
		gpio_irq_enable(&gpioptr->gpio_irq);
	}
}

U2C_BOOL u2c_platform_mutex_init(U2C_PLATFORM_MUTEX* mutex)
{
	mutex->_osMutexId = osMutexCreate(&mutex->_osMutexDef);
	return (mutex->_osMutexId != NULL);
}

#ifndef MBED_USE_MACROS
U2C_BOOL u2c_platform_mutex_lock(U2C_PLATFORM_MUTEX* mutex);
{
	return osMutexWait(mutex->_osMutexId, osWaitForever) == osOK;
}

U2C_BOOL u2c_platform_mutex_lock_timed(U2C_PLATFORM_MUTEX* mutex, uint32_t millisec);
{
	return osMutexWait(mutex->_osMutexId, millisec) == osOK;
}

U2C_BOOL u2c_platform_mutex_trylock(U2C_PLATFORM_MUTEX* mutex) {
	return (osMutexWait(mutex->_osMutexId, 0) == osOK);
}

U2C_BOOL u2c_platform_mutex_unlock(U2C_PLATFORM_MUTEX* mutex) {
	return osMutexRelease(mutex->_osMutexId) == osOK;
}
#endif

void u2c_platform_mutex_destroy(U2C_PLATFORM_MUTEX* mutex) {
	osMutexDelete(mutex->_osMutexId);
}

// time
#ifndef MBED_USE_MACROS
u2c_platform_time_t u2c_platform_read_usec()
{
	return us_ticker_read();
}

u2c_platform_time_t u2c_platform_diff_usec(u2c_platform_time_t timecur, u2c_platform_time_t timeprev)
{
	if (timecur >= timeprev)
		return timecur - timeprev;
	else
		return (0x7fffffff - timecur) + timeprev;
}

u2c_platform_time_t U2C_INLINE u2c_platform_diff_now(int timeprev)
{
	return u2c_platform_diff_usec(u2c_platform_read_usec(), timeprev);
}
#endif

// ticker
static void _u2c_platform_ticker_irq(uint32_t id)
{
	U2C_PLATFORM_TICKER* data = (U2C_PLATFORM_TICKER*)id;
	if (data->interval > 0)
	{
		us_ticker_insert_event(&data->evt, data->evt.timestamp + data->interval, (uint32_t)data);
	}
	data->cb(data->context);
}

void u2c_platform_ticker_set(U2C_PLATFORM_TICKER* data, u2c_platform_time_t interval, U2C_BOOL repeat, u2c_platform_ticker_cb_t cb, void* cb_context)
{
	static U2C_BOOL handler_set = U2C_FALSE;
		
	if (!handler_set)
	{
		us_ticker_set_handler(_u2c_platform_ticker_irq);
		handler_set = U2C_TRUE;
	}
	data->interval = (repeat > 0) ? interval : 0;
	data->evt.id = 0;
	data->evt.timestamp = 0;
	data->cb = cb;
	data->context = cb_context;

	us_ticker_insert_event(&data->evt, us_ticker_read() + interval, (uint32_t)data);
}

#ifndef MBED_USE_MACROS
U2C_PLATFORM_THREAD_ID u2c_platform_get_cur_task_id()
{
	return osThreadGetId();
}

void u2c_platform_signal_thread(U2C_PLATFORM_THREAD_ID tid)
{
	osSignalSet((tid), __MBED_U2C_PLATFORM_SIGNAL_ID);
}

void u2c_platform_signal_wait(void)
{
	osSignalWait(__MBED_U2C_PLATFORM_SIGNAL_ID, osWaitForever);
}

void u2c_platform_signal_wait_timed(int usec)
{
	osSignalWait(__MBED_U2C_PLATFORM_SIGNAL_ID, ((usec) / 1000);
}

#endif

U2C_BOOL u2c_platform_thread_create(u2c_thread_entry_cb_t entry, void* ctx, U2C_PLATFORM_THREAD_ID* out_id, U2C_PLATFORM_THREAD_DEF* out_def)
{
	out_def->pthread = (os_pthread)entry;
	out_def->tpriority = osPriorityNormal;
	out_def->stacksize = DEFAULT_STACK_SIZE;
	out_def->stack_pointer = (unsigned char*)malloc(DEFAULT_STACK_SIZE);
	if (out_def->stack_pointer == NULL)
		return U2C_FALSE;
	
	*out_id = osThreadCreate(out_def, ctx);
	return (*out_id) != NULL;
}


