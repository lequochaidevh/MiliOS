/**
 ******************************************************************************
 * @author: ThanNT
 * @date:   13/08/2016
 ******************************************************************************
 **/
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include <forward_list>
#include <functional>
#include <iterator>
#include <vector>
#include <deque>
#include <queue>
#include <array>
#include <map>

/* kernel include */
#include "core.h"
#include "message.h"
#include "timer.h"
#include "fsm.h"
#include "xprintf.h"

#include "task_list.h"

#include "ring_buffer.h"

#include "dummy.h"

#include "app.h"

#define APP_PRINT(fmt, ...) xprintf("[APP PRINT] " fmt, ##__VA_ARGS__)

#if defined(RELEASE)
const char* app_run_mode = "RELEASE";
#else
static const char* app_run_mode = "DEBUG";
#endif

/* init state machine for tasks
 * used for app tasks
 */
void app_init_state_machine() {}

void app_task_init() {
    task_post_pure_msg(AC_TASK_RF24_IF_ID, AC_RF24_IF_INIT_NETWORK);
    task_post_pure_msg(AC_TASK_DISPLAY_ID, AC_DISPLAY_INITIAL);
    task_post_pure_msg(AC_TASK_UART_IF_ID, AC_UART_IF_INIT);
    task_post_pure_msg(AC_TASK_AIRCOND_SCENE_ID, AC_AIRCOND_SCENE_INIT);
}

void app_start_timer() { /* start timer to toggle life led */
    APP_PRINT("Start timer\n");
}

/*****************************************************************************/
/*  app function declare
 */
/*****************************************************************************/

uint32_t sys_soft_reboot_counter __attribute__((section(".non_clear_ram")));

#define BUFFER_CONSOLE_REV_SIZE (256)
uint8_t            buffer_console_rev[BUFFER_CONSOLE_REV_SIZE];
ring_buffer_char_t ring_buffer_console_rev;

typedef struct {
    uint32_t magic_number;
    uint8_t  version[4];
} app_info_t;

const app_info_t app_info{
    APP_MAGIC_NUMBER,
    APP_VER,
};

int main_app() {
    APP_PRINT("App run mode: %s, App version: %d.%d.%d.%d\n", app_run_mode,
              app_info.version[0], app_info.version[1], app_info.version[2],
              app_info.version[3]);

    sys_soft_reboot_counter++;

    /******************************************************************************
     * init active kernel
     *******************************************************************************/
    ENTRY_CRITICAL();
    task_init();
    task_create((task_t*)app_task_table);
    task_polling_create((task_polling_t*)app_task_polling_table);
    EXIT_CRITICAL();

    /******************************************************************************
     * init applications
     *******************************************************************************/
    /*********************
     * hardware configure *
     **********************/
    /* init watch dog timer */
    // sys_ctrl_independent_watchdog_init(); /* 32s */
    // sys_ctrl_soft_watchdog_init(200);     /* 20s */

    // SPI.begin();

    /* adc peripheral configure */
    //	io_cfg_adc1();			/* configure adc for thermistor and CT
    // sensor
    //*/ 	adc_thermistor_io_cfg();

    /* adc configure for ct sensor */
    //	adc_ct_io_cfg();

    /* flash io init */
    // flash_io_ctrl_init();

    /*********************
     * software configure *
     **********************/
    /* initial boot object */
    // sys_boot_init();

    /* life led init */
    // led_init(&led_life, led_life_init, led_life_on, led_life_off);

    // ring_buffer_char_init(&ring_buffer_console_rev, buffer_console_rev,
    //                       BUFFER_CONSOLE_REV_SIZE);

    /* button init */
    // button_init(&btn_mode, 10, BUTTON_MODE_ID, io_button_mode_init,
    //             io_button_mode_read, btn_mode_callback);
    // button_init(&btn_up, 10, BUTTON_UP_ID, io_button_up_init,
    // io_button_up_read,
    //             btn_up_callback);
    // button_init(&btn_down, 10, BUTTON_DOWN_ID, io_button_down_init,
    //             io_button_down_read, btn_down_callback);

    // button_enable(&btn_mode);
    // button_enable(&btn_up);
    // button_enable(&btn_down);

    /* get boot share data */
    // flash_read(APP_FLASH_INTTERNAL_SHARE_DATA_SECTOR_1,
    //            reinterpret_cast<uint8_t*>(&boot_app_share_data),
    //            sizeof(boot_app_share_data_t));
    // if (boot_app_share_data.is_power_on_reset == SYS_POWER_ON_RESET) {
    //     app_power_on_reset();
    // }

    /* increase start time */
    //     fatal_log_t app_fatal_log;
    //     flash_read(APP_FLASH_AK_DBG_FATAL_LOG_SECTOR,
    //                reinterpret_cast<uint8_t*>(&app_fatal_log),
    //                sizeof(fatal_log_t));
    //     app_fatal_log.restart_times++;
    //     flash_erase_sector(APP_FLASH_AK_DBG_FATAL_LOG_SECTOR);
    //     flash_write(APP_FLASH_AK_DBG_FATAL_LOG_SECTOR,
    //                 reinterpret_cast<uint8_t*>(&app_fatal_log),
    //                 sizeof(fatal_log_t));

    // #if defined(TASK_MBMASTER_EN)
    //     xMBHandle xMBMMaster;
    //     eMBMSerialInit(&xMBMMaster, MB_RTU, MBM_SERIAL_PORT,
    //     MBM_SERIAL_BAUDRATE,
    //                    MB_PAR_NONE);
    // #endif

    // #if defined(TASK_ZIGBEE_EN)
    //     Serial2.begin();
    //     Serial2.setTimeout(100);
    // #endif

    //     EXIT_CRITICAL();

    // #if defined(TASK_ZIGBEE_EN)
    //     APP_PRINT("start_coordinator(0)\n");
    //     if (zigbee_network.start_coordinator(0) == 0) {
    //         APP_PRINT("OK\n");
    //     } else {
    //         APP_PRINT("NG\n");
    //     }
    // #endif

    /* start timer for application */
    app_init_state_machine();
    app_start_timer();

    /******************************************************************************
     * app task initial
     *******************************************************************************/
    app_task_init();

    /******************************************************************************
     * run applications
     *******************************************************************************/

    // sys_ctrl_shell_sw_to_nonblock();

    return task_run();
}

int main() {
    all_dummy_init();
    main_app();
    return 0;
}