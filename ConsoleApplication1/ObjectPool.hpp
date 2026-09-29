#pragma once

#include <cstddef>
#include <memory>
#include <stack>
#include <stdexcept>
#include <vector>
#include "PoolHandle.hpp"

template<typename T>
class ObjectPool
{
    friend class PoolHandle<T>;
public:
    explicit ObjectPool(std::size_t capacity) {
        objects_.reserve(capacity);
        for (std::size_t i = 0; i < capacity; ++i) {
            objects_.emplace_back(std::make_unique<T>());
            free_.push(objects_.back().get());
        }
    }
    PoolHandle<T> Acquire() {
        if (free_.emptr()) throw std::runtime_error("ObjectPool is emptr");
        T* obj = free_.top();
        free_.pop();
        return PoolHandle<T>(obj, this);
    }
private:
    void Release(T* obj) { free_.push(obj); }
    std::vector<std::unique_ptr<T>> objects_;
    std::stack<T*> free_;
};
template<typename T>
PoolHandle<T>::~PoolHandle()
{
    if (obj_ != nullptr && pool_ != nullptr) {
        pool_->Release(obj_);
    }
}