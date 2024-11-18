#pragma once

#include <functional>
#include "../../../GRAD2/Lab2/DynamicArray.h"
#include <map>

template <class T> requires std::is_arithmetic<T>::value
class CountingSorter : public ISorter<T>
{
public:
    void sort(ISorter<T>::Iterator begin, ISorter<T>::Iterator end, ISorter<T>::Comparator comp = std::less<T>()) override
    {
        std::map<T, int> freq;
        for (auto i = begin; i != end; ++i)
        {
            freq[*i]++;
        }
        auto current = begin;

        if(comp(0, 1)) 
        {
            for(auto current_pair = freq.begin(); current_pair != freq.end(); ++current_pair)
            {
                for (int i = 0; i < current_pair->second; ++i)
                {
                    *current = current_pair->first;
                    ++current;
                }
            }
        }
        else
        {
            for(auto current_pair = freq.rbegin(); current_pair != freq.rend(); ++current_pair)
            {
                for (int i = 0; i < current_pair->second; ++i)
                {
                    *current = current_pair->first;
                    ++current;
                }
            }
        }
    }
};