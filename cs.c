#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "script.h"
#include "parser.h"
#include "debug.h"

#define TMP_FILE_NAME "tmp.c"
#define EXEC_NAME "cscript"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Please specify a c-script!\n");
    return -1;
  }

  // Open script file and tmp file

  FILE *script_fp = fopen(argv[1], "r");
  if (script_fp == NULL) {
    fprintf(stderr, "Unable to open file\n");
    return -1;
  }

  FILE *out_fp = fopen(TMP_FILE_NAME, "w");
  if (out_fp == NULL) {
    fprintf(stderr, "Unable to create temp file\n");
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

  // Debug printing

  //print_script(script);

  // Generate source file

  generate_source(script, out_fp);
  dealloc_layout(script);

  // Close files
  fclose(script_fp);
  fclose(out_fp);

  // Compile generated C file

  int ret = fork();
  if (ret == -1) {
    perror("fork");
    return -1;
  } else if (ret == 0) { // Child process
    execlp("/usr/bin/gcc", "gcc", "-o", EXEC_NAME, TMP_FILE_NAME, (char *) NULL);
    _exit(0);
  } else { // Parent process
    waitpid(ret, NULL, 0);
  }

  // Execute generated executable

  ret = fork();
  if (ret == -1) {
    perror("fork");
    return -1;
  } else if (ret == 0) { // Child process
    execlp(EXEC_NAME, EXEC_NAME, (char *) NULL);
    _exit(-1);
  } else { // Parent process
    waitpid(ret, NULL, 0);
  }

  // Cleanup
  if (remove(EXEC_NAME) != 0) {
    fprintf(stderr, "Failed to cleanup temporary files\n");
    return -1;
  }

  return 0;
}
