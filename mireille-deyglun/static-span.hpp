#ifndef _MIREILLE_DEYGLUN_STATIC_SPAN_HPP
#define _MIREILLE_DEYGLUN_STATIC_SPAN_HPP

#include <stdlib.h>

#include "static-array.hpp"

template <typename DataT, size_t Size>
class StaticSpan
{
public:
    explicit StaticSpan(DataT * const data) :
        _data {data}
    {
    }

    explicit StaticSpan(StaticArray<DataT, Size>& array) :
        _data {array.data()}
    {
    }

    StaticSpan(const StaticSpan&) = default;
    StaticSpan& operator=(const StaticSpan&) = default;

    DataT *data() const
    {
        return _data;
    }

    size_t size() const
    {
        return Size;
    }

private:
    DataT *_data;
};

#endif // _MIREILLE_DEYGLUN_STATIC_SPAN_HPP
