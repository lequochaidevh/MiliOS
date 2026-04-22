/**
 ******************************************************************************
 * @author: Hari
 * @date:   20-4-2026
 * @details: Message handler
 ******************************************************************************
 **/

#ifndef __HARIS_MESSAGE_H__
#define __HARIS_MESSAGE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "haris_config.h"
#include "haris_log.h"

#define HARIS_MSG_NULL ((haris_msg_t*)0)

typedef struct haris_msg_t {
    /* message management - private for kernel */
    struct haris_msg_t* next;
    uint8_t             msg_type;

    /* message header - public for user application */
    uint8_t src_task_id;
    uint8_t des_task_id;
    uint8_t signal;

    /* link layer */
    uint8_t if_src_task_id;
    uint8_t if_des_task_id;
    uint8_t if_signal;
    uint8_t if_msg_type;
} haris_msg_t;

enum {
    SHELL_CMD_PARSER,
    USER_DEFINE_APP_SIGNAL = 0x10,
};

/******************************************************************************
 * message define
 *******************************************************************************/
#define PURE_MSG_TYPE    (0x01)
#define COMMON_MSG_TYPE  (0x02)
#define DYNAMIC_MSG_TYPE (0x04)

extern void msg_init();
extern void free_msg(haris_msg_t* msg);

/******************************************************************************
 * pure message define
 *******************************************************************************/
typedef struct {
    haris_msg_t msg_header;
} haris_pure_msg_t;

extern haris_msg_t* get_pure_msg();
extern uint8_t      get_pure_msg_free();

/******************************************************************************
 * common message define
 *******************************************************************************/
typedef struct {
    haris_msg_t msg_header;
    uint8_t     data_size;
    uint8_t     data[HARIS_COMMON_MSG_DATA_SIZE];
} haris_common_msg_t;

extern haris_msg_t* get_common_msg();
extern void set_data_common_msg(haris_msg_t* msg, uint8_t* data, uint8_t size);
extern uint8_t* get_data_common_msg(haris_msg_t* msg);
extern uint8_t  get_common_msg_free();

/******************************************************************************
 * dynamic message define
 *******************************************************************************/
typedef struct {
    haris_msg_t msg_header;
    uint8_t     data_size;
    uint8_t*    data;
} haris_dynamic_msg_t;

extern haris_msg_t* get_dynamic_msg();
extern void         set_data_dynamic_msg(haris_msg_t* msg, uint8_t* data,
                                         uint32_t size);
extern uint8_t*     get_data_dynamic_msg(haris_msg_t* msg);
extern uint8_t      get_dynamic_msg_free();

/******************************************************************************
 * dynamic memory allocate
 *******************************************************************************/
extern void* haris_malloc(size_t size);
extern void  haris_malloc_free(void* ptr);

#ifdef __cplusplus
}
#endif

#endif /* __HARIS_MESSAGE_H__ */
