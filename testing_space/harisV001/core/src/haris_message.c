/**
 ******************************************************************************
 * @author: Hari
 * @date:   20-4-2026
 * @details: Message handler
 ******************************************************************************
 **/

#include "haris_message.h"
#include <stdio.h>

#include "haris_common.h"

/* pure message pool memory */
static haris_pure_msg_t pure_msg_pool[HARIS_PURE_MSG_POOL_SIZE];
static haris_msg_t*     free_list_pure_msg_pool;
static uint32_t         free_list_pure_msg_used;

/* common message pool memory */
static haris_common_msg_t common_msg_pool[HARIS_COMMON_MSG_POOL_SIZE];
static haris_msg_t*       free_list_common_msg_pool;
static uint32_t           free_list_common_used;

/* dynamic message pool memory */
static haris_dynamic_msg_t dynamic_msg_pool[HARIS_DYNAMIC_MSG_POOL_SIZE];
static haris_msg_t*        free_list_dynamic_msg_pool;
static uint32_t            free_list_dynamic_msg_used;

/* messages init */
static void pure_msg_init();
static void common_msg_init();
static void dynamic_msg_init();

/* memory utility */
void* haris_malloc(size_t size);
void  haris_malloc_free(void* ptr);

/*****************************************************************************
 * pure message function
 *****************************************************************************/
void pure_msg_init() {
    ENTRY_CRITICAL();

    free_list_pure_msg_pool = (haris_msg_t*)pure_msg_pool;

    for (uint32_t index = 0; index < HARIS_PURE_MSG_POOL_SIZE; index++) {
        pure_msg_pool[index].msg_header.msg_type = PURE_MSG_TYPE;
        if (index == (HARIS_PURE_MSG_POOL_SIZE - 1)) {
            pure_msg_pool[index].msg_header.next = HARIS_MSG_NULL;
        } else {
            pure_msg_pool[index].msg_header.next =
                (haris_msg_t*)&pure_msg_pool[index + 1];
        }
    }

    free_list_pure_msg_used = 0;

    EXIT_CRITICAL();
}

haris_msg_t* get_pure_msg() {
    haris_msg_t* get_msg;

    ENTRY_CRITICAL();

    /* assign the free message list to new allocate message */
    get_msg = free_list_pure_msg_pool;

    if (get_msg == HARIS_MSG_NULL) {
        FATAL("MSG", 0x01);
    }

    /* move the free message list to new position */
    free_list_pure_msg_pool = get_msg->next;
    free_list_pure_msg_used++;

    EXIT_CRITICAL();

    return get_msg;
}

void free_pure_msg(haris_msg_t* msg) {
    ENTRY_CRITICAL();

    /* move the current message to front free message list */
    msg->next = free_list_pure_msg_pool;

    /* move the free message list to head */
    free_list_pure_msg_pool = msg;
    free_list_pure_msg_used--;

    EXIT_CRITICAL();
}

uint8_t get_pure_msg_free() {
    return (HARIS_PURE_MSG_POOL_SIZE - free_list_pure_msg_used);
}

/*****************************************************************************
 * common message function
 *****************************************************************************/
void common_msg_init() {
    ENTRY_CRITICAL();

    free_list_common_msg_pool = (haris_msg_t*)common_msg_pool;

    for (uint32_t index = 0; index < HARIS_COMMON_MSG_POOL_SIZE; index++) {
        common_msg_pool[index].msg_header.msg_type = COMMON_MSG_TYPE;
        if (index == (HARIS_COMMON_MSG_POOL_SIZE - 1)) {
            common_msg_pool[index].msg_header.next = HARIS_MSG_NULL;
        } else {
            common_msg_pool[index].msg_header.next =
                (haris_msg_t*)&common_msg_pool[index + 1];
        }
    }

    free_list_common_used = 0;

    EXIT_CRITICAL();
}

haris_msg_t* get_common_msg() {
    haris_msg_t* get_msg;

    ENTRY_CRITICAL();

    /* assign the free message list to new allocate message */
    get_msg = free_list_common_msg_pool;

    if (get_msg == HARIS_MSG_NULL) {
        FATAL("MSG", 0x02);
    }

    /* move the free message list to new position */
    free_list_common_msg_pool                 = get_msg->next;
    ((haris_common_msg_t*)get_msg)->data_size = 0;
    free_list_common_used++;

    EXIT_CRITICAL();

    return get_msg;
}

void set_data_common_msg(haris_msg_t* msg, uint8_t* data, uint8_t size) {
    if (msg->msg_type != COMMON_MSG_TYPE) {
        FATAL("MSG", 0x03);
    }

    if (size > HARIS_COMMON_MSG_DATA_SIZE) {
        FATAL("MSG", 0x04);
    }

    ((haris_common_msg_t*)msg)->data_size = size;
    memcpy(((haris_common_msg_t*)msg)->data, data, size);
}

uint8_t* get_data_common_msg(haris_msg_t* msg) {
    if (msg->msg_type != COMMON_MSG_TYPE) {
        FATAL("MSG", 0x05);
    }

    return ((haris_common_msg_t*)msg)->data;
}

void free_common_msg(haris_msg_t* msg) {
    ENTRY_CRITICAL();

    /* move the current message to front free message list */
    msg->next = free_list_common_msg_pool;

    /* move the free message list to head */
    free_list_common_msg_pool = msg;
    free_list_common_used--;

    EXIT_CRITICAL();
}

uint8_t get_common_msg_free() {
    return (HARIS_COMMON_MSG_POOL_SIZE - free_list_common_used);
}

/*****************************************************************************
 * dynamic message function
 *****************************************************************************/
void dynamic_msg_init() {
    ENTRY_CRITICAL();

    free_list_dynamic_msg_pool = (haris_msg_t*)dynamic_msg_pool;

    for (uint32_t index = 0; index < HARIS_DYNAMIC_MSG_POOL_SIZE; index++) {
        dynamic_msg_pool[index].msg_header.msg_type = DYNAMIC_MSG_TYPE;
        if (index == (HARIS_DYNAMIC_MSG_POOL_SIZE - 1)) {
            dynamic_msg_pool[index].msg_header.next = HARIS_MSG_NULL;
        } else {
            dynamic_msg_pool[index].msg_header.next =
                (haris_msg_t*)&dynamic_msg_pool[index + 1];
        }
    }

    free_list_dynamic_msg_used = 0;

    EXIT_CRITICAL();
}

haris_msg_t* get_dynamic_msg() {
    haris_msg_t* get_msg;

    ENTRY_CRITICAL();

    /* assign the free message list to new allocate message */
    get_msg = free_list_dynamic_msg_pool;

    if (get_msg == HARIS_MSG_NULL) {
        FATAL("MSG", 0x06);
    }

    /* move the free message list to new position */
    free_list_dynamic_msg_pool                 = get_msg->next;
    ((haris_dynamic_msg_t*)get_msg)->data_size = 0;
    ((haris_dynamic_msg_t*)get_msg)->data      = ((uint8_t*)0);
    free_list_dynamic_msg_used++;

    EXIT_CRITICAL();

    return get_msg;
}

void set_data_dynamic_msg(haris_msg_t* msg, uint8_t* data, uint32_t size) {
    if (msg->msg_type != DYNAMIC_MSG_TYPE) {
        FATAL("MSG", 0x07);
    }

    ((haris_dynamic_msg_t*)msg)->data_size = size;
    ((haris_dynamic_msg_t*)msg)->data      = (uint8_t*)haris_malloc(size);
    memcpy(((haris_dynamic_msg_t*)msg)->data, data, size);
}

uint8_t* get_data_dynamic_msg(haris_msg_t* msg) {
    if (msg->msg_type != DYNAMIC_MSG_TYPE) {
        FATAL("MSG", 0x08);
    }

    return ((haris_dynamic_msg_t*)msg)->data;
}

void free_dynamic_msg(haris_msg_t* msg) {
    ENTRY_CRITICAL();

    /* move the current message to front free message list */
    msg->next = free_list_dynamic_msg_pool;

    /* move the free message list to head */
    free_list_dynamic_msg_pool = msg;
    free_list_dynamic_msg_used--;

    /* free memory to heap section */
    haris_malloc_free(((haris_dynamic_msg_t*)msg)->data);

    EXIT_CRITICAL();
}

uint8_t get_dynamic_msg_free() {
    return (HARIS_DYNAMIC_MSG_POOL_SIZE - free_list_dynamic_msg_used);
}

/*****************************************************************************
 * message utility function
 *****************************************************************************/
void msg_init() {
    pure_msg_init();
    common_msg_init();
    dynamic_msg_init();
    HARIS_LOG_KERNEL(
        "[message] messsage pool memory initialized successfully\n");
}

void free_msg(haris_msg_t* msg) {
    switch (msg->msg_type) {
        case PURE_MSG_TYPE: {
            free_pure_msg(msg);
        } break;

        case COMMON_MSG_TYPE: {
            free_common_msg(msg);
        } break;

        case DYNAMIC_MSG_TYPE: {
            free_dynamic_msg(msg);
        } break;

        default: {
            FATAL("MSG", 0xFE);
        } break;
    }
}

void* haris_malloc(size_t size) {
    extern uintptr_t __heap_end__;

    static uint8_t* haris_mem_addr = NULL;

    if (haris_mem_addr != NULL) {
        if (((uintptr_t)haris_mem_addr + size) > ((uintptr_t)&__heap_end__)) {
            FATAL("MEM", 0x01);
        }
    }

    haris_mem_addr = malloc(size);

    if (haris_mem_addr == NULL) {
        FATAL("MEM", 0x02);
    }

    return haris_mem_addr;
}

void haris_malloc_free(void* ptr) { free(ptr); }
