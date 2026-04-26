/**
 ******************************************************************************
 * @author: HaiLQ
 * @date:   25/04/2026
 * @details: Dummy System Define Temporary Functions.
 ******************************************************************************
 **/
#ifndef __SYS_CTRL_H__
#define __SYS_CTRL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pch.h"

/* get current 1ms system timer variable */
extern uint32_t sys_ctrl_millis();  // empty

extern uint32_t sys_ctr_get_exception_number();  // empty

#ifdef __cplusplus
}
#endif

#endif  // __SYS_CTRL_H__
