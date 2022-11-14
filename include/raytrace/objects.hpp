#pragma once 

//=========================================================

#include "../general/general.hpp"
#include "../mystd/vector/vector.hpp"
#include "../colour/colour.hpp"
#include "raytrace.hpp"

//=========================================================

namespace RT // RayTracing
{

class Plane : public Object 
{
    // Ax + By + Cz + D = 0
    
    double a_ = 0;
    double b_ = 0;
    double c_ = 0;
    double d_ = 0;

    Vector pos_{};

    public:

        Plane(const Vector& normal, const Vector& pos):
            a_(normal.x()),
            b_(normal.y()),
            c_(normal.z()),
            d_(-(pos * normal)),
            pos_(pos)
            {}

        Plane           (const Plane& that) = default;
        Plane& operator=(const Plane& that) = default;
        virtual ~Plane()                    = default;

        void set(const Vector& normal, const Vector& pos)
            {
                a_ = normal.x();
                b_ = normal.y();
                c_ = normal.z();
                d_ = -(pos * normal);
                pos_ = pos;
            }

        void move(const Vector& offs)
            {
                pos_ += offs;

                Vector normal = get_normal(pos_);
                d_ = -(pos_ * normal);
            }

        Vector get_pos() const
            {
                return pos_;
            }

        Vector set_pos(const Vector& new_pos)
            {
                Vector prev_pos = pos_;
                pos_ = new_pos;

                Vector normal = get_normal(pos_);
                d_ = -(pos_ * normal);

                return prev_pos;
            }

        virtual Colour get_rgb(const Vector& point, 
                               const Ray& ray,
                               const Object_manager& obj_manager) const = 0;        

        Vector get_normal(const Vector& point) const
            {
                return Vector{a_, b_, c_};
            }

        double a() const { return a_;}
        double b() const { return b_;}
        double c() const { return c_;}
        double d() const { return d_;}

        bool ray_is_crossing(const Ray& ray, Vector* point) const;
};

//---------------------------------------------------------

class Non_trans_plane : public Plane
{
    Material material_{};

    public:

        Non_trans_plane(const Vector& normal, const Vector& pos, 
                                              const Material& material):
            Plane(normal, pos),
            material_(material)
            {}

            Colour get_rgb(const Vector& point, 
                        const Ray& ray,
                        const Object_manager& obj_manager) const override
                {
                    return material_.get_rgb(point, ray, *this, obj_manager);
                }
};

//---------------------------------------------------------

class Plane_light : public Plane
{
    Colour col_{};

    public:

        Plane_light(const Vector& normal, const Vector& pos, const Colour& col):
            Plane(normal, pos),
            col_(col)
            {}

        Plane_light            (const Plane_light& that) = default;
        Plane_light& operator= (const Plane_light& that) = default;
        ~Plane_light()                                   = default;

        Colour get_rgb(const Vector& point,
                          const Ray& ray, 
                          const Object_manager& obj_manager) const
            {
                return col_;
            }
};

//---------------------------------------------------------

class Sphere : public Object
{
    Vector pos_{};

    double rad_;

    public:

        Sphere(const Vector& pos, double rad):
            pos_(pos),
            rad_(rad)
            {}

        Sphere           (const Sphere& that) = default;
        Sphere& operator=(const Sphere& that) = default;
        virtual ~Sphere()                     = default;

        void move(const Vector& offs) override
            {
                pos_ += offs;
            }

        Vector get_pos() const override
            {
                return pos_;
            }

        Vector set_pos(const Vector& pos) override
            {
                Vector ret = pos_;
                pos_ = pos;
                return ret;
            }

        virtual Colour get_rgb(const Vector& point, 
                               const Ray& ray,
                               const Object_manager& obj_manager) const = 0;

        Vector get_normal(const Vector& point) const override
            {
                Vector normal = point - pos_;
                normal.normalize();

                return normal;
            }

        bool ray_is_crossing(const Ray& ray, Vector* point) const override;
        bool ray_cross      (const Ray& ray, Vector* point1, Vector* point2) const;
};

//---------------------------------------------------------

class Non_trans_sphere : public Sphere
{
    Material material_{};

    public:

        Non_trans_sphere(const Vector& pos, double rad, const Material& material):
            Sphere(pos, rad),
            material_(material)
            {}

            Colour get_rgb(const Vector& point, 
                        const Ray& ray,
                        const Object_manager& obj_manager) const override
                {
                    return material_.get_rgb(point, ray, *this, obj_manager);
                }
};

//---------------------------------------------------------

class Sphere_light : public Sphere
{
    Colour col_{};

    public:

        Sphere_light(const Vector& pos, double rad, const Colour& col):
            Sphere(pos, rad),
            col_(col)
            {}

        Sphere_light            (const Sphere_light& that) = default;
        Sphere_light& operator= (const Sphere_light& that) = default;
        ~Sphere_light()                                    = default;

        Colour get_rgb(const Vector& point,
                          const Ray& ray, 
                          const Object_manager& obj_manager) const
            {
                return col_;
            }
};

//---------------------------------------------------------

class Trans_sphere : public Sphere
{
    double ref_ind_ = 1.5;
    Colour col_{255, 255, 255};

    public:

        Trans_sphere(const Vector& pos, double rad, double ref_ind, const Colour& col = Colour{255, 255, 255}):
                Sphere(pos, rad),
                ref_ind_(ref_ind),
                col_(col)
                {}

        Trans_sphere            (const Trans_sphere& that) = default;
        Trans_sphere& operator= (const Trans_sphere& that) = default;
        ~Trans_sphere()                                    = default;

        Colour get_rgb(const Vector& point, 
                    const Ray& ray,
                    const Object_manager& obj_manager) const
            {
                Vector l = point - ray.start_point;
                Vector n = get_normal(point);
                l.normalize();

                double abs_cos_fi = fabs(l * n);
                double random = (double) rand() / (double) (RAND_MAX);

                // if (random * abs_cos_fi < 0.2)
                // {
                //     Vector l1 = reflect_vector(l, n);
                //     Ray reflected_ray{point, l1, ray.ref_num};
                    
                //     return col_ % obj_manager.trace_ray(this, reflected_ray);
                // }
                // else
                {
                    Vector refracted1 = refract_vector(l, n, ref_ind_);
                    Ray refracted_ray1{point, refracted1, ray.ref_num};

                    Vector p{};
                    Vector out_point{};
                    ray_cross(refracted_ray1, &p, &out_point);

                    Vector refracted2 = refract_vector(refracted1, - get_normal(out_point), 1.0 / ref_ind_);
                    Ray refracted_ray2{out_point, refracted2, ray.ref_num};

                    return col_ % obj_manager.trace_ray(this, refracted_ray2);
                }
            }
};

//---------------------------------------------------------

}; // namespace RT