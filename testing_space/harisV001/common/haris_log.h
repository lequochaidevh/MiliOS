/**
 ******************************************************************************
 * @author: Hari
 * @date:   20-4-2026
 * @details: Common ustils
 ******************************************************************************
 **/

#ifndef __HARIS_LOG_H__
#define __HARIS_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#define HARIS_LOG_KERNEL(...) printf(__VA_ARGS__)
#define FATAL(module, code)                                       \
    do {                                                          \
        printf("FATAL ERROR: [%s] Code: 0x%02X\n", module, code); \
        while (1)                                                 \
            ;                                                     \
    } while (0)
#define HARIS_LOG(...) printf(__VA_ARGS__)

static inline void ENTRY_CRITICAL(void) {}
static inline void EXIT_CRITICAL(void) {}

#ifdef __cplusplus
}
#endif

#endif /* __HARIS_COMMON_H__ */
