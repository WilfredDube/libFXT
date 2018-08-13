#ifndef FXT_PARSER_H
#define FXT_PARSER_H

#include "fxt_types.h"

struct _GsectionModelDesc {
};

struct _DsectionEntity {
};

struct _PsectionEntityData {
};

char *dsection_get_model_space_curve_type(int form_number);
Vertex *dsection_get_vertex(int start_vertex_ptr, int index);

PsectionEntityData *psection_entity_object_new(const int pd_pointer, const int ENTITY_TYPE, const char *ENTITY_NAME, void * entity_object);


#endif
