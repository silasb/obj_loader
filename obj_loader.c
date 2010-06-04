/*
 * loads the .obj file format
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
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
  while((token = _getToken(fp)) != NULL_T) // NULL_T is EOF
  {
    if(token == VERTEX_T) {
      printf("v ");
      vertices[vertex_num++] = _getVertex();
    }
    else if(token == VERTEX_NORM_T) {
      Vertex *test;
      printf("vn ");
      test = _getVertex();
    }
    else
      ;
  }

  fclose(fp);

  return 0;
}

Vertex *_getVertex()
{
  Vertex *vertex;
  vertex = malloc(sizeof(*vertex));

  fscanf(fp, "%f %f %f", &vertex->x, &vertex->y, &vertex->z);

  printf("(%f ", vertex->x);
  printf("%f ", vertex->y);
  printf("%f)\n", vertex->z);

  return vertex;
}

token_t _getToken(FILE *fp)
{
  str_loc = 0;
  char c;
  while((c = getc(fp)) == ' ' || c == '\n' || c == '\t' || c == '\r')
    ;
  if(c == 'v') {
    c = getc(fp);
    if(c == 'n')
      return VERTEX_NORM_T;
    return VERTEX_T;
  }
  else if(c == 'f')
    return FACE_T;
  else if(c == '#') {
    // we have a comment
    if((c = getc(fp) == ' '))
      ;
    else
      ungetc(c, fp);
    char comment[80];
    fgets(comment, 80, fp);
    return COMMENT_T;
  }
  else if(c == 'm') {
    ungetc(c, fp);
    char command[80];
    char filename[80];
    fscanf(fp, "%s", command);
    if(strcmp(command, "mtllib") == 0) {
      fscanf(fp, " %s", filename);
    }
    return MAT_T;
  }
  else if(c == 'o') {
    char temp[80];
    fgets(temp, 80, fp);
    return OBJNAME_T;
  }
  else if(c == 'g') {
    // group name
    char group_name[80];
    fscanf(fp, "%s", group_name);
    return GROUP_NAME_T;
  }
  else if(c == 'u') {
    ungetc(c, fp);
    char temp[80];
    char mat[80];
    fgets(temp, 80, fp);
    if(strcmp(temp, "usemtl") == 0) {
      fscanf(fp, "%s", mat);
    }
    return USEMAT_T;
  }
  else
    return NULL_T;
}

token_t _getFloat(FILE *fp)
{
  char c;
  while((c = getc(fp)) && isdigit(c))
    str_value[str_loc++] = c;
  if(c == 'e')
  {
    c = getc(fp);
    if(c == '+')
      ;
  } else
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
