#include <stdlib.h>
#include <string.h>

#include "script.h"

#define MAIN_BUF_SIZE 1000
#define DEFAULT_BUF_SIZE 5

void layout_init(struct script_layout *script) {
  if (script == NULL) {
    return;
  }

  script->main_body = malloc(sizeof(char) * MAIN_BUF_SIZE);
  script->defines = malloc(sizeof(char *) * DEFAULT_BUF_SIZE);
  script->includes = malloc(sizeof(char *) * DEFAULT_BUF_SIZE);
  script->functions = malloc(sizeof(char *) * DEFAULT_BUF_SIZE);

  script->main_size = 0;
  script->n_defines = 0;
  script->n_includes = 0;
  script->n_functions = 0;

  script->max_main_buf = MAIN_BUF_SIZE;
  script->max_defines = DEFAULT_BUF_SIZE;
  script->max_includes = DEFAULT_BUF_SIZE;
  script->max_functions = DEFAULT_BUF_SIZE;
}

int append_main(struct script_layout *script, char *line) {
  if (line == NULL) {
    return - 1;
  }

  if (script->main_size + strlen(line) >= script->max_main_buf) {
    // Reallocation
  }

  strcat(script->main_body, line);
  script->main_size += strlen(line);
  return 0;
}

int add_define(struct script_layout *script, char *content) {
  if (content == NULL) {
    return -1;
  }

  if (script->n_defines + 1 >= script->max_defines) {
    // Reallocation
  }

  script->defines[script->n_defines] = strdup(content);
  script->n_defines++;
  return 0;
}

int add_include(struct script_layout *script, char *content) {
  if (content == NULL) {
    return -1;
  }
  if (script->n_includes + 1 >= script->max_includes) {
    // Reallocation
  }

  script->includes[script->n_includes] = strdup(content);
  script->n_includes++;
  return 0;
}

int add_function(struct script_layout *script, char *content) {
  if (content == NULL) {
    return -1;
  }

  if (script->n_functions + 1 >= script->max_functions) {
    // Reallocation
  }

  script->functions[script->n_functions] = strdup(content);
  script->n_functions++;
  return 0;
}

/*
 * Generate Source
 *
 * Write to the file specified by argument the final 
 * C code to be compiled, as infered from the cscript.
 */
int generate_source(struct script_layout *script, FILE *out_fp) {
  if (out_fp == NULL) {
    return -1;
  }

  // Write includes
  for (int i = 0; i < script->n_includes; i++) {
    fprintf(out_fp, "%s\n", script->includes[i]);
  }

  // Write defines
  for (int i = 0; i < script->n_defines; i++) {
    fprintf(out_fp, "%s\n", script->defines[i]);
  }

  // Write functions
  for (int i = 0; i < script->n_functions; i++) {
    fprintf(out_fp, "%s\n", script->functions[i]);
  }

  // Write main
  fprintf(out_fp, "%s\n", script->main_body);

  return 0;
}

/*
 * Deallocate Layout
 *
 * Deallocate the memory used for a script_layout
 */
void dealloc_layout(struct script_layout *script) {
  // Main
  free(script->main_body);

  // Defines
  for (int i = 0; i < script->n_defines; i++) {
    free(script->defines[i]);
  }
  free(script->defines);

  // Includes
  for (int i = 0; i < script->n_includes; i++) {
    free(script->includes[i]);
  }
  free(script->includes);

  // Functions
  for (int i = 0; i < script->n_functions; i++) {
    free(script->functions[i]);
  }
  free(script->functions);

  // Script
  free(script);
}
