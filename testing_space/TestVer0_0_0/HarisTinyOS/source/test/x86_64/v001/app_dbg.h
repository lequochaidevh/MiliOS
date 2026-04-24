/**
 ******************************************************************************
 * @Author: HaiLQ
 * @Date:   25/04/2026
 ******************************************************************************
 **/
#ifndef __APP_DBG_H__
#define __APP_DBG_H__

#include "xprintf.h"

#define APP_DBG_EN     1
#define APP_PRINT_EN   1
#define LOGIN_PRINT_EN 1
#define APP_DBG_SIG_EN 1

#if defined(APP_DBG_EN)
#define APP_DBG(fmt, ...) xprintf("[APP DBG] " fmt, ##__VA_ARGS__)
#else
#define APP_DBG(fmt, ...)
#endif

#if defined(APP_PRINT_EN)
#define APP_PRINT(fmt, ...) xprintf("[APP PRINT] " fmt, ##__VA_ARGS__)
#else
#define APP_PRINT(fmt, ...)
#endif

#if defined(LOGIN_PRINT_EN)
#define LOGIN_PRINT(fmt, ...) xprintf(fmt, ##__VA_ARGS__)
#else
#define LOGIN_PRINT(fmt, ...)
#endif

#if defined(APP_DBG_SIG_EN)
#define APP_DBG_SIG(fmt, ...) xprintf("[APP DBG SIG] " fmt, ##__VA_ARGS__)
#else
#define APP_DBG_SIG(fmt, ...)
#endif

#endif  //__APP_DBG_H__