/**
 ******************************************************************************
 * @author: ThanNT
 * @date:   05/09/2016
 ******************************************************************************
 **/

#include "debug.h"

#include "timer.h"

// #include "sys_dbg.h"
#include "task_list.h"

/* define message data is transfered between interrupt heart beat and timer task
 */
struct core_timer_payload_irq_t {
    uint32_t counter;
    uint32_t enable_post_msg;
};

static volatile struct core_timer_payload_irq_t core_timer_payload_irq = {
    0, CORE_DISABLE};

/* data to manage memory of timer message */
static core_timer_t  timer_pool[CORE_TIMER_POOL_SIZE];
static core_timer_t* free_list_timer_pool;
static core_timer_t* timer_list_head;

/* allocate/free memory of timer message */
static void          timer_msg_pool_init();
static core_timer_t* get_timer_msg();
static void          free_timer_msg(core_timer_t* msg);

static uint8_t timer_remove_msg(task_id_t des_task_id, timer_sig_t sig);

void timer_msg_pool_init() {
    uint32_t index;

    ENTRY_CRITICAL();

    timer_list_head      = TIMER_MSG_NULL;
    free_list_timer_pool = (core_timer_t*)timer_pool;

    for (index = 0; index < CORE_TIMER_POOL_SIZE; index++) {
        if (index == (CORE_TIMER_POOL_SIZE - 1)) {
            timer_pool[index].next = TIMER_MSG_NULL;
        } else {
            timer_pool[index].next = (core_timer_t*)&timer_pool[index + 1];
        }
    }

    EXIT_CRITICAL();
}

core_timer_t* get_timer_msg() {
    core_timer_t* allocate_timer;

    ENTRY_CRITICAL();

    allocate_timer = free_list_timer_pool;

    if (allocate_timer == TIMER_MSG_NULL) {
        FATAL("MT", 0x30);
    } else {
        free_list_timer_pool = allocate_timer->next;
    }

    EXIT_CRITICAL();

    return allocate_timer;
}

void free_timer_msg(core_timer_t* msg) {
    ENTRY_CRITICAL();

    msg->next            = free_list_timer_pool;
    free_list_timer_pool = msg;

    EXIT_CRITICAL();
}

void task_timer_tick(core_msg_t* msg) {
    core_msg_t* timer_msg;

    core_timer_t* timer_list;
    core_timer_t* timer_del =
        TIMER_MSG_NULL; /* MUST-BE assign TIMER_MSG_NULL */

    uint32_t temp_counter;
    uint32_t irq_counter;

    ENTRY_CRITICAL();

    timer_list = timer_list_head;

    irq_counter = core_timer_payload_irq.counter;

    core_timer_payload_irq.counter         = 0;
    core_timer_payload_irq.enable_post_msg = CORE_ENABLE;

    EXIT_CRITICAL();

    switch (msg->sig) {
        case TIMER_TICK:
            while (timer_list != TIMER_MSG_NULL) {
                ENTRY_CRITICAL();

                if (irq_counter < timer_list->counter) {
                    timer_list->counter -= irq_counter;
                } else {
                    timer_list->counter = 0;
                }

                temp_counter = timer_list->counter;

                EXIT_CRITICAL();

                if (temp_counter == 0) {
                    timer_msg = get_pure_msg();
                    set_msg_sig(timer_msg, timer_list->sig);
                    task_post(timer_list->des_task_id, timer_msg);

                    ENTRY_CRITICAL();

                    if (timer_list->period) {
                        timer_list->counter = timer_list->period;
                    } else {
                        timer_del = timer_list;
                    }

                    EXIT_CRITICAL();
                }

                timer_list = timer_list->next;

                if (timer_del) {
                    timer_remove_msg(timer_del->des_task_id, timer_del->sig);
                    timer_del = TIMER_MSG_NULL;
                }
            }
            break;

        default:
            break;
    }
}

void timer_init() {
    timer_msg_pool_init();

    ENTRY_CRITICAL();

    core_timer_payload_irq.counter         = 0;
    core_timer_payload_irq.enable_post_msg = CORE_ENABLE;

    EXIT_CRITICAL();
}

void timer_tick(uint32_t t) {
    if (timer_list_head != TIMER_MSG_NULL) {
        core_timer_payload_irq.counter += t;

        if (core_timer_payload_irq.enable_post_msg == CORE_ENABLE) {
            core_timer_payload_irq.enable_post_msg = CORE_DISABLE;

            core_msg_t* s_msg = get_pure_msg();
            set_msg_sig(s_msg, TIMER_TICK);
            task_post(TASK_TIMER_TICK_ID, s_msg);
        }
    }
}

uint8_t timer_set(task_id_t des_task_id, timer_sig_t sig, uint32_t duty,
                  timer_type_t type) {
    core_timer_t* timer_msg;

    ENTRY_CRITICAL();

    timer_msg = timer_list_head;

    while (timer_msg != TIMER_MSG_NULL) {
        if (timer_msg->des_task_id == des_task_id && timer_msg->sig == sig) {
            timer_msg->counter = duty;

            EXIT_CRITICAL();

            return TIMER_RET_OK;
        } else {
            timer_msg = timer_msg->next;
        }
    }

    timer_msg = get_timer_msg();

    timer_msg->des_task_id = des_task_id;
    timer_msg->sig         = sig;
    timer_msg->counter     = duty;

    if (type == TIMER_PERIODIC) {
        timer_msg->period = duty;
    } else {
        timer_msg->period = 0;
    }

    if (timer_list_head == TIMER_MSG_NULL) {
        timer_msg->next = TIMER_MSG_NULL;
        timer_list_head = timer_msg;
    } else {
        timer_msg->next = timer_list_head;
        timer_list_head = timer_msg;
    }

    EXIT_CRITICAL();

    return TIMER_RET_OK;
}

uint8_t timer_remove_msg(task_id_t des_task_id, timer_sig_t sig) {
    core_timer_t* timer_msg;
    core_timer_t* timer_msg_prev;

    ENTRY_CRITICAL();

    timer_msg      = timer_list_head;
    timer_msg_prev = timer_msg;

    while (timer_msg != TIMER_MSG_NULL) {
        if (timer_msg->des_task_id == des_task_id && timer_msg->sig == sig) {
            if (timer_msg == timer_list_head) {
                timer_list_head = timer_msg->next;
            } else {
                timer_msg_prev->next = timer_msg->next;
            }

            free_timer_msg(timer_msg);

            EXIT_CRITICAL();

            return TIMER_RET_OK;
        } else {
            timer_msg_prev = timer_msg;
            timer_msg      = timer_msg->next;
        }
    }

    EXIT_CRITICAL();

    return TIMER_RET_NG;
}

uint8_t timer_remove_attr(task_id_t des_task_id, timer_sig_t sig) {
    uint8_t ret = timer_remove_msg(des_task_id, sig);

    task_remove_msg(des_task_id, sig);

    return ret;
}
