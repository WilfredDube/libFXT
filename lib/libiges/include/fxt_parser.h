#ifndef FXT_PARSER_H
#define FXT_PARSER_H

#include "fxt_types.h"

  PNONE,
struct _GsectionModelDesc {
};

struct _DsectionEntity {
};

struct _PsectionEntityData {
};

char *dsection_get_model_space_curve_type(int form_number);

Vertex *dsection_get_vertex(int entity_ptr, int index);
Edge *dsection_get_edge(int entity_ptr, int index);
Loop *dsection_get_loop(int entity_ptr);

PsectionEntityData *psection_entity_object_new(const int pd_pointer, const int ENTITY_TYPE, const char *ENTITY_NAME, void * entity_object);


#endif
