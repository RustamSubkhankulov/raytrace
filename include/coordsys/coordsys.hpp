#pragma once 

//=========================================================

#include <math.h>

//=========================================================

#include "../vector/vector.hpp"

//=========================================================

class Coordsys
{    
    int x_max_, x_min_, y_max_, y_min_;

    unsigned x_size_, y_size_;

    double x_scale_ = NAN, y_scale_ = NAN; 

    public:

        unsigned x_pos = 0, y_pos = 0;

        Coordsys(int x_max, int x_min, int y_max, int y_min, 
                unsigned x_size, unsigned y_size):
            x_max_(x_max),
            x_min_(x_min),
            y_max_(y_max),
            y_min_(y_min),
            x_size_(x_size),
            y_size_(y_size)
            {}

        ~Coordsys()               = default;
        Coordsys(const Coordsys&) = default;
        Coordsys(Coordsys&&)      = default;

        Coordsys& operator= (const Coordsys&) = default;
        Coordsys& operator= (Coordsys&&)      = default;

        Vector convert_coord        (const Vector& p); 
        Vector reverse_convert_coord(const Vector& p);

        void set_screen_size(unsigned x_size, unsigned y_size)
            {
                x_size_ = x_size;
                y_size_ = y_size;

                x_scale_ = NAN;
                y_scale_ = NAN;
            }

        void set_x_axis(int x_max, int x_min)
            {
                x_max_ = x_max;
                x_min_ = x_min;

                x_scale_ = NAN;
            }

        void set_y_axis(int y_max, int y_min)
            {
                y_max_ = y_max;
                y_min_ = y_min;

                y_scale_ = NAN;
            }

        unsigned x_size() const { return x_size_; }
        unsigned y_size() const { return y_size_; }

        int x_max() const { return x_max_; }
        int x_min() const { return x_min_; }
        int y_max() const { return y_max_; }
        int y_min() const { return y_min_; }

    private:

        void calc_scales();
};