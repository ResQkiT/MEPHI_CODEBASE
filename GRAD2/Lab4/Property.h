#pragma once
#include <iostream>
#include <functional>
#include <iostream>

template<typename T> 
class Property {
private:
    std::function<const T&()> _getter;
    std::function<const T&(const T&)> _setter;
    T t;
public:
    Property(T data) : t{data} {};
    operator const T& () const {
        if (_getter) return _getter();
        return get();
    }
    const T& operator= (const T& other) {
        if (_setter) return _setter(other);
        return set(other);
    }
    bool operator== (const T& other) const {
        return static_cast<const T&>(*this) == other;
    }
    const T& get() const {
        return t;
    } 
    const T& set(const T& other) {
        return t = other;
    }
};