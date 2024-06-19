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

    /// @brief map(): list<_From> -> list<_To>
    /// @param function(): _From -> _To
    virtual void map(std::function<_To(_From)> function) = 0;

    /// @brief where(): list<_From> -> list<bool>
    /// @param function(): _From -> bool
    virtual void where(std::function<bool(_From)> function) = 0;

    /// @brief reduce(): list<_From> x list<_From> -> list<_From>
    /// @param function(): _From -> _To
    /// @param start_value <From> - start value to reduce function
    virtual _From reduce(std::function<_From(_From, _From)> function) = 0;
};