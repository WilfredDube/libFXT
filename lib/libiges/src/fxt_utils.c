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
#include <stdio.h>

#define PARAM_MAX 1000 /**< Maximum number of parameters in the PD section. */
#define ARRAY_SIZE 100000

/** Extract entity parameters from string.
* @param ret array of pointer for store string tokens.
* @param str string to be convert to array.
* @param delim specifies a set of bytes that delimit the tokens in the parsed string
* @return array of string.
*/
int
utils_to_array(char **ret, char *str, char *delim)
{
  size_t count = 0;
  char *tok;

  while((tok = utils_strsep(&str, delim)) && count < PARAM_MAX)
        ret[count++] = tok;

  return 0;
}

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
long double
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
long double
utils_replace_char(char* str, char find, char replace)
{
  char *str_ptr;

  if (str == NULL) {
    printf("NULLL\n");
    exit(EXIT_FAILURE);
  }

  str_ptr = strchr(str, find);
  if (str_ptr != NULL) {
    *str_ptr = replace;
  }

  return utils_to_float(str);
}



/*
 * Get next token from string *stringp, where tokens are possibly-empty
 * strings separated by characters from delim.
 *
 * Writes NULs into the string at *stringp to end tokens.
 * delim need not remain constant from call to call.
 * On return, *stringp points past the last NUL written (if there might
 * be further tokens), or is NULL (if there are definitely no more tokens).
 *
 * If *stringp is NULL, strsep returns NULL.
 */
char *
utils_strsep(char **stringp, const char *delim)
{
	char *s;
	const char *spanp;
	int c, sc;
	char *tok;

	if ((s = *stringp) == NULL)
		return (NULL);
	for (tok = s;;) {
		c = *s++;
		spanp = delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == '\0')
					s = NULL;
				else
					s[-1] = '\0';
				*stringp = s;
				return (tok);
			}
		} while (sc != '\0');
	}
	/* NOTREACHED */
}
