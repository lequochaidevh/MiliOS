/**
 ******************************************************************************
 * @Author: HaiLQ
 * @Date:   23/04/2026
 ******************************************************************************
 **/
#ifndef __HARIS_BUILD_OPTION_H__
#define __HARIS_BUILD_OPTION_H__

#ifdef __cplusplus
extern "C" {
#endif

#define __CORE_PACKETED __attribute__((__packed__))
#define __CORE_WEAK     __attribute__((__weak__))

#define __CORE_MALLOC_CTRL_SIZE 8

#ifdef __cplusplus
}
#endif

#endif  //__HARIS_BUILD_OPTION_H__
