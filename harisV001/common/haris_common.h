/**
 ******************************************************************************
 * @author: Hari
 * @date:   20-4-2026
 * @details: Common ustils
 ******************************************************************************
 **/

#ifndef __HARIS_COMMON_H__
#define __HARIS_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "haris_log.h"

// #include "haris_console.h"

typedef void (*pf_haris_ctrl_common)();
typedef void (*pf_haris_ctrl_delay)(uint32_t);

typedef enum {
    APP_MODE_DEBUG,
    APP_MODE_RELEASE,
} app_mode_t;

/* haris common function */
extern void       haris_sys_ctrl_reboot_init(pf_haris_ctrl_common pf_reboot);
extern void       haris_sys_ctrl_reboot();
extern app_mode_t haris_get_app_mode();
extern void       haris_set_app_mode(app_mode_t mode);

/* haris system control delay */
extern void haris_sys_ctrl_delay_ms_init(pf_haris_ctrl_delay pf_delay_ms);
extern void haris_sys_ctrl_delay_ms(uint32_t ms);
extern void haris_sys_ctrl_delay_us_init(pf_haris_ctrl_delay pf_delay_us);
extern void haris_sys_ctrl_delay_us(uint32_t us);

/* haris control led status */
extern void haris_ctrl_led_init(pf_haris_ctrl_common led_on,
                                pf_haris_ctrl_common led_off);
extern void haris_ctrl_led_life_on();
extern void haris_ctrl_led_life_off();

#ifdef __cplusplus
}
#endif

#endif /* __HARIS_COMMON_H__ */
