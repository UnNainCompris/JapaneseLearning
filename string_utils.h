#ifndef ERIS_STRING_UTILS_H
#define ERIS_STRING_UTILS_H

#include <stdlib.h> // From memory management.
#include <stdio.h> // Debugging purpose only

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a > b ? b : a)

/**
 * Use to retrieve the length of a string.
 * @param string The string that we want to check his length.
 * @return The founded length of 'string'.
 */
int strlength(const char* string);

/**
 * Use to copy a string (char array) inside a new one.
 * @depend_on strlength(), calloc()
 * @param string The string to copy.
 * @return A copy of the string inside a new array.
 */
char* copy(const char* string);

/**
 * Use to create a substring of a string <br>
 * <br>
 * 'start' & 'end' min is automatically capped to 0 <br>
 * 'start' & 'end' max is automatically capped to string length <br>
 * <br>
 * If 'start' greater than 'end' this function return NULL <br>
 * If 'start' is equals to 'end' this function return an empty string ("") <br>
 * If 'start' is smaller than 'end' this function will work like so: <br>
 * <br>
 * substring("Hamburger", 0, 5); -> "Hambu" <br>
 * substring("Hamburger", 2, 7); -> "mburg" <br>
 * substring("Hamburger", 5, 9); -> "rger" <br>
 * substring("Hamburger", 3, 3); -> "" <br>
 * substring("Hamburger", -10000, 10000); -> "Hamburger"
 * @depend_on strlength(), max(), min(), calloc()
 * @param string The string to work with
 * @param start Index of where to start (INCLUSIVE)
 * @param end Index of where to stop (EXCLUSIVE)
 * @return The substring created and found from string with the start and end index
 */
char* substring(const char* string, int start, int end);

/**
 * Use to count how many char in a row are similar. <br>
 * <br>
 * ex: <br>
 * string = "For D.den"; model = "Forbidden" <br>
 * For D.den <br>
 * Forbidden <br>
 * ^^^XXX^^^ <br>
 * This will return 3 The last 3 doesn't work because they aren't in row.
 * @depend_on strlength()
 * @param string The string where we are going to search for model
 * @param model The model we are using to search in string
 * @return The amount of char in a row that is similar from the start of string.
 */
int count_matching_row_char(const char* string, const char* model);

/**
 * Use to count how many char in a are similar. <br>
 * <br>
 * ex: <br>
 * string = "Foo Bar"; model = "Honey" <br>
 * Foo Bar <br>
 * Honey <br>
 * X^XXX <br>
 * This will return 1
 * @depend_on strlength()
 * @param string The string where we are going to search for model.
 * @param model The model we are using to search in string.
 * @return The amount of char that is similar from the start of string.
 */
int count_matching_char(const char* string, const char* model);

/**
 * Use to find inside a string every start index occurrence of an model.
 * @param string The string we are going to search in.
 * @param model The model we are going to search for.
 * @param amount_of_index The pointer of where we are going to store the amount of index found.
 * @return A list of index that point to the start of the model inside the string.
 */
int* find_index(const char* string, const char* model, int* amount_of_index);

/**
 * Use to check if a string start with a certain model.
 * @depend_on strlength()
 * @param string The string we are going to check for.
 * @param model The model to check for at the start of the string.
 * @return 1 (True) if the string start with the model, 0 (False) if not.
 */
int start_with(const char* string, const char* model);

/**
 * Use to count a string inside another string.
 * @depend_on strlength(), substring(), start_with(), free()
 * @param string The string were we are going to count for 'to_count'
 * @param model The string we want to count the amount of occurrence inside 'string'
 * @return The amount of occurrence found inside 'string' of 'to_count'
 */
int count(const char* string, const char* model);

/**
 * Use to replace 'limit' occurrence of 'to_replace' by 'replacement' inside 'string'.
 * @depend_on strlength(), max(), calloc(), substring(), count_matching_row_char(), free()
 * @param string The string where we are going to replace things inside.
 * @param to_replace The string we want to replace.
 * @param replacement The string that is going to replace 'to_replace' inside 'string'
 * @param limit The amount of time we want to replace an occurrence (negative means infinite)
 * @return The string with all replacement done.
 */
char* replace(const char* string, const char* to_replace, const char* replacement, int limit);

/**
 * Use to replace the first occurrence of 'to_replace' by 'replacement' inside 'string'.
 * @depend_on replace()
 * @param string The string where we are going to replace things inside.
 * @param to_replace The string we want to replace.
 * @param replacement The string that is going to replace 'to_replace' inside 'string'
 * @return The string with all replacement done.
 */
char* replace_first(const char* string, const char* to_replace, const char* replacement);

/**
 * Use to replace 'limit' occurrence of 'to_replace' by 'replacement' inside 'string' from the end of the string.
 * @depend_on strlength(), max(), calloc(), substring(), count_matching_row_char(), free()
 * @param string The string where we are going to replace things inside.
 * @param to_replace The string we want to replace.
 * @param replacement The string that is going to replace 'to_replace' inside 'string'
 * @param limit The amount of time we want to replace an occurrence (negative means infinite)
 * @return The string with all replacement done.
 */
char* replace_from_end(const char* string, const char* to_replace, const char* replacement, int limit);

/**
 * Use to replace the last occurrence of 'to_replace' by 'replacement' inside 'string' from the end of the string.
 * @depend_on replace()
 * @param string The string where we are going to replace things inside.
 * @param to_replace The string we want to replace.
 * @param replacement The string that is going to replace 'to_replace' inside 'string'
 * @return The string with all replacement done.
 */
char* replace_last(const char* string, const char* to_replace, const char* replacement);

/**
 * Use to split a string in different string.
 * @depend_on count(), find_index(), calloc(), strlength(), substring(), free()
 * @param string The string that is going to be split.
 * @param splitter The string that will split the 'string'.
 * @param limit The max amount of split object (negative or null value mean infinite split).
 * @param string_amount A pointer of where we are going to write down the total of object inside the returned array.
 * @return A pointer to the array of string.
 */
char** split(const char* string, const char* splitter, int limit, int* string_amount);

int strequals(const char* first, const char* second);

/**
 * Use to repeat a 'times' time a sequence of char 'string'.
 * @param times The amount of time to repeat the string 'string'.
 * @param string The string that will be repeated.
 * @return The string 'string' repeated 'times' time.
 */
char* repeat(int times, const char* string);

/**
 * Make a char upper case if can
 * @param chr The char to make it upper case.
 * @return The upper case char equivalent.
 */
char toupper(char chr);

/**
 * Make a char lower case if can
 * @param chr The char to make it lower case.
 * @return The lower case char equivalent.
 */
char tolower(char chr);

#endif //ERIS_STRING_UTILS_H
