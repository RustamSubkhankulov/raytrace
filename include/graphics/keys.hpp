#pragma once 

//=========================================================

#include <SFML/Window.hpp>

//=========================================================

namespace Grph
{

enum Key
{
    A = sf::Keyboard::Key::A, B = sf::Keyboard::Key::B, 
    C = sf::Keyboard::Key::C, D = sf::Keyboard::Key::D, 
    E = sf::Keyboard::Key::E, F = sf::Keyboard::Key::F, 
    G = sf::Keyboard::Key::G, H = sf::Keyboard::Key::H, 
    I = sf::Keyboard::Key::I, J = sf::Keyboard::Key::J, 
    K = sf::Keyboard::Key::K, L = sf::Keyboard::Key::L, 
    M = sf::Keyboard::Key::M, N = sf::Keyboard::Key::N,
    O = sf::Keyboard::Key::O, P = sf::Keyboard::Key::P, 
    Q = sf::Keyboard::Key::Q, R = sf::Keyboard::Key::R, 
    S = sf::Keyboard::Key::S, T = sf::Keyboard::Key::T, 
    U = sf::Keyboard::Key::U, V = sf::Keyboard::Key::V, 
    W = sf::Keyboard::Key::W, X = sf::Keyboard::Key::X, 
    Y = sf::Keyboard::Key::Y, Z = sf::Keyboard::Key::Z,

    Num0 = sf::Keyboard::Key::Num0, Num1 = sf::Keyboard::Key::Num1,
    Num2 = sf::Keyboard::Key::Num2, Num3 = sf::Keyboard::Key::Num3, 
    Num4 = sf::Keyboard::Key::Num4, Num5 = sf::Keyboard::Key::Num5, 
    Num6 = sf::Keyboard::Key::Num6, Num7 = sf::Keyboard::Key::Num7,
    Num8 = sf::Keyboard::Key::Num8, Num9 = sf::Keyboard::Key::Num9, 

    Escape = sf::Keyboard::Key::Escape,
    LCtrl = sf::Keyboard::Key::LControl, LShift  = sf::Keyboard::Key::LShift, 
    LAlt  = sf::Keyboard::LAlt,          LSystem = sf::Keyboard::Key::LSystem,
    RCtrl = sf::Keyboard::Key::RControl, RShift  = sf::Keyboard::Key::RShift, 
    RAlt  = sf::Keyboard::Key::RAlt,     RSystem = sf::Keyboard::Key::RSystem,

    LBracket  = sf::Keyboard::Key::LBracket,  RBracket = sf::Keyboard::Key::RBracket,
    Semicolon = sf::Keyboard::Key::SemiColon, Comma    = sf::Keyboard::Key::Comma, 
    Dot       = sf::Keyboard::Key::Period,    Quote    = sf::Keyboard::Key::Quote,

    Slash  = sf::Keyboard::Key::Slash, Backslash = sf::Keyboard::Key::Backslash, 
    Tilde  = sf::Keyboard::Key::Tilde, Equal     = sf::Keyboard::Key::Equal, 
    Hyphen = sf::Keyboard::Key::Hyphen,
    
    Space     = sf::Keyboard::Key::Space,     Enter = sf::Keyboard::Key::Enter, 
    Backspace = sf::Keyboard::Key::Backspace, Tab   = sf::Keyboard::Key::Tab, 

    PageUp = sf::Keyboard::Key::PageUp, PageDown = sf::Keyboard::Key::PageDown, 
    End    = sf::Keyboard::Key::End,    Home     = sf::Keyboard::Key::Home, 
    Delete = sf::Keyboard::Key::Delete, Insert   = sf::Keyboard::Key::Insert, 

    Add = sf::Keyboard::Key::Add,      Sub = sf::Keyboard::Key::Subtract, 
    Mul = sf::Keyboard::Key::Multiply, Div = sf::Keyboard::Key::Divide, 
    
    ArrLeft = sf::Keyboard::Key::Left, ArrRight = sf::Keyboard::Key::Right, 
    ArrUp   = sf::Keyboard::Key::Up,   ArrDown  = sf::Keyboard::Key::Down,

    F1 = sf::Keyboard::Key::F1, F2  = sf::Keyboard::Key::F2,  F3  = sf::Keyboard::Key::F3,  
    F5 = sf::Keyboard::Key::F5, F6  = sf::Keyboard::Key::F6,  F7  = sf::Keyboard::Key::F7,  
    F9 = sf::Keyboard::Key::F9, F10 = sf::Keyboard::Key::F10, F11 = sf::Keyboard::Key::F11,
    F4 = sf::Keyboard::Key::F4, F8  = sf::Keyboard::Key::F8,  F12 = sf::Keyboard::Key::F12 
};

}; // namespace Grph