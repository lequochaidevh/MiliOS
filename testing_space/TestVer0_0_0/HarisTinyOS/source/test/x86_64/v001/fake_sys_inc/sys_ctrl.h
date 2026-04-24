/**
 ******************************************************************************
 * @Author: HaiLQ
 * @Date:   25/04/2026
 ******************************************************************************
 **/
#ifndef __SYS_CTRL_H__
#define __SYS_CTRL_H__

#ifdef __cplusplus
extern "C" {
#endif

/* get current 1ms system timer variable */
extern uint32_t sys_ctrl_millis();

extern uint32_t sys_ctr_get_exception_number();

#ifdef __cplusplus
}
#endif

#endif  // __SYS_CTRL_H__
