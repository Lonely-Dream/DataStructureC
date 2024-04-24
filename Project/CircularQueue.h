#ifndef _CIRCULAR_QUEUE_H_
#define _CIRCULAR_QUEUE_H_

#include "utils.h"

// 配置信息

// 队列最大长度
#define CQ_MAX_SIZE (8)
// 队列存储的数据类型
#define CQ_ITEM_TYPE uint8_t


struct CircularQueue {
    CQ_ITEM_TYPE data[CQ_MAX_SIZE];
    int head;
    int tail;
    int size;
};
typedef struct CircularQueue CircularQueue;


void CircularQueueInit(CircularQueue* cq);

/// @brief 入队,单个item
/// @param cq 循环队列指针
/// @param item 待入队元素指针
void CircularQueuePush(CircularQueue* cq, CQ_ITEM_TYPE* item);

/// @brief 入队,多个item
/// @param cq 循环队列指针
/// @param item 待入队元素首地址
/// @param number 待入队元素数量
void CircularQueuePushItems(CircularQueue* cq, CQ_ITEM_TYPE* item, int number);

/// @brief 出队
/// @param cq 循环队列指针
void CircularQueuePop(CircularQueue* cq);

/// @brief 获取环形队列中队首元素指针
/// @param cq 
/// @return 队列为空返回空指针
CQ_ITEM_TYPE* CircularQueueHead(CircularQueue* cq);

/// @brief 获取环形队列中队尾元素的指针(cq->tail的前一个位置)
/// @brief cq->tail 永远指向下一个可以存放的位置
/// @param cq 
/// @return 队列为空返回空指针
CQ_ITEM_TYPE* CircularQueueTail(CircularQueue* cq);

/// @brief 队列是否为空
/// @param cq 
/// @return 
uint8_t CircularQueueEmpty(CircularQueue* cq);

#endif // ! _CIRCULAR_QUEUE_H_

