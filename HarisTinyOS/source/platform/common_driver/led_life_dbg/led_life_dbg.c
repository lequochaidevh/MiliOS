#include "led_life_dbg.h"

// Helper
static void _led_hardware_toggle(led_attr_t* attr) {
    attr->state = !attr->state;
}

static bool set_led_active(void* data, int status) {
    led_attr_t* attr = (led_attr_t*)data;
    attr->is_active  = status;
    return true;
}

static int led_init(void* data) { return LED_DEBUG_INIT_OK; }

static void led_process(void* data) {
    led_attr_t* attr = (led_attr_t*)data;
    if (attr->is_active == DEVICE_STATUS_DISABLE) return;
    _led_hardware_toggle(attr);
}

const device_ops_t led_ops = {led_init, led_process, set_led_active, NULL};
