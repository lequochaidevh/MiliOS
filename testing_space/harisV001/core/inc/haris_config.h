/**
 ******************************************************************************
 * @author: Hari
 * @date:   20-4-2026
 * @details: Config for INFO, LOG, TASK
 ******************************************************************************
 **/

#ifndef __HARIS_CONFIG_H__
#define __HARIS_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*****************************************************************************
 * DEFINITION: lite thread version
 *
 *****************************************************************************/
#define HARIS_KERNEL_VERSION "0.0.1"

#define HARIS_DISABLE (0x00)
#define HARIS_ENABLE  (0x01)

/*****************************************************************************
 * DEFINITION: tasking
 *
 *****************************************************************************/
#define TASK_ACTIVE_OBJECT_MAX_SIZE (16)
#define TASK_POLLING_MAX_SIZE       (8)
#define TASK_PRIORITY_MAX_SIZE      (8)

/*****************************************************************************
 * DEFINITION: message
 *
 *****************************************************************************/
/* size of message pool */
#define HARIS_PURE_MSG_POOL_SIZE    (8)
#define HARIS_COMMON_MSG_POOL_SIZE  (8)
#define HARIS_COMMON_MSG_DATA_SIZE  (64)
#define HARIS_DYNAMIC_MSG_POOL_SIZE (8)

/*****************************************************************************
 * DEFINITION: timer
 *
 *****************************************************************************/
#define HARIS_TIMER_POOL_SIZE (16)

/*****************************************************************************
 * DEFINITION: console
 *
 *****************************************************************************/
#define SHELL_TABLE_MAX_SIZE           (16)
#define SHELL_RING_BUFFER_REV_MAX_SIZE (256)
#define SHELL_CMD_INPUT_MAX_SIZE       (32)

/*****************************************************************************
 * DEFINITION: log
 *
 *****************************************************************************/
#define HARIS_LOG_FATAL_OBJECT_MAX_SIZE (32)
#define HARIS_LOG_KERNEL_EN             (0)

/*****************************************************************************
 * DEFINITION: attribute
 *
 *****************************************************************************/
#define __HARIS_PACKETED__ __attribute__((__packed__))
#define __HARIS_WEAK__     __attribute__((__weak__))

#ifdef __cplusplus
}
#endif

#endif /* __HARIS_CONFIG_H__ */
