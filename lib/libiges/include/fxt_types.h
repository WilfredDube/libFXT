/**
* fxt_types.h
* - all externally visible types reside in this header file.
**/

#ifndef FXT_TYPES_H
#define FXT_TYPES_H

#define PARAM_MAX 1000 /**< Maximum number of parameters in the PD section. */
#define LOOPS_MAX 10 /** Maximum number of loops per face. */
#define DELIMITER ",;"

typedef enum _EdgeType EdgeType;

enum _EdgeType {
  ARC,
  LINE
};

/* IGES specification entity types. */
/* Point in 3-space (x,y,z) */
typedef struct _Point Point;
typedef struct _Point Vertex;

/* entity : 110 */
typedef struct _Line Line;

/* entity : 102 */
typedef struct _CompositeCurve CompositeCurve;

/* entity : 124 */
typedef struct _TransformationMatrix TransformationMatrix;

/* entity : 126 */
typedef struct _RBSCurve RBSCurve;
/* entity : 128 */
typedef struct _RBSSurface RBSSurface;

/* entity : 142*/
typedef struct _CurveOnParametricSurface CurveOnParametricSurface;
/* entity : 144*/
typedef struct _TrimmedSurface TrimmedSurface;

/* entity : 186*/
typedef struct _ManufoldSolidBrepObject ManufoldSolidBrepObject;
/* entity : 308 */
typedef struct _SubfigureDefObject SubfigureDefObject;
/* entity : 308 */
typedef struct _SingularSubfigureDefObject SingularSubfigureDefObject;
/* entity :  408*/
typedef struct _SingularSubfigureInstanceObject SingularSubfigureInstanceObject;

/* entity : 314 */
typedef struct _Color Color;
/* entity : 502 */
typedef struct _VertexList VertexList;

/* entity : 504 */
typedef struct _Edge Edge;
typedef struct _EdgeList EdgeList;

/* entity : 508 */
typedef struct _LoopEdge LoopEdge;
typedef struct _Loop Loop;

/* entity : 510 */
typedef struct _Face Face;

/* entity : 514 */
typedef struct _ShellFace ShellFace;
typedef struct _Shell Shell;

/** Parser types */
typedef struct _DsectionEntity DsectionEntity;
typedef struct _PsectionEntityData PsectionEntityData;
typedef struct _GsectionModelDesc GsectionModelDesc;

#endif
