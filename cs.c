#include <stdio.h>
#include <regex.h>

#include "script.h"

#define TMP_FILE_NAME "tmp.c"

FILE *create_source_file() {
  FILE *fp = fopen(TMP_FILE_NAME, "w");
  if (fp == NULL) {
    return NULL;
  }

  //fprintf(fp, "int main(int argc, char *argv[]) {%s}", NULL);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Please specify a c-script!");
    return -1;
  }

  FILE *script_fp = fopen(argv[1], "r");
  if (script_fp == NULL) {
    fprintf(stderr, "Unable to open file");
    return -1;
  }

  FILE *out_fp = create_source_file();
  if (out_fp == NULL) {
    fprintf(stderr, "Unable to create temporary files");
    return -1;
  }
}
