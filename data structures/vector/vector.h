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
        void pop_back();

        size_t max_size() const noexcept;
        void clear() const noexcept;
        void reserve(size_t new_capacity);
        void reset();
        void shrink_to_fit();
        void swap(); // friend

        // getters
        size_t size() const noexcept;
        size_t capacity() const noexcept;
        bool empty() const noexcept;
        T front() const;
        T back() const;

        ~vector();

    private:
        T *data_;
        size_t size_;
        size_t capacity_;
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
    return data_[ind];
}

template <typename T>
const T &kns::vector<T>::operator[](unsigned int ind) const
{
    return data_[ind];
}

// OPERATIONS /////
template <typename T>
void kns::vector<T>::push_back(T element)
{
    if (size_ == capacity_)
    {
        capacity_ += capacity_ * 1.2;

        T *new_data = operator new[](sizeof(T));

        for (auto i = 0; i < size_; ++i)
        {
            new_data[i] = data_[i];
        }

        delete[] data_;
        data_ = new_data;
    }

    data_[size_] = element;
    ++size_;
}

template <typename T>
void kns::vector<T>::pop_back()
{
    --size_;
}

template <typename T>
size_t kns::vector<T>::max_size() const noexcept
{
    return (pow(2, (sizeof(nullptr) * 8))) / sizeof(T) - 1;
}

template <typename T>
void kns::vector<T>::clear() const noexcept
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

    for (auto i = 0; i < size_; ++i)
    {
        new_data[i] = data_[i];
    }

    delete[] data_;
    data_ = new_data;
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

#endif
