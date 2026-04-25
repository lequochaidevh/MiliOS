#include "system.h"
#include "timer.h"
#include "app.h"

static pthread_t thread_id;
static uint32_t  millis_current;

/**/
void systick_handler() {
    static uint32_t div_counter = 0;

    task_entry_interrupt();

    /* increasing millis counter */
    millis_current++;

    timer_tick(1);

    if (div_counter == 10) {
        div_counter = 0;
    }

    switch (div_counter) {
        case 0:
            sys_irq_timer_10ms();
            // xprintf("timer_tick= %d\n", millis_current);
            break;

        default:
            break;
    }

    div_counter++;

    task_exit_interrupt();
}

void timer_handler(int sig) { systick_handler(); }

void* system_tick_thread(void* arg) {
    while (1) {
        systick_handler();
        usleep(1000);  // c
    }
    return NULL;
}

void start_system_tick_thread_dummy() {
    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, system_tick_thread, NULL) != 0) {
        perror("Failed to create tick thread");
    } else {
        printf("[System] Tick thread started (1ms)\n");
    }
}