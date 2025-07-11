#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "DynamicArray.h"

template <typename T>
class PriorityQueue {
private:
    struct Node {
        T data;
        int priority;
    };

    DynamicArray<Node> heap;

    void heapifyUp(int index) {
        while (index > 0 && heap[index].priority < heap[(index - 1) / 2].priority) {
            std::swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int n = heap.size();
        while (2 * index + 1 < n) {
            int minIdx = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            if (left < n && heap[left].priority < heap[minIdx].priority)
                minIdx = left;
            if (right < n && heap[right].priority < heap[minIdx].priority)
                minIdx = right;
            if (minIdx == index) break;
            std::swap(heap[index], heap[minIdx]);
            index = minIdx;
        }
    }

public:
    void push(const T& val, int priority) {
        heap.push_back({val, priority});
        heapifyUp(heap.size() - 1);
    }

    T top() const {
        return heap[0].data;
    }

    void pop() {
        int n = heap.size();
        if (n == 0) return;
        heap[0] = heap[n - 1];
        heap.clear(); // You’ll want a remove-last function for better control
        heapifyDown(0);
    }

    bool empty() const {
        return heap.size() == 0;
    }
};

#endif
