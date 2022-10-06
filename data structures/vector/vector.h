#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

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
        vector() : vector(1) {}

        vector(size_t capacity)
        {
            data_ = operator new[](sizeof(T) * capacity);
            size_ = 0;
            capacity_ = capacity;
        }

        // operators
        T &operator[](int ind)
        {
            return data_[ind];
        }

        const T &operator[](int ind) const
        {
            return data_[ind];
        }

        // operations
        void push_back(T element)
        {
            if (size_ == capacity_)
            {
                capacity_ += capacity_ * 1.2;

                T *new_data = operator new[](sizeof(T));

                for (auto i = 0; i < size_; ++i)
                {
                    new_data[i] = data_[i];
                }

                data_ = new_data;
            }

            data_[size_] = element;
            ++size_;
        }

        void pop_back()
        {
            --size_;
            data_[size_].~T();
        }

        void resize();
        void reserve();
        void clear();
        void reset();
        void shrink_to_fit();
        void swap();

        // getters
        size_t size() const noexcept
        {
            return size_;
        }

        size_t capacity() const noexcept
        {
            return capacity_;
        }

        bool empty() const noexcept
        {
            return !size_;
        }

        T front() const;
        T back() const;

        ~vector()
        {
            delete[] data_;
        }

    private:
        T *data_;
        size_t size_;
        size_t capacity_;
    };
}

#endif
