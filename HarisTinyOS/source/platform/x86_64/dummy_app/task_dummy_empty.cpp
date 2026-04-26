/**
 ******************************************************************************
 * @author: HaiLQ
 * @date:   25/04/2026
 * @details: Dummy System Declare Empty Functions.
 ******************************************************************************
 **/
#include "task_list.h"
#include "xprintf.h"
#include "app.h"

/*****************************************************************************/
/*  DECLARE: Task entry point
 */
/*****************************************************************************/
/* APP TASKS */
// void task_system(core_msg_t*){};
void task_fw(core_msg_t*){};
void task_shell(core_msg_t*){};
// void task_life(core_msg_t*){};
void task_if(core_msg_t*){};
void task_rf24_if(core_msg_t*){};
void task_uart_if(core_msg_t*){};
void task_dbg(core_msg_t*){};
void task_display(core_msg_t*){};
void task_zigbee(core_msg_t*){};
void task_aircond_scene(core_msg_t*){};

/* RF24 NETWORK TASK */
void task_rf24_phy(core_msg_t*){};
void task_rf24_mac(core_msg_t*){};
void task_rf24_nwk(core_msg_t*){};

/* LINK TASK */
void task_link_phy(core_msg_t*){};
void task_link_mac(core_msg_t*){};
void task_link(core_msg_t*){};
