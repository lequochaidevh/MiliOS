/**
 ******************************************************************************
 * @author: HaiLQ
 * @date:   25/04/2026
 * @details: Dummy System Declare Temporary Functions.
 ******************************************************************************
 **/
#include "task_list.h"
#include "xprintf.h"
#include "app.h"

#include <thread>
#include <chrono>

#include "hal_device_config.h"

#define APP_START_ADDR 0x08003000

void task_system(core_msg_t* msg) {
    switch (msg->sig) {
        case SYSTEM_CORE_FLASH_UPDATE_REQ: {
            xprintf("SYSTEM_CORE_FLASH_UPDATE_REQ\n");

            // sys_boot_t sb;
            // sys_boot_get(&sb);

            // /* cmd update request */
            // sb.fw_app_cmd.cmd       = SYS_BOOT_CMD_UPDATE_REQ;
            // sb.fw_app_cmd.container = SYS_BOOT_CONTAINER_DIRECTLY;
            // sb.fw_app_cmd.io_driver = SYS_BOOT_IO_DRIVER_UART;
            // sb.fw_app_cmd.des_addr  = APP_START_ADDR;
            // sb.fw_app_cmd.src_addr  = 0;
            // sys_boot_set(&sb);

            // sys_ctrl_reset();
        } break;

        default:
            break;
    }
}

void task_life(core_msg_t* msg) {
    const led_attr_t* const led_data =
        (led_attr_t*)active_devices[0].private_data;  //
                                                      // for cast

    static const uint8_t led_dbg_init_once =
        device_initialize(&active_devices[GROUP_LED_LIFE_DBG_ID]);

    static uint8_t test_disable_device_cnt = 0;  // test by log
    test_disable_device_cnt++;

    switch (msg->sig) {
        case AC_LIFE_SYSTEM_CHECK:
            /* reset watchdog */
            xprintf("Reset watchdog\n");

#if defined(CORE_IO_IRQ_ANALYZER)
#else
            // led_data = (led_attr_t*)active_devices[0].private_data;  // for
            // cast

            active_devices[0].ops->process_fn(active_devices[0].private_data);
            /* toggle led indicator */
            xprintf("       --- Hearth beat = %s %d ---\n\n",
                    active_devices[0].name, led_data->state);

            if (test_disable_device_cnt > 5) {
                // test: disable -> state not change after process_fn
                active_devices[0].ops->set_active_fn(
                    active_devices[0].private_data, DEVICE_STATUS_DISABLE);
            }

            if (test_disable_device_cnt > 11) {
                // test: multi init will be warning
                device_initialize(&active_devices[GROUP_LED_LIFE_DBG_ID]);

                // test: enable device -> process_fn work ok
                active_devices[0].ops->set_active_fn(
                    active_devices[0].private_data, DEVICE_STATUS_ENABLE);
            }
#endif
            break;

        default:
            break;
    }
}

void task_polling_zigbee(){};
void task_polling_console(){};