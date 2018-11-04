#ifndef INC_04_MY_VECTOR_H
#define INC_04_MY_VECTOR_H

#include <string>
#include <iostream>
#include <cstdint>
#include <exception>

template<typename T>
class MyVector {
private:
    static const std::size_t BASE_CAPACITY = 10;

    std::size_t mem_capacity;
    std::size_t length;
    T *values;

    void change_capacity(std::size_t new_capacity);

public:
    MyVector();

    MyVector(std::size_t length);

    MyVector(std::size_t length, const T &value);

    MyVector(const MyVector<T> &other);

    MyVector(MyVector<T> &&other);

    inline std::size_t size() const;

    inline std::size_t capacity() const;

    void add(T &value);

    void add(T &&value);

    T &pop();

    T &last();

    const T &last() const;

    T &first();

    const T &first() const;

    void resize(std::size_t new_size);

    T &operator[](std::size_t pos);

    const T &operator[](std::size_t pos) const;

    MyVector<T> &operator=(const MyVector<T> &other);

    MyVector<T> &operator=(MyVector<T> &&other);

    bool operator==(const MyVector<T> &other) const;

    bool operator!=(const MyVector<T> &other) const;

    ~MyVector();
};

template<typename T>
MyVector<T>::MyVector() :
        mem_capacity(BASE_CAPACITY),
        length(0),
        values((T *) malloc(mem_capacity * sizeof(T))) {
}

template<typename T>
MyVector<T>::MyVector(std::size_t len) :
        mem_capacity(len * 2 > BASE_CAPACITY ? len : BASE_CAPACITY),
        length(len),
        values((T *) malloc(mem_capacity * sizeof(T))) {
}

template<typename T>
MyVector<T>::MyVector(std::size_t len, const T &value) :
        mem_capacity(len * 2 > BASE_CAPACITY ? len : BASE_CAPACITY),
        length(len),
        values((T *) malloc(mem_capacity * sizeof(T))) {
    for (std::size_t i = 0; i < size; i++) {
        values[i] = value;
    }
}

template<typename T>
MyVector<T>::MyVector(const MyVector<T> &other) :
        mem_capacity(other.size() * 2 > BASE_CAPACITY ? other.size() : BASE_CAPACITY),
        length(other.size()),
        values((T *) malloc(mem_capacity * sizeof(T))) {
    std::copy(other.values, other.values + size(), values);
}

template<typename T>
MyVector<T>::MyVector(MyVector<T> &&other) :
        values(other.values),
        mem_capacity(other.capacity()),
        length(other.size()) {
    other.values = nullptr;
}

template<typename T>
MyVector<T> &MyVector<T>::operator=(const MyVector<T> &other) {
    delete[] values;
    mem_capacity = other.size() * 2 > BASE_CAPACITY ? other.size() : BASE_CAPACITY;
    length = other.size();
    values = (T *) malloc(capacity() * sizeof(T));
    std::copy(other.values, other.values + size(), values);
}

template<typename T>
MyVector<T> &MyVector<T>::operator=(MyVector<T> &&other) {
    delete[] values;
    mem_capacity = other.capacity();
    length = other.size();
    values = other.values;
    other.values = nullptr;
}

template<typename T>
MyVector<T>::~MyVector() {
    delete[] values;
}

template<typename T>
inline std::size_t MyVector<T>::size() const {
    return length;
}

template<typename T>
inline std::size_t MyVector<T>::capacity() const {
    return mem_capacity;
}

template<typename T>
void MyVector<T>::add(T &value) {
    if (capacity() > size())
        values[length++] = value;
    else {
        change_capacity(mem_capacity * 2);
        values[length++] = value;
    }
}

template<typename T>
void MyVector<T>::add(T &&value) {
    if (capacity() > size())
        values[length++] = value;
    else {
        change_capacity(mem_capacity * 2);
        values[length++] = value;
    }
}

template<typename T>
T &MyVector<T>::pop() {
    length--;
    if (size() < capacity() / 3 && size() >= BASE_CAPACITY / 2) {
        change_capacity(size() * 2);
    }
}

template<typename T>
void MyVector<T>::change_capacity(std::size_t new_capacity) {
    mem_capacity = new_capacity;
    if (new_capacity < size())
        length = new_capacity;

    if (new_capacity == 0) {
        delete[] values;
        values = nullptr;
    } else {
        values = (T *) realloc(values, new_capacity * sizeof(T));
    }
}

template<typename T>
void MyVector<T>::resize(std::size_t new_size) {
    length = new_size;

    if (size() < capacity() / 3) {
        if (size() >= BASE_CAPACITY / 2)
            change_capacity(size() * 2);
        else
            change_capacity(BASE_CAPACITY);
    }
}

template<typename T>
T &MyVector<T>::last() {
    if (size() == 0)
        throw std::out_of_range("");
    return values[size() - 1];
}

template<typename T>
const T &MyVector<T>::last() const {
    if (size() == 0)
        throw std::out_of_range("");
    return values[size() - 1];
}

template<typename T>
T &MyVector<T>::first() {
    if (size() == 0)
        throw std::out_of_range("");
    return values[0];
}

template<typename T>
const T &MyVector<T>::first() const {
    if (size() == 0)
        throw std::out_of_range("");
    return values[0];
}

template<typename T>
T &MyVector<T>::operator[](std::size_t pos) {
    if (pos >= size())
        throw std::out_of_range("");
    return values[pos];
}

template<typename T>
const T &MyVector<T>::operator[](std::size_t pos) const {
    if (pos >= size())
        throw std::out_of_range("");
    return values[pos];
}

template<typename T>
bool MyVector<T>::operator==(const MyVector<T> &other) const {
    if (size() != other.size())
        return false;
    for (int i = 0; i < size(); i++) {
        if (values[i] != other.values[i])
            return false;
    }
    return true;
}

template<typename T>
bool MyVector<T>::operator!=(const MyVector<T> &other) const {
    return this->operator==(other);
}

#endif //INC_04_MY_VECTOR_H
