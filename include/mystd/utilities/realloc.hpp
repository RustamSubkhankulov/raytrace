#pragma once 

//---------------------------------------------------------

#include <algorithm>

//=========================================================

namespace MyStd
{

template <class Type> 
Type* emplc_synt_realloc(Type* old_buf, size_t old_size, size_t new_size)
{
    Type* new_buf = (Type*)(new char[new_size * sizeof(Type)]);

    size_t min_size = std::min(new_size, old_size);

    for (unsigned iter = 0; iter < min_size; iter++)
    {
        new (&new_buf[iter]) Type(old_buf[iter]);
        old_buf[iter].~Type();
    }

    delete[] (char*) old_buf;
    return new_buf;
}

}; // namespace MyStd