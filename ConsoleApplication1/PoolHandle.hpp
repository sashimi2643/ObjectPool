#pragma once

template <typename T>
class ObjectPool;
template <typename T>
class PoolHandle {
    friend class ObjectPool<T>;
private:
    explicit PoolHandle(T* obj, ObjectPool<T>* pool)
        : obj_(obj), pool_(pool) {
    }
public:
    PoolHandle(const PoolHandle&) = delete;
    PoolHandle& operator=(const PoolHandle&) = delete;
    PoolHandle(PoolHandle&& other) noexcept
        : obj_(other.obj_), pool_(other.pool_) {
        other.obj_ = nullptr;
        other.pool_ = nullptr;
    }
    PoolHandle& operator=(PoolHandle&&) = delete;
    ~PoolHandle();
    T* operator->() { return obj_; }
    const T* operator->() const { return obj_; }
    T& operator*() { return *obj_; }
    const T& operator*() const { return *obj_; }
private:
    T* obj_ = nullptr;
    ObjectPool<T>* pool_ = nullptr;
};