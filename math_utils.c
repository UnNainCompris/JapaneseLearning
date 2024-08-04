#include "math_utils.h"

double dabs(double number) {
    if (number < 0) {
        return -number;
    } else {
        return number;
    }
}

double ipow(double x, int n) {
    if (n == 0) {
        return 1;
    }

    double result = x;

    for (int i = 0 ; i < dabs(n) - 1 ; i++) {
        result *= x;
    }

    return (n < 0 ? 1/result : result);
}

int find_integer_part(double number) {
    int sign = (number < 0) ? -1 : 1;
    int digit_amount = find_digit_amount(number);
    int current_digit_index = digit_amount;
    int integer_part = 0;

    number = dabs(number);

    while (current_digit_index >= 0) {
        int current_exp = (int)ipow(10, current_digit_index);
        if (number >= current_exp) {
            integer_part += current_exp;
            number -= current_exp;
        }
        if (number < current_exp) {
            current_digit_index--;
        }
    }

    return integer_part * sign;
}

int dfloor(double x) {
    int x_integer = find_integer_part(x);
    double x_decimal = x - x_integer;

    if (x > 0) {
        return x_integer;
    } else {
        if (x_decimal == 0) {
            return x_integer;
        } else {
            return x_integer - 1;
        }
    }
}

int dceil(double x) {
    int x_integer = find_integer_part(x);
    double x_decimal = x - x_integer;

    if (x > 0) {
        if (x_decimal == 0) {
            return x_integer;
        } else {
            return x_integer + 1;
        }
    } else {
        return x_integer;
    }
}

int dround(double x) {
    int x_integer = find_integer_part(x);
    double x_decimal = x - x_integer;

    if (x_decimal >= 0.5) {
        return x_integer + 1;
    } else {
        return x_integer;
    }
}

int find_digit_amount(double x) {
    int amount = 0;
    do {
        amount++;
    } while(x / ipow(10, amount) >= 1);

    return amount;
}
// https://math.stackexchange.com/questions/977586/is-there-an-approximation-to-the-natural-log-function-at-large-values
double ln(double x) {
    int n = find_digit_amount(x);
    double A = x / ipow(10,  n- 1);
    double y = (A - 1) / (A + 1);
    double total = 0;
    int precision = 10;
    for (int i = 0 ; i < precision ; i++) {
        int current_odd = 2 * i + 1;
        total += ipow(y, current_odd) / current_odd;
    }

    return (n - 1) * LN10_32 + (2 * total);
}

unsigned long factorial(long x) {
    if (x < 0) {
        return 0;
    }

    long result = 1;

    for (int i = 1 ; i <= x ; i++) {
        result *= i;
    }

    return result;
}

double pow(double x, double n) {
    double abs_x = dabs(x);
    double ln_x = ln(abs_x);
    int precision = 10;
    double exp = 1;

    for (int i = 1 ; i <= precision ; i++) {
        exp += ipow(abs_x, i) / factorial(i);
    }

    double result = exp * n * ln_x;
    return x < 0 ? 1 / result : result;
}

double rad_to_deg(double radians) {
    return radians * RAD_TO_DEG_32;
}

double deg_to_rad(double degree) {
    return degree * DEG_TO_RAD_32;
}
// https://math.stackexchange.com/questions/106396/sine-approximation-of-bhaskara
double rad_sin(double radians) {
    int sign = radians < 0 ? -1 : 1;
    radians = dabs(radians);

    /*------------------------------------------------*/
    double ratio = radians / PI_32;                     // Here we cap the input radians between '0' and 'pi'
    int integer_part = find_integer_part(ratio); // Because bhaskara approximation only for those boundaries
    double rest = ratio - integer_part;                 //
    radians = rest * PI_32;                             //
    /*------------------------------------------------*/

    /**
     * 16x(pi-x)
     * ---------
     * 5pi² - 4x(pi-x)
     */

    double result =
                        (16*radians*(PI_32 - radians)) /
        /*  -----------------------------------------------------*/
            (5*ipow(PI_32, 2) - 4*radians*(PI_32 - radians));

    if (ratio >= 1 && ratio < 2) {
        result *= -1;
    }

    return result * sign;
}

double deg_sin(double degree) {
    return rad_sin(deg_to_rad(degree));
}

double rad_arcsin(double sin_value) {
    if (sin_value > 1 || sin_value < -1) {
        return 0;
    }

    int precision = 10;
    double result = 0;

    for (int i = 0 ; i < precision ; i++) {
        result +=                        (factorial(2 * i) /
                /* ------------------------------------------------------------------ */
                   (ipow(2, 2*i) * ipow(factorial(i), 2) * (2 * i + 1)))
                        * ipow(sin_value, 2 * i + 1);
    }

    return result;
}

double deg_arcsin(double sin_value) {
    return rad_to_deg(rad_arcsin(sin_value));
}

double rad_cos(double radians) {
    return rad_sin(radians - ONE_AND_HALF_PI_32);
}

double deg_cos(double degree) {
    return rad_arcsin(degree - 270);
}

double rad_arccos(double cos_value) {
    return HALF_PI_32 - rad_arcsin(cos_value);
}

double deg_arccos(double cos_value) {
    return rad_to_deg(rad_arccos(cos_value));
}

double rad_tan(double radians) {
    return rad_sin(radians) / rad_cos(radians);
}

double deg_tan(double degree) {
    return rad_tan(deg_to_rad(degree));
}

double rad_arctan(double tan_value) {
    if (tan_value > 1 || tan_value < -1) {
        return 0;
    }

    int precision = 10;
    double result = 0;

    for (int i = 0 ; i < precision ; i++) {
        result +=     ipow(-1, i) /
                  /* ------------------ */
                        (2*i+1)
                        * ipow(tan_value, 2 * i + 1);
    }

    return result;
}

double deg_arctan(double tan_value) {
    return rad_to_deg(rad_arctan(tan_value));
}