#include <gtest/gtest.h>
#include "../include/Queue.hpp"
#include <thread>

TEST(QueueTest, BasicPushPop) {
    Queue<int> q(2);
    q.push(10);
    q.push(20);
    EXPECT_EQ(q.pop(), 10);
    EXPECT_EQ(q.pop(), 20);
}

TEST(QueueTest, PushBlocksUntilPop) {
    Queue<int> q(1);
    q.push(1);

    std::thread t([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        q.pop();
    });

    EXPECT_NO_THROW(q.push(2, 200));
    t.join();
}

TEST(QueueTest, PopBlocksUntilPush) {
    Queue<int> q(1);

    std::thread t([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        q.push(5);
    });

    EXPECT_EQ(q.pop(200), 5);
    t.join();
}

TEST(QueueTest, PushTimeout) {
    Queue<int> q(1);
    q.push(1);
    EXPECT_THROW(q.push(2, 100), std::runtime_error);
}

TEST(QueueTest, PopTimeout) {
    Queue<int> q(1);
    EXPECT_THROW(q.pop(100), std::runtime_error);
}