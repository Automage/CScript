#ifndef SCRIPT_H
#define SCRIPT_H

struct script_layout {
  char *main_body;

  char **defines;
  char **includes;
  char **functions;

  int n_defines;
  int n_includes;
  int n_functions;
};

void layout_init(struct script_layout *);

#endif
