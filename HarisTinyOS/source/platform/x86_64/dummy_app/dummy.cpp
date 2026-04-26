/**
 ******************************************************************************
 * @author: HaiLQ
 * @date:   25/04/2026
 * @details: Dummy Implementation
 ******************************************************************************
 **/
#include "dummy.h"
#include "pch.h"
#include "xprintf.h"

#include "system_dummy.h"

static bool is_short_file_debug = true;
static bool is_debug_crit       = false;

static pthread_mutex_t kernel_mutex = PTHREAD_MUTEX_INITIALIZER;

void entry_critical(const char* file, const char* func, int line) {
    pthread_mutex_lock(&kernel_mutex);

    if (!is_debug_crit) return;
    if (!is_short_file_debug) {
        printf("[entry_critical] at %s:%d (%s)\n", file, line, func);
        fflush(stdout);
        return;
    }

    const char* last_slash = strrchr(file, '/');
    const char* short_file = (last_slash) ? last_slash + 1 : file;

    printf("[entry_critical] at %s:%d (%s)\n", short_file, line, func);
    fflush(stdout);
}

void exit_critical(const char* file, const char* func, int line) {
    pthread_mutex_unlock(&kernel_mutex);
    if (!is_debug_crit) return;
    if (!is_short_file_debug) {
        printf("[exit_critical] at %s:%d (%s)\n", file, line, func);
        fflush(stdout);
        return;
    }

    const char* last_slash = strrchr(file, '/');
    const char* short_file = (last_slash) ? last_slash + 1 : file;

    printf("[exit_critical] at %s:%d (%s)\n", short_file, line, func);
    fflush(stdout);
}

static uint8_t fake_heap[64 * 1024];

uintptr_t __heap_end__;

void dummy_heap_init(void) {
    __heap_end__ = (uintptr_t)(&fake_heap[0] + sizeof(fake_heap));
}
void all_dummy_init() {
    dummy_heap_init();
    dummy_system_init();
}

uint32_t sys_ctrl_millis() { return 1; }

uint32_t sys_ctr_get_exception_number() { return 0; }
