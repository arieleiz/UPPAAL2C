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
	u2c_add_task(&Light_TASK);
}

static void init_inputs()
{
	// uncomment and edit required hardware inputs
	//u2c_set_channel_input(GLOBAL_CHANNEL_VAR_press, /*fill pin here*/, /*fill mode here*/, /*U2C_ReceiveChannel...*/);
}

static void init_outputs()
{
	// uncomment and edit required hardware outputs
}

static void init_callbacks()
{
	// --- Light ---
	// === uncomment and edit required process callbacks ===
	//u2c_set_process_start_cb(&Light_TASK, /*function*/, /*ctx*/);
	// === uncomment and edit required state callbacks ===
	//u2c_set_state_enter_cb(&Light_STATE_bright, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Light_STATE_bright, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Light_STATE_low, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Light_STATE_low, /*function*/, /*ctx*/);
	//u2c_set_state_enter_cb(&Light_STATE_off, /*function*/, /*ctx*/);
	//u2c_set_state_leave_cb(&Light_STATE_off, /*function*/, /*ctx*/);
	// == uncomment and edit required transition callbacks ===
	//u2c_set_transition_execute_cb(&Light_TRANS_bright__off__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Light_TRANS_low__bright__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Light_TRANS_low__off__0, /*function*/, /*ctx*/);
	//u2c_set_transition_execute_cb(&Light_TRANS_off__low__0, /*function*/, /*ctx*/);
}

