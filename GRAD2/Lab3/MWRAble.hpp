#pragma once
#include <functional>

/// @brief
/// @tparam _From отображаемое множество
/// @tparam _To множество на которое происходит отображение
template <class _From, class _To>
class MWRAble
{
public:
    virtual ~MWRAble() = default;
    virtual void map(std::function<_To(_From)> function) = 0;
    virtual void where(std::function<bool(_From)> function) = 0;
    virtual _From reduce(std::function<_From(_From, _From)> function, _From start_value) = 0;
};