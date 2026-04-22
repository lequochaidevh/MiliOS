/**
 ******************************************************************************
 * @author: Hari
 * @date:   20-4-2026
 * @details: Common ustils
 ******************************************************************************
 **/

#include "haris_common.h"

/* haris common pfunction */
pf_haris_ctrl_common pf_ctrl_sys_reboot   = (pf_haris_ctrl_common)0;
pf_haris_ctrl_delay  pf_ctrl_delay_ms     = (pf_haris_ctrl_delay)0;
pf_haris_ctrl_delay  pf_ctrl_delay_us     = (pf_haris_ctrl_delay)0;
pf_haris_ctrl_common pf_ctrl_led_life_on  = (pf_haris_ctrl_common)0;
pf_haris_ctrl_common pf_ctrl_led_life_off = (pf_haris_ctrl_common)0;

/* app run mode */
static app_mode_t app_mode = APP_MODE_DEBUG;

void haris_sys_ctrl_reboot_init(pf_haris_ctrl_common pf_reboot) {
    pf_ctrl_sys_reboot = pf_reboot;
}

void haris_sys_ctrl_reboot() {
    if (pf_ctrl_sys_reboot) {
        pf_ctrl_sys_reboot();
    }
}

void haris_sys_ctrl_delay_ms_init(pf_haris_ctrl_delay pf_delay_ms) {
    pf_ctrl_delay_ms = pf_delay_ms;
}

void haris_sys_ctrl_delay_ms(uint32_t ms) {
    if (pf_ctrl_delay_ms) {
        pf_ctrl_delay_ms(ms);
    }
}

void haris_sys_ctrl_delay_us_init(pf_haris_ctrl_delay pf_delay_us) {
    pf_ctrl_delay_us = pf_delay_us;
}

void haris_sys_ctrl_delay_us(uint32_t us) {
    if (pf_ctrl_delay_us) {
        pf_ctrl_delay_us(us);
    }
}

void haris_ctrl_led_init(pf_haris_ctrl_common led_on,
                         pf_haris_ctrl_common led_off) {
    pf_ctrl_led_life_on  = led_on;
    pf_ctrl_led_life_off = led_off;
}

void haris_ctrl_led_life_on() {
    if (pf_ctrl_led_life_on) {
        pf_ctrl_led_life_on();
    }
}

void haris_ctrl_led_life_off() {
    if (pf_ctrl_led_life_off) {
        pf_ctrl_led_life_off();
    }
}

app_mode_t haris_get_app_mode() { return app_mode; }

void haris_set_app_mode(app_mode_t mode) { app_mode = mode; }
