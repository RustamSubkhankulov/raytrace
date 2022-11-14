//=========================================================

#include "../../include/coordsys/coordsys.hpp"

//=========================================================

Vector Coordsys::convert_coord(const Vector& p)
{
    if (isnan(x_scale_) || isnan(y_scale_))
        calc_scales();

    return Vector ((-x_min_ + p.x()) * x_scale_ + x_pos, (y_max_ - p.y()) * y_scale_ + y_pos);
}

//---------------------------------------------------------

Vector Coordsys::reverse_convert_coord(const Vector& p)
{
    if (isnan(x_scale_) || isnan(y_scale_))
        calc_scales();

    return Vector (((p.x() - x_pos) / x_scale_) + x_min_, y_max_ - ((p.y() - y_pos) / y_scale_));
}

//---------------------------------------------------------

void Coordsys::calc_scales()
{
    if (isnan(x_scale_))
        x_scale_ = (double) x_size_ / (x_max_ - x_min_);

    if (isnan(y_scale_))
        y_scale_ = (double) y_size_ / (y_max_ - y_min_);
}

