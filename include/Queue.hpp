#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <mutex>
#include <condition_variable>
#include <chrono>
#include <stdexcept>
#include <optional>

/**
 * @brief Thread-safe queue with optional timeout.
 * @tparam T Type of element to store.
 */
template<typename T>
class Queue {
public:
    Queue(size_t capacity);
    ~Queue();

    void push(const T& item, std::optional<int> timeout_ms = std::nullopt);
    T pop(std::optional<int> timeout_ms = std::nullopt);
    size_t size() const;

private:
    size_t capacity_;
    T* data_;
    size_t head_, tail_, count_;
    mutable std::mutex mtx_;
    std::condition_variable not_full_, not_empty_;
};

#include "Queue.tpp"

#endif // QUEUE_HPP