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

#include "uppaal2c.h"

#ifdef __cplusplus
extern "C" {
#endif

// forward declarations
typedef struct U2C_STATENODE_DATA U2C_STATENODE_DATA;
typedef struct U2C_STATENODE U2C_STATENODE;
typedef struct U2C_TRANSITION_DATA U2C_TRANSITION_DATA;
typedef struct U2C_TRANSITION U2C_TRANSITION;
typedef struct U2C_CHANNEL_DATA U2C_CHANNEL_DATA;
typedef struct U2C_CHANNEL U2C_CHANNEL;
typedef struct U2C_TASK_DATA U2C_TASK_DATA;
typedef struct U2C_TASK U2C_TASK;

// transition functions
typedef U2C_BOOL (*func_guard_t)();
typedef void (*func_update_t)();

// debug strings
#ifdef DISPATCH_DEBUG
#define DBG_FIELD(str)	str,
#define DBG_FIELD_DECL(str)	str;
#define DBG_STR(str)	str
#else
#define DBG_FIELD(str)	
#define DBG_FIELD_DECL(str)	
#define DBG_STR(str)	NULL
#endif

// state enums
typedef enum
{
	U2C_ProcessInit, U2C_ProcessRunning, U2C_ProcessWaiting, U2C_ProcessDeadlocked
} U2C_ProcessState;

typedef enum
{
	U2C_StateNormal = 0x1, U2C_StateUrgent = 0x2, U2C_StateCommited = 0x4
} U2C_StateMode;

// channels
struct U2C_CHANNEL_DATA
{
	DBG_FIELD_DECL(const char* name)
	U2C_BOOL urgent;
	U2C_BOOL broadcast;
};

#define U2C_MAX_SEND_DATA 2

typedef struct U2C_SENDDATA
{
	U2C_PLATFORM_PIN_NAME pin;
	U2C_SendChannelMode mode;
	int pulse_length_us;
	U2C_PLATFORM_GPIO gpio;
	int last_write;
	U2C_PLATFORM_TICKER ticker;
} U2C_SENDDATA;

typedef struct U2C_RECVDATA
{
	U2C_ReceiveChannelMode mode;
	U2C_PLATFORM_GPIO gpio;
	U2C_CHANNEL* channel;
} U2C_RECVDATA;

struct U2C_CHANNEL
{
	const U2C_CHANNEL_DATA* data;
	void(*fired_cb)(U2C_CHANNEL* channel);
	void* context;
	U2C_BOOL cur_fired;
	U2C_BOOL prev_fired;

	U2C_PLATFORM_MUTEX mutex;
	U2C_SENDDATA send[U2C_MAX_SEND_DATA];
	U2C_RECVDATA recv;
};

// states
struct U2C_STATENODE_DATA
{
	DBG_FIELD_DECL(const char* name)
		U2C_TRANSITION* const* transitions;
	U2C_StateMode mode;
	func_guard_t guard;
};

struct U2C_STATENODE
{
	const U2C_STATENODE_DATA* data;
	void(*state_enter)(U2C_STATENODE* me);
	void(*state_leave)(U2C_STATENODE* me);
	void* context;
};

// transitions
struct U2C_TRANSITION_DATA
{
	DBG_FIELD_DECL(const char* name)
		U2C_STATENODE* target;
	U2C_CHANNEL *receive;
	U2C_CHANNEL *send;
	func_guard_t	guard;
	func_update_t   update;
};

struct U2C_TRANSITION
{
	const U2C_TRANSITION_DATA* data;
	void(*transition_execute_cb)(U2C_TRANSITION* me);
	void* context;
};

// tasks
struct U2C_TASK_DATA
{
	DBG_FIELD_DECL(const char* name)
	U2C_STATENODE* initstate;
};

struct U2C_TASK
{
	const U2C_TASK_DATA* data;
	void(*process_start)(U2C_TASK* me);
	void* context;
	U2C_STATENODE* current;
	U2C_BOOL stepped;
	U2C_BOOL normal_stepped;
	U2C_ProcessState state;
	U2C_PLATFORM_THREAD_DEF thread_def;
	U2C_PLATFORM_THREAD_ID  thread_id;
	U2C_PLATFORM_MUTEX		mutex;
};


#ifdef __cplusplus
}
#endif

