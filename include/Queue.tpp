#include <optional>
#include <chrono>

template<typename T>
Queue<T>::Queue(size_t capacity)
    : capacity_(capacity), head_(0), tail_(0), count_(0) {
    data_ = new T[capacity];
}

template<typename T>
Queue<T>::~Queue() {
    delete[] data_;
}

template<typename T>
void Queue<T>::push(const T& item, std::optional<int> timeout_ms) {
    std::unique_lock<std::mutex> lock(mtx_);
    if (timeout_ms) {
        if (!not_full_.wait_for(lock, std::chrono::milliseconds(*timeout_ms),
                                [this] { return count_ < capacity_; }))
            throw std::runtime_error("Timeout on push");
    } else {
        not_full_.wait(lock, [this] { return count_ < capacity_; });
    }

    data_[tail_] = item;
    tail_ = (tail_ + 1) % capacity_;
    ++count_;
    not_empty_.notify_one();
}

template<typename T>
T Queue<T>::pop(std::optional<int> timeout_ms) {
    std::unique_lock<std::mutex> lock(mtx_);
    if (timeout_ms) {
        if (!not_empty_.wait_for(lock, std::chrono::milliseconds(*timeout_ms),
                                 [this] { return count_ > 0; }))
            throw std::runtime_error("Timeout on pop");
    } else {
        not_empty_.wait(lock, [this] { return count_ > 0; });
    }

    T item = data_[head_];
    head_ = (head_ + 1) % capacity_;
    --count_;
    not_full_.notify_one();
    return item;
}

template<typename T>
size_t Queue<T>::size() const {
    std::lock_guard<std::mutex> lock(mtx_);
    return count_;
}