#include "uppaal2c.h"
#include "model.h"

static void init_tasks();
static void init_inputs();
static void init_outputs();
static void init_callbacks();

int main (void)
{
	u2c_init();
	u2c_set_clock_multiplier(1000 /*us*/);

	init_inputs();
	init_outputs();
	init_callbacks();
	init_tasks();
	u2c_run();

}

static void init_tasks()
{
	u2c_add_task(&HM_ModeSwitch_TASK);
	u2c_add_task(&HM_Asignal_TASK);
	u2c_add_task(&HM_Apace_TASK);
	u2c_add_task(&HM_Vsignal_TASK);
	u2c_add_task(&HM_Vpace_TASK);
	u2c_add_task(&HM_Leds_Apace_TASK);
	u2c_add_task(&HM_Leds_Asignal_TASK);
	u2c_add_task(&HM_Leds_Vpace_TASK);
	u2c_add_task(&HM_Leds_Vsignal_TASK);
	u2c_add_task(&HM_DisplayAndAlarm_TASK);
	u2c_add_task(&PM_ModeSwitch_TASK);
	u2c_add_task(&PM_Sensor_A_TASK);
	u2c_add_task(&PM_Sensor_V_TASK);
	u2c_add_task(&PM_Pacer_AA_TASK);
	u2c_add_task(&PM_Leds_Apace_TASK);
	u2c_add_task(&PM_Leds_Asense_TASK);
	u2c_add_task(&PM_Leds_Vpace_TASK);
	u2c_add_task(&PM_Leds_Vsense_TASK);
	u2c_add_task(&PM_DisplayAndAlarm_TASK);
	u2c_add_task(&Tester_HM_Random_TASK);
	u2c_add_task(&Tester_HM_Predefined1_TASK);
	u2c_add_task(&Tester_HM_Predefined2_TASK);
	u2c_add_task(&Tester_HM_Predefined3_TASK);
	u2c_add_task(&Tester_HM_HeIsDeadJim_TASK);
	u2c_add_task(&Observer_PS_TASK);
	u2c_add_task(&Observer_LRI_TASK);
	u2c_add_task(&Observer_URI_TASK);
	u2c_add_task(&Observer_VRP_TASK);
	u2c_add_task(&Observer_AV_TASK);
}

static void init_inputs()
{
	// uncomment and edit required hardware inputs
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_Apace, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_Asense, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_Asignal, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_HMmodechange, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_PMmodechange, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_testHM_gen_0, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_testHM_gen_1, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_testHM_manual, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_testHM_random, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_testHM_test, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_testPM_gen_0, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_testPM_gen_1, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_testPM_manual, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_testPM_normal, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_testPM_sleep, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_testPM_sports, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_Vpace, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_Vsense, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_Vsignal, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
}

static void init_outputs()
{
	// uncomment and edit required hardware outputs
	//u2c_set_channel_output(GLOBAL_CHANNEL_VAR_AlarmH, /*fill pin here*/, /*U2C_SendChannelMode...*/, 0 /* or pulse time */);
	//u2c_set_channel_output(GLOBAL_CHANNEL_VAR_AlarmL, /*fill pin here*/, /*U2C_SendChannelMode...*/, 0 /* or pulse time */);
	//u2c_set_channel_output(GLOBAL_CHANNEL_VAR_Apace, /*fill pin here*/, /*U2C_SendChannelMode...*/, 0 /* or pulse time */);
	//u2c_set_channel_output(GLOBAL_CHANNEL_VAR_Asense, /*fill pin here*/, /*U2C_SendChannelMode...*/, 0 /* or pulse time */);
	//u2c_set_channel_output(GLOBAL_CHANNEL_VAR_Asignal, /*fill pin here*/, /*U2C_SendChannelMode...*/, 0 /* or pulse time */);
	//u2c_set_channel_output(GLOBAL_CHANNEL_VAR_HMmodechange, /*fill pin here*/, /*U2C_SendChannelMode...*/, 0 /* or pulse time */);
	//u2c_set_channel_output(GLOBAL_CHANNEL_VAR_NoAlarm, /*fill pin here*/, /*U2C_SendChannelMode...*/, 0 /* or pulse time */);
	//u2c_set_channel_output(GLOBAL_CHANNEL_VAR_PMmodechange, /*fill pin here*/, /*U2C_SendChannelMode...*/, 0 /* or pulse time */);
	//u2c_set_channel_output(GLOBAL_CHANNEL_VAR_testHM_random, /*fill pin here*/, /*U2C_SendChannelMode...*/, 0 /* or pulse time */);
	//u2c_set_channel_output(GLOBAL_CHANNEL_VAR_testHM_test, /*fill pin here*/, /*U2C_SendChannelMode...*/, 0 /* or pulse time */);
	//u2c_set_channel_output(GLOBAL_CHANNEL_VAR_Vpace, /*fill pin here*/, /*U2C_SendChannelMode...*/, 0 /* or pulse time */);
	//u2c_set_channel_output(GLOBAL_CHANNEL_VAR_Vsense, /*fill pin here*/, /*U2C_SendChannelMode...*/, 0 /* or pulse time */);
	//u2c_set_channel_output(GLOBAL_CHANNEL_VAR_Vsignal, /*fill pin here*/, /*U2C_SendChannelMode...*/, 0 /* or pulse time */);
}

static void init_callbacks()
{
	// --- HM_ModeSwitch ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&HM_ModeSwitch_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&HM_ModeSwitch_STATE_Unnamed0, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_ModeSwitch_STATE_Unnamed0, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&HM_ModeSwitch_STATE_Unnamed1, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_ModeSwitch_STATE_Unnamed1, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&HM_ModeSwitch_STATE_Unnamed2, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_ModeSwitch_STATE_Unnamed2, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&HM_ModeSwitch_STATE_Unnamed3, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_ModeSwitch_STATE_Unnamed3, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&HM_ModeSwitch_STATE_Manual, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_ModeSwitch_STATE_Manual, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&HM_ModeSwitch_STATE_Init, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_ModeSwitch_STATE_Init, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&HM_ModeSwitch_TRANS_Unnamed0__Manual__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_ModeSwitch_TRANS_Unnamed1__Init__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_ModeSwitch_TRANS_Unnamed2__Manual__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_ModeSwitch_TRANS_Manual__Unnamed2__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_ModeSwitch_TRANS_Unnamed3__Manual__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_ModeSwitch_TRANS_Manual__Unnamed3__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_ModeSwitch_TRANS_Manual__Unnamed1__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_ModeSwitch_TRANS_Manual__Unnamed1__1, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_ModeSwitch_TRANS_Init__Unnamed1__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_ModeSwitch_TRANS_Init__Unnamed1__1, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_ModeSwitch_TRANS_Init__Unnamed0__0, /*function*/, /*ctx*/);
	// --- HM_Asignal ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&HM_Asignal_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&HM_Asignal_STATE_Disabled, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_Asignal_STATE_Disabled, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&HM_Asignal_STATE_RHM, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_Asignal_STATE_RHM, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&HM_Asignal_TRANS_Disabled__RHM__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_Asignal_TRANS_RHM__Disabled__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_Asignal_TRANS_RHM__RHM__0, /*function*/, /*ctx*/);
	// --- HM_Apace ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&HM_Apace_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&HM_Apace_STATE_AIdle, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_Apace_STATE_AIdle, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&HM_Apace_TRANS_AIdle__AIdle__0, /*function*/, /*ctx*/);
	// --- HM_Vsignal ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&HM_Vsignal_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&HM_Vsignal_STATE_Disabled, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_Vsignal_STATE_Disabled, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&HM_Vsignal_STATE_RHM, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_Vsignal_STATE_RHM, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&HM_Vsignal_TRANS_RHM__Disabled__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_Vsignal_TRANS_Disabled__RHM__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_Vsignal_TRANS_RHM__RHM__0, /*function*/, /*ctx*/);
	// --- HM_Vpace ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&HM_Vpace_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&HM_Vpace_STATE_VIdle, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_Vpace_STATE_VIdle, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&HM_Vpace_TRANS_VIdle__VIdle__0, /*function*/, /*ctx*/);
	// --- HM_Leds_Apace ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&HM_Leds_Apace_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&HM_Leds_Apace_STATE_On, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_Leds_Apace_STATE_On, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&HM_Leds_Apace_STATE_Off, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_Leds_Apace_STATE_Off, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&HM_Leds_Apace_TRANS_On__Off__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_Leds_Apace_TRANS_Off__On__0, /*function*/, /*ctx*/);
	// --- HM_Leds_Asignal ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&HM_Leds_Asignal_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&HM_Leds_Asignal_STATE_On, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_Leds_Asignal_STATE_On, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&HM_Leds_Asignal_STATE_Off, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_Leds_Asignal_STATE_Off, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&HM_Leds_Asignal_TRANS_On__Off__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_Leds_Asignal_TRANS_Off__On__0, /*function*/, /*ctx*/);
	// --- HM_Leds_Vpace ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&HM_Leds_Vpace_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&HM_Leds_Vpace_STATE_On, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_Leds_Vpace_STATE_On, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&HM_Leds_Vpace_STATE_Off, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_Leds_Vpace_STATE_Off, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&HM_Leds_Vpace_TRANS_On__Off__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_Leds_Vpace_TRANS_Off__On__0, /*function*/, /*ctx*/);
	// --- HM_Leds_Vsignal ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&HM_Leds_Vsignal_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&HM_Leds_Vsignal_STATE_On, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_Leds_Vsignal_STATE_On, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&HM_Leds_Vsignal_STATE_Off, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_Leds_Vsignal_STATE_Off, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&HM_Leds_Vsignal_TRANS_On__Off__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_Leds_Vsignal_TRANS_Off__On__0, /*function*/, /*ctx*/);
	// --- HM_DisplayAndAlarm ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&HM_DisplayAndAlarm_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&HM_DisplayAndAlarm_STATE_ShowRate, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_DisplayAndAlarm_STATE_ShowRate, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&HM_DisplayAndAlarm_STATE_Incr, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_DisplayAndAlarm_STATE_Incr, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&HM_DisplayAndAlarm_STATE_Init, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&HM_DisplayAndAlarm_STATE_Init, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&HM_DisplayAndAlarm_TRANS_ShowRate__Init__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_DisplayAndAlarm_TRANS_ShowRate__Init__1, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_DisplayAndAlarm_TRANS_ShowRate__Init__2, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_DisplayAndAlarm_TRANS_ShowRate__Init__3, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_DisplayAndAlarm_TRANS_Init__ShowRate__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_DisplayAndAlarm_TRANS_Incr__Init__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_DisplayAndAlarm_TRANS_Init__Incr__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&HM_DisplayAndAlarm_TRANS_Init__Incr__1, /*function*/, /*ctx*/);
	// --- PM_ModeSwitch ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&PM_ModeSwitch_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&PM_ModeSwitch_STATE_Unnamed4, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_ModeSwitch_STATE_Unnamed4, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_ModeSwitch_STATE_Unnamed5, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_ModeSwitch_STATE_Unnamed5, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_ModeSwitch_STATE_Unnamed6, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_ModeSwitch_STATE_Unnamed6, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_ModeSwitch_STATE_Unnamed7, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_ModeSwitch_STATE_Unnamed7, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_ModeSwitch_STATE_Unnamed8, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_ModeSwitch_STATE_Unnamed8, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_ModeSwitch_STATE_Unnamed9, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_ModeSwitch_STATE_Unnamed9, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_ModeSwitch_STATE_Unnamed10, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_ModeSwitch_STATE_Unnamed10, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_ModeSwitch_STATE_Manual, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_ModeSwitch_STATE_Manual, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_ModeSwitch_STATE_Init, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_ModeSwitch_STATE_Init, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&PM_ModeSwitch_TRANS_Init__Unnamed6__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_ModeSwitch_TRANS_Init__Unnamed5__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_ModeSwitch_TRANS_Init__Unnamed4__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_ModeSwitch_TRANS_Manual__Unnamed4__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_ModeSwitch_TRANS_Unnamed4__Unnamed8__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_ModeSwitch_TRANS_Unnamed7__Manual__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_ModeSwitch_TRANS_Unnamed8__Init__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_ModeSwitch_TRANS_Unnamed9__Manual__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_ModeSwitch_TRANS_Manual__Unnamed9__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_ModeSwitch_TRANS_Unnamed10__Manual__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_ModeSwitch_TRANS_Manual__Unnamed10__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_ModeSwitch_TRANS_Manual__Unnamed5__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_ModeSwitch_TRANS_Manual__Unnamed6__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_ModeSwitch_TRANS_Unnamed5__Unnamed8__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_ModeSwitch_TRANS_Unnamed6__Unnamed8__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_ModeSwitch_TRANS_Init__Unnamed7__0, /*function*/, /*ctx*/);
	// --- PM_Sensor_A ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&PM_Sensor_A_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&PM_Sensor_A_STATE_Aevent, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Sensor_A_STATE_Aevent, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Sensor_A_STATE_Wait_URI, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Sensor_A_STATE_Wait_URI, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Sensor_A_STATE_Wait_PVARP, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Sensor_A_STATE_Wait_PVARP, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Sensor_A_STATE_VEvent, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Sensor_A_STATE_VEvent, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Sensor_A_STATE_WaitAVI, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Sensor_A_STATE_WaitAVI, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Sensor_A_STATE_ResetClk, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Sensor_A_STATE_ResetClk, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Sensor_A_STATE_Await, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Sensor_A_STATE_Await, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&PM_Sensor_A_TRANS_Aevent__ResetClk__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_A_TRANS_Await__Aevent__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_A_TRANS_Wait_URI__Await__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_A_TRANS_Wait_PVARP__Wait_URI__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_A_TRANS_VEvent__Wait_PVARP__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_A_TRANS_WaitAVI__VEvent__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_A_TRANS_WaitAVI__VEvent__1, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_A_TRANS_ResetClk__WaitAVI__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_A_TRANS_Await__ResetClk__0, /*function*/, /*ctx*/);
	// --- PM_Sensor_V ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&PM_Sensor_V_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&PM_Sensor_V_STATE_PVC, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Sensor_V_STATE_PVC, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Sensor_V_STATE_Unnamed11, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Sensor_V_STATE_Unnamed11, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Sensor_V_STATE_DoneVRP, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Sensor_V_STATE_DoneVRP, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Sensor_V_STATE_WaitVRP, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Sensor_V_STATE_WaitVRP, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Sensor_V_STATE_VEvent, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Sensor_V_STATE_VEvent, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Sensor_V_STATE_WaitVEvent, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Sensor_V_STATE_WaitVEvent, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Sensor_V_STATE_Wait_PVAB, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Sensor_V_STATE_Wait_PVAB, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Sensor_V_STATE_Init_PVAB, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Sensor_V_STATE_Init_PVAB, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Sensor_V_STATE_Init, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Sensor_V_STATE_Init, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&PM_Sensor_V_TRANS_PVC__Init__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_V_TRANS_Init__PVC__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_V_TRANS_Unnamed11__VEvent__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_V_TRANS_WaitVEvent__Unnamed11__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_V_TRANS_DoneVRP__Init__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_V_TRANS_WaitVRP__DoneVRP__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_V_TRANS_VEvent__WaitVRP__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_V_TRANS_WaitVEvent__VEvent__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_V_TRANS_Wait_PVAB__WaitVEvent__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_V_TRANS_Init_PVAB__Wait_PVAB__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_V_TRANS_Init__Init_PVAB__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Sensor_V_TRANS_Init__Init_PVAB__1, /*function*/, /*ctx*/);
	// --- PM_Pacer_AA ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&PM_Pacer_AA_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&PM_Pacer_AA_STATE_PaceV, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Pacer_AA_STATE_PaceV, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Pacer_AA_STATE_PMManualMode, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Pacer_AA_STATE_PMManualMode, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Pacer_AA_STATE_Adone, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Pacer_AA_STATE_Adone, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Pacer_AA_STATE_PVC, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Pacer_AA_STATE_PVC, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Pacer_AA_STATE_PaceA, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Pacer_AA_STATE_PaceA, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Pacer_AA_STATE_Vevent, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Pacer_AA_STATE_Vevent, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Pacer_AA_STATE_AVI_Wait, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Pacer_AA_STATE_AVI_Wait, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&PM_Pacer_AA_TRANS_PaceV__Vevent__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Pacer_AA_TRANS_Adone__PMManualMode__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Pacer_AA_TRANS_PaceA__PMManualMode__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Pacer_AA_TRANS_PVC__PMManualMode__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Pacer_AA_TRANS_Vevent__PMManualMode__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Pacer_AA_TRANS_AVI_Wait__PMManualMode__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Pacer_AA_TRANS_PMManualMode__AVI_Wait__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Pacer_AA_TRANS_PVC__Adone__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Pacer_AA_TRANS_PaceA__Adone__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Pacer_AA_TRANS_Adone__AVI_Wait__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Pacer_AA_TRANS_Vevent__Adone__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Pacer_AA_TRANS_PVC__PaceA__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Pacer_AA_TRANS_Vevent__PVC__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Pacer_AA_TRANS_Vevent__PaceA__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Pacer_AA_TRANS_AVI_Wait__Vevent__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Pacer_AA_TRANS_AVI_Wait__PaceV__0, /*function*/, /*ctx*/);
	// --- PM_Leds_Apace ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&PM_Leds_Apace_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&PM_Leds_Apace_STATE_On, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Leds_Apace_STATE_On, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Leds_Apace_STATE_Off, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Leds_Apace_STATE_Off, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&PM_Leds_Apace_TRANS_On__Off__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Leds_Apace_TRANS_Off__On__0, /*function*/, /*ctx*/);
	// --- PM_Leds_Asense ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&PM_Leds_Asense_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&PM_Leds_Asense_STATE_On, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Leds_Asense_STATE_On, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Leds_Asense_STATE_Off, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Leds_Asense_STATE_Off, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&PM_Leds_Asense_TRANS_On__Off__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Leds_Asense_TRANS_Off__On__0, /*function*/, /*ctx*/);
	// --- PM_Leds_Vpace ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&PM_Leds_Vpace_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&PM_Leds_Vpace_STATE_On, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Leds_Vpace_STATE_On, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Leds_Vpace_STATE_Off, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Leds_Vpace_STATE_Off, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&PM_Leds_Vpace_TRANS_On__Off__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Leds_Vpace_TRANS_Off__On__0, /*function*/, /*ctx*/);
	// --- PM_Leds_Vsense ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&PM_Leds_Vsense_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&PM_Leds_Vsense_STATE_On, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Leds_Vsense_STATE_On, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_Leds_Vsense_STATE_Off, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_Leds_Vsense_STATE_Off, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&PM_Leds_Vsense_TRANS_On__Off__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_Leds_Vsense_TRANS_Off__On__0, /*function*/, /*ctx*/);
	// --- PM_DisplayAndAlarm ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&PM_DisplayAndAlarm_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&PM_DisplayAndAlarm_STATE_ShowRate, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_DisplayAndAlarm_STATE_ShowRate, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_DisplayAndAlarm_STATE_Incr, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_DisplayAndAlarm_STATE_Incr, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&PM_DisplayAndAlarm_STATE_Init, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&PM_DisplayAndAlarm_STATE_Init, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&PM_DisplayAndAlarm_TRANS_ShowRate__Init__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_DisplayAndAlarm_TRANS_ShowRate__Init__1, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_DisplayAndAlarm_TRANS_ShowRate__Init__2, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_DisplayAndAlarm_TRANS_ShowRate__Init__3, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_DisplayAndAlarm_TRANS_Init__ShowRate__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_DisplayAndAlarm_TRANS_Incr__Init__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_DisplayAndAlarm_TRANS_Init__Incr__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&PM_DisplayAndAlarm_TRANS_Init__Incr__1, /*function*/, /*ctx*/);
	// --- Tester_HM_Random ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&Tester_HM_Random_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&Tester_HM_Random_STATE_Unnamed12, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Tester_HM_Random_STATE_Unnamed12, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Tester_HM_Random_STATE_Unnamed13, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Tester_HM_Random_STATE_Unnamed13, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&Tester_HM_Random_TRANS_Unnamed13__Unnamed12__0, /*function*/, /*ctx*/);
	// --- Tester_HM_Predefined1 ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&Tester_HM_Predefined1_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&Tester_HM_Predefined1_STATE_VAdelay, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Tester_HM_Predefined1_STATE_VAdelay, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Tester_HM_Predefined1_STATE_AVdelay, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Tester_HM_Predefined1_STATE_AVdelay, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Tester_HM_Predefined1_STATE_GenA, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Tester_HM_Predefined1_STATE_GenA, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Tester_HM_Predefined1_STATE_Unnamed17, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Tester_HM_Predefined1_STATE_Unnamed17, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&Tester_HM_Predefined1_TRANS_VAdelay__GenA__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Tester_HM_Predefined1_TRANS_AVdelay__VAdelay__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Tester_HM_Predefined1_TRANS_GenA__AVdelay__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Tester_HM_Predefined1_TRANS_Unnamed17__GenA__0, /*function*/, /*ctx*/);
	// --- Tester_HM_Predefined2 ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&Tester_HM_Predefined2_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&Tester_HM_Predefined2_STATE_VAdelay, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Tester_HM_Predefined2_STATE_VAdelay, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Tester_HM_Predefined2_STATE_AVdelay, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Tester_HM_Predefined2_STATE_AVdelay, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Tester_HM_Predefined2_STATE_GenA, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Tester_HM_Predefined2_STATE_GenA, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Tester_HM_Predefined2_STATE_Unnamed18, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Tester_HM_Predefined2_STATE_Unnamed18, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&Tester_HM_Predefined2_TRANS_VAdelay__GenA__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Tester_HM_Predefined2_TRANS_AVdelay__VAdelay__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Tester_HM_Predefined2_TRANS_GenA__AVdelay__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Tester_HM_Predefined2_TRANS_Unnamed18__GenA__0, /*function*/, /*ctx*/);
	// --- Tester_HM_Predefined3 ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&Tester_HM_Predefined3_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&Tester_HM_Predefined3_STATE_VAdelay, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Tester_HM_Predefined3_STATE_VAdelay, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Tester_HM_Predefined3_STATE_AVdelay, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Tester_HM_Predefined3_STATE_AVdelay, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Tester_HM_Predefined3_STATE_GenA, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Tester_HM_Predefined3_STATE_GenA, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Tester_HM_Predefined3_STATE_Unnamed19, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Tester_HM_Predefined3_STATE_Unnamed19, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&Tester_HM_Predefined3_TRANS_VAdelay__GenA__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Tester_HM_Predefined3_TRANS_AVdelay__VAdelay__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Tester_HM_Predefined3_TRANS_GenA__AVdelay__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Tester_HM_Predefined3_TRANS_Unnamed19__GenA__0, /*function*/, /*ctx*/);
	// --- Tester_HM_HeIsDeadJim ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&Tester_HM_HeIsDeadJim_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&Tester_HM_HeIsDeadJim_STATE_DoNothing, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Tester_HM_HeIsDeadJim_STATE_DoNothing, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&Tester_HM_HeIsDeadJim_TRANS_DoNothing__DoNothing__0, /*function*/, /*ctx*/);
	// --- Observer_PS ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&Observer_PS_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&Observer_PS_STATE_Vsensed, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_PS_STATE_Vsensed, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_PS_STATE_Asensed, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_PS_STATE_Asensed, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_PS_STATE_Vsignalled, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_PS_STATE_Vsignalled, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_PS_STATE_Vpaced, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_PS_STATE_Vpaced, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_PS_STATE_Asignalled, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_PS_STATE_Asignalled, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_PS_STATE_Apaced, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_PS_STATE_Apaced, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_PS_STATE_Observer, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_PS_STATE_Observer, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&Observer_PS_TRANS_Vsensed__Observer__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_PS_TRANS_Observer__Vsensed__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_PS_TRANS_Asensed__Observer__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_PS_TRANS_Observer__Asensed__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_PS_TRANS_Vsignalled__Observer__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_PS_TRANS_Observer__Vsignalled__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_PS_TRANS_Vpaced__Observer__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_PS_TRANS_Observer__Vpaced__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_PS_TRANS_Asignalled__Observer__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_PS_TRANS_Observer__Asignalled__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_PS_TRANS_Apaced__Observer__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_PS_TRANS_Observer__Apaced__0, /*function*/, /*ctx*/);
	// --- Observer_LRI ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&Observer_LRI_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&Observer_LRI_STATE_S3, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_LRI_STATE_S3, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_LRI_STATE_S2, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_LRI_STATE_S2, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_LRI_STATE_S1, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_LRI_STATE_S1, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&Observer_LRI_TRANS_S3__S2__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_LRI_TRANS_S2__S3__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_LRI_TRANS_S2__S3__1, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_LRI_TRANS_S1__S2__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_LRI_TRANS_S1__S2__1, /*function*/, /*ctx*/);
	// --- Observer_URI ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&Observer_URI_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&Observer_URI_STATE_S3, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_URI_STATE_S3, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_URI_STATE_S2, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_URI_STATE_S2, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_URI_STATE_S1, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_URI_STATE_S1, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&Observer_URI_TRANS_S3__S2__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_URI_TRANS_S2__S3__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_URI_TRANS_S2__S2__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_URI_TRANS_S1__S2__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_URI_TRANS_S1__S2__1, /*function*/, /*ctx*/);
	// --- Observer_VRP ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&Observer_VRP_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&Observer_VRP_STATE_S3, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_VRP_STATE_S3, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_VRP_STATE_S2, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_VRP_STATE_S2, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_VRP_STATE_S1, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_VRP_STATE_S1, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&Observer_VRP_TRANS_S3__S2__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_VRP_TRANS_S2__S3__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_VRP_TRANS_S2__S3__1, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_VRP_TRANS_S1__S2__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_VRP_TRANS_S1__S2__1, /*function*/, /*ctx*/);
	// --- Observer_AV ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&Observer_AV_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&Observer_AV_STATE_BAD2, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_AV_STATE_BAD2, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_AV_STATE_S35, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_AV_STATE_S35, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_AV_STATE_BAD1, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_AV_STATE_BAD1, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_AV_STATE_S7, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_AV_STATE_S7, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_AV_STATE_S6, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_AV_STATE_S6, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_AV_STATE_S5, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_AV_STATE_S5, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_AV_STATE_S1, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_AV_STATE_S1, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_AV_STATE_S4, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_AV_STATE_S4, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_AV_STATE_S3, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_AV_STATE_S3, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Observer_AV_STATE_S2, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Observer_AV_STATE_S2, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_BAD2__S5__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_S35__BAD2__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_S35__S5__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_S35__S5__1, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_S5__S4__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_S5__S4__1, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_BAD1__S6__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_S5__BAD1__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_S6__S7__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_S6__S7__1, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_S5__S6__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_S7__S3__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_S4__S5__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_S4__S5__1, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_S1__S2__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_S1__S2__1, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_S3__S35__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_S3__S4__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_S2__S3__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Observer_AV_TRANS_S2__S3__1, /*function*/, /*ctx*/);
}

