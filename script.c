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

void append_main(struct script_layout *script, char *line) {
  if (line == NULL) {
    return;
  }

  if (script->main_size + strlen(line) >= script->max_main_buf) {
    // Reallocation
  }

  strcpy(script->main_body, line);
  script->main_size += strlen(line);
}

int add_define(struct script_layout *script, char *content) {
  if (content == NULL) {
    return -1;
  }

  if (script->n_defines + 1 >= script->max_defines) {
    // Reallocation
  }

  script->defines[script->n_defines] = content;
  script->n_defines++;
  return 1;
}

int add_include(struct script_layout *script, char *content) {
  if (content == NULL) {
    return -1;
  }
  if (script->n_includes + 1 >= script->max_includes) {
    // Reallocation
  }

  script->includes[script->n_includes] = content;
  script->n_includes++;
  return 1;
}

int add_function(struct script_layout *script, char *content) {
  if (content == NULL) {
    return -1;
  }

  if (script->n_functions + 1 >= script->max_functions) {
    // Reallocation
  }

  script->functions[script->n_functions] = content;
  script->n_functions++;
  return 1;
}

/*
 * Generate Source
 *
 * Write to the file specified by argument the final 
 * C code to be compiled, as infered from the cscript.
 */
int generate_source(struct script_layout *script, FILE *out) {
  return 1;
}
