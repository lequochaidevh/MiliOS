/**
 ******************************************************************************
 * @author: HaiLQ
 * @date:   26/04/2026
 * @details: Devices Config
 ******************************************************************************
 **/

#ifndef __DEVICE_CONFIG_H__
#define __DEVICE_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_device_interface.h"

/* LED LIFE DEBUG */
#include "led_life_dbg.h"

#define USE_LED_LIFE_DEBUG_14 1

enum { GROUP_LED_LIFE_DBG_ID, GROUP_DEVICE_ID_COUNT };

extern device_t active_devices[];

extern uint8_t device_initialize(device_t* devices);

#ifdef __cplusplus
}
#endif

#endif  //__DEVICE_CONFIG_H__
