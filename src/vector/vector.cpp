#include <math.h>

//=========================================================

#include "../../include/vector/vector.hpp" 

//=========================================================

// Works only for 2d
Vector orthogonal_2d_only(const Vector& v)
{
    return Vector {v.y_, -v.x_};
}

//---------------------------------------------------------

Vector operator+ (const Vector& a, const Vector& b)
{
    Vector res = a;
    res += b;
    return res;
}

Vector operator- (const Vector& a, const Vector& b)
{
    Vector res = a;
    res -= b;
    return res;
}

Vector operator* (const Vector& v, const double mul)
{
    return Vector {v.x_ * mul, v.y_ * mul, v.z_ * mul};
}

Vector operator* (const double mul, const Vector& v)
{
    return Vector {v.x_ * mul, v.y_ * mul, v.z_ * mul};
}

double operator* (const Vector& a, const Vector& b)
{
    return a.x_ * b.x_ + a.y_ * b.y_ + a.z_ * b.z_;
}

//---------------------------------------------------------

Vector operator- (const Vector& v)
{
    return Vector{ - v.x_, - v.y_, - v.z_ };
}

//---------------------------------------------------------

void Vector::rotate_z(const double rad_angle)
{
    double sinus  = sin(rad_angle);
    double cosine = cos(rad_angle);

    rotate_z(sinus, cosine);
}

void Vector::rotate_z(const double sin, const double cos)
{
    double x1 = x_;
    double y1 = y_;

    set_x(cos * x1 - sin * y1);
    set_y(sin * x1 + cos * y1);
}

//---------------------------------------------------------

void Vector::rotate_x(const double rad_angle)
{
    double sinus  = sin(rad_angle);
    double cosine = cos(rad_angle);

    rotate_x(sinus, cosine);
}

void Vector::rotate_x(const double sin, const double cos)
{
    double y1 = y_;
    double z1 = z_;

    set_y(cos * y1 - sin * z1);
    set_z(sin * y1 + cos * z1);
}

//---------------------------------------------------------


void Vector::rotate_y(const double rad_angle)
{
    double sinus  = sin(rad_angle);
    double cosine = cos(rad_angle);

    rotate_y(sinus, cosine);
}

void Vector::rotate_y(const double sin, const double cos)
{
    double x1 = x_;
    double z1 = z_;

    set_x(cos * x1 - sin * z1);
    set_z(sin * x1 + cos * z1);
}

//---------------------------------------------------------

void Vector::normalize()
{
    double length = len();
    (*this) *= (1 / length);
}

//---------------------------------------------------------