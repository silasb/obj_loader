#include <stdio.h>
#include <stdlib.h>
#include "obj_loader.h"

int main()
{
  Vertex **vertices;
  vertices = malloc(sizeof(vertices) * 2000);

  /*
  if(obj_load(filename, vertices) == -1) {
    fprintf(stderr, "Couldn't load object: %s\n", fileName);
    return NULL;
  }
  */

  printf("Testing\n");
}
