#include "hal_device_config.h"

// Builtin driver at
// Compile time
device_t active_devices[] = {
#if (USE_LED_LIFE_DEBUG_14 == 1)
    {"SYSTEM_LED_14",
     {GROUP_LED_LIFE_DBG_ID, 0},  // ID: minor is a index of array
     DEVICE_STATUS_ENABLE,
     &led_ops,
     &main_led_14_attr},
#endif
};

#define NUMBER_OF_DEVICE (sizeof(active_devices) / sizeof(active_devices[0]))

static dev_id_t cache_init_device_id[GROUP_DEVICE_ID_COUNT] = {-1, -1};

uint8_t device_initialize(device_t* devices) {
    for (int i = 0; i < GROUP_DEVICE_ID_COUNT; i++) {
        if (cache_init_device_id[devices->id.minor].major ==
            devices->id.major) {
            xprintf(
                "[WARNING]: Device have init before major: %d - minor: %d \n",
                devices->id.major, devices->id.minor);
            return LED_DEBUG_INIT_FAILED;
        };
    }

    // Store device be already_inited
    cache_init_device_id[devices->id.minor].major = devices->id.major;

    return active_devices[devices->id.minor].ops->init_fn(
        active_devices[devices->id.minor].private_data);
}
