#pragma once 

//=========================================================

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

//---------------------------------------------------------

#include "keys.hpp"
#include "../vector/vector.hpp"
#include "../colour/colour.hpp"
#include "../coordsys/coordsys.hpp"

//=========================================================

namespace Grph
{

enum class Event_type
{
    Closed              = sf::Event::Closed,
    Resized             = sf::Event::Resized,
    KeyPressed          = sf::Event::KeyPressed,
    KeyReleased         = sf::Event::KeyReleased,
    MouseButtonPressed  = sf::Event::MouseButtonPressed,
    MouseButtonReleased = sf::Event::MouseButtonReleased,
    MouseMoved          = sf::Event::MouseMoved,
};

enum class Mouse_button
{
    Left,
    Right,
    Middle,
    Unknown
};

//---------------------------------------------------------

class Window;
class Event;
class Text;
class Texture;

//---------------------------------------------------------

class Texture
{
    sf::Texture texture_{};

    friend class Rectangle;
    friend class Circle;
    friend class Window;

    public:

        Texture():
            texture_()
            {}

        Texture(sf::Texture texture):
            texture_(texture)
            {}

        Texture(const Texture& that):
            texture_(that.texture_)
            {}

        bool create(unsigned w, unsigned h)
            {
                return texture_.create(w, h);
            }

        bool load_from_file(std::string filename)
            {
                return texture_.loadFromFile(filename);
            }

        Vector get_size()
            {
                sf::Vector2u size = texture_.getSize();
                return Vector{(double) size.x, (double) size.y};
            }

        void update(unsigned char* pixels, unsigned w, unsigned h,
                                           unsigned x_offs = 0,
                                           unsigned y_offs = 0)
            {
                texture_.update((const sf::Uint8*)pixels, w, h, x_offs, y_offs);
            }

        void update(const Texture& that)
            {
                texture_.update(that.texture_);
            }

        void update(const Texture& that, const Vector& pos)
            {
                texture_.update(that.texture_, pos.x(), pos.y());
            }

        void set_smooth(bool smooth)
            {
                texture_.setSmooth(smooth);
            }

        bool is_smooth() const
            {
                return texture_.isSmooth();
            }

        void set_repeated(bool repeated)
            {
                texture_.setRepeated(repeated);
            }

        bool is_repeated() const
            {
                return texture_.isRepeated();
            }

        Texture& operator= (const Texture& that)
            {
                texture_ = that.texture_;
                return *this;
            }

        void swap(Texture& that)
            {
                texture_.swap(that.texture_);
            }
};

//---------------------------------------------------------

class Rectangle
{
    sf::RectangleShape rectangle_{};

    friend class Window;

    public:

        Rectangle(const Vector& size = Vector{0, 0}):
            rectangle_(sf::Vector2f(size.x(), size.y()))
            {}

        void set_size(const Vector& size)
            {
                sf::Vector2f sz(size.x(), size.y());
                rectangle_.setSize(sz);
            }

        Vector get_size() const
            {
                sf::Vector2f sz = rectangle_.getSize();
                return Vector{sz.x, sz.y};
            }

        void set_texture(const Texture& texture)
            {
                rectangle_.setTexture(&texture.texture_);    
            }

        void set_fill_color(const Colour& colour)
            {
                rectangle_.setFillColor(sf::Color(colour.get_r(),
                                                colour.get_g(),
                                                colour.get_b()));
            }

        void set_outline_color(const Colour& colour)
            {
                rectangle_.setOutlineColor(sf::Color(colour.get_r(),
                                                    colour.get_g(),
                                                    colour.get_b()));
            }

        void set_outline_thickness(float thickness)
            {
                rectangle_.setOutlineThickness(thickness);
            }

        Texture get_texture() const
            {
                return Texture{*(rectangle_.getTexture())};       
            }

        Colour get_fill_color() const
            {
                sf::Color color = rectangle_.getFillColor();
                return Colour{color.r, color.g, color.b};
            }

        Colour get_outline_color() const
            {
                sf::Color color = rectangle_.getOutlineColor();
                return Colour{color.r, color.g, color.b};
            }

        float get_outline_thickness() const
            {
                return rectangle_.getOutlineThickness();
            }

        void set_position(float x, float y)
            {
                rectangle_.setPosition(x, y);
            }

        void set_position(const Vector& vector)
            {
                rectangle_.setPosition(vector.x(), vector.y());
            }

        void set_rotation(float angle)
            {
                rectangle_.setRotation(angle);
            }

        Vector get_position() const
            {
                sf::Vector2f pos = rectangle_.getPosition();
                return Vector{pos.x, pos.y};
            }

        float get_rotation() const
            {
                return rectangle_.getRotation();
            }

        void move(float x_offs, float y_offs)
            {
                rectangle_.move(x_offs, y_offs);
            }

        void move(const Vector& vector)
            {
                rectangle_.move(vector.x(), vector.y());
            }

        void rotate(float angle)
            {
                rectangle_.rotate(angle);
            }
};

//---------------------------------------------------------

class Circle
{
    sf::CircleShape circle_{};

    friend class Window;

    public:

        Circle(float rad = 0, size_t point_count = 30):
            circle_(rad, point_count)
            {}

        void set_rad(float rad)
            {
                circle_.setRadius(rad);
            }

        float get_rad() const
            {
                return circle_.getRadius();
            }

        void set_point_count(size_t point_count)
            {
                circle_.setPointCount(point_count);
            }

        size_t get_point_count() const
            {
                return (size_t) circle_.getPointCount();
            }

        void set_texture(const Texture& texture)
            {
                circle_.setTexture(&texture.texture_);
            }

        void set_fill_color(const Colour& colour)
            {
                circle_.setFillColor(sf::Color(colour.get_r(),
                                               colour.get_g(),
                                               colour.get_b()));
            }

        void set_outline_color(const Colour& colour)
            {
                circle_.setOutlineColor(sf::Color(colour.get_r(),
                                                  colour.get_g(),
                                                  colour.get_b()));
            }

        void set_outline_thickness(float thickness)
            {
                circle_.setOutlineThickness(thickness);
            }

        Texture get_texture()
            {
                return Texture{*(circle_.getTexture())};
            }

        Colour get_fill_color() const
            {
                sf::Color color = circle_.getFillColor();
                return Colour{color.r, color.g, color.b};
            }

        Colour get_outline_color() const
            {
                sf::Color color = circle_.getOutlineColor();
                return Colour{color.r, color.g, color.b};
            }

        float get_outline_thickness() const
            {
                return circle_.getOutlineThickness();
            }

        void set_position(float x, float y)
            {
                circle_.setPosition(x, y);
            }

        void set_position(const Vector& vector)
            {
                circle_.setPosition(vector.x(), vector.y());
            }

        void set_rotation(float angle)
            {
                circle_.setRotation(angle);
            }

        Vector get_position() const
            {
                sf::Vector2f pos = circle_.getPosition();
                return Vector{pos.x, pos.y};
            }

        float get_rotation() const
            {
                return circle_.getRotation();
            }

        void move(float x_offs, float y_offs)
            {
                circle_.move(x_offs, y_offs);
            }

        void move(const Vector& vector)
            {
                circle_.move(vector.x(), vector.y());
            }

        void rotate(float angle)
            {
                circle_.rotate(angle);
            }
};

//---------------------------------------------------------

class Font
{
    sf::Font font_{};

    friend class Text;

    public:

        Font():
            font_()
            {}

        Font(sf::Font font):
            font_(font)
            {}

        Font(std::string filename):
            font_()
            {
                font_.loadFromFile(filename);
            }

        Font(const Font& that):
            font_(that.font_)
            {}

        Font& operator= (const Font& that)
            {
                font_ = that.font_;
                return *this;
            }

        bool load_from_file(const std::string filename)
            {
                return font_.loadFromFile(filename);
            }
};

//---------------------------------------------------------


class Text
{
    sf::Text text_{};
    sf::Font font_{};

    friend class Window;

    public:

        enum class Style
        {
            Regular        = sf::Text::Style::Regular,
            Bold           = sf::Text::Style::Bold,
            Italic         = sf::Text::Style::Italic,
            Underlined     = sf::Text::Style::Underlined,
            Strike_through = sf::Text::Style::StrikeThrough
        };

        Text():
            text_(),
            font_()
            {}

        Text(const std::string& str, unsigned char_size = 20):
            text_(),
            font_()
            {
                text_.setCharacterSize(char_size);
                text_.setString(str);
            }

        Font get_font() const
            {
                return Font{*text_.getFont()};
            }

        void set_font(const Font& font)
            {
                font_ = font.font_;
                text_.setFont(font_);
            }

        void set_string(const std::string& str)
            {
                text_.setString(str);
            }

        void set_char_size(const unsigned size)
            {
                text_.setCharacterSize(size);
            }

        void set_style(Style style)
            {
                text_.setStyle((sf::Uint32)style);
            }

        void set_fill_color(const Colour& colour)
            {
                sf::Color fill_color(sf::Uint8(colour.get_r()),
                                     sf::Uint8(colour.get_g()),
                                     sf::Uint8(colour.get_b()));
                text_.setFillColor(fill_color);
            }

        void set_outline_color(const Colour& colour)
            {
                sf::Color outl_color(sf::Uint8(colour.get_r()),
                                     sf::Uint8(colour.get_g()),
                                     sf::Uint8(colour.get_b()));
                text_.setOutlineColor(outl_color);
            }

        void set_outline_thickness(float thickness)
            {
                text_.setOutlineThickness(thickness);
            }

        std::string get_string() const
            {
                return std::string(text_.getString());
            }

        unsigned get_char_size() const
            {
                return text_.getCharacterSize();
            }

        Style get_style() const
            {
                return (Style) text_.getStyle();
            }

        Colour get_fill_color() const
            {
                sf::Color color = text_.getFillColor();
                return Colour{color.r, color.g, color.b};
            }

        Colour get_outline_color() const
            {
                sf::Color color = text_.getOutlineColor();
                return Colour{color.r, color.g, color.b};
            }

        float get_outline_thickness() const
            {
                return text_.getOutlineThickness();
            }

        void set_position(const Vector& vector)
            {
                text_.setPosition((float)vector.x(), (float)vector.y());
            }

        Vector get_position() const
            {
                const sf::Vector2f pos = text_.getPosition();
                return Vector{pos.x, pos.y};
            }

        void set_rotation(const float angle)
            {
                text_.setRotation(angle);
            }

        float get_rotation() const
            {
                return text_.getRotation();
            }

        void move(const Vector& vector)
            {
                text_.move((float)vector.x(), (float)vector.y());
            }

        void rotate(float angle)
            {
                text_.rotate(angle);
            }
};

//---------------------------------------------------------


class Event
{
    sf::Event event_{};

    public:

        Event():
            event_()
            {}

        Event_type type(void)
            {
                return (Event_type) event_.type;
            }

        Mouse_button get_mouse_button()
            {
                return (Mouse_button) event_.mouseButton.button;
            }

        Vector get_mouse_click_pos()
            {
                return Vector{(double) event_.mouseButton.x,
                              (double) event_.mouseButton.y};
            }

        Vector get_mouse_mov_pos()
            {
                return Vector{(double) event_.mouseMove.x,
                              (double) event_.mouseMove.y};
            }

        Grph::Key get_key_pressed()
            {
                return (Grph::Key) event_.key.code;
            }

        Grph::Key get_key_released()
            {
                return (Grph::Key) event_.key.code;
            }

    friend class Window;
};

//---------------------------------------------------------

class Window
{
    friend class Texture; 

    protected:

    sf::RenderWindow window_{};

    public:

        enum class Style
        {
            Titlebar = sf::Style::Titlebar,
            Resize   = sf::Style::Resize,
            Close    = sf::Style::Close,
            Default  = (sf::Style::Resize | sf::Style::Close),
        };

        Window():
            window_{}
            {}

        virtual ~Window() {}

        Window(unsigned x_size, unsigned y_size, Style style = Style::Default):
            window_{sf::VideoMode(x_size, y_size), "", (sf::Uint32) style}
            {}

        Window(const Vector& size, Style style = Style::Default):
            window_{sf::VideoMode((unsigned) size.x(), (unsigned) size.y()), "", (sf::Uint32) style}
            {}

        bool is_open()
            {
                return window_.isOpen();
            }

        bool get_event(Event& event)
            {
                return window_.pollEvent(event.event_);
            }

        void clear()
            {
                window_.clear(sf::Color::White);
            }

        void close()
            {
                window_.close();
            }

        void display()
            {
                window_.display();
            }

        Vector get_size() const
            {
                sf::Vector2u size = window_.getSize();
                return Vector {(double) size.x, (double) size.y};
            }

        bool is_mouse_button_pressed(Mouse_button mouse_button);

        Vector get_mouse_pos()
            {
                sf::Vector2i pos = sf::Mouse::getPosition(window_);
                return Vector{(double) pos.x, (double) pos.y};
            }

        void draw(Coordsys& coordsys);
        void draw(const Vector_posed& vectorp, Coordsys& coordsys);

        void draw(const Text& text)
            {
                window_.draw(text.text_);
            }

        void draw(const Rectangle& rectangle)
            {
                window_.draw(rectangle.rectangle_);
            }

        void draw(const Circle circle)
            {
                window_.draw(circle.circle_);
            }

    private:

        //int setup_pxls_array();

        void draw_vector_body(const Vector_posed& vectorp, Coordsys& coordsys);
        void draw_vector_ptr (const Vector_posed& vectorp, Coordsys& coordsys);

        void draw_axis_div  (Coordsys& coordsys, Vector_posed& axis, int axis_min);
        void draw_div_number(Coordsys& coordsys, sf::Text& div_num, const Vector& num_point);
};

//---------------------------------------------------------

class PixelsWindow : public Window
{
    sf::Texture texture_{};
    sf::Sprite  sprite_{};
    sf::Uint8*  pixels_{};

    unsigned x_size_;
    unsigned y_size_;

    public:

        PixelsWindow(unsigned x_size, unsigned y_size, Style style = Style::Default):
            Window{x_size, y_size, style},
            x_size_{x_size},
            y_size_{y_size},
            texture_{},
            sprite_{}
            {
                pixels_ = new sf::Uint8[x_size_ * y_size_ * 4];

                texture_.create(x_size_, y_size_);
                texture_.update(pixels_, x_size_, y_size_, 0, 0);
                
                sprite_.setTexture(texture_);
            }

        ~PixelsWindow()
            {
                delete[] pixels_;
            }

        bool set_pixel(const Vector& pxl_pos,          const Colour& pxl_val, unsigned char alpha);
        bool set_pixel(unsigned x_pos, unsigned y_pos, const Colour& pxl_val, unsigned char alpha);

        Colour get_pixel(const Vector& pxl_pos,          unsigned char* alpha);
        Colour get_pixel(unsigned x_pos, unsigned y_pos, unsigned char* alpha);
        

        void pixels_update()
            {
                texture_.update(pixels_, x_size_, y_size_, 0, 0);
            }

        void pixels_draw()
            {
                window_.draw(sprite_);
            }
};

//---------------------------------------------------------

char enum_key_to_char     (Key key);

bool enum_key_is_printable(Key key);

}; //namespace Grph