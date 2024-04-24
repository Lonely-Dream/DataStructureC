#ifndef _UTILS_H
#define _UTILS_H

#include <stdint.h>

#ifndef NULL
#define NULL ((void *)0)
#endif

#define Min(a,b) \
({ \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a < _b ? _a : _b; \
})

#define Max(a,b) \
({ \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a > _b ? _a : _b; \
})

void DumpHex16(void* dst, int length);

/// @brief 内存复制
/// @param dst
/// @param src
/// @param length
void MemoryCopy(void* dst, void const* src, int length);

/// @brief 填充内存
/// @param dst
/// @param value 会被强转成 `uint8_t`
/// @param length
void MemorySet(void* dst, int value, int length);

/// @brief 字节序交换
/// @param src 
/// @param length 
void ExchangeByte(void* src, uint32_t length);

#endif
