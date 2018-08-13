/**
 * @file fxt_color.c
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
 * The Color class represents the iges color definition entity (314).
 */

#include "../include/fxt_utils.h"
#include "../include/fxt_color.h"
#include "../include/fxt_parser.h"

#include <math.h>

#define ENTITY_TYPE 314 /**< IGES Entity Type */
#define ENTITY_NAME "Color Definition" /**< IGES Entity Name */

/**
* @enum color - iges color number (0 to 8)
*/
enum color {
  NONE,
  BLACK,
  RED,
  GREEN,
  BLUE,
  YELLOW,
  MAGENTA,
  CYAN,
  WHITE
};

/** Calculates the rgb color percentages.
* @param value (0 <= value <= 255)
* @returns ceiling color value in iges % standard.
*/
static float
color_percentage(const int value)
{
  return ceil((value/255)*100);
}

/** Allocate a new color object wtih the given values.
* @param r Red component (0 <= r <= 100)
* @param g Green component (0 <= g <= 100)
* @param b Blue component (0 <= b <= 100)
* @param name name of the color (default - NULL)
* @returns A newly allocated color object.  This should be freed after use.
*/
static Color *
color_new(float r, float g, float b, char *name)
{
  Color *col = (Color *)malloc(sizeof(*col));
  col->red = r;
  col->green = g;
  col->blue = b;

  if (name == NULL){
    name = NULL;
  }else{
    col->name = name;
  }

  return col;
}

/** Converts standard RGB values to Percentage Iges color values
* @param r Red component (0 <= r <= 255)
* @param g Green component (0 <= g <= 255)
* @param b Blue component (0 <= b <= 255)
* @param name name of the color (default - NULL)
* @returns A newly allocated color object.  This should be freed after use.
*/
static Color *
color_rgb_convert(float r, float g, float b, char *name)
{
  r = color_percentage(r);
  g = color_percentage(g);
  b = color_percentage(b);

  return color_new(r,g,b,name);
}

/** Converts iges color number to RGB color object
* @param num value corresponding to the enum color values.
* @returns Color object
*/
Color *
color_by_number(const unsigned num)
{
  Color *col = (Color *)malloc(sizeof(* col));

  switch (num) {
    case NONE:
      col = NULL;
      break;
    case BLACK:
      col = color_rgb_convert(0,0,0,"BLACK");
      break;
    case RED:
      col = color_rgb_convert(255,0,0,"RED");
      break;
    case GREEN:
      col = color_rgb_convert(0,255,0,"GREEN");
      break;
    case BLUE:
      col = color_rgb_convert(0,0,255,"BLUE");
      break;
    case YELLOW:
      col = color_rgb_convert(255,255,0,"YELLOW");
      break;
    case MAGENTA:
      col = color_rgb_convert(255,0,255,"MAGENTA");
      break;
    case CYAN:
      col = color_rgb_convert(0,255,255,"CYAN");
      break;
    case WHITE:
      col = color_rgb_convert(255,255,255,"WHITE");
      break;
    default:
      ;
  }

  return col;
}

/** Creates a color entity object from the pd sections data.
* @param pd_pointer key to uniquely identify each PsectionEntityData object.
* @param ps_data unprocessed pd section data (0 - 64).
* @param colornum entity color number (0 - 7) default = 0, if pd_pointer != NULL then colornum = -1
* @return pointer to the PsectionEntityData.
*/
PsectionEntityData *
color_extract(const int pd_pointer, char *ps_data, const int colornum)
{
  float r,g,b;
  char *name;
  char *color_array[PARAM_MAX] = {NULL};
  Color *col = NULL;
  PsectionEntityData * psd = NULL;

  if (ps_data != NULL) {
    utils_to_array(color_array, ps_data, ",");

    r = utils_to_float(color_array[1]);
    g = utils_to_float(color_array[2]);
    b = utils_to_float(color_array[3]);

    name = color_array[4];

    col = color_new(r, g, b, name);
  }

  if (colornum != -1){
    col = color_by_number(colornum);
  }

  psd = (PsectionEntityData *)malloc(sizeof(PsectionEntityData *));

  psd = psection_entity_object_new(pd_pointer, ENTITY_TYPE, ENTITY_NAME, col);

  return psd;
}
