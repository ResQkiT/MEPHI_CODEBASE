#include <functional>
#include "../../../GRAD2/Lab2/DynamicArray.h"

template <typename T>
class SelectionSorter : public ISorter<T>
{
public:
    void sort(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, std::function<int(T, T)> comp) override
    {
        for (auto i = begin; i != end; ++i)
        {
            auto min = i;
            for (auto j = i + 1; j != end; ++j)
            {
                if (comp(*j, *min) < 0)
                {
                    min = j;
                }
            }
            std::swap(*i, *min);
        }
    }
};