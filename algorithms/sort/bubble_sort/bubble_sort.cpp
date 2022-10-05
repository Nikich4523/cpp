#include <bubble_sort.h>
#include <vector>

template <typename T>
void bubble_sort(std::vector<T> &vector)
{
    T temp;
    for (auto i = 0; i < vector.sise(); ++i)
    {
        for (auto j = 0; j < vector.size() - 1; ++j)
        {
            if (vector[j] > vector[j + 1])
            {
                temp = vector[j];
                vector[j] = vector[j + 1];
                vector[j] = temp;
            }
        }
    }
}