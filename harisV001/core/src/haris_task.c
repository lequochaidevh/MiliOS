/**
 ******************************************************************************
 * @author: Hari
 * @date:   20-4-2026
 * @details: Task Management
 ******************************************************************************
 **/

#include "haris_task.h"

// #include "haris_log.h"
// #include "haris_common.h"
#include "haris_timer.h"

// #include "haris_console.h"
// #include "task_console.h"

#define LOG2LKUP(val) ((uint_fast8_t)(32U - __builtin_clz(val)))

/* active object management */
static haris_task_t task_list[TASK_ACTIVE_OBJECT_MAX_SIZE];
static haris_tcb_t  active_object_task_queue[TASK_PRIORITY_MAX_SIZE];
static uint8_t      haris_task_table_size = 0;
static uint8_t      task_ready            = 0;

/* polling object management */
static haris_task_polling_t task_polling_list[TASK_POLLING_MAX_SIZE];
static uint8_t              task_polling_size = 0;

/* log object */
static haris_msg_t  current_active_object;
static haris_task_t current_task_info;

/* kernel task */
haris_task_t         task_console;
haris_task_polling_t task_polling_console;

/* banner */
// static void haris_banner();

void haris_banner() {
    HARIS_LOG("\n");
    HARIS_LOG(" _   _   ___  ______  _____  _____ \n");
    HARIS_LOG("| | | | / _ \\ | ___ \\|_   _|/  ___|\n");
    HARIS_LOG("| |_| |/ /_\\ \\| |_/ /  | |  \\ `--. \n");
    HARIS_LOG("|  _  ||  _  ||    /   | |   `--. \\\n");
    HARIS_LOG("| | | || | | || |\\ \\  _| |_ /\\__/ /\n");
    HARIS_LOG("\\_| |_/\\_| |_/\\_| \\_| \\___/ \\____/ \n");
    HARIS_LOG("\n");
    HARIS_LOG("Kernel version: %s\n", HARIS_KERNEL_VERSION);
    HARIS_LOG("Build date: %s %s\n", __DATE__, __TIME__);
}

void task_init() {
    haris_tcb_t* tcb;
    uint8_t      pri;
    task_polling_size = 0;

    /* init active object queue */
    for (pri = 1; pri <= TASK_PRIORITY_MAX_SIZE; pri++) {
        tcb        = &active_object_task_queue[pri - 1];
        tcb->mask  = (1 << (pri - 1));
        tcb->qhead = HARIS_MSG_NULL;
        tcb->qtail = HARIS_MSG_NULL;
    }

    /* console init */
    task_console.task_id  = TASK_CONSOLE_ID;
    task_console.priority = TASK_PRIORITY_LEVEL_2;
    // TODO: task_console_handler
    // task_console.task_handler = task_console_handler;
    task_console.info = (const uint8_t*)"task console";
    task_create(&task_console);

    task_polling_console.id      = TASK_POLLING_CONSOLE_ID;
    task_polling_console.ability = HARIS_ENABLE;
    // TODO: Add task_polling_console_handler
    // task_polling_console.task_polling_handler = task_polling_console_handler;
    task_polling_console.info = (const uint8_t*)"task polling console";
    task_polling_create(&task_polling_console);

    HARIS_LOG_KERNEL("[task] kernel task initialized successfully\n");
}

void haris_init() {
    /* kernel banner */
    haris_banner();

    /* message init */
    msg_init();

    /* timer service init */
    timer_init();

    /* kernel task init */
    task_init();

    HARIS_LOG("\n");
    HARIS_LOG("[KERNEL] system init successfully\n");
    HARIS_LOG("[KERNEL] application start\n");
    HARIS_LOG("\n");
}

void task_create(haris_task_t* task) {
    if (haris_task_table_size > TASK_ACTIVE_OBJECT_MAX_SIZE) {
        FATAL("TASK", 0x01);
    }

    ENTRY_CRITICAL();
    task_list[haris_task_table_size++] = *task;
    EXIT_CRITICAL();
}

void task_create_table(haris_task_t* app_task_table) {
    uint8_t size = 0;
    while (app_task_table[size].task_handler != (pf_task)0) {
        size++;
    }

    if ((haris_task_table_size + size) > TASK_ACTIVE_OBJECT_MAX_SIZE) {
        FATAL("TASK", 0x02);
    }

    for (uint8_t i = 0; i < size; i++) {
        task_create(&app_task_table[i]);
    }
}

void task_post(task_id_t task_id, haris_msg_t* msg) {
    haris_tcb_t* tcb;

    if (task_id >= haris_task_table_size) {
        FATAL("TASK", 0x03);
    }

    ENTRY_CRITICAL();

    tcb = &active_object_task_queue[task_list[task_id].priority];

    /* assign the task_id to message */
    msg->next        = HARIS_MSG_NULL;
    msg->src_task_id = current_task_info.task_id;
    msg->des_task_id = task_id;

    if (tcb->qtail == HARIS_MSG_NULL) {
        /* put message to queue */
        tcb->qtail = msg;
        tcb->qhead = msg;

        /* change status task to ready */
        task_ready |= tcb->mask;
    } else {
        /* put message to queue */
        tcb->qtail->next = msg;
        tcb->qtail       = msg;
    }

    EXIT_CRITICAL();
}

void task_post_pure_msg(task_id_t des_task_id, uint8_t signal) {
    haris_msg_t* get_pure_msg_from_pool = get_pure_msg();
    get_pure_msg_from_pool->signal      = signal;
    task_post(des_task_id, get_pure_msg_from_pool);
}

void task_post_common_msg(task_id_t des_task_id, uint8_t signal, uint8_t* data,
                          uint8_t len) {
    haris_msg_t* get_common_msg_from_pool = get_common_msg();
    get_common_msg_from_pool->signal      = signal;
    set_data_common_msg(get_common_msg_from_pool, data, len);
    task_post(des_task_id, get_common_msg_from_pool);
}

void task_post_dynamic_msg(task_id_t des_task_id, uint8_t signal, uint8_t* data,
                           uint32_t len) {
    haris_msg_t* get_dynamic_msg_from_pool = get_dynamic_msg();
    get_dynamic_msg_from_pool->signal      = signal;
    set_data_dynamic_msg(get_dynamic_msg_from_pool, data, len);
    task_post(des_task_id, get_dynamic_msg_from_pool);
}

void task_scheduler() {
    ENTRY_CRITICAL();

    uint8_t task_exe;

    while ((task_exe = LOG2LKUP(task_ready)) > 0) {
        /* get task execute */
        haris_tcb_t* tcb = &active_object_task_queue[task_exe - 1];

        /* get message from queue */
        haris_msg_t* msg_exe = tcb->qhead;

        /* move head message queue to new position */
        tcb->qhead = msg_exe->next;

        if (msg_exe->next == HARIS_MSG_NULL) {
            tcb->qtail = HARIS_MSG_NULL;

            /* change status of task to inactive */
            task_ready &= ~tcb->mask;
        }

        /* update current active object */
        memcpy((haris_task_t*)&current_task_info,
               &task_list[msg_exe->des_task_id], sizeof(haris_task_t));
        memcpy((haris_msg_t*)&current_active_object, msg_exe,
               sizeof(haris_msg_t));

        EXIT_CRITICAL();

        /* execute task */
        task_list[msg_exe->des_task_id].task_handler(msg_exe);

        /* free message to pool memory */
        free_msg(msg_exe);
    }

    EXIT_CRITICAL();
}

void task_polling_create(haris_task_polling_t* task_polling) {
    if (task_polling_size >= TASK_POLLING_MAX_SIZE) {
        FATAL("TASK", 0x04);
    }

    ENTRY_CRITICAL();
    task_polling_list[task_polling_size++] = *task_polling;
    EXIT_CRITICAL();
}

void task_polling_create_table(haris_task_polling_t* task_polling_table) {
    uint8_t size = 0;

    while (task_polling_table[size].task_polling_handler !=
           (pf_task_polling)0) {
        size++;
    }

    if ((task_polling_size + size) > TASK_POLLING_MAX_SIZE) {
        FATAL("TASK", 0x05);
    }

    for (uint8_t i = 0; i < size; i++) {
        task_polling_create(&task_polling_table[i]);
    }
}

void task_polling_run() {
    for (uint8_t i = 0; i < task_polling_size; i++) {
        ENTRY_CRITICAL();
        if (task_polling_list[i].ability == HARIS_ENABLE) {
            EXIT_CRITICAL();
            task_polling_list[i].task_polling_handler();
        } else {
            EXIT_CRITICAL();
        }
    }
}

void task_polling_set_ability(task_id_t task_polling_id, uint8_t ability) {
    for (uint8_t i = 0; i < task_polling_size; i++) {
        if (task_polling_list[i].id == task_polling_id) {
            ENTRY_CRITICAL();
            task_polling_list[i].ability = ability;
            EXIT_CRITICAL();
            return;
        }
    }

    FATAL("TASK", 0x06);
}

void task_init_info() {
    HARIS_LOG("\n");
    HARIS_LOG("task init information:\n");
    HARIS_LOG("[active_obj]\n");
    for (uint8_t i = 0; i < haris_task_table_size; i++) {
        HARIS_LOG("task id: %d \ttask pri: %d \ttask info: %s\n",
                  task_list[i].task_id, task_list[i].priority,
                  task_list[i].info);
    }
    HARIS_LOG("\n");
    HARIS_LOG("[polling_obj]\n");
    for (uint8_t i = 0; i < task_polling_size; i++) {
        HARIS_LOG("task id: %d \tinitial: %d \ttask info: %s\n",
                  task_polling_list[i].id, task_polling_list[i].ability,
                  task_polling_list[i].info);
    }
    HARIS_LOG("\n");
}

int task_run() {
    for (;;) {
        task_scheduler();
        task_polling_run();
    }
}

haris_task_t* get_current_task_info() {
    return (haris_task_t*)&current_task_info;
}

haris_msg_t* get_current_active_object() {
    return (haris_msg_t*)&current_active_object;
}
