#ifndef KNS_VECTOR_H
#define KNS_VECTOR_H

#include <cmath>
#include <cstddef>
#include <stdexcept>

// sizeof(T) вынести в отдельную приватную переменную? или не надо?
// smart pointer
// operator new[] vs new[] & operator delete[] vs delete[]

namespace kns
{
    template <typename T>
    class vector
    {
    public:
        // constructors
        vector();

        vector(size_t capacity);

        // operators
        T &operator[](unsigned int ind);
        const T &operator[](unsigned int ind) const;

        // operations
        void push_back(T element);
        void pop_back() noexcept;

        size_t max_size() const noexcept;
        void clear() noexcept;
        void reserve(size_t new_capacity);
        void reset();
        void resize();
        void shrink_to_fit();
        void swap(); // friend

        // getters
        size_t size() const noexcept;
        size_t capacity() const noexcept;
        bool empty() const noexcept;
        T front() const noexcept;
        T back() const noexcept;

        ~vector();

    private:
        T *data_;
        size_t size_;
        size_t capacity_;
        float expansion_coefficient_ = 1.2;

    private:
        T *copy_(T *src, T *dst, size_t src_size);
    };
}

// CONSTRUCTORS & DESTRUCTOR/////
template <typename T>
kns::vector<T>::vector() : vector(1) {}

template <typename T>
kns::vector<T>::vector(size_t capacity)
{
    data_ = operator new[](sizeof(T) * capacity);
    size_ = 0;
    capacity_ = capacity;
}

template <typename T>
kns::vector<T>::~vector()
{
    delete[] data_;
}

// OPERATORS /////
template <typename T>
T &kns::vector<T>::operator[](unsigned int ind)
{
    if (ind > size_)
        throw(std::length_error("index was outside the bounds of vector"));

    return data_[ind];
}

template <typename T>
const T &kns::vector<T>::operator[](unsigned int ind) const
{
    if (ind > size_)
        throw(std::length_error("index was outside the bounds of vector"));

    return data_[ind];
}

// OPERATIONS /////
template <typename T>
void kns::vector<T>::push_back(T element)
{
    if (size_ == capacity_)
    {
        size_t new_capacity = capacity_ + capacity_ * expansion_coefficient_;

        T *new_data = operator new[](sizeof(T) * new_capacity);
        data_ = copy_(data_, new_data, size_);
        capacity_ = new_capacity;
    }

    data_[size_] = element;
    ++size_;
}

template <typename T>
void kns::vector<T>::pop_back() noexcept
{
    --size_;
}

template <typename T>
size_t kns::vector<T>::max_size() const noexcept
{
    return (pow(2, (sizeof(nullptr) * 8))) / sizeof(T) - 1;
}

template <typename T>
void kns::vector<T>::clear() noexcept
{
    size_ = 0;
}

template <typename T>
void kns::vector<T>::reserve(size_t new_capacity)
{
    if (new_capacity > this->max_size())
        throw(std::length_error("new capacity more than max size"));
    if (new_capacity <= capacity_)
        return;

    T *new_data = operator new[](sizeof(T) * new_capacity);
    data_ = copy_(data_, new_data, size_);
    capacity_ = new_capacity;
}

// GETTERS /////
template <typename T>
size_t kns::vector<T>::size() const noexcept
{
    return size_;
}

template <typename T>
size_t kns::vector<T>::capacity() const noexcept
{
    return capacity_;
}

template <typename T>
bool kns::vector<T>::empty() const noexcept
{
    return !size_;
}

template <typename T>
T kns::vector<T>::front() const noexcept
{
    if (size > 0)
        return data_[0];
}

template <typename T>
T kns::vector<T>::back() const noexcept
{
    if (size > 0)
        return data_[size_ - 1];
}

// PRIVATE /////
template <typename T>
T *kns::vector<T>::copy_(T *src, T *dst, size_t src_size)
{
    for (auto i = 0; i < src_size; ++i)
    {
        dst[i] = src[i];
    }
    delete[] src;
    return dst;
}

#endif
