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

#ifdef __cplusplus
extern "C" {
#endif

#ifdef C_INLINE_SUPPORTED
#define U2C_INLINE inline
#else
#define U2C_INLINE 
#endif

typedef enum U2C_SendChannelMode U2C_SendChannelMode;
typedef enum U2C_ReceiveChannelMode U2C_ReceiveChannelMode;

#ifdef __MBED__
#include "uppaal2c_platform_cmsis.h"
#endif

#ifdef __cplusplus
}
#endif

