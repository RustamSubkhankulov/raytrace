#pragma once 

//---------------------------------------------------------

#include <unistd.h>
#include <assert.h>

#include <initializer_list>
#include <utility>

//=========================================================

namespace MyStd
{

template <class Type,  size_t Num>
class Array
{
    Type data_[Num];

    public:

        /////////// type members ///////////

        typedef       Type        value_type;
        typedef       value_type* pointer;
        typedef const value_type* const_pointer;
        typedef       value_type& reference;
        typedef const value_type& const_reference;
        typedef       value_type* iterator;
        typedef const value_type* const_iterator;
        typedef       size_t      size_type;

        /////////// ctors & dtor ///////////

        Array(std::initializer_list<Type> l)
            {
                size_type l_size = l.size();
                assert(l_size <= Num);

                for (size_type iter = 0; iter < l_size; iter++)
                {
                    data_[iter] = *(l.begin() + iter);
                }
            }

        ~Array() = default;

        Array(const Array&) = default;
        Array(Array&&)      = default;

        Array& operator= (const Array&)  = default;
        Array& operator= (Array&&)       = default;

        ////////// element access //////////

        reference at(size_type pos)
            {
                assert(pos < Num && "array: out of bounds");
                return data_[pos];
            }

        const_reference at(size_type pos) const
            {
                assert(pos < Num && "array: out of bounds");
                return data_[pos];
            }

        reference       operator[] (size_type pos)       { return data_[pos]; }
        const_reference operator[] (size_type pos) const { return data_[pos]; }

        reference       front()       { return data_[0]; }
        const_reference front() const { return data_[0]; }

        reference       back()        { return data_[Num - 1]; }
        const_reference back()  const { return data_[Num - 1]; }

        pointer         data()        { return data_; }
        const_pointer   data()  const { return data_; }

        //////////// operations ////////////

        void fill(const Type& value)
            { 
                for (size_type iter = 0; iter < Num; iter++)
                    data_[iter] = value;
            }

        void swap(Array& that)
            {
                for (size_type iter = 0; iter < Num; iter++)
                {
                    Type temp     = std::move(  that [iter]);
                      that [iter] = std::move((*this)[iter]);
                    (*this)[iter] = std::move(  temp       );
                }
            }

        ///////////// capacity /////////////

        constexpr size_type size() const { return Num; }

        // since we don't have default constuctor, array can not empty
        constexpr bool empty() const noexcept { return false; }

        constexpr size_type max_size() const { return Num; } 

        ///////////// iterators ////////////

        iterator       begin()        { return data_; }
        const_iterator begin()  const { return data_; }
        const_iterator cbegin() const { return data_; }
        
        iterator       end()          { return data_ + Num; }
        const_iterator end()    const { return data_ + Num; }
        const_iterator cend()   const { return data_ + Num; }       
};

//---------------------------------------------------------

template <class Type, size_t Num>
bool operator> (const Array<Type, Num>& a, const Array<Type, Num>& b)
{
    for (typename Array<Type, Num>::size_type iter = 0; iter < Num; iter++)
        if (a[iter] < b[iter])
            return 0;

    return 1;
}

//---------------------------------------------------------

template <class Type, size_t Num>
bool operator>= (const Array<Type, Num>& a, const Array<Type, Num>& b)
{
    return ((a > b) || (a == b));
}

//---------------------------------------------------------

template <class Type, size_t Num>
bool operator<= (const Array<Type, Num>& a, const Array<Type, Num>& b)
{
    return ((a < b) || (a == b));
}

//---------------------------------------------------------

template <class Type, size_t Num>
bool operator< (const Array<Type, Num>& a, const Array<Type, Num>& b)
{
    return !(a > b);
}

//---------------------------------------------------------

template <class Type, size_t Num>
bool operator== (const Array<Type, Num>& a, const Array<Type, Num>& b)
{
    for (typename Array<Type, Num>::size_type iter = 0; iter < Num; iter++)
        if (a[iter] != b[iter])
            return false;

    return true;
}

//---------------------------------------------------------

template <class Type, size_t Num>
bool operator!= (const Array<Type, Num>& a, const Array<Type, Num>& b)
{
    return !(a == b);
}

}; // namespace MyStd