#ifndef _MIREILLE_DEYGLUN_STATIC_SPAN_HPP
#define _MIREILLE_DEYGLUN_STATIC_SPAN_HPP

#include <stdint.h>

#include "static-array.hpp"

template <typename DataT, uint8_t Size>
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

    uint8_t size() const
    {
        return _size;
    }

private:
    DataT *_data;
    uint8_t _size = Size;
};

#endif // _MIREILLE_DEYGLUN_STATIC_SPAN_HPP
