/**
 ******************************************************************************
 * @Author: HaiLQ
 * @Date:   23/04/2026
 ******************************************************************************
 **/
#ifndef __PRINTF_INTERFACE_H__
#define __PRINTF_INTERFACE_H__

#include "xprintf.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HARIS_PRINTF(fmt, ...) xprintf(fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif  //__PRINTF_INTERFACE_H__