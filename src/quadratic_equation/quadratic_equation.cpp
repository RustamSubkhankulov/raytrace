///@file equation.c source file contains code for functions declarated if equation.h

/// definition used as number of printing "*" for better looking output
///@see stars();

//---------------------------------------------------------

#include <assert.h>
#include <math.h>

//---------------------------------------------------------

#include "../../include/quadratic_equation/quadratic_equation.hpp"
#include "../../include/general/general.hpp"

//=====================================================

#define EPSILON 1e-6

static bool isequal(const double num1, const double num2) {
    if (fabs(num1 - num2) <= EPSILON) return 1;
    else return 0;
}

//=====================================================

static double zerofix(double value) {
    
    return (isequal(value, 0)) ? fabs(value) : value;
}

//=====================================================

void solve_equation(struct Equation* equation) {
    assert(equation != NULL);

    if (isequal(equation->a, 0))
        solve_linear(equation);
    else
        solve_quadratic(equation);
}

//=====================================================

void equation_init(struct Equation* equation){
    equation->a = NAN;
    equation->b = NAN;
    equation->c = NAN;
    equation->root1 = NAN;
    equation->root2 = NAN;
    equation->roots_ct = NOT_STATED_CASE;
}

//=====================================================

void read_args(struct Equation* equation) {
    assert(equation != NULL);

    int res = 0;

    while (res != 3) {

        printf("Enter the coefficients of the quadratic equation"
             " a*x^2 + b*x + c = 0 in order \"a b c\", separated by spaces: ");
        res = scanf("%lf %lf %lf", &(equation->a), &(equation->b), &(equation->c));

        if (res != 3) {
            clearstdin();
            printf("ERROR on input, try again.\n");
            // print_stars_line();
        }
    }
}

//=====================================================

void show_args(const struct Equation* equation) {
    assert(equation != NULL);
    assert(isfinite(equation->a));
    assert(isfinite(equation->b));
    assert(isfinite(equation->c));

    // print_stars_line();
    printf("a = %g  b = %g  c = %g\n", equation->a, equation->b, equation->c);
}

//=====================================================

void solve_linear(struct Equation* equation) {
    assert(equation != NULL);

    double c = equation->c;
    double b = equation->b;

    if (isequal(c, 0) && isequal(b, 0)) equation->roots_ct = INF_ROOTS;
    
    else if (!isequal(c, 0) && isequal(b, 0)) 
        equation->roots_ct = NO_ROOTS;

    else if (!isequal(b, 0)) {
        equation->roots_ct = ONE_ROOT;
        equation->root1 = (-c) / b;
        
        equation->root1 = zerofix(equation->root1);                        
    }
}

//=====================================================

void solve_quadratic(struct Equation* equation) {
    assert(equation != NULL);

    double a = equation->a;
    double b = equation->b;
    double c = equation->c;
    double discr = NAN;



    discr = b * b - 4 * a * c;

    // assert(isfinite(discr));

    if (isequal(discr, 0)) {

        equation->roots_ct = ONE_ROOT;
        equation->root1 = (-b) / (2 * a);

        equation->root1 = zerofix(equation->root1);
    }
    else if (discr > 0) {
        double discr_sqrt = sqrt(discr);
        a *= 2;

        equation->root1 = (-b - discr_sqrt) / a;                          
        equation->root2 = (-b + discr_sqrt) / a;

        equation->roots_ct = TWO_ROOTS;
    }
    else equation->roots_ct = NO_ROOTS;
}

//=====================================================

void show_result(const struct Equation* equation) {
    assert(equation != NULL);

    switch (equation->roots_ct) {
    case INF_ROOTS:
        printf("Linear equation has infinite amount of roots.\n");
        break;
    case ONE_ROOT:
        printf("%s equation has one root: %g.\n", (isequal(equation->a, 0)) ? "Linear" : "Quadratic", equation->root1);
        break;
    case TWO_ROOTS:
        printf("Quadratic equation has two root: %g and %g.\n", equation->root1, equation->root2);
        break;
    case NO_ROOTS:
        printf("Equation has no roots.\n");
        break;
    default:
        printf("Unexpected amount of roots.\n");
        break;
    }
}

//========================================================

int user_interface_menu(void) {
    int ans = NOT_STATED;
    while (ans != YES && ans != NO) {

        // print_stars_line();

        printf("Do you want to repeat? 1.YES or 2.NO\n");
        printf("Your answer is: ");
        int res = scanf("%d", &ans);

        if ((ans != YES && ans != NO) || res != 1) {

            clearstdin();
            // print_stars_line();

            printf("Try again\n");
            printf("Please enter 1 to repeat or 2 to stop.\n");
        }
    }
    return ans;
}