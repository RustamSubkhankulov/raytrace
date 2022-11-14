#pragma once 

//---------------------------------------------------------

#include <unistd.h>
#include <assert.h>
#include <limits.h>

#include <initializer_list>
#include <utility>

#include "../utilities/realloc.hpp"
#include "../exception/exception.hpp"
#include "../../logs/logs.hpp"

//=========================================================

namespace MyStd
{

static const size_t Vector_start_size    = 1;
static const size_t Vector_cap_incr_step = 2;

template <class Type>
class Vector
{
    size_t size_     = 0;
    size_t capacity_ = 0; 
    Type*  data_     = nullptr;

    // error_code err_code = 0;

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

        Vector() 
            {} // empty vector

        ~Vector()
            {
                for (size_type iter = 0; iter < size_; iter++)
                {
                    data_[iter].~Type();
                }

                delete[] (char*) data_;
            }

        explicit Vector(const size_type capacity):
            size_    (0),
            capacity_(0),
            data_    (nullptr)
            {
                if (capacity == 0)
                    return;

                Type* data = (Type*) new char[capacity * sizeof(Type)];

                capacity_ = capacity;
                data_     = data;     
            }

        Vector(const Vector& that):
            size_    (0),
            capacity_(0),
            data_    (nullptr)
            {
                if (that.size_ == 0)
                    return;

                Type* data = (Type*) new char[that.size_ * sizeof(Type)];

                try_data_copy_ctor(that.size_, data, that.begin());

                size_     = that.size_;
                capacity_ = that.size_;
                data_     = data;
            }

        Vector(Vector&& that):
            size_    (that.size_),
            capacity_(that.capacity_),
            data_    (that.data_)
            {
                that.size_     = 0;
                that.capacity_ = 0;
                that.data_     = nullptr;
            }

        Vector(std::initializer_list<Type> list):
            size_    (0),
            capacity_(0),
            data_    (nullptr)
            {
                size_type list_size = list.size();

                if (list_size == 0)
                    return;

                Type* data = (Type*) new char[list_size * sizeof(Type)];

                try_data_copy_ctor(list_size, data, list.begin());

                size_     = list_size;
                capacity_ = list_size;
                data_     = data;
            }

        ///////// errors and casts /////////

        // operator      bool() const { return err_code; } 

        // bool        is_err() const { return err_code; }

        // error_code get_err() const { return err_code; }

        //////////// assignment ////////////

        Vector& operator= (const Vector& that)
            {
                if (this == &that)
                    return *this;

                if (capacity_ >= that.size_)
                {
                    resize(that.size_);

                    for (size_type iter = 0; iter < size_; iter++)
                    {
                        data_[iter] = that.data_[iter];
                    }
                }
                else
                {
                    for (size_type iter = 0; iter < size_; iter++)
                    {
                        data_[iter].~Type();
                    }

                    delete[] (char*)data_; 

                    size_     = that.size_;
                    capacity_ = that.size_;
                    data_     = (Type*)(new char[capacity_ * sizeof(Type)]);
                
                    for (size_type iter = 0; iter < size_; iter++)
                    {
                        ::new (&data_[iter]) Type(that.data_[iter]);
                    }
                }

                return *this;
            }

        Vector& operator= (Vector&& that)
            {
                if (this == &that)size_     = that.size_;
                capacity_ = that.capacity_;
                    return *this;

                for (size_type iter = 0; iter < size_; iter++)
                {
                    data_[iter].~Type();
                }

                delete[] (char*)data_;

                size_     = that.size_;
                capacity_ = that.capacity_;
                data_     = that.data_;

                that.size_     = 0;
                that.capacity_ = 0;
                that.data_     = nullptr;

                return *this;
            }

        Vector& operator= (std::initializer_list<Type> list)
            {
                size_type list_size = list.size();

                if (capacity_ >= list_size)
                {
                    resize(list_size);

                    for (size_type iter = 0; iter < size_; iter++)
                        data_[iter] = *(list.begin() + iter);
                }
                else
                {
                    for (size_type iter = 0; iter < size_; iter++)
                    {
                        data_[iter].~Type();
                    }

                    delete[] (char*)data_;

                    size_     = list_size;
                    capacity_ = size_;
                    data_     = (Type*)(new char[capacity_ * sizeof(char)]);

                    for (size_type iter = 0; iter < size_; iter++)
                        ::new (&data_[iter]) Type(*(list.begin() + iter));
                }

                return *this;
            }

        void assign(std::initializer_list<Type> list)
            {
                *this = list;
            }

        void assign(size_type count, const Type& value)
            {
                if (capacity_ >= count)
                {
                    resize(count);

                    for (size_type iter = 0; iter < size_; iter++)
                    {
                        data_[iter] = value;
                    }
                }
                else
                {
                    for (size_type iter = 0; iter < size_; iter++)
                    {
                        data_[iter].~Type();
                    }

                    delete[] (char*)data_;

                    size_     = count;
                    capacity_ = size_;
                    data_     = (Type*)(new char[capacity_ * sizeof(char)]);

                    for (size_type iter = 0; iter < size_; iter++)
                        ::new (&data_[iter]) Type(value);
                }
            }

        ////////// element access //////////
        
        reference at(size_type pos)
            {
                if (pos >= size_)
                    throw new EXCP(MYSTD_VECTOR_OUT_BOUNDS, \
                    "out of bounds in at() member function");
                return data_[pos];
            }

        const_reference at(size_type pos) const
            {
                if (pos >= size_)
                    throw new EXCP(MYSTD_VECTOR_OUT_BOUNDS, \
                    "out of bounds in at() member function");
                return data_[pos];
            }

        reference operator[] (size_type pos)       
            { 
                if (pos >= size_)
                    throw new EXCP(MYSTD_VECTOR_OUT_BOUNDS, \
                    "out of bounds in operator[] member function");
                return data_[pos]; 
            }

        const_reference operator[] (size_type pos) const 
            {
                if (pos >= size_)
                    throw new EXCP(MYSTD_VECTOR_OUT_BOUNDS, \
                    "out of bounds in operator[] member function");
                return data_[pos]; 
            }

        reference       front()       { return data_[0]; }
        const_reference front() const { return data_[0]; }

        reference       back()        { return data_[size_ - 1]; }
        const_reference back()  const { return data_[size_ - 1]; }

        pointer         data()        { return data_; }
        const_pointer   data()  const { return data_; }

        ///////////// iterators ////////////

        iterator       begin()        { return data_; }
        const_iterator begin()  const { return data_; }
        const_iterator cbegin() const { return data_; }
        
        iterator       end()          { return data_ + size_; }
        const_iterator end()    const { return data_ + size_; }
        const_iterator cend()   const { return data_ + size_; }  

        /////////////// capacity //////////////

        bool      empty()    const { return (size_ > 0); }
        size_type size()     const { return  size_;      }
        size_type max_size() const { return  SIZE_MAX;   }
        size_type capacity() const { return  capacity_;  }

        void reserve(size_type new_cap)
            {
                if (new_cap <= capacity_)
                    return;

                realloc_vector(new_cap);
            }

        void shrink_to_fit()
            {
                if (size_ == capacity_)
                    return;

                realloc_vector(size_);
            }

        ///////////////// modifiers /////////////////

        void clear()
            {
                for (size_type iter = 0; iter < size_; iter++)
                {
                    data_[iter].~Type();
                }

                size_ = 0;
            }

        iterator insert(const_iterator pos, Type&& value )
            {
                size_type base = pos - begin();
                move_data_right(base, 1);

                if (base < size_)
                    data_[base] = std::move(value);
                else 
                    ::new (&data_[base]) Type(std::move(value));

                size_ ++;
                return &(data_[base]);
            }

        iterator insert(const_iterator pos, const Type& value )
            {
                return insert(pos, 1, value);
            }

        iterator insert(const_iterator pos, size_type count, const Type& value )
            {
                if (count == 0)
                    return (iterator)pos;

                size_type base = pos - begin();
                move_data_right(base, count);

                for (size_type iter = base; iter < base + count; iter++)
                {
                    if (iter < size_)
                        data_[iter] = value;
                    else 
                        ::new (&data_[iter]) Type(value);
                }

                size_ += count;
                return &(data_[base]);
            }

        iterator erase(iterator pos)
            {
                size_type base = pos - begin();
                move_data_left(base, 1); 
                size_--;
                
                if (size_)
                    return &(data_[base]);
                else 
                    return end();
            }

        void push_back(const Type& value)
            {
                if (size_ >= capacity_)
                    increase_vector_capacity();

                ::new (&data_[size_++]) Type(value);
            }

        void push_back(Type&& value)
            {
                if (size_ >= capacity_)
                    increase_vector_capacity();

                ::new (&data_[size_++]) Type(std::move(value));
            }

        void pop_back()
            {
                if (size_ == 0)
                    throw new EXCP(MYSTD_VECTOR_EMPTY_POP, "pop_back() while size is 0");

                data_[size_ - 1].~Type();
                size_--;
            }

        void resize(size_type count, Type value = Type())
            {
                if (size_ == count)
                {
                    return;
                }
                else if (size_ > count)
                {
                    while(size_ > count)
                        pop_back();
                }
                else
                {
                    while(size_ < count)
                        push_back(value);
                }
            }

        void swap(Vector& that)
            {
                size_type temp = size_;
                size_          = that.size_;
                that.size_     = temp;

                temp           = capacity_;
                capacity_      = that.capacity_;
                that.capacity_ = temp;

                Type* data_temp = data_;
                data_             = that.data_;
                that.data_        = data_temp;
            }

        private:

            void increase_vector_capacity()
                {
                    realloc_vector((capacity_ == 0)  ? 
                                    Vector_start_size:
                                    capacity_ * Vector_cap_incr_step);
                }

            void realloc_vector(size_type new_cap)
                {
                    assert(new_cap >= size_);

                    Type* new_data = MyStd::emplc_synt_realloc<Type>(data_, capacity_, new_cap);

                    data_     = new_data;
                    capacity_ = new_cap;
                }

            void move_data_right(size_type base, size_type offset)
                {
                    while (capacity_ - size_ < offset)
                        increase_vector_capacity();

                    int iter     = (int)size_ - 1;
                    int offset_i = (int)offset;
                    int   size_i = (int)size_;  

                    for (; (iter >= (int)base) && (iter >= (size_i - offset_i)); iter--)
                    {
                        ::new (&data_[iter + offset_i]) Type(std::move(data_[iter]));
                    }
                    
                    for (; iter >= (int)base; iter--)
                    {
                        data_[iter + offset_i] = std::move(data_[iter]);
                    }
                }

            void move_data_left(size_type base, size_type offset)
                {
                    assert(offset - 1 <= base);

                    if (size_ == 0) return;

                    for (int iter = base; iter < size_ - offset; iter++)
                    {
                        data_[iter] = std::move(data_[iter + offset]);
                    }

                    int ind = size_ - offset;
                    for (int iter = 0; iter < offset; iter++)
                    {
                        data_[iter + ind].~Type();
                    }
                }

            void try_data_copy_ctor(size_type size, Type* data, const Type* src)
                {
                    for (size_type iter = 0; iter < size; iter++)
                    {
                        try 
                        {
                            ::new (&data[iter]) Type(*(src + iter));
                        }
                        catch(...)
                        {
                            while (true)
                            {
                                if (iter == 0)
                                    break;
                                
                                iter--;
                                data[iter].~Type();
                            }

                            delete[] (char*) data;
                            throw;
                        }
                    }
                }
};

//---------------------------------------------------------

template <class Type>
bool operator== (const Vector<Type>& a, const Vector<Type>& b)
{
    size_t a_num = a.size() - 1;
    size_t b_num = b.size() - 1;

    typename Vector<Type>::size_type iter = 0;

    for (iter = 0; (iter < a_num) && (iter < b_num); iter++)
    {
        if (a[iter] != b[iter])
            break;
    }

    return !!(a[iter] - b[iter]);
}

//---------------------------------------------------------

template <class Type>
bool operator!= (const Vector<Type>& a, const Vector<Type>& b)
{
    return !(a == b);
}

//---------------------------------------------------------

template <class Type>
bool operator> (const Vector<Type>& a, const Vector<Type>& b)
{
    size_t a_num = a.size() - 1;
    size_t b_num = b.size() - 1;

    typename Vector<Type>::size_type iter = 0;

    for (iter = 0; (iter < a_num) && (iter < b_num); iter++)
    {
        if (a[iter] != b[iter])
            break;
    }

    if (a[iter] - b [iter] > 0)
        return true;
    else
        return false;
}

//---------------------------------------------------------

template <class Type>
bool operator< (const Vector<Type>& a, const Vector<Type>& b)
{
    return !(a > b);
}

//---------------------------------------------------------

template <class Type>
bool operator<= (const Vector<Type>& a, const Vector<Type>& b)
{
    return ((a < b) || (a == b));
}

//---------------------------------------------------------

template <class Type>
bool operator>= (const Vector<Type>& a, const Vector<Type>& b)
{
    return ((a > b) || (a == b));
}

//---------------------------------------------------------

}; // namespace MyStd
