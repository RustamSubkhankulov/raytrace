#include <assert.h>

//---------------------------------------------------------

#include "../../include/graphics/graphics.hpp"

//=========================================================

static const double Sin_45_degree =  sin(45 * M_PI / 180);

static const float Vector_pointer_scale = 0.1; //pointer_len = 1 * 0.1

static const char* Font_def_filename = "fonts/regular.ttf";

//=========================================================

static void div_num_text_init(sf::Text& div_num, sf::Font& font);

//=========================================================

char Grph::enum_key_to_char(Grph::Key key)
{
    if (key >= Key::A && key <= Key::Z)
        return 'A' + (key - Key::A);

    else if (key >= Key::Num0 && key <= Key::Num9)
        return '0' + (key - Key::Num0);

    else
    {
        switch(key)
        {
            case Key::LBracket : return  '('; break; 
            case Key::RBracket : return  ')'; break;
            case Key::Semicolon: return  ';'; break; 
            case Key::Comma    : return  ','; break; 
            case Key::Dot      : return  '.'; break; 
            case Key::Quote    : return '\''; break;
            case Key::Slash    : return  '/'; break;
            case Key::Backslash: return '\\'; break;
            case Key::Tilde    : return  '~'; break;
            case Key::Equal    : return  '='; break;
            case Key::Hyphen   : return  '-'; break;
            case Key::Space    : return  ' '; break;
            case Key::Tab      : return '\t'; break;
            case Key::Add      : return  '+'; break;
            case Key::Sub      : return  '-'; break;
            case Key::Mul      : return  '*'; break;
            case Key::Div      : return  ':'; break;
            default            : return '\a'; break;
        }
    }

    return '\a';
}

//---------------------------------------------------------

bool Grph::enum_key_is_printable(Grph::Key key)
{
    if (key >= Key::A && key <= Key::Num9)
        return true;

    if (key >= Key::LBracket && key <= Key::Space)
        return true;

    if (key == Key::Tab)
        return true;

    if (key >= Key::Add && key <= Key::Div)
        return true;

    return false;
}

//---------------------------------------------------------

bool Grph::Window::is_mouse_button_pressed(Mouse_button mouse_button)
{
    switch (mouse_button)
    {
        case Mouse_button::Left:
            return sf::Mouse::isButtonPressed(sf::Mouse::Left);

        case Mouse_button::Right:
            return sf::Mouse::isButtonPressed(sf::Mouse::Right);

        case Mouse_button::Middle:
            return sf::Mouse::isButtonPressed(sf::Mouse::Middle);
        
        case Mouse_button::Unknown:
            break;

        default:
            return 0;
    }

    return 0;
}

//---------------------------------------------------------

void Grph::Window::draw(Coordsys& coordsys)
{
    Vector x_axis_start{   (double) coordsys.x_min(), 0};
    Vector y_axis_start{0, (double) coordsys.y_min()   };

    Vector_posed x_axis{x_axis_start, Vector{   (double) coordsys.x_max() - coordsys.x_min(), 0}};
    Vector_posed y_axis{y_axis_start, Vector{0, (double) coordsys.y_max() - coordsys.y_min()   }};

    draw(x_axis, coordsys);
    draw(y_axis, coordsys);

    draw_axis_div(coordsys, x_axis, coordsys.x_min());
    draw_axis_div(coordsys, y_axis, coordsys.y_min());
}

//---------------------------------------------------------

void Grph::Window::draw_axis_div(Coordsys& coordsys, Vector_posed& axis, int axis_min)
{
    Vector start = axis.point();
    Vector vec   = axis.vector();

    Vector ort = orthogonal_2d_only(vec);
    ort.normalize();
    ort *= 0.1;

    Vector rad = start - ort;
    Vector_posed div{rad, ort * 2}; // vector for drawing axis division

    Vector tau = axis.vector();  // vector for moving div and num_point
    tau.normalize();

    Vector num_point = rad + ort;    // division number drawing point

    sf::Font font;                
    sf::Text div_num;
    div_num_text_init(div_num, font);

    for (unsigned int iter = 0; iter < axis.len(); iter++, axis_min++)
    {   
        draw_vector_body(div, coordsys); //draw axis division

        std::string str = std::to_string(axis_min);
        div_num.setString(str);

        if (axis_min != 0)                       
            draw_div_number(coordsys, div_num, num_point);

        rad = rad + tau;
        num_point = num_point + tau;
        div.set_point(rad);
    }
}

//---------------------------------------------------------

void Grph::Window::draw(const Vector_posed& vectorp, Coordsys& coordsys)
{
    draw_vector_body(vectorp, coordsys);
    draw_vector_ptr (vectorp, coordsys);
}

//---------------------------------------------------------

void Grph::Window::draw_vector_body(const Vector_posed& vectorp, Coordsys& coordsys)
{
    Vector start = coordsys.convert_coord(vectorp.point());
    Vector end   = coordsys.convert_coord(vectorp.point() + vectorp.vector());

    sf::Vertex line[] = { sf::Vertex(sf::Vector2f(start.x(), start.y()), sf::Color::Black),
                          sf::Vertex(sf::Vector2f(end.  x(), end.  y()), sf::Color::Black) };

    window_.draw(line, 2, sf::Lines);
}

//---------------------------------------------------------

void Grph::Window::draw_vector_ptr (const Vector_posed& vectorp, Coordsys& coordsys)
{
    Vector_posed vec {vectorp.point() + vectorp.vector(), 
                             orthogonal_2d_only(vectorp.vector())};

    vec.rotate_z(-Sin_45_degree, -Sin_45_degree);
    vec.normalize();
    vec *= Vector_pointer_scale;

    draw_vector_body(vec, coordsys);
    vec.rotate_z(1, 0);
    draw_vector_body(vec, coordsys);
}

//---------------------------------------------------------

static void div_num_text_init(sf::Text& div_num, sf::Font& font)
{
    if (!font.loadFromFile(Font_def_filename))
    {
        fprintf(stderr, "Could not load font from file %s \n", Font_def_filename);
    }

    div_num.setFont(font);
    div_num.setCharacterSize(10);
    div_num.setFillColor(sf::Color::Black);

    return;
}

//---------------------------------------------------------

void Grph::Window::draw_div_number(Coordsys& coordsys, sf::Text& div_num, const Vector& num_point)
{
    Vector real_coords = coordsys.convert_coord(num_point);
    div_num.setPosition(real_coords.x(), real_coords.y());

    window_.draw(div_num);
}

//---------------------------------------------------------

Colour Grph::PixelsWindow::get_pixel(const Vector& pxl_pos, unsigned char* alpha)
{
    unsigned x_pos = (unsigned) pxl_pos.x();
    unsigned y_pos = (unsigned) pxl_pos.y();

    return get_pixel(x_pos, y_pos, alpha);
}

//---------------------------------------------------------

Colour Grph::PixelsWindow::get_pixel(unsigned x_pos, unsigned y_pos, unsigned char* alpha)
{
    if (x_pos < x_size_ && y_pos < y_size_)
    {
        unsigned cur_pos = (y_pos * x_size_ + x_pos) * 4;

        unsigned char r = (unsigned char) pixels_[cur_pos    ];
        unsigned char g = (unsigned char) pixels_[cur_pos + 1];
        unsigned char b = (unsigned char) pixels_[cur_pos + 2]; 
        
        if (alpha)
            *alpha = (unsigned char) pixels_[cur_pos + 3];

        return Colour{r, g, b};
    }
    else
    {
        return Colour{};
    }
}

//---------------------------------------------------------

bool Grph::PixelsWindow::set_pixel(const Vector& pxl_pos, const Colour& pxl_val, unsigned char alpha)
{
    unsigned x_pos = (unsigned) pxl_pos.x();
    unsigned y_pos = (unsigned) pxl_pos.y();

    return set_pixel(x_pos, y_pos, pxl_val, alpha);
}

//---------------------------------------------------------

bool Grph::PixelsWindow::set_pixel(unsigned x_pos, unsigned y_pos, const Colour& pxl_val, unsigned char alpha)
{
    if (x_pos < x_size_ && y_pos < y_size_)
    {
        unsigned cur_pos = (y_pos * x_size_ + x_pos) * 4;

        pixels_[cur_pos    ] = (unsigned char) pxl_val.get_r(); 
        pixels_[cur_pos + 1] = (unsigned char) pxl_val.get_g(); 
        pixels_[cur_pos + 2] = (unsigned char) pxl_val.get_b(); 
        pixels_[cur_pos + 3] = alpha;                       // a

        return true;
    }
    else
    {
        return false;
    }
}

