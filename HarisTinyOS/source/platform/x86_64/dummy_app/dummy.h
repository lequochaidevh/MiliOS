/**
 ******************************************************************************
 * @author: HaiLQ
 * @date:   25/04/2026
 * @details: Dummy Header and Config
 ******************************************************************************
 **/
#pragma once

#include <pthread.h>
#include <unistd.h>

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

extern void entry_critical(const char* file, const char* func, int line);
extern void exit_critical(const char* file, const char* func, int line);

#define ENTRY_CRITICAL() entry_critical(__FILE__, __FUNCTION__, __LINE__)
#define EXIT_CRITICAL()  exit_critical(__FILE__, __FUNCTION__, __LINE__)

extern void all_dummy_init();

#ifdef __cplusplus
}
#endif