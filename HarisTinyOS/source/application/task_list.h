#ifndef __TASK_LIST_H__
#define __TASK_LIST_H__

#include "core.h"
#include "task.h"

extern const task_t         app_task_table[];
extern const task_polling_t app_task_polling_table[];

/*****************************************************************************/
/*  DECLARE: Internal Task ID
 *  Note: Task id MUST be increasing order.
 */
/*****************************************************************************/
enum {
    /* SYSTEM TASKS */
    TASK_TIMER_TICK_ID,

    /* APP TASKS */
    AC_TASK_SYSTEM_ID,
    AC_TASK_FW_ID,
    AC_TASK_SHELL_ID,
    AC_TASK_LIFE_ID,
    AC_TASK_IF_ID,
    AC_TASK_RF24_IF_ID,
    AC_TASK_UART_IF_ID,
    AC_TASK_DBG_ID,
    AC_TASK_DISPLAY_ID,
    AC_TASK_AIRCOND_SCENE_ID,

#if defined(TASK_ZIGBEE_EN)
    AC_TASK_ZIGBEE_ID,
#endif

/* NRF24 NETWORKS */
#if defined(IF_NETWORK_NRF24_EN)
    AC_RF24_PHY_ID,
    AC_RF24_MAC_ID,
    AC_RF24_NWK_ID,
#endif

/* LINK */
#if defined(IF_LINK_UART_EN)
    AC_LINK_PHY_ID,
    AC_LINK_MAC_ID,
    AC_LINK_ID,
#endif

    /* EOT task ID */
    CORE_TASK_EOT_ID,
};

/*****************************************************************************/
/*  DECLARE: Internal Polling Task ID
 *  Note: Task id MUST be increasing order.
 */
/*****************************************************************************/
enum {
    /* APP TASKS */
    AC_TASK_POLLING_ZIGBEE_ID,
    AC_TASK_POLLING_CONSOLE_ID,

    /* EOT polling task ID */
    CORE_TASK_POLLING_EOT_ID,
};

/*****************************************************************************/
/*  DECLARE: Task entry point
 */
/*****************************************************************************/
/* APP TASKS */
extern void task_system(core_msg_t*);
extern void task_fw(core_msg_t*);
extern void task_shell(core_msg_t*);
extern void task_life(core_msg_t*);
extern void task_if(core_msg_t*);
extern void task_rf24_if(core_msg_t*);
extern void task_uart_if(core_msg_t*);
extern void task_dbg(core_msg_t*);
extern void task_display(core_msg_t*);
extern void task_zigbee(core_msg_t*);
extern void task_aircond_scene(core_msg_t*);

/* RF24 NETWORK TASK */
extern void task_rf24_phy(core_msg_t*);
extern void task_rf24_mac(core_msg_t*);
extern void task_rf24_nwk(core_msg_t*);

/* LINK TASK */
extern void task_link_phy(core_msg_t*);
extern void task_link_mac(core_msg_t*);
extern void task_link(core_msg_t*);

/*****************************************************************************/
/*  DECLARE: Task polling
 */
/*****************************************************************************/
extern void task_polling_zigbee();
extern void task_polling_console();

#endif  //__TASK_LIST_H__
