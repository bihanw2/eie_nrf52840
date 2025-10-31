/**
 * @file state_machine.c
 */

#include <zephyr/smf.h>
#include <zephyr/sys/printk.h>

#include "BTN.h"
#include "LED.h"
#include "state_machine.h"

// Function prototypes for STATE entry, run, exit functions
static void state_input_char0_entry(void* o);
static void smf_state_result state_input_char0_run(void* o);
static void state_input_char0_exit(void* o)

static void state_input_char1_entry(void* o);
static void smf_state_result state_input_char1_run(void* o);
static void state_input_char1_exit(void* o);

static void state_display_string_entry(void* o);
static void smf_state_result state_display_string_run(void* o);
static void state_display_string_exit(void* o);

static void state_standby_entry(void* o);
static void smf_state_result state_standby_run(void* o);
static void state_standby_exit(void* o);

// STATE enum
enum string_state_machine_states {
    STATE_INPUT_CHAR0,
    STATE_INPUT_CHAR1,
    STATE_DISPLAY_STRING,
    STATE_STANDBY
};

// Assign entry, run, exit functions to each STATE
static const struct smf_state string_states[] = {
    [STATE_INPUT_CHAR0] = SMF_CREATE_STATE(state_input_char0_entry, state_input_char0_run, state_input_char0_exit, NULL, NULL),
    [STATE_INPUT_CHAR1] = SMF_CREATE_STATE(state_input_char1_entry, state_input_char1_run, state_input_char1_exit, NULL, NULL),
    [STATE_DISPLAY_STRING] = SMF_CREATE_STATE(state_display_string_entry, state_display_string_run, state_display_string_exit, NULL, NULL),
    [STATE_STANDBY] = SMF_CREATE_STATE(state_standby_entry, state_standby_run, state_standby_exit, NULL, NULL)
};

void state_machine_init() {}

int state_machine_run() {}
