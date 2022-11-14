
//---------------------------------------------------------

#include "../../include/mystd/vector/vector.hpp"
#include "../../include/graphics/graphics.hpp"
#include "../../include/raytrace/raytrace.hpp"
#include "../../include/raytrace/objects.hpp"
#include "../../include/raytrace/raytrace_conf.hpp"

//=========================================================

// Window & coordsys preferences

static const int Coordsys_x_max = +5;
static const int Coordsys_x_min = -5;
static const int Coordsys_y_max = +5;
static const int Coordsys_y_min = -5;

static const unsigned Coordsys_x_pos = 0;
static const unsigned Coordsys_y_pos = 0;

static const unsigned Wndw_x_size = 1000u;
static const unsigned Wndw_y_size = 1000u;

//---------------------------------------------------------

// static const int Frame_num = 1;

//---------------------------------------------------------

static const double Camera_view_step = 0.5;

static const double Rot_angle_rad = (1 * M_PI / 180);
static const double Rot_angle_sin = sin(Rot_angle_rad);
static const double Rot_angle_cos = cos(Rot_angle_rad);

//---------------------------------------------------------

static const int Key_W = 0;
static const int Key_A = 1;
static const int Key_S = 2;
static const int Key_D = 3;

static const int Key_ArrUp    = 4;
static const int Key_ArrLeft  = 5;
static const int Key_ArrDown  = 6;
static const int Key_ArrRight = 7;

static const int Key_LShift = 8;
static const int Key_LCtrl  = 9;

static const int Control_keys_num = 10;

//=========================================================

static int raytrace_test();

static Vector get_direction(const RT::View& view, const Vector& cur_point);

static void move_view_point(RT::View* view, double forward, double up, double right);

static bool update_scene(RT::View* view, const char keys_pressed[]);

static Colour average_rgb(const Colour& new_col, const Colour& old_col, const int frames_still);

//=========================================================

int main()
{
    return raytrace_test();
}

//---------------------------------------------------------

static int raytrace_test()
{
    Coordsys coordsys{Coordsys_x_max,
                      Coordsys_x_min,
                      Coordsys_y_max,
                      Coordsys_y_min,
                      Wndw_x_size,
                      Wndw_y_size};

    coordsys.x_pos = Coordsys_x_pos;
    coordsys.y_pos = Coordsys_y_pos;

    // Objects
    
    //---------------------------------

    MyStd::Vector<RT::Object*> objects{};

    RT::Non_trans_sphere  metal {Vector{ -5,    0,   0},   3, RT::Material{Colour{123,  57, 204}, 0.4, 1}};
    RT::Non_trans_sphere  matte {Vector{  5, -1.5,   7}, 1.5, RT::Material{Colour{237, 149, 245},   1, 1}};
    RT::Non_trans_sphere  allum {Vector{  2, -1.5,   3}, 1.5, RT::Material{Colour{178, 237, 232}, 0.9, 1}};
    RT::Non_trans_sphere  mirror{Vector{  3, -2.5,  18}, 0.5, RT::Material{Colour{255, 255, 255},   0, 1}};
    RT::Trans_sphere      trans {Vector{ -1,   -2,  15},   1, 1.5};
    RT::Sphere_light      light {Vector{ -3 , -2.2,  15}, 0.8, Colour{139, 247, 160}};

    objects.push_back(&metal);
    objects.push_back(&matte);
    objects.push_back(&allum);
    objects.push_back(&trans);
    objects.push_back(&light);
    objects.push_back(&mirror);
    
    RT::Non_trans_plane bottom{Vector{0, 1, 0}, Vector{  0, -3,   0}, RT::Material{Colour{255, 255, 255},   1, 1}};
    RT::Non_trans_plane left  {Vector{1, 0, 0}, Vector{-10,  0,   0}, RT::Material{Colour{255, 159,  53},   1, 1}};
    RT::Non_trans_plane right {Vector{1, 0, 0}, Vector{+10,  0,   0}, RT::Material{Colour{ 87, 170, 252},   1, 1}};
    RT::Non_trans_plane back  {Vector{0, 0, 1}, Vector{  0,  0, -20}, RT::Material{Colour{202, 214, 222}, 0.5, 1}};
    RT::Plane_light     top   {Vector{0, 1, 0}, Vector{  0, 10,   0}, Colour{255, 255, 255}};
    RT::Non_trans_plane front {Vector{0, 0, 1}, Vector{  0,  0,  51}, RT::Material{Colour{255, 255, 255},   1, 1}};

    objects.push_back(&bottom);
    objects.push_back(&top);
    objects.push_back(&left);
    objects.push_back(&right);
    objects.push_back(&back);
    objects.push_back(&front);

    RT::View view{Vector{0, 0, 50}, Vector{0, 0, -25}, 0, 0};

    // Scene & Object_manager setup
    RT::Scene scene{objects, view};
    RT::Object_manager object_manager{&scene};

    Grph::PixelsWindow window{Wndw_x_size, Wndw_y_size};

    char keys_pressed[Control_keys_num] = { 0 };
    int  frames_still = 0;

    while (window.is_open())
    {
        Grph::Event event;
        while (window.get_event(event))
        {
            if (event.type() == Grph::Event_type::Closed)
                window.close();

            else if (event.type() == Grph::Event_type::KeyPressed)
            {
                Grph::Key key = event.get_key_pressed();

                switch(key)
                {
                    case Grph::Key::W:        keys_pressed[Key_W       ] = 1; break;
                    case Grph::Key::A:        keys_pressed[Key_A       ] = 1; break; 
                    case Grph::Key::S:        keys_pressed[Key_S       ] = 1; break;
                    case Grph::Key::D:        keys_pressed[Key_D       ] = 1; break;
                    case Grph::Key::ArrUp:    keys_pressed[Key_ArrUp   ] = 1; break;
                    case Grph::Key::ArrLeft:  keys_pressed[Key_ArrLeft ] = 1; break;
                    case Grph::Key::ArrDown:  keys_pressed[Key_ArrDown ] = 1; break;
                    case Grph::Key::ArrRight: keys_pressed[Key_ArrRight] = 1; break;
                    case Grph::Key::LShift:   keys_pressed[Key_LShift  ] = 1; break;
                    case Grph::Key::LCtrl:    keys_pressed[Key_LCtrl   ] = 1; break;

                    default: break;
                }
            }

            else if (event.type() == Grph::Event_type::KeyReleased)
            {
                Grph::Key key = event.get_key_pressed();

                switch(key)
                {
                    case Grph::Key::W:        keys_pressed[Key_W       ] = 0; break;
                    case Grph::Key::A:        keys_pressed[Key_A       ] = 0; break; 
                    case Grph::Key::S:        keys_pressed[Key_S       ] = 0; break;
                    case Grph::Key::D:        keys_pressed[Key_D       ] = 0; break;
                    case Grph::Key::ArrUp:    keys_pressed[Key_ArrUp   ] = 0; break;
                    case Grph::Key::ArrLeft:  keys_pressed[Key_ArrLeft ] = 0; break;
                    case Grph::Key::ArrDown:  keys_pressed[Key_ArrDown ] = 0; break;
                    case Grph::Key::ArrRight: keys_pressed[Key_ArrRight] = 0; break;
                    case Grph::Key::LShift:   keys_pressed[Key_LShift  ] = 0; break;
                    case Grph::Key::LCtrl:    keys_pressed[Key_LCtrl   ] = 0; break;
                    
                    default: break;
                }
            }
        }

        bool is_changed = update_scene(&(scene.view), keys_pressed);
        if (is_changed)
            frames_still = 0;

        srand(time(nullptr));

        for (unsigned cur_y_pos = 0; cur_y_pos < Wndw_y_size; cur_y_pos += 1)
        {
            for (unsigned cur_x_pos = 0; cur_x_pos < Wndw_x_size; cur_x_pos += 1)
            {
                Vector cur_point_r{(double)cur_x_pos, (double)cur_y_pos};
                Vector cur_point = coordsys.reverse_convert_coord(cur_point_r);
                cur_point.set_z(0);

                cur_point = scene.view.view_point + scene.view.image_plane_pos + cur_point;

                Vector direction = get_direction(scene.view, cur_point);

                RT::Ray ray{scene.view.view_point, direction, 0};
                Colour cur_point_rgb = 1.2 * object_manager.trace_ray(nullptr, ray);

                Colour prev = window.get_pixel(cur_point_r, nullptr);
                Colour res  = average_rgb(cur_point_rgb, prev, frames_still);

                bool is_set = window.set_pixel(cur_point_r, res, Alpha_default);
                {
                    if (is_set == false)
                    {
                        error_report(PIXEL_ISNT_SET);
                        return PIXEL_ISNT_SET;
                    }
                }
            }
        }
    

        window.pixels_update();
        window.pixels_draw();
        frames_still++;

        window.display();
    }

    return 0;
}

//---------------------------------------------------------

static Colour average_rgb(const Colour& new_col, const Colour& old_col, const int frames_still)
{
    Vector new_v = (Vector) new_col;
    Vector old_v = (Vector) old_col;

    Vector aver = (old_v * frames_still + new_v) * (1.0 / (frames_still + 1.0));
    return Colour{aver};
}

//---------------------------------------------------------

static bool update_scene(RT::View* view, const char keys_pressed[])
{
    assert(view);

    double forward = 0;
    double up      = 0;
    double right   = 0;

    bool is_changed = false;
    
    for (unsigned iter = 0; iter < Control_keys_num; iter++)
        if (keys_pressed[iter])
        {
            is_changed = true;
            break;
        }

    if (keys_pressed[Key_W]) 
        forward += Camera_view_step;

    if (keys_pressed[Key_A]) 
        right   -= Camera_view_step;

    if (keys_pressed[Key_S]) 
        forward -= Camera_view_step;

    if (keys_pressed[Key_D]) 
        right   += Camera_view_step;

    if (keys_pressed[Key_LShift]) 
        up      += Camera_view_step;

    if (keys_pressed[Key_LCtrl]) 
        up      -= Camera_view_step;

    if (keys_pressed[Key_ArrUp]) 
        view->ver_rot += Rot_angle_rad;

    if (keys_pressed[Key_ArrLeft]) 
        view->hor_rot += Rot_angle_rad;

    if (keys_pressed[Key_ArrDown]) 
        view->ver_rot -= Rot_angle_rad;

    if (keys_pressed[Key_ArrRight]) 
        view->hor_rot -= Rot_angle_rad;

    move_view_point(view, forward, up, right);

    return is_changed;
}

//---------------------------------------------------------

static void move_view_point(RT::View* view, double forward, double up, double right)
{
    assert(view);

    Vector offs{right, up, -forward};

    offs.rotate_x(+view->ver_rot);
    offs.rotate_y(-view->hor_rot);

    view->view_point += offs;

    return;
}

//---------------------------------------------------------

static Vector get_direction(const RT::View& view, const Vector& cur_point)
{
    Vector rotatable = cur_point - view.view_point;

    rotatable.rotate_x(+view.ver_rot);
    rotatable.rotate_y(-view.hor_rot);

    return rotatable;
}
