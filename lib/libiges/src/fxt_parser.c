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
#include "../include/fxt_edge.h"
#include "../include/fxt_loop.h"
#include "../include/fxt_face.h"
#include "../include/fxt_parser.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <glib.h>

#define GSEC_MAX 26
#define PS_MAX 100000

GHashTable *dsection_ht = NULL;
GHashTable *psection_ht = NULL;

// static void parser_psection_reassign(gpointer key, gpointer value, gpointer userdata);
static void parser_dsection_add_entitydata(gpointer key, gpointer value, gpointer userdata);
static void parser_dsection_add_transmatrix(gpointer key, gpointer value, gpointer userdata);
void parser_psection_new(PsectionEntityData *ps_object, char *desc_ptr, int sequence_number);
void parser_add_ps_object(GHashTable * ht, PsectionEntityData *ps);
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
get_psection_vt_list(IgesFile *fp, PsectionEntityData *ps)
{
  int sequence_number = 0;
  static int line_count = 0;
  static int ps_object_count = 0;
  char temp_str[PS_MAX] = "";
  char *line = malloc(100);
  char substr[70];
  char *desc_array[PARAM_MAX] = {NULL};

  psection_ht = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);

  line = get_line(fp, line);

  while (line){
    if (line[72] == 'P') {
      ++line_count;
      /* Add line to temp_str */
      get_field(line, substr, 1, 64);
      strncat(temp_str, substr, 65);

      if (line_count == 1) {
        /* get object 's sequence number */
        get_field(line, substr, 74, 8);
        sequence_number = utils_to_int(substr);
      }

      if (strchr(temp_str, ';')) {        /* ';' terminator found in string */
        /* Tokenize String & PS object creation */
        char *str = (char *)malloc(strlen(temp_str) + 1);
        strcpy(str, temp_str);
        utils_to_array(desc_array, str, DELIMITER);

        if (utils_to_int(desc_array[0]) == 502){
          parser_psection_new(ps, temp_str, sequence_number);
        }

        /* Initialize variable for next entity */
        ps = (PsectionEntityData *)malloc(sizeof(PsectionEntityData));
        temp_str[0] = '\0';
        line_count = 0;

        /* Count created objects */
        ++ps_object_count;
      }
    }

    line = get_line(fp, line);
  }
}


void
get_psection_edge_list(IgesFile *fp, PsectionEntityData *ps)
{
  int sequence_number = 0;
  static int line_count = 0;
  static int ps_object_count = 0;
  char temp_str[PS_MAX] = "";
  char *line = malloc(100);
  char substr[70];
  char *desc_array[PARAM_MAX] = {NULL};

  // psection_ht = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);

  line = get_line(fp, line);

  while (line){
    if (line[72] == 'P') {
      ++line_count;
      /* Add line to temp_str */
      get_field(line, substr, 1, 64);
      strncat(temp_str, substr, 65);

      if (line_count == 1) {
        /* get object 's sequence number */
        get_field(line, substr, 74, 8);
        sequence_number = utils_to_int(substr);
      }

      if (strchr(temp_str, ';')) {        /* ';' terminator found in string */
        /* Tokenize String & PS object creation */
        char *str = (char *)malloc(strlen(temp_str) + 1);
        strcpy(str, temp_str);
        utils_to_array(desc_array, str, DELIMITER);

        if (utils_to_int(desc_array[0]) == 504){
          parser_psection_new(ps, temp_str, sequence_number);
        }

        /* Initialize variable for next entity */
        ps = (PsectionEntityData *)malloc(sizeof(PsectionEntityData));
        temp_str[0] = '\0';
        line_count = 0;

        /* Count created objects */
        ++ps_object_count;
      }
    }

    line = get_line(fp, line);
  }
}

void
get_psection_loop(IgesFile *fp, PsectionEntityData *ps)
{
  int sequence_number = 0;
  static int line_count = 0;
  static int ps_object_count = 0;
  char temp_str[PS_MAX] = "";
  char *line = malloc(100);
  char substr[70];
  char *desc_array[PARAM_MAX] = {NULL};

  // psection_ht = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);

  line = get_line(fp, line);

  while (line){
    if (line[72] == 'P') {
      ++line_count;
      /* Add line to temp_str */
      get_field(line, substr, 1, 64);
      strncat(temp_str, substr, 65);

      if (line_count == 1) {
        /* get object 's sequence number */
        get_field(line, substr, 74, 8);
        sequence_number = utils_to_int(substr);
      }

      if (strchr(temp_str, ';')) {        /* ';' terminator found in string */
        /* Tokenize String & PS object creation */
        char *str = (char *)malloc(strlen(temp_str) + 1);
        strcpy(str, temp_str);
        utils_to_array(desc_array, str, DELIMITER);

        if (utils_to_int(desc_array[0]) == 508){
          parser_psection_new(ps, temp_str, sequence_number);
        }

        /* Initialize variable for next entity */
        ps = (PsectionEntityData *)malloc(sizeof(PsectionEntityData));
        temp_str[0] = '\0';
        line_count = 0;

        /* Count created objects */
        ++ps_object_count;
      }
    }

    line = get_line(fp, line);
  }
}

void
get_psection_face(IgesFile *fp, PsectionEntityData *ps)
{
  int sequence_number = 0;
  static int line_count = 0;
  static int ps_object_count = 0;
  char temp_str[PS_MAX] = "";
  char *line = malloc(100);
  char substr[70];
  char *desc_array[PARAM_MAX] = {NULL};

  // psection_ht = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);

  line = get_line(fp, line);

  while (line){
    if (line[72] == 'P') {
      ++line_count;
      /* Add line to temp_str */
      get_field(line, substr, 1, 64);
      strncat(temp_str, substr, 65);

      if (line_count == 1) {
        /* get object 's sequence number */
        get_field(line, substr, 74, 8);
        sequence_number = utils_to_int(substr);
      }

      if (strchr(temp_str, ';')) {        /* ';' terminator found in string */
        /* Tokenize String & PS object creation */
        char *str = (char *)malloc(strlen(temp_str) + 1);
        strcpy(str, temp_str);
        utils_to_array(desc_array, str, DELIMITER);

        if (utils_to_int(desc_array[0]) == 510){
          parser_psection_new(ps, temp_str, sequence_number);
        }

        /* Initialize variable for next entity */
        ps = (PsectionEntityData *)malloc(sizeof(PsectionEntityData));
        temp_str[0] = '\0';
        line_count = 0;

        /* Count created objects */
        ++ps_object_count;
      }
    }

    line = get_line(fp, line);
  }
}

void
parser_psection_new(PsectionEntityData *ps_object, char *ps_line, int sequence_number)
{
  int entity_no;
  char *desc_array[PARAM_MAX] = {NULL};

  ps_object = (PsectionEntityData *)malloc(sizeof(PsectionEntityData));

  // printf("%s\n", ps_line);
  utils_to_array(desc_array, ps_line, DELIMITER);
  entity_no = utils_to_int(desc_array[0]);

  switch (entity_no) {
    case 502:
      ps_object->entity_param_ptr = sequence_number;
      ps_object->entity_type = entity_no;
      ps_object->entity_name = "VERTEXT LIST";
      ps_object->entity_data_object = vertexlist_extract(desc_array);
      parser_add_ps_object(psection_ht, ps_object);
      /* TODO : IMPORTANT CODE BELOW */
      // vertex_get_coords(NULL, ((VertexList *)ps_object->entity_data_object)->vertices[0]);
      // printf("%d\n", ((VertexList *)ps_object->entity_data_object)->n);
      break;
    case 504:
      ps_object->entity_param_ptr = sequence_number;
      ps_object->entity_type = entity_no;
      ps_object->entity_name = "EDGE LIST";
      ps_object->entity_data_object = edgelist_extract(desc_array);
      parser_add_ps_object(psection_ht, ps_object);
      break;
    case 508:
      ps_object->entity_param_ptr = sequence_number;
      ps_object->entity_type = entity_no;
      ps_object->entity_name = "LOOP";
      ps_object->entity_data_object = loop_extract(desc_array);
      parser_add_ps_object(psection_ht, ps_object);
      break;
    case 510:
      ps_object->entity_param_ptr = sequence_number;
      ps_object->entity_type = entity_no;
      ps_object->entity_name = "FACE";
      ps_object->entity_data_object = face_extract(desc_array);
      parser_add_ps_object(psection_ht, ps_object);
      break;
  }

  *desc_array = "";
}

void
parser_add_ps_object(GHashTable * ht, PsectionEntityData *ps)
{
  // printf("ON ADD>>>>>>>>>>>>\n");
  if(g_hash_table_insert(ht, GINT_TO_POINTER(ps->entity_param_ptr), (gpointer)ps) == TRUE){
    // printf("====================================\n");
    // printf("KEY : %d\n", GPOINTER_TO_INT(GINT_TO_POINTER(ps->entity_param_ptr)));
    // printf("Entity Name : %s\n", ps->entity_name);
    // printf("Entity Type : %d\n", ps->entity_type);
    // printf("Data Object : %p\n", (char *)ps->entity_data_object);
    // printf("====================================\n");

  }
}

void
get_dsection(IgesFile *fp, DsectionEntity *ds)
{
  char *line1 = malloc(91);
  char *line2 = malloc(91);
  dsection_ht = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);

  line1 = get_line(fp, line1);
  int i = 0;
  while (line1) {
    if (line1[72] == 'D') {
      line2 = get_line(fp, line2);
      // printf("Line 1 : %s", line1);
      // printf("Line 2 : %s", line2);

      parser_dsection_new(ds, line1, line2);
      // printf("%d\n", ds->sequence_number);
      parser_add_ds_object(dsection_ht, ds);
      ++i;
      ds = (DsectionEntity *) malloc(sizeof(DsectionEntity));

      if (i == 5){
        // break;
      }
      line1 = get_line(fp, line1);
    } else {
      line1 = get_line(fp, line1);
    }
  }
}

void
get_gsection(IgesFile *fp, char *lines, char ch)
{
  char *line = malloc(700);

  line = fgets(line, 81, fp);
  while(line != NULL){
    if(line[72] == ch){
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
  // printf("%s\n", desc_ptr);

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
}

void
parser_dsection_new(DsectionEntity *dsec_entity, char *line1, char *line2)
{
  char substr[10];

  // dsec_entity = (DsectionEntity *) malloc(sizeof(DsectionEntity));

  get_field(line1, substr, 1, 8);
  dsec_entity->entity_type = utils_to_int(substr);
  get_field(line1, substr, 9, 8);
  dsec_entity->ps_data_ptr  = utils_to_int(substr);
  dsec_entity->entity_object = NULL;
  get_field(line1, substr, 17, 8);
  dsec_entity->structure = utils_to_int(substr);
  get_field(line1, substr, 25, 8);
  dsec_entity->line_font_pattern = utils_to_int(substr);
  get_field(line1, substr, 33, 8);
  dsec_entity->layer_or_level = utils_to_int(substr);
  get_field(line1, substr, 41, 8);
  dsec_entity->view_ptr = utils_to_int(substr); /** TODO: Investigate the use of this value. */
  get_field(line1, substr, 49, 8);
  dsec_entity->transmatrix = utils_to_int(substr);
  // printf("%d\n", dsec_entity->transmatrix);
  dsec_entity->entity_transmatrix = NULL;
  get_field(line1, substr, 57, 7);
  dsec_entity->label_display_assoc = utils_to_int(substr);
  get_field(line1, substr, 65, 8);
  dsec_entity->status_number = utils_to_int(substr);
  get_field(line1, substr, 74, 8);
  dsec_entity->sequence_number = utils_to_int(substr);

  get_field(line1, substr, 9, 8);
  dsec_entity->line_weight = utils_to_int(substr);
  get_field(line1, substr, 17, 8);
  dsec_entity->color = utils_to_int(substr);
  get_field(line1, substr, 25, 8);
  dsec_entity->ps_line_count = utils_to_int(substr);
  get_field(line1, substr, 33, 8);
  dsec_entity->form_number = utils_to_int(substr);
  get_field(line1, substr, 57, 8);
  dsec_entity->entity_label = substr;
  get_field(line1, substr, 65, 8);
  dsec_entity->entity_subscript_number = utils_to_int(substr);
}

void
parser_add_ds_object(GHashTable * ht, DsectionEntity *dsec_entity)
{
  // printf("ON ADD>>>>>>>>>>>>\n");
  if(g_hash_table_insert(ht, GINT_TO_POINTER(dsec_entity->sequence_number), (gpointer)dsec_entity) == TRUE){
    // printf("KEY : %d\n", GPOINTER_TO_INT(GINT_TO_POINTER(dsec_entity->sequence_number)));
    // printf("SQ : %d\n", dsec_entity->sequence_number);
    // printf("Entity : %d\n", dsec_entity->entity_type);
    // printf("====================================\n");

  }
}

void
parser_find_entity(int lookup_key, void *key, void *value)
{
  // return (DsectionEntity *)g_hash_table_lookup(dsection_ht, GINT_TO_POINTER(1));
  gpointer *d = g_hash_table_lookup(dsection_ht, GINT_TO_POINTER(lookup_key));

  if (d) {
    /* code */
    print_dsec((DsectionEntity *)d);
  }

  // printf("ON PRINT>>>>>>>>>>>>>>>>>>>>\n");
  // g_hash_table_foreach(dsection_ht, print_values, NULL);
}

void
print_dsec(DsectionEntity *ds)
{
  printf("%d\n", ds->entity_type);
}

void
parser_dsection_add_entitydata(gpointer key, gpointer value, gpointer userdata)
{
  gpointer *obj = g_hash_table_lookup(psection_ht, GINT_TO_POINTER(((DsectionEntity *)value)->ps_data_ptr));
  if (obj != NULL) {
    // printf(">%p\n", (VertexList *)((PsectionEntityData *)obj)->entity_data_object);
    (((DsectionEntity *)value)->entity_object) = ((PsectionEntityData *)obj)->entity_data_object;
    // printf("%p\n", &(((DsectionEntity *)value)->entity_type));
    // printf("%p\n", &(((DsectionEntity *)value)->ps_data_ptr));
    // printf("%p\n", (((DsectionEntity *)value)->entity_object));
    // printf("%p\n", &(((DsectionEntity *)value)->structure));
    // printf("%p\n", &(((DsectionEntity *)value)->line_font_pattern));
    // printf("%p\n", &(((DsectionEntity *)value)->layer_or_level));
    // printf("%p\n", &(((DsectionEntity *)value)->transmatrix));
    // printf("%p\n", (((DsectionEntity *)value)->entity_transmatrix));
    // printf("%p\n", &(((DsectionEntity *)value)->label_display_assoc));
    // printf("%p\n", &(((DsectionEntity *)value)->status_number));
    // printf("%p\n", &(((DsectionEntity *)value)->sequence_number));
    // printf("===================================================\n");
    }
}

void
parser_dsection_add_transmatrix(gpointer key, gpointer value, gpointer userdata)
{
  if (((DsectionEntity *)value)->transmatrix != 0) {
    // gpointer *obj = g_hash_table_lookup(psection_ht, GINT_TO_POINTER(((DsectionEntity *)value)->transmatrix));
    // printf("wwwwww%s\n", ((PsectionEntityData *)obj)->entity_name);
    (((DsectionEntity *)value)->entity_transmatrix) = (TransformationMatrix *)((PsectionEntityData *) g_hash_table_lookup(psection_ht, GINT_TO_POINTER(((DsectionEntity *)value)->transmatrix)))->entity_data_object;
  }
}

void
parser_reassign_caller(void)
{
  g_hash_table_foreach(dsection_ht, parser_dsection_add_transmatrix, NULL);
  g_hash_table_foreach(dsection_ht, parser_dsection_add_entitydata, NULL);
}
//
// void
// print_values(gpointer key, gpointer value, gpointer userdata)
// {
//   int realkey = GPOINTER_TO_INT(key);
//   DsectionEntity *realvalue = (DsectionEntity *)value;
//
//   printf("KEY : %d\n", realkey);
//   printf("SQ : %d\n", realvalue->sequence_number);
//   printf("Entity : %d\n", realvalue->entity_type);
//   printf("====================================\n");
// }

Vertex *
dsection_get_vertex(int lookup_key, int index)
{
  gpointer *ds_object = g_hash_table_lookup(dsection_ht, GINT_TO_POINTER(lookup_key));
  if (ds_object == NULL) {
    /* code */
    // printf("ds NULL\n");
    return NULL;
  }
  // printf("%d\n", ((DsectionEntity *)ds_object)->ps_data_ptr);
  gpointer *ps_object = g_hash_table_lookup(psection_ht, GINT_TO_POINTER(((DsectionEntity *)ds_object)->ps_data_ptr));

  if (ps_object == NULL) {
    /* code */
    return NULL;
  }

  // printf("FOUND\n");
  // printf("X : %d\n", ((VertexList *)ps_object)->n);
  // printf("%Lg\n", ((VertexList *)((PsectionEntityData *)ps_object)->entity_data_object)->vertices[index - 1]->x);
  return ((VertexList *)((PsectionEntityData *)ps_object)->entity_data_object)->vertices[index - 1];
}

Edge *
dsection_get_edge(int entity_ptr, int index)
{
  gpointer *ds_object = g_hash_table_lookup(dsection_ht, GINT_TO_POINTER(entity_ptr));
  if (ds_object == NULL) {
    /* code */
    // printf("ds NULL\n");
    return NULL;
  }
  gpointer *ps_object = g_hash_table_lookup(psection_ht, GINT_TO_POINTER(((DsectionEntity *)ds_object)->ps_data_ptr));

  if (ps_object == NULL) {
    /* code */
    return NULL;
  }

  // printf("%s\n",((PsectionEntityData *)ps_object)->entity_name);
  // printf("X : %Lg\n", ((EdgeList *)((PsectionEntityData *)ps_object)->entity_data_object)->edges[3]->start_vertex->x);
  return ((EdgeList *)((PsectionEntityData *)ps_object)->entity_data_object)->edges[index - 1];
}

Loop *
dsection_get_loop(int entity_ptr)
{
  gpointer *ps_object = g_hash_table_lookup(psection_ht, GINT_TO_POINTER(entity_ptr));

  if (ps_object == NULL) {
    /* code */
    return NULL;
  }

  return ((Loop *)ps_object);
}

int
dsection_get_model_space_curve_type(int ds_index)
{
  gpointer *ds = g_hash_table_lookup(dsection_ht, GINT_TO_POINTER(ds_index));

  if (ds == NULL) {
    return -1;
  }

  return ((DsectionEntity *)ds)->form_number;
}
