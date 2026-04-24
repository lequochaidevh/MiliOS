#include "dummy.h"
#include "pch.h"
#include "xprintf.h"

#include "system_dummy.h"

void entry_critical() { printf("[entry_critical]\n"); }

void exit_critical() { printf("[exit_critical]\n"); }

static uint8_t fake_heap[64 * 1024];

uintptr_t __heap_end__;

void dummy_heap_init(void) {
    __heap_end__ = (uintptr_t)(&fake_heap[0] + sizeof(fake_heap));
}
void all_dummy_init() {
    dummy_heap_init();
    dummy_system_init();
}
