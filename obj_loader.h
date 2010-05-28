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
  INT_T
} token_t;

typedef struct {
  float x, y, z;
} Vertex; 

/*
 * public prototypes
 */
int obj_load(char *filename, Vertex **);

/*
 * private prototypes
 */
Vertex  *_getVertex(void);
token_t _getToken(FILE *);
token_t _getFloat(FILE *);
float   _getValue(void);

#endif 