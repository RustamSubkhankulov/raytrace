/// @file equation.h header file contains function declarations, structures, enumerations used for solving equation
#pragma once

//=========================================================

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

//=========================================================

///Enumeration type for possible solution cases
/// 
///This enumeration type is being used to identify case of equation solution.
///-1 stands for INF_ROOTS, 0 for NO_ROOTS, 1 for ONE_ROOT and 2 for TWO_ROOTS
/// @see roots_ct
enum root_cases {
    INF_ROOTS = 3,
    NO_ROOTS=4,
    ONE_ROOT=5, 
    TWO_ROOTS=6,
    NOT_STATED_CASE = 7 
};

///Enumeration type used for better looking code
///
///Used for variable "ans" to determine if the user wants to use the program again.
enum answers { NOT_STATED = 0, YES = 1, NO = 2 };

///Structure containing roots, coefficients, discriminant of the equation and amount of roots.
///
///This structure is being used in functions working with coefficients and roots 
///such as read_args(), show_args(),show_result(), solve_equation(), solve_linear() and solve_quadratic().
struct Equation {
    double a = NAN;
    double b = NAN;
    double c = NAN;
    double root1 = NAN;
    double root2 = NAN;
    enum root_cases roots_ct = NOT_STATED_CASE;
};

///Function read coefficients
///
///This function receives floating point numbers as coefficients of equation.
///In case of input error function clearline() clears input and user can try to enter coefficients again.
///@param equation - structure including roots, coefficients and amount of roots.
///@see struct Equation
void read_args(struct Equation* equation);

///Function shows coefficients received from user.
///
///This function helps user check if read_args() read coefficients correctly.
///@param equation - structure including roots, coefficients and amount of roots.
///@see struct Equation 
void show_args(const struct Equation* equation);

///Function solves linear equation.
/// 
///Variable roots_ct in struct Equation equation is being chaged by this function according to case of equation solution.
///@param equation - structure including roots, coefficients and amount of roots.
///@see struct Equation, solve_equation();
void solve_linear(struct Equation* equation);

///Function solves quadratic equation.
/// 
///Variable roots_ct in struct Equation equation is being changed by this function according to case of equation solution.
///@param equation - structure including roots, coefficients and amount of roots.
///@see struct Equation, solve_equation();
void solve_quadratic(struct Equation* equation);

///Function solves equation.
///
///This function calls solve_linear ar solve_quadratic.
///@param equation - structure including roots, coefficients and amount of roots.
///@see struct Equation, solve_linear() , solve_quadratic(); 
void solve_equation(struct Equation* equation);

///Function shows results of solving the equation
///
///@param equation - structure including roots, coefficients and amount of roots.
///@see struct Equation
void show_result(const struct Equation* equation);

///Initialization of the structure
///
///Initializating coefficients of the equation at the start
///@param equation - structure including roots, coefficients and amount of roots.
///@see struct Equation
void equation_init(struct Equation* equation);

///Menu for UI
///
///@returns integer value for ans variable
int user_interface_menu(void);