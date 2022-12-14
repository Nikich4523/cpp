#ifndef KNS_VECTOR_H
#define KNS_VECTOR_H

// initializer_list
// shrink_to_fit, можно ли переделать? не перевыделяя память
// clear и pop_back - нужно ли вызвать деструкторы принудительно?
// https://habr.com/ru/post/593803/#comment_23813311
// https://habr.com/ru/post/593803/#comment_23795745
// https://habr.com/ru/post/593803/#comment_23795623

#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <stdexcept>

namespace kns
{
    template <typename T>
    class vector
    {
    public:
        // constructors & destructors
        vector();
        vector(size_t capacity);
        vector(vector<T> &other);
        vector(vector<T> &&other) noexcept;
        vector(const std::initializer_list<T> list);
        ~vector();

        // operators
        vector<T> *operator=(vector<T> &other);
        vector<T> *operator=(vector<T> &&other) noexcept;

        T &operator[](unsigned int ind);
        const T &operator[](unsigned int ind) const;

        // operations
        void push_back(T element);
        void pop_back() noexcept;

        size_t max_size() const noexcept;
        void clear() noexcept;
        void reserve(size_t new_capacity);
        void shrink_to_fit();
        void swap(vector<T> &vec) noexcept;

        // getters
        size_t size() const noexcept;
        size_t capacity() const noexcept;
        bool empty() const noexcept;
        T front() const noexcept;
        T back() const noexcept;

    private:
        std::unique_ptr<T[]> data_;
        size_t size_;
        size_t capacity_;
        float expansion_coefficient_ = 1.2;

    private:
        void reallocate_data_(size_t new_capacity);
        void copy_(std::unique_ptr<T[]> &src, std::unique_ptr<T[]> &dst, size_t src_size);
    };
}

// CONSTRUCTORS & DESTRUCTOR/////
template <typename T>
kns::vector<T>::vector() : vector(0) {}

template <typename T>
kns::vector<T>::vector(size_t capacity) : data_(new T[capacity]), size_(0), capacity_(capacity) {}

template <typename T>
kns::vector<T>::vector(vector<T> &other) : data_(new T[other.size_]), size_(other.size_), capacity_(other.capacity_)
{
    copy_(other.data_, data_, other.size_);
}

template <typename T>
kns::vector<T>::vector(vector<T> &&other) noexcept
    : data_(std::move(other.data_)), size_(std::move(other.size_)), capacity_(std::move(other.capacity_)) {}

template <typename T>
kns::vector<T>::vector(const std::initializer_list<T> list)
    : data_(new T[list.size()]), size_(list.size()), capacity_(size_)
{
    size_t i = 0;
    for (auto element : list)
    {
        data_[i] = element;
        ++i;
    }
}

template <typename T>
kns::vector<T>::~vector() {}

// OPERATORS /////
template <typename T>
kns::vector<T> *kns::vector<T>::operator=(vector<T> &other)
{
    std::unique_ptr<T[]> temp(new T[other.size_]);
    copy_(other.data_, temp, other.size_);
    data_ = std::move(temp);
    size_ = other.size_;
    capacity_ = other.capacity_;
}

template <typename T>
kns::vector<T> *kns::vector<T>::operator=(vector<T> &&other) noexcept
{
    data_ = std::move(other.data_);
    size_ = std::move(other.size_);
    capacity_ = std::move(other.capacity_);
}

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
        reallocate_data_(capacity_ * expansion_coefficient_ + capacity_ + 1);
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

    reallocate_data_(new_capacity);
}

template <typename T>
void kns::vector<T>::shrink_to_fit()
{
    if (size_ == 0 || size_ == capacity_)
        return;

    reallocate_data_(size_);
}

template <typename T>
void kns::vector<T>::swap(vector<T> &vec) noexcept
{
    std::swap(data_, vec.data_);
    std::swap(size_, vec.size_);
    std::swap(capacity_, vec.capacity_);
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
void kns::vector<T>::reallocate_data_(size_t new_capacity)
{
    std::unique_ptr<T[]> new_data(new T[new_capacity]);
    copy_(data_, new_data, size_);
    std::swap(data_, new_data);
    capacity_ = new_capacity;
}

template <typename T>
void kns::vector<T>::copy_(std::unique_ptr<T[]> &src, std::unique_ptr<T[]> &dst, size_t src_size)
{
    for (auto i = 0; i < src_size; ++i)
    {
        dst[i] = src[i];
    }
}

#endif
