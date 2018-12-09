#pragma once

template<class T>
class Allocator {
private:
    static constexpr size_t max_capacity = 1000000;
public:
    T *allocate(size_t count) {
        return static_cast<T *>(::operator new(count * sizeof(T)));
    }

    void deallocate(T *ptr, size_t count) {
        ::operator delete(ptr);
    }

    template<class... Args>
    void construct(T *ptr, Args &&... args) {
        ::new(ptr) T(std::forward<Args>(args)...);
    }

    void destroy(T *ptr) {
        ptr->~T();
    }

    constexpr size_t max_size() const noexcept {
        return max_capacity;
    }
};

template<class T>
class Iterator {
    T *valueRef;
    bool reversed;
public:

    explicit Iterator(T *ptr, bool reversed = false)
            : valueRef(ptr), reversed(reversed) {}

    void operator=(T *ptr) {
        valueRef = ptr;
    }

    T &operator*() const {
        return *valueRef;
    }

    Iterator operator+(size_t n) const {
        return Iterator(valueRef + n);
    }

    Iterator &operator++() {
        valueRef = valueRef + (reversed ? -1 : 1);
        return *this;
    }

    bool operator==(const Iterator<T> &other) const {
        return valueRef == other.valueRef;
    }

    bool operator!=(const Iterator<T> &other) const {
        return !(*this == other);
    }
};

template<class T>
class Vector {
private:
    static constexpr std::size_t BASE_CAPACITY = 10;

    T *arr;
    size_t size_;
    size_t capacity_;
    Allocator<T> allocator;
public:

    Vector() : arr(nullptr), size_(0), capacity_(0) {}

    Vector(size_t N) :
            size_(N),
            capacity_(2 * size_),
            arr(allocator.allocate(capacity_)) {
        for (auto i = 0; i < size_; i++)
            allocator.construct(arr + i);
    }

    void clear() {
        for (auto i = 0; i < size_; ++i) {
            allocator.destroy(arr + i);
        }
        size_ = 0;
        capacity_ = 0;
    }

    T &operator[](size_t pos) {
        if (pos >= size())
            throw std::out_of_range("");
        return arr[pos];
    }

    size_t size() const {
        return size_;
    }

    bool empty() {
        return (size_ == 0);
    }

    void resize(size_t new_size) {
        if (capacity() < new_size) {
            reserve(2 * new_size);
            for (auto i = size_; i < new_size; i++) {
                allocator.construct(arr + i);
            }
        } else if (size() < new_size) {
            for (auto i = size_; i < new_size; i++)
                allocator.construct(arr + i);
        } else if (size() > new_size) {
            for (auto i = new_size; i < size_; i++)
                allocator.destroy(arr + i);
        }
        size_ = new_size;
    }

    void reserve(size_t new_capacity) {
        if (capacity_ < new_capacity) {
            T *buff = allocator.allocate(new_capacity);
            for (size_t i = 0; i < size_; i++) {
                allocator.construct(buff + i, std::forward<T>(*(arr + i)));
                allocator.destroy(arr + i);
            }
            allocator.deallocate(arr, capacity_);
            capacity_ = new_capacity;
            arr = buff;
        }
    }

    size_t capacity() const {
        return capacity_;
    }

    void pop_back() {
        if (size() == 0)
            throw std::out_of_range("");
        allocator.destroy(arr + size_);
        --size_;
    }

    void push_back(const T &new_el) {
        if (size_ >= capacity_)
            reserve((capacity_ > 0) ? (2 * capacity_) : BASE_CAPACITY);
        allocator.construct(arr + size_, (new_el));
        size_++;
    }

    void push_back(T &&new_el) {
        if (size_ >= capacity_)
            reserve((capacity_ > 0) ? (2 * capacity_) : BASE_CAPACITY);
        allocator.construct(arr + size_, std::move(new_el));
        size_++;
    }

    Iterator<T> begin() {
        return Iterator<T>(arr);
    }

    Iterator<T> end() {
        return Iterator<T>(arr + size_);
    }

    Iterator<T> rbegin() {
        return Iterator<T>(arr + size_ - 1, true);
    }

    Iterator<T> rend() {
        return Iterator<T>(arr - 1, true);
    }

    ~Vector() {
        clear();
        allocator.deallocate(arr, capacity_);
    }
};