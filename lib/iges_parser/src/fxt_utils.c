/**
 * @file fxt_utils.c
 * @author  Wilfred Dube <wilfreddube@gmail.com>
 * @date 12 August 2018
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * https://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * Provides utility functions.
 */

#include "../include/fxt_utils.h"
#include <stdlib.h>
#include <string.h>

/** Convert string to a int.
* @param str string to be convert to int.
* @return int value of the string.
*/
int
utils_to_int(char *str)
{
  return atoi(str);
}

/** Convert string to a float.
* @param str string to be convert to float.
* @return floating point value of the string.
*/
float
utils_to_float(char *str)
{
  return atof(str);
}

/** Replaces a character in a string i.e replaces the D in an iges floating point with an E(mathematical exponent character)
* @param str string to Process
* @param find character to replace
* @param replace character to replace find with
* @return floating point value of the processed string
*/
float
utils_replace_char(char* str, char find, char replace)
{
    char *current_pos = strchr(str,find);
    while (current_pos){
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return utils_to_float(str);
}
