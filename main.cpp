#include <iostream>
#include <thread>
#include "Queue.hpp"

void producer(Queue<int>& q) {
    for (int i = 1; i <= 5; ++i) {
        std::cout << "Pushing: " << i << std::endl;
        q.push(i);
    }
}

void consumer(Queue<int>& q) {
    for (int i = 1; i <= 5; ++i) {
        int value = q.pop();
        std::cout << "Popped: " << value << std::endl;
    }
}

int main() {
    Queue<int> queue(2);
    std::thread t1(producer, std::ref(queue));
    std::thread t2(consumer, std::ref(queue));
    t1.join();
    t2.join();
    return 0;
}