#include <functional>
#include "../../../GRAD2/Lab2/DynamicArray.h"

template <class T>
class SelectionSorter : public ISorter<T>
{
public:
    void sort(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, std::function<bool(const T&, const T&)> comp = std::less<T>()) override
    {
        for (auto i = begin; i != end; ++i)
        {
            auto min = i;
            for (auto j = i + 1; j != end; ++j)
            {
                if (comp(*j, *min))
                {
                    min = j;
                }
            }
            std::swap(*i, *min);
        }
    }
};