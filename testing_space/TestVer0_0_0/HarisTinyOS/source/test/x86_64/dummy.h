#pragma once

#include "xprintf.h"

#define FATAL(s, c)         \
    do {                    \
        xprintf("[FATAL]"); \
    } while (0)

#ifdef __cplusplus
extern "C" {
#endif

#define SYS_PRINT(fmt, ...) xprintf((const char*)fmt, ##__VA_ARGS__)
#define LOG2LKUP(val)       ((uint_fast8_t)(32U - __builtin_clz(val)))

extern void entry_critical();
extern void exit_critical();

#define ENTRY_CRITICAL() entry_critical()
#define EXIT_CRITICAL()  exit_critical()

#ifdef __cplusplus
}
#endif