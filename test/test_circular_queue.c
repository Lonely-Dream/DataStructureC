#include "../circular_queue/circular_queue.h"
#include <assert.h>
#include <stdio.h>

void test_init() {
    CircularQueue cq;
    CircularQueueInit(&cq);
    assert(CircularQueueIsEmpty(&cq));
    assert(!CircularQueueIsFull(&cq));
    assert(CircularQueueLength(&cq) == 0);
    printf("test_init passed.\n");
}

void test_empty_operations() {
    CircularQueue cq;
    CircularQueueInit(&cq);
    // assert(CircularQueuePop(&cq), "Pop on empty queue failed."); 
    assert(CircularQueueHead(&cq) == NULL);
    assert(CircularQueueTail(&cq) == NULL);
    printf("test_empty_operations passed.\n");
}

void test_push_pop() {
    CircularQueue cq;
    CircularQueueInit(&cq);

    for (int i = 0; i < 10; ++i) {
        CircularQueuePush(&cq, &i);
        assert(CircularQueueLength(&cq) == i + 1);
    }

    for (int i = 0; i < 10; ++i) {
        CQ_ITEM_TYPE* head = CircularQueueHead(&cq);
        assert(head != NULL);
        assert(*head == i);
        CircularQueuePop(&cq);
        assert(CircularQueueLength(&cq) == 9 - i);
    }

    assert(CircularQueueIsEmpty(&cq));
    printf("test_push_pop passed.\n");
}

void test_wraparound() {
    CircularQueue cq;
    CircularQueueInit(&cq);

    for (int i = 0; i < CQ_MAX_SIZE; ++i) {
        CircularQueuePush(&cq, &i);
    }
    assert(CircularQueueIsFull(&cq));
    assert(CircularQueueLength(&cq) == CQ_MAX_SIZE-1);

    int next = 42;
    CircularQueuePush(&cq, &next);
    assert(CircularQueueLength(&cq) == CQ_MAX_SIZE-1);
    assert(*CircularQueueHead(&cq) == 2);

    printf("test_wraparound passed.\n");
}

void test_length() {
    CircularQueue cq;
    CircularQueueInit(&cq);

    assert(CircularQueueLength(&cq) == 0);

    for (int i = 0; i < 100; ++i) {
        CircularQueuePush(&cq, &i);
        assert(CircularQueueLength(&cq) <= CQ_MAX_SIZE);
    }

    printf("test_length passed.\n");
}

int main() {
    test_init();
    test_empty_operations();
    test_push_pop();
    test_wraparound();
    test_length();
    printf("All tests passed.\n");
    return 0;
}
