#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "CircularQueue.h"


void DumpHex16CircularQueue(CircularQueue* cq)
{
    printf("[H:%d] [T:%d]\n", cq->head, cq->tail);
    for (int i = 0; i < cq->size; ++i) {
        printf("%02X ", cq->data[(cq->head + i) % CQ_MAX_SIZE]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void CalcSize(CircularQueue* cq)
{
    int seq_tail = cq->tail;
    if (cq->head > seq_tail) {
        seq_tail += CQ_MAX_SIZE;
    }
    cq->size = seq_tail - cq->head;
}

int main()
{
    {
        // 初始化
        CircularQueue cq = {
            .data = {0x01,0x02,0x03,0x04,0x00,0x00,0x00,0x00},
            .head = 2,
            .tail = 0 };
        CalcSize(&cq);
        // 操作
        CircularQueuePop(&cq);
        // 期望
        CircularQueue expect = {
            .data = {0x01,0x02,0x03,0x04,0x00,0x00,0x00,0x00},
            .head = 3,
            .tail = 0 };
        CalcSize(&expect);

        // 检查
        if (memcmp(&cq, &expect, sizeof(cq))) {
            fprintf(stderr, "ERROR line:%d\n", __LINE__);
            DumpHex16CircularQueue(&expect);
            DumpHex16CircularQueue(&cq);
        }
    }

    {
        // 测试入队超出队列缓冲区的元素

        // 初始化
        CircularQueue cq = {
            .data = {0x01,0x02,0x03,0x04,0x00,0x00,0x00,0x00},
            .head = 2,
            .tail = 0 };
        CalcSize(&cq);
        // 操作
        // Push 16个 80 81 82 83 84 85 86 87 88 89 8A 8B 8C 8D 8E 8F 
        CQ_ITEM_TYPE data[16] = { 0 };
        for (int i = 0; i < 16; ++i) {
            data[i] = 0x80 | i;
        }
        CircularQueuePushItems(&cq, data, sizeof(data));

        // 期望
        CircularQueue expect = {
            .data = {0x88, 0x89, 0x8A, 0x8B , 0x8C , 0x8D , 0x8E , 0x8F},
            .head = 1,
            .tail = 0 };
        CalcSize(&expect);

        // 检查
        if (memcmp(&cq, &expect, sizeof(cq))) {
            fprintf(stderr, "ERROR line:%d\n", __LINE__);
            DumpHex16CircularQueue(&expect);
            DumpHex16CircularQueue(&cq);
        }
    }

    {
        // 测试多元素入队

        // 初始化
        CircularQueue cq = {
            .data = {0x01,0x02,0x03,0x04,0x00,0x00,0x00,0x00},
            .head = 1,
            .tail = 3 };
        CalcSize(&cq);
        // 操作
        // Push 4个 80 81 82 83 84 
        CQ_ITEM_TYPE data[4] = { 0 };
        for (int i = 0; i < 4; ++i) {
            data[i] = 0x80 | i;
        }
        CircularQueuePushItems(&cq, data, sizeof(data));

        // 期望
        CircularQueue expect = {
            .data = {0x01,0x02,0x03,0x80,0x81,0x82,0x83,0x00},
            .head = 1,
            .tail = 7 };
        CalcSize(&expect);

        // 检查
        if (memcmp(&cq, &expect, sizeof(cq))) {
            fprintf(stderr, "ERROR line:%d\n", __LINE__);
            DumpHex16CircularQueue(&expect);
            DumpHex16CircularQueue(&cq);
        }
    }

    {
        // 测试空队列进行出队操作

        // 初始化
        CircularQueue cq = {
            .data = {0x01,0x02,0x03,0x04,0x00,0x00,0x00,0x00},
            .head = 0,
            .tail = 0 };
        CalcSize(&cq);
        // 操作
        CircularQueuePop(&cq);

        // 期望
        CircularQueue expect = {
            .data = {0x01,0x02,0x03,0x04,0x00,0x00,0x00,0x00},
            .head = 0,
            .tail = 0 };
        CalcSize(&expect);

        // 检查
        if (memcmp(&cq, &expect, sizeof(cq))) {
            fprintf(stderr, "ERROR line:%d\n", __LINE__);
            DumpHex16CircularQueue(&expect);
            DumpHex16CircularQueue(&cq);
        }
    }

    return 0;
}
