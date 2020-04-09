#ifndef SCRIPT_H
#define SCRIPT_H

#include <stdio.h>

struct script_layout {
  char *main_body;

  char **defines;
  char **includes;
  char **functions;

  int main_size;
  int n_defines;
  int n_includes;
  int n_functions;

  int max_main_buf;
  int max_defines;
  int max_includes;
  int max_functions;
};

void layout_init(struct script_layout *);
int append_main(struct script_layout *, char *);
int add_define(struct script_layout *, char *);
int add_include(struct script_layout *, char *);
int add_function(struct script_layout *, char *);
int generate_source(struct script_layout *, FILE *);
void dealloc_layout(struct script_layout *);

#endif
