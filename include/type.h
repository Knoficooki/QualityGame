/*
* 
* MADE BY: Noffie
* 
* Noffie: Jann Christoph Hoffmann (m | 03.05.2007)
* 
* LICENCE: MIT LICENCE
* 
*/

#ifndef TYPE_H
#define TYPE_H

#pragma once
#include <stdint.h>

typedef uintmax_t   umax_t;
typedef uint64_t    u64;
typedef uint32_t    u32;
typedef uint16_t    u16;
typedef uint8_t     u8;
typedef intmax_t    smax_t;
typedef int64_t     s64;
typedef int32_t     s32;
typedef int16_t     s16;
typedef int8_t      s8;
typedef float       f32;

#ifndef _MAX_TYPES_DEFINED
#define _MAX_TYPES_DEFINED
typedef umax_t      umax;
typedef smax_t      smax;
#endif // _MAX_TYPES_DEFINED

#if defined(__cplusplus)
    typedef double      f64;
    #define scast(var, type) static_cast<type>(var)
#else 
    #define scast(var, type) ((type)var)
#endif
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

#if defined(USE_128BIT_INT)
    typedef __uint128_t u128;
    #if !defined(DONT_USE_128BIT_INT_AS_MAX)
        typedef u128 umax_t;
    #endif
#endif

#endif // !TYPE_H
