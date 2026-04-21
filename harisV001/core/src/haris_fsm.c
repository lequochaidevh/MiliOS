/**
 ******************************************************************************
 * @author: Hari
 * @date:   20-4-2026
 * @details: State Machine
 ******************************************************************************
 **/

#include "haris_fsm.h"

void fsm_dispatch(fsm_t* me, haris_msg_t* msg) { me->state(msg); }
