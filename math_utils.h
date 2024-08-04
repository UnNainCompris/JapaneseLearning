#ifndef ERIS_MATH_UTILS_H
#define ERIS_MATH_UTILS_H

#include <stdio.h>

// Const_name_DigitAmount
#define HALF_PI_32 1.5707963267948966192313216916398
#define PI_32 3.1415926535897932384626433832795
#define ONE_AND_HALF_PI_32 4.7123889803846898576939650749193
#define TWOPI_32 6.2831853071795864769252867665590

#define RAD_TO_DEG_32 57.295779513082320876798154814105
#define DEG_TO_RAD_32 0.0174532925199432957692369076848

#define LN10_32 2.3025850929940456840179914546844

/**
 * Replicate math absolute value by return the positive value of any number.
 * @param number The basic number we want to know his positive value.
 * @return The positive value of 'number'.
 */
double dabs(double number);

/**
 * Use to raise 'x' to the power of 'n'
 * @param x The number to raise to the power of 'n'
 * @param n The power to raise 'x' represented by an INT
 * @return The number 'x' raised to the power of 'n'.
 */
double ipow(double x, int n);

/**
 * Use to find the integer part of a decimal number. <br>
 * 324.45 > 324 <br>
 * 4732.574 > 4732 <br>
 * -4423.435 > 4423
 * @depend_on find_digit_amount(), dabs(), ipow()
 * @param number
 * @return
 */
int find_integer_part(double number);

/**
 * Use to reduce 'x' to the closet lower integer. <br>
 * Ex: <br>
 * 10.0 > 10 <br>
 * 10.1 > 10 <br>
 * 9.9 > 9 <br>
 * 364.32452 > 364 <br>
 * -234.44 > -235
 * @depend_on find_integer_part()
 * @param x The number to floor.
 * @return The nearest lowest integer of 'x'.
 */
int dfloor(double x);

/**
 * Use to raise 'x' to the closet greater integer.
 * 10.0 > 10 <br>
 * 10.1 > 11 <br>
 * 9.9 > 10 <br>
 * 364.32452 > 365 <br>
 * -234.44 > -234
 * @depend_on find_integer_part()
 * @param x The number to ceil.
 * @return The nearest greatest integer of 'x'.
 */
int dceil(double x);

/** Use to round a number flowing the basic math rounding rule. <br>
 * When x decimal value is equals or greater than 0.5 return the x integer part value plus one (x+1) <br>
 * If not return x integer part
 * @depend_on find_integer_part()
 * @param x The number to round
 * @return The number 'x' rounded.
 */
int dround(double x);

/**
 * Use to find the amount of digit of an integer. <br>
 * Ex: <br>
 * 10.000 > 2 <br>
 * 1.382 > 1 <br>
 * 3255 > 4
 * @depend_on ipow()
 * @param x  The number x we want to find his number of digit
 * @return The number of digit inside the number 'x'.
 */
int find_digit_amount(double x);

/**
 * Use to know the natural log of an 'x' number.
 * @depend_on find_digit_amount(), ipow(), LN10_32
 * @formula_source https://math.stackexchange.com/questions/977586/is-there-an-approximation-to-the-natural-log-function-at-large-values
 * @param x The number we want to find his natural log.
 * @return The natural log of x.
 */
double ln(double x);

/**
 * Use to retrieve the factorial value of a number x.
 * @param x The number we want to know his factorial value. (x should always be equals or greater than 0)
 * @return The factorial number of 'x'.
 */
unsigned long factorial(long x);

/**
 * Use to raise a number 'x' to the power of 'n' <br>
 * The difference with ipow is that here n can be a decimal value.
 * @depend_on dabs(), ln(), ipow(), factorial()
 * @formula_source https://stackoverflow.com/questions/2882706/how-can-i-write-a-power-function-myself
 * @param x The number that we will raise to the power of 'n'
 * @param n The power to applies on 'x'
 * @return The number 'x' raised to the power of 'n'
 */
double pow(double x, double n);

/**
 * Convert radians angle into degree angle
 * @depend_on RAD_TO_DEG_32;
 * @param radians The angle in radians to transform into an degree angle.
 * @return The angle 'radians' in degree.
 */
double rad_to_deg(double radians);

/**
 * Convert degree angle into radians angle
 * @depend_on DEG_TO_RAD_32;
 * @param degree The angle in degree to transform into an radians angle.
 * @return The angle 'degree' in radians.
 */
double deg_to_rad(double degree);

/**
 * Sin math function with input as radians. <br>
 * To make this we use bhaskara approximation algorithm
 * @formula_source https://math.stackexchange.com/questions/106396/sine-approximation-of-bhaskara
 * @depend_on dabs() PI_32, find_integer_part(), ipow()
 * @param radians The input used for sin function.
 * @return The resul of a sin with the input.
 */
double rad_sin(double radians);

/**
 * Sin math function with input as degree.
 * @see rad_sin()
 * @depend_on rad_sin(), deg_to_rad()
 * @param degree The input used for sin function.
 * @return The resul of a sin with the input.
 */
double deg_sin(double degree);

/**
 * Arcsin math function, the input "should" be a sin output. <br>
 * sin_value should be greater or equals to -1 and lower or equals than 1.
 * @formula_source https://scipp.ucsc.edu/~haber/ph116A/taylor11.pdf | page 4
 * @depend_on factorial(), ipow()
 * @param sin_value The input used for arcsin function.
 * @return The result of a arcsin with the input, in radians.
 */
double rad_arcsin(double radians);

/**
 * Arcsin math function, the input "should" be a sin output. <br>
 * sin_value should be greater or equals to -1 and lower or equals than 1.
 * @see rad_arcsin()
 * @depend_on arcsin(), rad_to_deg()
 * @param sin_value The input used for arcsin function.
 * @return The result of a arcsin with the input, in degree.
 */
double deg_arcsin(double degree);

/**
 * Cos math function with input as radians.
 * @see rad_sin()
 * @depend_on rad_sin(), ONE_AND_HALF_PI_32
 * @param radians The input used for cos function.
 * @return The resul of a cos with the input.
 */
double rad_cos(double radians);

/**
 * Cos math function with input as degree.
 * @see rad_sin()
 * @depend_on deg_sin()
 * @param degree The input used for cos function.
 * @return The resul of a cos with the input.
 */
double deg_cos(double degree);

/**
 * Arccos math function, the input "should" be a cos output. <br>
 * cos_value should be greater or equals to -1 and lower or equals than 1.
 * @see rad_arcsin()
 * @formula_source https://scipp.ucsc.edu/~haber/ph116A/taylor11.pdf | page 4 (Equality: 1/2π − arccos(x))
 * @depend_on HALF_PI_32, rad_arcsin()
 * @param cos_value The input used for arccos function.
 * @return The result of a arccos with the input, in radians.
 */
double rad_arccos(double cos_value);

/**
 * Arccos math function, the input "should" be a cos output. <br>
 * cos_value should be greater or equals to -1 and lower or equals than 1.
 * @see rad_arccos()
 * @formula_source https://scipp.ucsc.edu/~haber/ph116A/taylor11.pdf | page 4 (Equality: 1/2π − arccos(x))
 * @depend_on rad_to_deg(), rad_arccos()
 * @param cos_value The input used for arccos function.
 * @return The result of a arccos with the input, in degree.
 */
double deg_arccos(double cos_value);

/**
 * Tan math function with input as radians. <br>
 * Obtain the tan result by diving the result of a sin of the input angle by the result of a cos of the input angle (sin(radians) / cos(radians))
 * @see rad_sin(), rad_cos()
 * @depend_on rad_sin(), rad_cos()
 * @param radians The input used for tan function.
 * @return The resul of a tan with the input.
 */
double rad_tan(double radians);

/**
 * Tan math function with input as radians.
 * @see rad_tan()
 * @depend_on rad_tan(), deg_to_rad()
 * @param degree The input used for tan function.
 * @return The resul of a tan with the input.
 */
double deg_tan(double degree);

/**
 * Arctan math function, the input "should" be a tan output. <br>
 * tan_value should be greater or equals to -1 and lower or equals than 1.
 * @formula_source https://scipp.ucsc.edu/~haber/ph116A/taylor11.pdf | page 4
 * @depend_on ipow()
 * @param tan_value The input used for arctan function.
 * @return The result of a arctan with the input, in radians.
 */
double rad_arctan(double tan_value);

/**
 * Arctan math function, the input "should" be a tan output. <br>
 * tan_value should be greater or equals to -1 and lower or equals than 1.
 * @see rad_arctan()
 * @depend_on rad_to_deg(), rad_arctan()
 * @param tan_value The input used for arctan function.
 * @return The result of a arctan with the input, in degree.
 */
double deg_arctan(double tan_value);

#endif //ERIS_MATH_UTILS_H
