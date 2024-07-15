#include "JakobsthalSeq.hpp"

template <typename T>
JakobsthalSeq<T>::JakobsthalSeq() : _data(nullptr), _size(0) {}

template <typename T>
JakobsthalSeq<T>::~JakobsthalSeq()
{
    delete[] _data;
}

template <typename T>
JakobsthalSeq<T>::JakobsthalSeq(const JakobsthalSeq &other) : _data(new T[other._size]), _size(other._size)
{
    for (size_t i = 0; i < _size; i++)
    {
        _data[i] = other._data[i];
    }
}

template <typename T>
JakobsthalSeq<T> &JakobsthalSeq<T>::operator=(const JakobsthalSeq &other)
{
    if (this != &other)
    {
        delete[] _data;
        _data = new T[other._size];
        _size = other._size;
        for (size_t i = 0; i < _size; i++)
        {
            _data[i] = other._data[i];
        }
    }
    return *this;
}

