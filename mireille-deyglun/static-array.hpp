#ifndef _MIREILLE_DEYGLUN_STATIC_ARRAY_HPP
#define _MIREILLE_DEYGLUN_STATIC_ARRAY_HPP

#include <stdlib.h>

template <typename DataT, size_t Size>
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

    size_t size() const
    {
        return Size;
    }

private:
    DataT _data[Size];
};

#endif // _MIREILLE_DEYGLUN_STATIC_ARRAY_HPP
