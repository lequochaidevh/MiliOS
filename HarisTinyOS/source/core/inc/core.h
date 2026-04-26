/**
 ******************************************************************************
 * @author: ThanNT
 * @date:   13/08/2016
 * @brief:  Main defination of active kernel
 ******************************************************************************
 **/

#ifndef __CORE_H__
#define __CORE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pch.h"

/*****************************************************************************
 * DEFINITION: active kernel
 *
 *****************************************************************************/
#define CORE_VERSION "1.3"
#define CORE_ENABLE  (0x01)
#define CORE_DISABLE (0x00)

#define CORE_FLAG_ON  (0x01)
#define CORE_FLAG_OFF (0x00)

#define CORE_RET_OK (0x01)
#define CORE_RET_NG (0x00)

/*****************************************************************************
 * DEFINITION: signals
 *
 *****************************************************************************/
#define CORE_USER_DEFINE_SIG (10)

/*****************************************************************************
 * DEFINITION: tasking
 *
 *****************************************************************************/
#define TASK_PRI_MAX_SIZE (8)

#define TASK_PRI_LEVEL_0 (0)
#define TASK_PRI_LEVEL_1 (1)
#define TASK_PRI_LEVEL_2 (2)
#define TASK_PRI_LEVEL_3 (3)
#define TASK_PRI_LEVEL_4 (4)
#define TASK_PRI_LEVEL_5 (5)
#define TASK_PRI_LEVEL_6 (6)
#define TASK_PRI_LEVEL_7 (7)

#define CORE_TASK_INTERRUPT_ID (0xEE)
#define CORE_TASK_IDLE_ID      (0xEF)

#ifdef __cplusplus
}
#endif

#endif  // __CORE_H__
