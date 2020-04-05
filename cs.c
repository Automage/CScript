#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Please specify a c-script!");
    return -1;
  }

  FILE *fp = fopen(argv[1]);
  if (fp == NULL) {
    fprintf(stderr, "Unable to open file");
    return -1;
  }

}
