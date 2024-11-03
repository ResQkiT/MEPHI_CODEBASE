#include <functional>
#include "../../../GRAD2/Lab2/DynamicArray.h"

template <class T>
class CountingSorter : public ISorter<T>
{
public:
    void sort(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, std::function<bool(const T&, const T&)> comp = std::less<T>()) override
    {
        T max = *begin;
        T min = *begin;
        for (auto i = begin; i != end; ++i)
        {
            if (!comp(*i, max))
            {
                max = *i;
            }
            if (comp(*i, min))
            {
                min = *i;
            }
        }
        DynamicArray<T> count(max - min + 1);
        for (auto i = begin; i != end; ++i)
        {
            count[*i - min]++;
        }
        auto j = begin;
        for (size_t i = 0; i < count.get_size(); i++)
        {
            for (size_t k = 0; k < count[i]; k++)
            {
                *j = i + min;
                ++j;
            }
        }
    }
};