/**
 ******************************************************************************
 * @author: Hari
 * @date:   20-4-2026
 * @details: State Machine
 ******************************************************************************
 **/

#ifndef __HARIS_FSM_H__
#define __HARIS_FSM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "haris_task.h"

#define FSM(me, init_func)   ((fsm_t*)me)->state = (state_handler)init_func
#define FSM_TRAN(me, target) ((fsm_t*)me)->state = (state_handler)target

typedef void (*state_handler)(haris_msg_t*);

typedef struct {
    state_handler state;
} fsm_t;

extern void fsm_dispatch(fsm_t* me, haris_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __HARIS_FSM_H__ */
