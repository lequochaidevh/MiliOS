/**
 ******************************************************************************
 * @author: HaiLQ
 * @date:   26/04/2026
 * @details: Hardware Apstraction Layer Interface
 ******************************************************************************
 **/

#ifndef __HAL_DEVICE_INTERFACE_H__
#define __HAL_DEVICE_INTERFACE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pch.h"

/*****************************************************************************
 * DEFINITION: Build Hardware Apstraction with C type
 *
 *****************************************************************************/

enum {  // Active builtin driver
    DEVICE_STATUS_DISABLE,
    DEVICE_STATUS_ENABLE,  // builtin and runtime detect
    DEVICE_STATUS_OK,
    DEVICE_STATUS_ADD_ON
};

// Alias
typedef int (*pf_device_init)(void* private_data);
typedef void (*pf_device_process)(void* private_data);
typedef bool (*pf_device_set_active)(void* private_data, int status);
typedef void (*pf_device_deinit)(void* private_data);

typedef struct {
    pf_device_init const       init_fn;
    pf_device_process const    process_fn;
    pf_device_set_active const set_active_fn;
    pf_device_deinit const     deinit_fn;
} device_ops_t;

typedef struct {
    int8_t major;
    int8_t minor;
} dev_id_t;

typedef struct {
    const char*         name;
    dev_id_t            id;
    int                 status;
    const device_ops_t* ops;
    void*               private_data;
} device_t;

#ifdef __cplusplus
}
#endif

#endif  // __HAL_DEVICE_INTERFACE_H__