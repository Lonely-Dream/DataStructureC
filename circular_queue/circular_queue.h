#ifndef CIRCULAR_QUEUE_H_
#define CIRCULAR_QUEUE_H_

#include <stdint.h>
#include <string.h>

// ----------------------------配置信息----------------------------
// #include "your_config.h"

/// @brief 队列最大长度
/// @note 队列最大长度必须是2的整数幂，以便于计算循环索引
#define CQ_MAX_SIZE (1<<10)
// 队列存储的数据类型
// #define CQ_ITEM_TYPE your_data_type
#define CQ_ITEM_TYPE int
// ----------------------------配置信息----------------------------

#if (CQ_MAX_SIZE & (CQ_MAX_SIZE - 1)) != 0
#error "CQ_MAX_SIZE must be a power of 2!"
#endif

struct CircularQueue {
    CQ_ITEM_TYPE data[CQ_MAX_SIZE];
    int head;

    /// @brief 队尾指针
    /// @note 永远指向下一个可以存放的位置
    int tail;
};
typedef struct CircularQueue CircularQueue;


/// @brief 初始化队列
/// @param cq 队列指针
static inline void CircularQueueInit(CircularQueue* cq)
{
    cq->head = 0;
    cq->tail = 0;
}

/// @brief 判断队列是否为空
/// @param cq 队列指针
/// @return 1: 空 0: 非空
static inline int CircularQueueIsEmpty(CircularQueue* cq)
{
    return cq->head == cq->tail;
}

/// @brief 判断队列是否已满
/// @param cq 队列指针
/// @return 1: 满 0: 未满
static inline int CircularQueueIsFull(const CircularQueue* cq)
{
    return ((cq->tail + 1) & (CQ_MAX_SIZE - 1)) == cq->head;
}

/// @brief 获取队列长度
/// @param cq 队列指针
/// @return 当前队列中的元素个数
/// @note 由于tail永远指向下一个可以存放的位置，所以实际最大长度为CQ_MAX_SIZE-1
static inline int CircularQueueLength(const CircularQueue* cq)
{
    return (cq->tail - cq->head + CQ_MAX_SIZE) & (CQ_MAX_SIZE - 1);
}

/// @brief 获取队首元素指针
/// @param cq 队列指针
/// @return 队列为空返回空指针
static inline CQ_ITEM_TYPE* CircularQueueHead(CircularQueue* cq)
{
    return CircularQueueIsEmpty(cq) ? NULL : &cq->data[cq->head];
}

/// @brief 获取环形队列中队尾元素的指针(cq->tail的前一个位置)
/// @param cq 
/// @return 队列为空返回空指针
static inline CQ_ITEM_TYPE* CircularQueueTail(CircularQueue* cq)
{
    if (CircularQueueIsEmpty(cq)) {
        return NULL;
    }
    if (cq->tail == 0) {
        return cq->data + CQ_MAX_SIZE - 1;
    }
    return cq->data + cq->tail - 1;
}

/// @brief 入队
/// @param cq 循环队列指针
/// @param item 待入队元素指针
/// @note 如果队列已满，会覆盖队首元素，队列的head位置向后移动一位。
static inline void CircularQueuePush(CircularQueue* cq, const CQ_ITEM_TYPE* item)
{
    if (item == NULL) {
        return;
    }
    memcpy(cq->data + cq->tail, item, sizeof(CQ_ITEM_TYPE));
    cq->tail = (cq->tail + 1) & (CQ_MAX_SIZE - 1);
    if (cq->head == cq->tail) {
        cq->head = (cq->head + 1) & (CQ_MAX_SIZE - 1);
    }
}

/// @brief 入队
/// @param cq 循环队列指针
/// @return 返回指向新插入元素的指针
/// @note 如果队列已满，会覆盖队首元素，队列的head位置向后移动一位。
static inline CQ_ITEM_TYPE* CircularQueuePushByPointer(CircularQueue* cq)
{
    CQ_ITEM_TYPE* p = cq->data + cq->tail;
    cq->tail = (cq->tail + 1) & (CQ_MAX_SIZE - 1);
    if (cq->head == cq->tail) {
        cq->head = (cq->head + 1) & (CQ_MAX_SIZE - 1);
    }
    return p;
}

/// @brief 出队
/// @param cq 
static inline void CircularQueuePop(CircularQueue* cq)
{
    if (CircularQueueIsEmpty(cq)) {
        return;
    }
    cq->head = (cq->head + 1) & (CQ_MAX_SIZE - 1);
}

#endif // ! CIRCULAR_QUEUE_H_
