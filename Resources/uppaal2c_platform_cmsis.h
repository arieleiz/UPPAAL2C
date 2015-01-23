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

#include "PinNames.h"
#include "cmsis_os.h"
#include "gpio_api.h"
#include "gpio_irq_api.h"
#include "us_ticker_api.h"

#define MBED_USE_MACROS

// bool
typedef int U2C_BOOL;
#define U2C_TRUE 1
#define U2C_FALSE 0

// trace
#define U2C_TRACE(msg) do { } while(0)

// gpio
typedef enum PinName U2C_PLATFORM_PIN_NAME;
typedef enum PinMode U2C_PLATFORM_PIN_MODE;
typedef struct {
	gpio_t gpio;
	gpio_irq_t gpio_irq;
} U2C_PLATFORM_GPIO;

#define U2C_GPIO_IRQ_HANDLER_PARAM_DECL uint32_t _u2c_id, gpio_irq_event _u2c_evt
#define U2C_GPIO_IRQ_HANDLER_PARAM_CTX ((void*)_u2c_id)
#define U2C_GPIO_IRQ_HANDLER_PARAM_EVTMODE _u2c_evt

typedef void(*u2c_gpio_irq_handler_cb_t)(U2C_GPIO_IRQ_HANDLER_PARAM_DECL);

#define u2c_platform_gpio_clear(gpioptr) memset((gpioptr), 0, sizeof(U2C_PLATFORM_GPIO))
void u2c_platform_gpio_init_in(U2C_PLATFORM_GPIO* gpioptr, U2C_PLATFORM_PIN_NAME pin, U2C_PLATFORM_PIN_MODE mode);
void u2c_platform_gpio_init_interrupt(U2C_PLATFORM_GPIO* gpioptr, U2C_PLATFORM_PIN_NAME pin, U2C_PLATFORM_PIN_MODE mode,
	u2c_gpio_irq_handler_cb_t cb, void* ctx);
void u2c_platform_gpio_interrupt_set(U2C_PLATFORM_GPIO* gpioptr, U2C_ReceiveChannelMode rcmode);
#define u2c_platform_gpio_init_out(gpioptr, pin) gpio_init_out(&(gpioptr)->gpio, pin)
#define u2c_platform_gpio_free(gpioptr) gpio_irq_free(&(gpioptr)->gpio_irq)
#define u2c_platform_gpio_set(gpioptr) gpio_write(&(gpioptr)->gpio, 1)
#define u2c_platform_gpio_reset(gpioptr) gpio_write(&(gpioptr)->gpio, 0)
#define u2c_platform_is_interrupt_mode(mode, evtmode) \
				( (((mode) == U2C_ReceiveChannelInterruptRise) && ((evtmode) == IRQ_RISE))  \
                  || (((mode) == U2C_ReceiveChannelInterruptFall) && ((evtmode) == IRQ_FALL)))

// mutex
typedef struct {
	osMutexId _osMutexId;
	osMutexDef_t _osMutexDef;
} U2C_PLATFORM_MUTEX;

U2C_BOOL u2c_platform_mutex_init(U2C_PLATFORM_MUTEX* mutex);

#ifdef MBED_USE_MACROS
#define u2c_platform_mutex_lock(mutex) (osMutexWait((mutex)->_osMutexId, osWaitForever) == osOK)
#define u2c_platform_mutex_lock_timed(mutex, millisec) (osMutexWait((mutex)->_osMutexId, millisec) == osOK)
#define u2c_platform_mutex_trylock(mutex) (osMutexWait((mutex)->_osMutexId, 0) == osOK)
#define u2c_platform_mutex_unlock(mutex) (osMutexRelease((mutex)->_osMutexId) == osOK)
#else
U2C_BOOL u2c_platform_mutex_lock(U2C_PLATFORM_MUTEX* mutex);
U2C_BOOL u2c_platform_mutex_lock_timed(U2C_PLATFORM_MUTEX* mutex, uint32_t millisec);
U2C_BOOL u2c_platform_mutex_trylock(U2C_PLATFORM_MUTEX* mutex);
U2C_BOOL u2c_platform_mutex_unlock(U2C_PLATFORM_MUTEX* mutex);
#endif
void u2c_platform_mutex_destroy(U2C_PLATFORM_MUTEX* mutex);

// time
typedef uint32_t u2c_platform_time_t;

#ifdef MBED_USE_MACROS
#define u2c_platform_read_usec() us_ticker_read()
//#define u2c_platform_diff_usec(timecur, timeprev) (((timecur) >= (timeprev)) ? ((timecur) - (timeprev)) : ((0x7fffffff - (timecur)) + (timeprev))
#define u2c_platform_diff_usec(timecur, timeprev) ((timecur) - (timeprev))
#define u2c_platform_diff_now(timeprev) u2c_platform_diff_usec(u2c_platform_read_usec(), (timeprev))
#else
u2c_platform_time_t u2c_platform_read_usec();
u2c_platform_time_t u2c_platform_diff_usec(u2c_platform_time_t timecur, u2c_platform_time_t timeprev);
u2c_platform_time_t u2c_platform_diff_now(int timeprev);
#endif

// ticker
typedef void(*u2c_platform_ticker_cb_t)(void* context);

typedef struct 
{
	u2c_platform_ticker_cb_t cb;
	void* context;
	ticker_event_t evt;
	u2c_platform_time_t interval;
} U2C_PLATFORM_TICKER;

void u2c_platform_ticker_set(U2C_PLATFORM_TICKER* ticker, u2c_platform_time_t interval, U2C_BOOL repeat, u2c_platform_ticker_cb_t cb, void* cb_context);

// thread
typedef osThreadId		U2C_PLATFORM_THREAD_ID;
typedef osThreadDef_t   U2C_PLATFORM_THREAD_DEF;

#define __MBED_U2C_PLATFORM_SIGNAL_ID 1

#ifdef MBED_USE_MACROS
#define u2c_platform_get_cur_task_id() osThreadGetId()
#define u2c_platform_signal_thread(tid) osSignalSet((tid), __MBED_U2C_PLATFORM_SIGNAL_ID)
#define u2c_platform_signal_wait() osSignalWait(__MBED_U2C_PLATFORM_SIGNAL_ID, osWaitForever)
#define u2c_platform_signal_wait_timed(usec) osSignalWait(__MBED_U2C_PLATFORM_SIGNAL_ID, ((usec) / 1000))
#else
U2C_PLATFORM_THREAD_ID u2c_platform_get_cur_task_id();
void u2c_platform_signal_thread(U2C_PLATFORM_THREAD_ID tid);
void u2c_platform_signal_wait(void);
void u2c_platform_signal_wait_timed(int usec);
#endif

typedef void(*u2c_thread_entry_cb_t)(void* ctx);

U2C_BOOL u2c_platform_thread_create(u2c_thread_entry_cb_t entry, void* ctx, U2C_PLATFORM_THREAD_ID* out_id, U2C_PLATFORM_THREAD_DEF* out_def);

#ifdef __cplusplus
}
#endif

