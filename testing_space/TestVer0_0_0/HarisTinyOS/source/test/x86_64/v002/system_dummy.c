#include "xprintf.h"
#include "system_dummy.h"
// #include "dummy.h"
#include "pch.h"

void sys_ctrl_shell_put_char(uint8_t c) {
    bool _flag_trigger = false;

    // ENTRY_CRITICAL();

    if (ring_buffer_char_is_empty(&ring_buffer_char_shell_send)) {
        _flag_trigger = true;
        printf("ring_buffer_char_is_empty\n");
    }

    ring_buffer_char_put(&ring_buffer_char_shell_send, c);
    printf("%c", c);
    // EXIT_CRITICAL();

    if (_flag_trigger) {
        // printf("_flag_trigger with DUMMY UART\n");
    }
}

void dummy_system_init() {
    ring_buffer_char_init(&ring_buffer_char_shell_send,
                          ring_buffer_char_shell_send_buffer,
                          RING_BUFFER_CHAR_SHELL_SEND_BUFFER_SIZE);
    xfunc_output = (void (*)(int))sys_ctrl_shell_put_char;
}
