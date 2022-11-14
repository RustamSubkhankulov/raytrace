#include "../../include/raytrace/objects.hpp"
#include "../../include/quadratic_equation/quadratic_equation.hpp"

//=========================================================

namespace RT // RayTracing
{

bool Plane::ray_is_crossing(const Ray& ray, Vector* point) const
{
    Vector normal = get_normal(pos_);
    double scalar = normal * ray.direction;

    if (double_is_equal(scalar, 0))
        return false;

    double t = (- d_ - (normal * ray.start_point)) / scalar;

    if (point)
        *point = ray.start_point + t * ray.direction;

    return true;
}

//---------------------------------------------------------

bool Sphere::ray_cross(const Ray& ray, Vector* point1, Vector* point2) const
{
    // (k1^2 + k2^2 + k3^2)t^2 + 2 * (k1w1 + k2w2 + k3w3)t + (w1^2 + w2^2 + w3^2 - R^2) = 0
    
    Vector dir = ray.direction;
    dir.normalize();

    Vector w = ray.start_point - pos_;
    double w_len = w.len();

    double b = 2 * (dir * w);
    double c = w_len * w_len - rad_ * rad_;

    Equation equ{.a = 1, .b = b, .c = c};
    solve_equation(&equ);

    double t1 = 0; // TODO параметр больше нуля
    double t2 = 0;

    if (equ.roots_ct == ONE_ROOT)
    {
        t1 = equ.root1;
    }
    else if (equ.roots_ct == TWO_ROOTS)
    {
        if (equ.root1 < equ.root2)
        {
            t1 = equ.root1;
            t2 = equ.root2;
        }
        else
        {
            t1 = equ.root2;
            t2 = equ.root1;
        }
    }
    else
    {
        return false;
    }

    if (point1 != nullptr)
        *point1 = ray.start_point + t1 * dir;

    if (point2 != nullptr)
        *point2 = ray.start_point + t2 * dir;    

    return true;
}

//---------------------------------------------------------

bool Sphere::ray_is_crossing(const Ray& ray, Vector* point) const
{
    // (k1^2 + k2^2 + k3^2)t^2 + 2 * (k1w1 + k2w2 + k3w3)t + (w1^2 + w2^2 + w3^2 - R^2) = 0
    
    Vector dir = ray.direction;
    dir.normalize();

    Vector w = ray.start_point - pos_;
    double w_len = w.len();

    double b = 2 * (dir * w);
    double c = w_len * w_len - rad_ * rad_;

    Equation equ{.a = 1, .b = b, .c = c};
    solve_equation(&equ);

    double t = 0;

    if (equ.roots_ct == ONE_ROOT)
    {
        t = equ.root1;
    }
    else if (equ.roots_ct == TWO_ROOTS)
    {
        t = (equ.root1 > equ.root2) ? equ.root2 : equ.root1;
    }
    else
    {
        return false;
    }

    if (point != nullptr)
    {
        *point = ray.start_point + t * dir;
    }

    return true;
}

}; // namespace RT