/**
 * @file my_state_machine.c
 */

#include <zephyr/smf.h>
#include <zephyr/sys/printk.h>

#include "BTN.h"
#include "LED.h"
#include "my_state_machine.h"

// Function prototypes
static void state_off_entry(void* o);
static enum smf_state_result state_off_run(void* o);
static void state_off_exit(void* o);

static void state_led1_blink_entry(void* o);
static enum smf_state_result state_led1_blink_run(void* o);
static void state_led1_blink_exit(void* o);

static void state_odd_on_entry(void* o);
static enum smf_state_result state_odd_on_run(void* o);
static void state_odd_on_exit(void* o);

static void state_even_on_entry(void* o);
static enum smf_state_result state_even_on_run(void* o);
static void state_even_on_exit(void* o);

static void state_all_blink_entry(void* o);
static enum smf_state_result state_all_blink_run(void* o);
static void state_all_blink_exit(void* o);

// Typedefs
enum led_state_machine_states {
    STATE_OFF,
    STATE_LED1_BLINK,
    STATE_ODD_ON,
    STATE_EVEN_ON,
    STATE_ALL_BLINK
};

typedef struct {
    
    struct smf_ctx ctx;
    uint16_t count;

} led_state_object_t;

// Local vars
static const struct smf_state led_states[] = {
    [STATE_OFF] = SMF_CREATE_STATE(state_off_entry, state_off_run, state_off_exit, NULL, NULL),
    [STATE_LED1_BLINK] = SMF_CREATE_STATE(state_led1_blink_entry, state_led1_blink_run, state_led1_blink_exit, NULL, NULL),
    [STATE_ODD_ON] = SMF_CREATE_STATE(state_odd_on_entry, state_odd_on_run, state_odd_on_exit, NULL, NULL),
    [STATE_EVEN_ON] = SMF_CREATE_STATE(state_even_on_entry, state_even_on_run, state_even_on_exit, NULL, NULL),
    [STATE_ALL_BLINK] = SMF_CREATE_STATE(state_all_blink_entry, state_all_blink_run, state_all_blink_exit, NULL, NULL)
}; // each state has a function for its entry, runtime, and exit

static led_state_object_t led_state_object; // current state variable

void state_machine_init() {
    led_state_object.count = 0;
    smf_set_initial(SMF_CTX(&led_state_object), &led_states[STATE_OFF]); // set initial state
}

int state_machine_run() {
    return smf_run_state(SMF_CTX(&led_state_object)); // call the run function of the current state
}

static void state_off_entry(void* o) {
    printk("\n\rEntering STATE_OFF: all LEDs off.");
    LED_set(LED0, LED_OFF);
    LED_set(LED1, LED_OFF);
    LED_set(LED2, LED_OFF);
    LED_set(LED3, LED_OFF);
}

static enum smf_state_result state_off_run(void* o) {
    if (BTN_check_clear_pressed(BTN0)) {
	smf_set_state(SMF_CTX(&led_state_object), &led_states[STATE_LED1_BLINK]);
    } else {
	;
    }
    return SMF_EVENT_HANDLED;
}

static void state_off_exit(void* o) {
    printk("\n\rExiting STATE_OFF...");
}

/*
static void led_on_state_entry(void* o) {
    LED_set(LED0, LED_ON);
}

static enum smf_state_result led_on_state_run(void* o) {
    if (led_state_object.count > 500) {
        led_state_object.count = 0;
	smf_set_state(SMF_CTX(&led_state_object), &led_states[LED_OFF_STATE]);
    } else {
        led_state_object.count++;
    }

    return SMF_EVENT_HANDLED;
}

static void led_on_state_exit(void* o) {
    LED_set(LED0, LED_OFF);
}*/

