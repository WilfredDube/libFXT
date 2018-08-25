/**
 * @file fxt_parser.c
 * @author  Wilfred Dube <wilfreddube@gmail.com>
 * @date 16 August 2018
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
 * The Parser class for parsing the iges file.
 */
#include "../include/fxt_utils.h"
#include "../include/fxt_vertex.h"
#include "../include/fxt_parser.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <glib.h>

#define GSEC_MAX 26

GHashTable *dsection_ht = NULL;

static void parser_add_ds_object(GHashTable * ht, DsectionEntity *dsec_entity);
// static void print_values(gpointer key, gpointer value, gpointer userdata);

int
read_iges_line(FILE *f, char *s)
{
  /* read filerow from iges*/
  int i;
  int c;
  for (i=0; i < 80; i++) {
    c=getc(f);
    if (c == EOF) return -1;
    s[i]=(char) c;
    if (i==0) { /* eat CR LF in line beginning and reset "i" to zero */
      switch (s[i]) {
        case '\x0D': i--; break;
        case '\x0A': i--; break;
      }
    }
  }
  return 0;
}

int
parser_init(IgesFile *fp, char *filename)
{
  char line[81];

  if ((fp = fopen(filename, "rb")) == NULL) {
    exit(EXIT_FAILURE);
  }

  if (read_iges_line(fp, line) == -1) {
    puts("ERROR : End Of File");
    exit(EXIT_FAILURE);
  }

  if (line[72] == 'F') {
    puts("ERROR : Binary Iges file.");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}

//C substring function definition
void
get_field(char s[], char sub[], int p, int l) {
   int c = 0;

   while (c < l) {
      sub[c] = s[p+c-1];
      c++;
   }
   sub[c] = '\0';
}

char *get_line(IgesFile *fp, char *line){
  return fgets(line, 90, fp);
}

void
get_dsection(IgesFile *fp, DsectionEntity *ds)
{
  char *line = malloc(700);
  char *line2 = malloc(700);

  line = fgets(line, 81, fp);
  while(line != NULL){
    if(line[72] == 'D'){
      line = fgets(line, 81, fp);
      strncat(lines, line, 72);
      line2 = fgets(line, 81, fp);
      strncat(lines, line2, 27);
    } else{
      line = fgets(line, 81, fp);
    }
  }
}

void
get_gsection(IgesFile *fp, char *lines)
{
  char *line = malloc(700);

  line = fgets(line, 81, fp);
  while(line != NULL){
    if(line[72] == 'G'){
      strncat(lines, line, 72);
      line = fgets(line, 81, fp);
    } else{
      line = fgets(line, 81, fp);
    }
  }
}

void
parser_gsection_new(GsectionModelDesc *gsec_model_desc, char *desc_ptr)
{
  char *desc_array[GSEC_MAX] = {NULL};

  utils_to_array(desc_array, desc_ptr, DELIMITER);

  gsec_model_desc = (GsectionModelDesc *) malloc(sizeof(GsectionModelDesc));

  gsec_model_desc->param_delimeter = ',';
  gsec_model_desc->record_delimeter = ';';
  gsec_model_desc->source_PID = (char *)desc_array[2];
  gsec_model_desc->filename = (char *)desc_array[3];
  gsec_model_desc->native_system_PID = (char *)desc_array[4];
  gsec_model_desc->preprocessor_version = (char *)desc_array[5];
  gsec_model_desc->nbits = utils_to_int(desc_array[6]);
  gsec_model_desc->max_float_power = utils_to_int(desc_array[7]);
  gsec_model_desc->number_of_sig_digits_float = utils_to_int(desc_array[8]);
  gsec_model_desc->max_double_power = utils_to_int(desc_array[9]);
  gsec_model_desc->number_of_sig_digits_double = utils_to_int(desc_array[10]);
  gsec_model_desc->receiver_PID = (char *)desc_array[11];
  gsec_model_desc->model_space_scale = utils_replace_char(desc_array[12], 'D', 'E');
  gsec_model_desc->unit_flag = (Unit)desc_array[13];
  gsec_model_desc->unit_name = (char *)desc_array[14];
  gsec_model_desc->max_line_weight = utils_replace_char(desc_array[15], 'D', 'E');
  gsec_model_desc->max_line_weight_gradations = utils_to_int(desc_array[16]);
  gsec_model_desc->date_time_of_generation = (char *)desc_array[17];
  gsec_model_desc->min_resolution_or_granulation = utils_replace_char(desc_array[18], 'D', 'E'); /**< TODO: Investigate this value. */
  gsec_model_desc->approx_max_coordinate = utils_replace_char(desc_array[19], 'D', 'E');
  gsec_model_desc->author_name = (char *)desc_array[20];
  gsec_model_desc->author_organization = (char  *)desc_array[21];
  gsec_model_desc->specification_version = utils_to_int(desc_array[22]); /** TODO: enum 0 - 7  */
  gsec_model_desc->drafting_standard = utils_to_int(desc_array[23]); /** TODO: enum 0 - 7  */
  gsec_model_desc->created_or_last_modification_time = (char *)desc_array[24];
  gsec_model_desc->descriptor = (char *)desc_array[25];

  // size_t i = 0;
  // while (i < 26) {
  //   printf("%s\n", desc_array[i]);
  //   i++;
  // }
}

void
parser_dsection_new(DsectionEntity *dsec_entity, char *desc_ptr)
{
  char *desc_array[GSEC_MAX] = {NULL};

  utils_to_array(desc_array, desc_ptr, DELIMITER);

  dsec_entity = (DsectionEntity *) malloc(sizeof(DsectionEntity));

}
