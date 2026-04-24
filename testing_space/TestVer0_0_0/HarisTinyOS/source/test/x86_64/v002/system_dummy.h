// system_dummy.h
#ifndef SYSTEM_DUMMY_H
#define SYSTEM_DUMMY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pch.h"
#include "ring_buffer.h"
/**
 * Build xprintf log to screen
 */

/******************************************************************************
 * system utilities function
 *******************************************************************************/

#define RING_BUFFER_CHAR_SHELL_SEND_BUFFER_SIZE 512

static volatile uint32_t delay_coeficient = 0;

/* Private define */
ring_buffer_char_t ring_buffer_char_shell_send;

static uint8_t
    ring_buffer_char_shell_send_buffer[RING_BUFFER_CHAR_SHELL_SEND_BUFFER_SIZE];

extern void sys_ctrl_shell_put_char(uint8_t c);

extern void dummy_system_init();

#ifdef __cplusplus
}
#endif

#endif