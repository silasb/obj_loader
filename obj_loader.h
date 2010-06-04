#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <stdio.h>

/*
 * variables
 */
float value;

/*
 * structures
 */
typedef enum {
  NULL_T,
  VERTEX_T,
  FACE_T,
  FLOAT_T,
  INT_T,
  COMMENT_T,
  MAT_T,
  OBJNAME_T,
  VERTEX_NORM_T,
  GROUP_NAME_T,
  USEMAT_T
} token_t;

typedef struct {
  float x, y, z;
} Vertex; 

typedef struct {
  int vert1, vert2, vert3, vert4;
} Face;

/*
 * public prototypes
 */
int obj_load(char *filename, Vertex **);

/*
 * private prototypes
 */
Vertex *_getVertex(void);
Face   *_getFace();
token_t _getToken(FILE *);
token_t _getFloat(FILE *);
float   _getValue(void);

#endif 
