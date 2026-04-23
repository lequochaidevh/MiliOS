#include "task_list.h"
#include "xprintf.h"
#include "app.h"

#define APP_START_ADDR 0x08003000

void task_system(core_msg_t* msg) {
    switch (msg->sig) {
        case SYSTEM_AK_FLASH_UPDATE_REQ: {
            xprintf("SYSTEM_AK_FLASH_UPDATE_REQ\n");

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
    switch (msg->sig) {
        case AC_LIFE_SYSTEM_CHECK:
            /* reset watchdog */
            xprintf("AC_LIFE_SYSTEM_CHECK\n");

#if defined(AK_IO_IRQ_ANALYZER)
#else
            /* toggle led indicator */
            xprintf("led_toggle\n");
#endif
            break;

        default:
            break;
    }
}

void task_polling_zigbee(){};
void task_polling_console(){};