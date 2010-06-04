#include <stdio.h>
#include <stdlib.h>
#include "obj_loader.h"

int main(int argc, char *argv[])
{
  char *filename = argv[1];
  printf("opening: %s\n", filename);

  printf("alloc vertices\n");
  Vertex **vertices;
  vertices = malloc(sizeof(vertices) * 2000);

  printf("loading object\n");
  if(obj_load(filename, vertices) == -1) {
    fprintf(stderr, "Couldn't load object: %s\n", filename);
    exit(-1);
  }

//  printf("%f %f %f\n", vertices[0]->x, vertices[0]->y, vertices[0]->z);

  free(vertices);
}
