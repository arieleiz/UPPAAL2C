// VERSION: 2
/*
*  UPPAAAL2C (c) 2014 Ariel Eizenberg - arieleiz@seas.upenn.edu.
*
*    This file is part of UPPAAAL2C. You can redistribute it and/or modify
*    it under the terms of the Academic Free License 3.0
*	  (http://opensource.org/licenses/AFL-3.0).
*
*/
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// public interface in this file

#include "uppaal2c_platform.h"

typedef enum
{
	U2C_SendChannelModeNone, U2C_SendChannelModeSet, U2C_SendChannelModeToggle, U2C_SendChannelModeReset, U2C_SendChannelModePulseUp, U2C_SendChannelModePulseDown
} U2C_SendChannelMode;

typedef enum
{
	U2C_ReceiveChannelModeNone, U2C_ReceiveChannelInterruptRise, U2C_ReceiveChannelInterruptFall
} U2C_ReceiveChannelMode;

typedef struct U2C_CHANNEL U2C_CHANNEL;
typedef struct U2C_STATENODE U2C_STATENODE;
typedef struct U2C_TRANSITION U2C_TRANSITION;
typedef struct U2C_TASK U2C_TASK;
typedef int u2c_clk_t;

// init
void u2c_init();
#ifdef DISPATCH_DEBUG
typedef void (*debug_print_cb_t)(const char* msg);
void u2c_init_debug(debug_print_cb_t cb);
#endif
void u2c_set_clock_multiplier(int multiplier);
void u2c_add_task(U2C_TASK* ps);

// run
void u2c_run();
int u2c_get_tick();

// channels
void u2c_fire_channel(U2C_CHANNEL* channel);
void u2c_set_channel_fire_cb(U2C_CHANNEL* channel, void(*func)(U2C_CHANNEL* me), void* context);
void u2c_set_channel_output(U2C_CHANNEL* channel, U2C_PLATFORM_PIN_NAME pin, U2C_SendChannelMode mode, int pulse_length_us /* = 0 */);
void u2c_disable_channel_outputs(U2C_CHANNEL* channel);
void u2c_set_channel_input(U2C_CHANNEL* channel, U2C_PLATFORM_PIN_NAME pin, U2C_PLATFORM_PIN_MODE mode, U2C_ReceiveChannelMode rcmode);

// states
void u2c_set_state_enter_cb(U2C_STATENODE* state, void(*func)(U2C_STATENODE* me), void* context);
void u2c_set_state_leave_cb(U2C_STATENODE* state, void(*func)(U2C_STATENODE* me), void* context);

// transitions
void u2c_set_transition_execute_cb(U2C_STATENODE* transition, void(*func)(U2C_STATENODE* me), void* context);

// tasks
void u2c_set_process_start_cb(U2C_TASK* entry, void(*func)(U2C_TASK* me), void* context);

#ifdef __cplusplus
}
#endif
