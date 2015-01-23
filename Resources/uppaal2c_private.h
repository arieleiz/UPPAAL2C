// VERSION: 1
/*
*  UPPAAAL2C (c) 2014 Ariel Eizenberg - arieleiz@seas.upenn.edu.
*
*    This file is part of UPPAAAL2C. You can redistribute it and/or modify
*    it under the terms of the Academic Free License 3.0
*	  (http://opensource.org/licenses/AFL-3.0).
*
*/
#pragma once

#include <stdlib.h> // for NULL
#include "uppaal2c_platform.h"
#include "uppaal2c_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// clocks
#define _U2C_GET_TICK() DISPATCHER._tick

#define _U2C_INIT_CLK(clk)			do { clk = _U2C_GET_TICK(); } while(0)
#define _U2C_GET_CLK(clk)			(_U2C_GET_TICK() - (clk))
#define _U2C_SET_CLK(clk, value)	do { clk = _U2C_GET_TICK() - value; } while(0)

typedef struct {
	int					   _cnt_proc;
	U2C_PLATFORM_MUTEX     _lock;
	U2C_PLATFORM_TICKER    _ticker;
	U2C_PLATFORM_THREAD_ID _main_disp_tid;

	int						_clock_multiplier;
	int						_tick;
} U2C_DISPATCHER_STATE;

extern U2C_DISPATCHER_STATE DISPATCHER;

#ifdef __cplusplus
}
#endif

