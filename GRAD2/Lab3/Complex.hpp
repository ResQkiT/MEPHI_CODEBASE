#pragma once
#include <concepts>

template <typename T>
concept is_number = requires(T a, T b) {
    a + b;
    a *b;
    a == b;
    a != b;
};
// TODO добавить сопряженность и деление
template <is_number T>
class Complex
{
private:
    T _real;
    T _imaginary;

public:
    Complex(T real, T imaginary) : _real{real}, _imaginary{imaginary} {}

    Complex() : _real{T()}, _imaginary{T()} {}

    ~Complex() = default;
    T get_real()
    {
        return _real;
    }

    T get_imaginary()
    {
        return _imaginary;
    }

    Complex<T> operator+(const Complex<T> &other)
    {
        return Complex<T>(_real + other._real, _imaginary + other._imaginary);
    }
    Complex<T> operator-(const Complex<T> &other)
    {
        return Complex<T>(_real - other._real, _imaginary - other._imaginary);
    }
    Complex<T> &operator+=(const Complex<T> &other)
    {
        _real += other._real;
        _imaginary += other._imaginary;
        return this;
    }
    Complex<T> &operator-=(const Complex<T> &other)
    {
        _real -= other._real;
        _imaginary -= other._imaginary;
        return this;
    }

    Complex<T> operator*(const Complex<T> &other)
    {
        return Complex<T>(_real * other._real - _imaginary * other._imaginary,
                          _real * other._imaginary + other._real * _imaginary);
    }

    bool operator==(const Complex<T> &other)
    {
        return _real == other._real && _imaginary == other._imaginary;
    }

    bool operator!=(const Complex<T> &other)
    {
        return _real != other._real || _imaginary != other._imaginary;
    }
};