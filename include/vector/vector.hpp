#pragma once 

//=========================================================

#include <math.h>

class Vector;

class Vector_posed;

//=========================================================

class Vector
{
    double x_ = 0, y_ = 0, z_ = 0;
    mutable double len_ = NAN;

    public:

        Vector() {}

        Vector(const double x, const double y, const double z = 0):
            x_(x), 
            y_(y),
            z_(z),
            len_( ((!x_) && (!y_) && (!z_))? 0: NAN )
            {}

        ~Vector()             = default;
        Vector(const Vector&) = default; //copy ctor
        Vector(Vector&&)      = default; //move ctor

        Vector& operator= (const Vector&)  = default; //copy assignment
        Vector& operator= (Vector&&)       = default; //move assignment

        void set(const double x, const double y, const double z = 0)
            {
                len_ = ((fabs(x_) == fabs(x)) 
                     && (fabs(y_) == fabs(y))
                     && (fabs(z_) == fabs(z)))? len_: NAN;
                x_ = x; 
                y_ = y;
                z_ = z;
            }

        void set_x(const double x)
            {
                len_ = (fabs(x_) == fabs(x))? len_: NAN;
                x_ = x;
            }

        void set_y(const double y)
            {
                len_ = (fabs(y_) == fabs(y))? len_: NAN;
                y_ = y;
            }

        void set_z(const double z)
            {
                len_ = (fabs(z_) == fabs(z))? len_: NAN;
                z_ = z;
            }

        Vector& operator*= (const double mul)
            {
                set(x_ * mul, y_ * mul, z_ * mul);
                return *this;
            }

        Vector& operator+= (const Vector& v)
            {
                set(x_ + v.x_, y_ + v.y_, z_ + v.z_);
                return *this;
            }

        Vector& operator-= (const Vector& v)
            {
                set(x_ - v.x_, y_ - v.y_, z_ - v.z_);
                return *this;
            }

        double x() const { return x_; }
        double y() const { return y_; }
        double z() const { return z_; }

        double len() const 
            {
                if (!isnan(len_))
                    return len_;

                len_ = sqrt(pow(x_,2) + pow(y_,2) + pow(z_,2));
                return len_;
            }

        void rotate_z(const double rad_angle);
        void rotate_z(const double sin, double cos);

        void rotate_x(const double rad_angle);
        void rotate_x(const double sin, double cos);

        void rotate_y(const double rad_angle);
        void rotate_y(const double sin, double cos);

        void normalize();

        friend Vector orthogonal_2d_only(const Vector& v);

        friend Vector operator- (const Vector& a);
        friend Vector operator+ (const Vector& a,  const Vector& b);   
        friend Vector operator- (const Vector& a,  const Vector& b);  
        friend double operator* (const Vector& a,  const Vector& b);  
        friend Vector operator% (const Vector& a,  const Vector& b);
        friend Vector operator* (const Vector& v,  const double mul);
        friend Vector operator* (const double mul, const Vector& v);
};

//---------------------------------------------------------

class Vector_posed 
{
    Vector point_;
    Vector vector_;

    public:

        Vector_posed():
            point_(),
            vector_()
            {}
        
        Vector_posed(const Vector& r, const Vector& v):
            point_ (r),
            vector_(v)
            {}

        Vector_posed(const Vector_posed&) = default;
        Vector_posed(Vector_posed&&)      = default;

        Vector_posed& operator= (const Vector_posed&)  = default; //copy assignment
        Vector_posed& operator= (Vector_posed&&)       = default; //move assignment

        void set_point(const Vector& r)
            {
                point_ = r;
            }

        void set_vector(const Vector& v)
            {
                vector_ = v;
            }

        void rotate_z(const double rad_angle)
            {
                vector_.rotate_z(rad_angle);
            }

        void rotate_z(const double sin, const double cos)
            {
                vector_.rotate_z(sin, cos);
            }

        Vector vector() const { return vector_; }
        Vector point()  const { return point_;  }

        Vector_posed& operator*= (const double mul)
            {
                vector_ *= mul;
                return *this;
            }
        
        Vector_posed& operator+= (const Vector& v)
            {
                vector_ += v;
                return *this;
            }
        
        Vector_posed operator-()
            {
                return Vector_posed {point_, - vector_};
            }

        double len()
            {
                return vector_.len();
            }

        void normalize()
            {
                vector_.normalize();
            }

        void set_dir(const Vector& dir)
            {
                set_vector(dir - point_);
            }
};

//=========================================================