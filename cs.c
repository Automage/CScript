#include <stdlib.h>
#include <stdio.h>

#include "script.h"
#include "parser.h"
#include "debug.h"

#define TMP_FILE_NAME "tmp.c"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Please specify a c-script!\n");
    return -1;
  }

  // Open script file

  FILE *script_fp = fopen(argv[1], "r");
  if (script_fp == NULL) {
    fprintf(stderr, "Unable to open file\n");
    return -1;
  }

  // Parse script

  struct script_layout *script = malloc(sizeof(struct script_layout));
  layout_init(script);

  if (parser_init() != 0) {
    fprintf(stderr, "Failed to initialize parser\n");
    return -1;
  }

  parse_script(script, script_fp);

  print_script(script);

  // Generate source file
  /*
  FILE *out_fp = fopen("tmp.c", "w");
  if (out_fp == NULL) {
    fprintf(stderr, "Unable to create file\n");
    return -1;
  }
  generate_source(out_fp);
  */

  dealloc_layout(script);
}
