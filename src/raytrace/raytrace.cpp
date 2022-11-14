#include <cstdlib>
#include <cmath>
#include <assert.h>

//---------------------------------------------------------

#include "../../include/raytrace/raytrace.hpp"
#include "../../include/general/general.hpp"

//=========================================================

namespace RT // RayTracing
{

Vector random_vector()
{
    Vector random{(double) (rand() - RAND_MAX / 2) / (double) (RAND_MAX / 2), 
                  (double) (rand() - RAND_MAX / 2) / (double) (RAND_MAX / 2), 
                  (double) (rand() - RAND_MAX / 2) / (double) (RAND_MAX / 2)};
    
    random.normalize();
    return random;
}

//---------------------------------------------------------

Vector reflect_vector(const Vector& vector, const Vector& normal)
{
    return (vector - normal * (2 * normal * vector));
}

//---------------------------------------------------------

Vector refract_vector(const Vector& vector, const Vector& normal, double ref_ind)
{
    Vector v = vector;
    v.normalize();

    double cos_fi  = normal * v;
    double sin_fi  = sqrt(1 - cos_fi * cos_fi);

    double sin_psi = sin_fi / ref_ind;
    double cos_psi = sqrt(1 - sin_psi * sin_psi);
    double tan_psi = sin_psi / sqrt(1 - sin_psi * sin_psi);

    v = -v;
    v *= (1 / fabs(cos_fi));

    Vector u = v - normal;
    u.normalize();

    Vector w = tan_psi * (-u);
    return Vector{w - normal};
}

//---------------------------------------------------------

Colour Material::get_rgb(const Vector& point, 
                         const Ray& ray,
                         const Object& self,
                         const Object_manager& obj_manager) const
{
    Vector l    = point - ray.start_point;
    Vector n    = self.get_normal(point);
    Vector refl = reflect_vector(l, n);

    Colour res{0, 0, 0};

    for (unsigned iter = 0; iter < ray_num_; iter++)
    {
        Vector rand = random_vector();
        Vector rand_dir  = rand * (self.get_normal(point) * rand);
        rand_dir.normalize();

        Vector diff = rand_dir - refl;
        Vector dir  = refl + (matte_coeff_ * diff);

        Ray reflected_ray{point, dir, ray.ref_num + 1};
        
        res += (1 / ray_num_) * col_ % obj_manager.trace_ray(&self, reflected_ray);   
    }

    return res;
} 

//---------------------------------------------------------

Colour Object_manager::trace_ray(const Object* self, const Ray& ray) const
{
    if (scene_ptr_ == nullptr)
        return Colour{0, 0, 0};

    if (ray.ref_num == Max_ref)
        return Colour{0, 0, 0};

    Vector point{};

    Object* object = find_object_crossing(ray, self, &point);
    if (object == nullptr)
        return Colour{};
        
    assert(self != object);

    return object->get_rgb(point, ray, *this);
}

//---------------------------------------------------------

// returns index of object in vector of objects in struct Scene
// 'point' - out parameter for crossing point 
// 'point' is the first point on the way of the ray
// if pointer is nullptr, nothing returned 

Object* Object_manager::find_object_crossing(const Ray& ray, const Object* self, Vector* point) const
{
    if (scene_ptr_ == nullptr)
        return nullptr;

    int object_ind = -1;

    Vector closest_point{};
    double closest_dist = 0;

    size_t objects_num = scene_ptr_->objects.size();

    for (size_t iter = 0; iter < objects_num; iter++)
    {
        const Object* cur_object = scene_ptr_->objects[iter];
        
        Vector cur_point{};
        bool is_crossing = false;

        is_crossing = cur_object->ray_is_crossing(ray, &cur_point);

        if (is_crossing == false)
            continue;

        if (cur_object == self)
            continue;

        if (ray.direction * (cur_point - ray.start_point) < 0)
            continue;

        double cur_dist = (cur_point - ray.start_point).len();

        if (object_ind == -1 || cur_dist < closest_dist)
        {
            object_ind    = iter;
            closest_point = cur_point;
            closest_dist  = cur_dist;
        }
    }

    if (object_ind == -1)
        return nullptr;
    
    if (point)
        *point = closest_point;
    
    return scene_ptr_->objects[object_ind]; 
}

}; // namespace RT