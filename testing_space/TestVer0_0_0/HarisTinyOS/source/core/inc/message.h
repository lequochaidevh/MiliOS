/**
 ******************************************************************************
 * @author: ThanNT
 * @date:   13/08/2016
 ******************************************************************************
 **/

#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "core.h"

#define CORE_MSG_NULL ((core_msg_t*)0)

#define CORE_MSG_NG (0)
#define CORE_MSG_OK (1)

/* sizeof common message pool */
#ifndef CORE_COMMON_MSG_POOL_SIZE
#define CORE_COMMON_MSG_POOL_SIZE (8)
#endif

/* sizeof data common message */
#ifndef CORE_COMMON_MSG_DATA_SIZE
#define CORE_COMMON_MSG_DATA_SIZE (64)
#endif

/* sizeof pure message pool */
#ifndef CORE_PURE_MSG_POOL_SIZE
#define CORE_PURE_MSG_POOL_SIZE (32)
#endif

/* sizeof dynamic message pool */
#ifndef CORE_DYNAMIC_MSG_POOL_SIZE
#define CORE_DYNAMIC_MSG_POOL_SIZE (8)
#endif

/* numbers of dynamic pool data unit */
#ifndef CORE_DYNAMIC_DATA_POOL_SIZE
#define CORE_DYNAMIC_DATA_POOL_SIZE (128)
#endif

/* sizeof dynamic pool data unit */
#ifndef CORE_DYNAMIC_PDU_SIZE
#define CORE_DYNAMIC_PDU_SIZE (4)
#endif

#define CORE_MSG_TYPE_MASK      (0xC0)
#define CORE_MSG_REF_COUNT_MASK (0x3F)

#define CORE_MSG_REF_COUNT_MAX (7)

#define get_msg_ref_count(x) \
    ((((core_msg_t*)x)->ref_count) & CORE_MSG_REF_COUNT_MASK)
#define get_msg_type(x) ((((core_msg_t*)x)->ref_count) & CORE_MSG_TYPE_MASK)

typedef struct {
    /* time of message handler */
    uint32_t start_post;
    uint32_t start_exe;
    uint32_t stop_exe;
} dbg_handler_t;

/**************/
/* core_message */
/**************/
typedef struct core_msg_t {
    /*******************************
     * private for kernel.
     ******************************/
    /* message management */
    struct core_msg_t* next;

    /*******************************
     * kernel debug.
     ******************************/
    /* task debug */
#if (CORE_TASK_DEBUG == CORE_ENABLE)
    dbg_handler_t dbg_handler;
#endif

    /* task header */
    uint8_t src_task_id;
    uint8_t des_task_id;
    uint8_t ref_count;
    uint8_t sig;

    /*******************************
     * public for user application.
     ******************************/
    /* external task header */
    uint8_t if_src_task_id;
    uint8_t if_des_task_id;
    uint8_t if_src_type;
    uint8_t if_des_type;
    uint8_t if_sig;
} core_msg_t;

/******************/
/* common message */
/******************/
typedef struct {
    core_msg_t msg_header;
    uint8_t    len;
    uint8_t    data[CORE_COMMON_MSG_DATA_SIZE];
} core_msg_common_t;

/****************/
/* pure message */
/****************/
typedef struct {
    core_msg_t msg_header;
} core_msg_pure_t;

/*******************/
/* dynamic message */
/*******************/
typedef struct {
    core_msg_t msg_header;
    uint32_t   len;
    uint8_t*   data;
} core_msg_dynamic_t;

/*******************************/
/* core interface header message */
/*******************************/
typedef struct {
    uint8_t type;
    uint8_t src_task_id;
    uint8_t des_task_id;
    uint8_t sig;
    uint8_t if_src_type;
    uint8_t if_des_type;
} __CORE_PACKETED core_msg_if_header_t;

/*****************************/
/* core pure interface message */
/*****************************/
typedef struct {
    core_msg_if_header_t header;
} core_msg_pure_if_t;

/*******************************/
/* core common interface message */
/*******************************/
typedef struct {
    core_msg_if_header_t header;

    uint8_t len;
    uint8_t data[CORE_COMMON_MSG_DATA_SIZE];
} __CORE_PACKETED core_msg_common_if_t;

/*******************************/
/* core dynamic interface message */
/*******************************/
typedef struct {
    core_msg_if_header_t header;

    uint32_t len;
    uint8_t* data;
} __CORE_PACKETED core_msg_dynamic_if_t;

#define set_msg_sig(m, s)         (((core_msg_t*)m)->sig = s)
#define set_msg_src_task_id(m, t) (((core_msg_t*)m)->src_task_id = t)
#define set_msg_des_task_id(m, t) (((core_msg_t*)m)->des_task_id = t)

/* external if interface */
#define set_if_src_task_id(m, t)         (((core_msg_t*)m)->if_src_task_id = t)
#define set_if_des_task_id(m, t)         (((core_msg_t*)m)->if_des_task_id = t)
#define set_if_src_type(m, t)            (((core_msg_t*)m)->if_src_type = t)
#define set_if_des_type(m, t)            (((core_msg_t*)m)->if_des_type = t)
#define set_if_sig(m, s)                 (((core_msg_t*)m)->if_sig = s)
#define set_if_data_common_msg(m, d, s)  set_data_common_msg(m, d, s)
#define set_if_data_dynamic_msg(m, d, s) set_data_dynamic_msg(m, d, s)

extern void msg_init();
extern void msg_free(core_msg_t* msg);
extern void msg_inc_ref_count(core_msg_t* msg);
extern void msg_dec_ref_count(core_msg_t* msg);

/*****************************************************************************
 * DEFINITION: dynamic allocate
 *
 *****************************************************************************/
extern void* core_malloc(size_t);
extern void  core_free(void*);

/*****************************************************************************
 * DEFINITION: message
 *
 *****************************************************************************/
#define PURE_MSG_TYPE    (0x80)
#define COMMON_MSG_TYPE  (0xC0)
#define DYNAMIC_MSG_TYPE (0x40)

/* pure message
 * message only contain the task signal.
 */
extern core_msg_t* get_pure_msg();
extern uint32_t    get_pure_msg_pool_used();

/* common message
 * message contain a continue block memory with size =
 * CORE_COMMON_MSG_DATA_SIZE.
 */
extern core_msg_t* get_common_msg();
extern uint32_t    get_common_msg_pool_used();
extern uint8_t     set_data_common_msg(core_msg_t* msg, uint8_t* data,
                                       uint8_t size);
extern uint8_t*    get_data_common_msg(core_msg_t* msg);
extern uint8_t     get_data_len_common_msg(core_msg_t* msg);

/* dynmic message
 * message contain a link list block memory.
 */
extern core_msg_t* get_dynamic_msg();
extern uint32_t    get_dynamic_msg_pool_used();
extern uint8_t     set_data_dynamic_msg(core_msg_t* msg, uint8_t* data,
                                        uint32_t size);
extern uint8_t*    get_data_dynamic_msg(core_msg_t* msg);
extern uint32_t    get_data_len_dynamic_msg(core_msg_t* msg);

/*****************************************************************************
 * DEFINITION: debug message
 *
 *****************************************************************************/
extern void msg_dbg_dum(core_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif  //__MESSAGE_H__
