#ifndef FXT_PARSER_H
#define FXT_PARSER_H

#include "fxt_types.h"

#include <stdio.h>

typedef enum unit{
  INCH = 1,
  MILLIMTER,
  FEET,
  MILES,
  METER,
  KILOMETER,
  MILS,
  MICRONS,
  CENTIMETER,
  MICROINCHES
} Unit;

typedef enum pattern {
  PNONE,
  SOLID,
  DASHED,
  PHANTOM,
  CENTERLINE,
  DOTTED
} Pattern;

struct _GsectionModelDesc {
  char param_delimeter;
  char record_delimeter;
  char *source_PID;
  char *filename;
  char *native_system_PID;
  char *preprocessor_version;
  int nbits;
  int max_float_power;
  int number_of_sig_digits_float;
  int max_double_power;
  int number_of_sig_digits_double;
  char *receiver_PID;
  float model_space_scale;
  Unit unit_flag;
  char *unit_name;
  long double max_line_weight;
  int max_line_weight_gradations;
  char *date_time_of_generation;
  long double min_resolution_or_granulation; /**< TODO: Investigate this value. */
  long double approx_max_coordinate;
  char *author_name;
  char *author_organization;
  int specification_version; /** TODO: enum 0 - 7  */
  int drafting_standard; /** TODO: enum 0 - 7  */
  char *created_or_last_modification_time;
  char *descriptor;
};

struct _DsectionEntity {
  int entity_type;
  int ps_data_ptr;
  void *entity_object;
  int structure;
  Pattern line_font_pattern;
  int layer_or_level;
  int view_ptr; /** TODO: Investigate the use of this value. */
  int transmatrix;
  TransformationMatrix *entity_transmatrix;
  int label_display_assoc;
  int status_number;
  int sequence_number;
  int line_weight;
  int color;
  int ps_line_count;
  int form_number;
  char *entity_label;
  unsigned entity_subscript_number;
};

struct _PsectionEntityData {
  int entity_param_ptr;
  int entity_type;
  int entity_name;
  void *entity_data_object;
};

typedef FILE IgesFile;

void get_gsection(IgesFile *fp, char *line);
void parser_gsection_new(GsectionModelDesc *gsec_model_desc, char *desc_ptr);
char *dsection_get_model_space_curve_type(int form_number);

Vertex *dsection_get_vertex(int entity_ptr, int index);
Edge *dsection_get_edge(int entity_ptr, int index);
Loop *dsection_get_loop(int entity_ptr);

PsectionEntityData *psection_entity_object_new(const int pd_pointer, const int ENTITY_TYPE, const char *ENTITY_NAME, void * entity_object);

#endif
