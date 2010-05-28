/*
 * loads the .obj file format
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "obj_loader.h"

// stores the current value of the token if it is a number
char str_value[10];
int str_loc = 0;
token_t token;
FILE *fp = NULL;

int obj_load(char *filename, Vertex **vertices)
{

  if((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Error loading file: %s\n", filename);
    return -1;
  }

  int vertex_num = 0;
  while((token = _getToken(fp)) == VERTEX_T)
  {
    vertices[vertex_num++] = _getVertex();
  }

  fclose(fp);

  return 0;
}

Vertex *_getVertex()
{
  Vertex *vertex;
  vertex = malloc(sizeof(*vertex));

  token = _getToken(fp); // gets x
  vertex->x = _getValue();
  token = _getToken(fp); // gets y
  vertex->y = _getValue();
  token = _getToken(fp); // gets z
  vertex->z = _getValue();

  return vertex;
}

token_t _getToken(FILE *fp)
{
  str_loc = 0;
  char c;
  while((c = getc(fp)) == ' ' || c == '\n' || c == '\t')
    ;
  if(c == 'v')
    return VERTEX_T;
  else if(c == 'f')
    return FACE_T;
  else if(isdigit(c)) {
    str_value[str_loc++] = c;
    if((c = getc(fp)) == '.' || isdigit(c)) {
      str_value[str_loc++] = c;
      return _getFloat(fp);
    } else {
      ungetc(c, fp);
      return INT_T;
    }
  }
  else if(c == '-') {
    str_value[str_loc++] = '-';
    c = getc(fp);
    str_value[str_loc++] = c;
    if((c = getc(fp)) == '.' || isdigit(c)) {
      str_value[str_loc++] = c;
      return _getFloat(fp);
    } else {
      ungetc(c, fp);
      return INT_T;
    }
  }
  else
    return NULL_T;
}

token_t _getFloat(FILE *fp)
{
  char c;
  while((c = getc(fp)) && isdigit(c))
    str_value[str_loc++] = c;
  ungetc(c, fp);
  str_value[str_loc++] = '\0';
  return FLOAT_T;
}

float _getValue()
{
  if(token == FLOAT_T)
    sscanf(str_value, "%f", &value);
  else if(token == INT_T)
    sscanf(str_value, "%f", &value);
  return value;
}
