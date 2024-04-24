#include "utils.h"

#include <stdio.h>

void DumpHex16(void* dst, int length)
{
    uint8_t* data = (uint8_t*)dst;
    for (int i = 0; i < length; ++i) {
        printf("%02X ", data[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

/// @brief 内存复制
/// @param dst
/// @param src
/// @param length
void MemoryCopy(void* dst, void const* src, int length)
{
    if (dst == 0 || src == 0) {
        return;
    }
    uint8_t* _dst = (uint8_t*)dst;
    uint8_t* _src = (uint8_t*)src;
    for (int i = 0; i < length; ++i) {
        _dst[i] = _src[i];
    }
}

/// @brief 填充内存
/// @param dst
/// @param value 会被强转成 `uint8_t`
/// @param length
void MemorySet(void* dst, int value, int length)
{
    if (dst == 0) {
        return;
    }
    uint8_t* _dst = (uint8_t*)dst;
    uint8_t _value = (uint8_t)value;
    for (int i = 0; i < length; ++i) {
        _dst[i] = _value;
    }
}

/// @brief 字节序交换
/// @param src 
/// @param length 
void ExchangeByte(void* src, uint32_t length)
{
    if (src == 0) {
        return;
    }
    uint8_t* _src = (uint8_t*)src;
    uint8_t temp;
    uint32_t half_length = length >> 1;
    for (uint32_t i = 0; i < half_length; ++i) {
        temp = _src[i];
        _src[i] = _src[length - 1 - i];
        _src[length - 1 - i] = temp;
    }
}
