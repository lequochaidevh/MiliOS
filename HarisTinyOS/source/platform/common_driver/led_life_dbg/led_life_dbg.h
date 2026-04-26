/**
 ******************************************************************************
 * @author: HaiLQ
 * @date:   26/04/2026
 * @details: HAL Device Led Life Debug Layer
 ******************************************************************************
 **/

#ifndef __LED_LIFE_DBG_H__
#define __LED_LIFE_DBG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_device_interface.h"

#define LED_LIFE_DBG_PIN          14
#define LED_LIFE_DBG_DEFALT_STATE 0

// hal private data structure
typedef struct {
    uint8_t  is_active;
    uint8_t  state;
    uint16_t pin;
} led_attr_t;

static led_attr_t main_led_14_attr = {LED_LIFE_DBG_PIN,
                                      LED_LIFE_DBG_DEFALT_STATE};

enum { LED_DEBUG_INIT_FAILED, LED_DEBUG_INIT_OK };

extern const device_ops_t led_ops;

#ifdef __cplusplus
}
#endif

#endif  //__LED_LIFE_DBG_H__
