#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>   


template <typename T>
class Vector{
    private:
        T* data;
        size_t _capacity;
        size_t _size;

    public:
        Vector();
        Vector(const Vector& vector);
        Vector(size_t n);
        ~Vector();

        Vector& operator=(const Vector& vector);
        T& operator[](size_t index);

        void push_back(const T& value);
        void pop_back();
        void reserve(size_t newCapacity);
        void resize(size_t newSize);
        void clear();
        size_t getSize() const;
        size_t getCapacity() const;

        bool isEmpty() const {
            return _size == 0;
        }
};

template <typename T>
Vector<T>::Vector() : data(nullptr), _capacity(0), _size(0) {}
template <typename T>
Vector<T>::Vector(const Vector& vector) : _capacity(vector._capacity), _size(vector._size) {
    data = new T[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        data[i] = vector.data[i];
    }
}

template <typename T>
Vector<T>::Vector(size_t n) : _capacity(n), _size(n) {
    data = new T[_capacity];
}

template <typename T>
Vector<T>::~Vector() {
    delete[] data;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& vector) { 
    if (this != &vector) {
        delete[] data;
        _capacity = vector._capacity;
        _size = vector._size;
        data = new T[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            data[i] = vector.data[i];
        }
    }
    return *this;
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    return data[index];
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (_size >= _capacity) {
        reserve(_capacity == 0 ? 1 : _capacity * 2);
    }
    data[_size++] = value;
}

template <typename T>
void Vector<T>::pop_back() {
    if (_size > 0) {
        data[_size - 1].~T();
        --_size;
    }
}

template <typename T>
void Vector<T>::reserve(size_t newCapacity) {
    if (newCapacity > _capacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < _size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        _capacity = newCapacity;
    }
}

template <typename T>
void Vector<T>::resize(size_t newSize) {
    if (newSize > _capacity) {
        reserve(newSize);
    }
    if (newSize > _size) {
        for (size_t i = _size; i < newSize; ++i) {
            data[i] = T();
        }
    }
    _size = newSize;
}

template <typename T>
void Vector<T>::clear() {
    for(size_t i = 0; i < _size; ++i) {
        data[i].~T();
    }
    _size = 0;
}

template <typename T>
size_t Vector<T>::getSize() const {
    return _size;
}

template <typename T>
size_t Vector<T>::getCapacity() const {
    return _capacity;
}

#endif