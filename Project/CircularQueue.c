#include "CircularQueue.h"


void CircularQueueInit(CircularQueue* cq)
{
    cq->head = 0;
    cq->tail = 0;
    cq->size = 0;
}

/// @brief 入队,单个item
/// @param cq 循环队列指针
/// @param item 待入队元素指针
void CircularQueuePush(CircularQueue* cq, CQ_ITEM_TYPE* item)
{
    MemoryCopy(cq->data + cq->tail, item, sizeof(CQ_ITEM_TYPE));
    ++cq->tail;
    cq->tail %= CQ_MAX_SIZE;
    if (cq->tail == cq->head) {
        // if (cq->tail > cq->head) { // 头尾可以重合
            // 环形队列满，头部数据丢弃
        ++cq->head;
        cq->head %= CQ_MAX_SIZE;
    }

    ++cq->size;
    if (cq->size > (CQ_MAX_SIZE - 1)) {
        cq->size = (CQ_MAX_SIZE - 1);
    }
}

/// @brief 入队,多个item
/// @param cq 循环队列指针
/// @param item 待入队元素首地址
/// @param number 待入队元素数量
void CircularQueuePushItems(CircularQueue* cq, CQ_ITEM_TYPE* item, int number)
{
    int offset = 0;
    if (number > CQ_MAX_SIZE) {
        // 入队元素超过队列容量，前offset个元素丢弃
        offset = number - CQ_MAX_SIZE;
        number = CQ_MAX_SIZE;
    }
    CQ_ITEM_TYPE* p = item + offset;

    int first_part_length = CQ_MAX_SIZE - cq->tail;
    if (number <= first_part_length) {
        MemoryCopy(cq->data + cq->tail, p, number * sizeof(CQ_ITEM_TYPE));
        p += number;
    } else {
        MemoryCopy(cq->data + cq->tail, p, first_part_length * sizeof(CQ_ITEM_TYPE));
        p += first_part_length;

        int second_part_length = number - first_part_length;
        MemoryCopy(cq->data, p, second_part_length * sizeof(CQ_ITEM_TYPE));
        p += second_part_length;
    }

    int seq_head = cq->head;
    int seq_tail = cq->tail;
    if (seq_head > seq_tail) {
        // 将循环队列的指针“展开”
        // 0 1 2 3 4 5 6 7
        //   T   H
        // 0 1 2 3 4 5 6 7 8 9 a
        //       H           T
        seq_tail += CQ_MAX_SIZE;
    }

    // 移动指针
    seq_tail += number;
    if (cq->head > cq->tail) {
        // 0 1 2 3 4 5 6 7
        //   T   H
        if (seq_tail >= seq_head) {
            seq_head = seq_tail + 1;
        }
    }
    cq->tail = seq_tail % CQ_MAX_SIZE;
    cq->head = seq_head % CQ_MAX_SIZE;

    cq->size += number;
    if (cq->size > (CQ_MAX_SIZE - 1)) {
        cq->size = (CQ_MAX_SIZE - 1);
    }
}

/// @brief 出队
/// @param cq 循环队列指针
void CircularQueuePop(CircularQueue* cq)
{
    if (cq->size == 0) {
        // 环形队列为空
        return;
    }

    ++cq->head;
    cq->head %= CQ_MAX_SIZE;

    --cq->size;
}

/// @brief 获取环形队列中队首元素指针
/// @param cq 
/// @return 队列为空返回空指针
CQ_ITEM_TYPE* CircularQueueHead(CircularQueue* cq)
{
    if (cq->size == 0) {
        // 环形队列为空
        return NULL;
    }
    return cq->data + cq->head;
}

/// @brief 获取环形队列中队尾元素的指针(cq->tail的前一个位置)
/// @brief cq->tail 永远指向下一个可以存放的位置
/// @param cq 
/// @return 队列为空返回空指针
CQ_ITEM_TYPE* CircularQueueTail(CircularQueue* cq)
{
    if (cq->size == 0) {
        // 环形队列为空
        return NULL;
    }
    int last_item_index = cq->tail;
    if (last_item_index == 0) {
        last_item_index = CQ_MAX_SIZE;
    } else {
        --last_item_index;
    }
    return cq->data + last_item_index;
}

/// @brief 队列是否为空
/// @param cq 
/// @return 
uint8_t CircularQueueEmpty(CircularQueue* cq)
{
    return cq->size == 0;
}
