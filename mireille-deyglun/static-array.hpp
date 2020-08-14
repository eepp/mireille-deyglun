#ifndef _MIREILLE_DEYGLUN_STATIC_ARRAY_HPP
#define _MIREILLE_DEYGLUN_STATIC_ARRAY_HPP

#include <stdint.h>

template <typename DataT, uint8_t Size>
class StaticArray
{
public:
    StaticArray() = default;
    StaticArray(const StaticArray&) = default;
    StaticArray& operator=(const StaticArray&) = default;

    DataT *data()
    {
        return _data;
    }

    const DataT *data() const
    {
        return _data;
    }

    uint8_t size() const
    {
        return _size;
    }

private:
    DataT _data[Size];
    uint8_t _size = Size;
};

#endif // _MIREILLE_DEYGLUN_STATIC_ARRAY_HPP
