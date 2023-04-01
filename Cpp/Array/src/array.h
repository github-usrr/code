#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>

template <typename T>
class Array
{
public:
    explicit Array( size_t size = 0, const T & value = T() )
        : _size(size)
    {
        arr = (_size ? new T[_size] : nullptr);

        for (size_t i = 0; i < _size; i++)
        {
            arr[i] = value;
        }
    }

    Array(const Array<T> & other)
    {
        copy(other);
    }

    Array & operator=(const Array<T> & other)
    {
        delete[] arr;
        copy(other);

        return *this;
    }

    size_t size() const  { return _size; }

    T &       operator[](size_t i)         
    { if (i < _size) return arr[i]; else throw std::out_of_range("Error! Index out of range"); }

    const T & operator[](size_t i) const   
    { if (i < _size) return arr[i]; else throw std::out_of_range("Error! Index out of range"); }

    ~Array()  { delete[] arr; }

private:
    void copy(const Array<T> & other)
    {
        _size = other.size();
        arr = (_size ? new T[_size] : nullptr);

        for (size_t i = 0; i < _size; i++)
        {
            arr[i] = other[i];
        }
    }

    T * arr;
    size_t _size;
};

template <typename T>
std::ostream & operator<<(std::ostream & out, const Array<T> & arr)
{
    for (size_t i = 0; i < arr.size(); i++)  out << arr[i] << ' ';
    return out;
}