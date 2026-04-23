/**
 ******************************************************************************
 * @author: ThanNT
 * @date:   13/08/2016
 * @brief:  Finite state machine.
 ******************************************************************************
 **/

#ifndef __FSM_H__
#define __FSM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "message.h"

#define FSM(me, init_func)   ((fsm_t*)me)->state = (state_handler)init_func
#define FSM_TRAN(me, target) ((fsm_t*)me)->state = (state_handler)target

// (void (*)(core_msg_t*))
typedef void (*state_handler)(core_msg_t* msg);

typedef struct {
    state_handler state;
} fsm_t;

void fsm_dispatch(fsm_t* me, core_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif  //__FSM_H__
