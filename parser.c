#include <sys/types.h>
#include <regex.h>

#include "parser.h"

#define MAX_LINE_SIZE 150

/*
 * Parse Script
 *
 * Read in_file line by line to populate script, using regex
 * to determine script features.
 */
int parse_script(struct script_layout *script, FILE *in_file) {
  if (in_file == NULL) {
    return -1;
  }

  // Regex constants

  const char DEFINE_REGEX[] = "^#define .*$";
  const char INCLUDE_REGEX[] = "^#include .*$";
  //const char FUNCTION_REGEX[] = "^\\w+ \\w+\\((( *\\w+ \\w+)?(, *\\w+ (\\w|\\[|\\])+)*)?\\) *\\{?$";
  //const char FUNCTION_REGEX[] = "^(\\w|\\[|\\]|\\*)+ (\\w|\\*)+\\((( *(\\w|\\[|\\]|\\*)+ (\\w|\\[|\\]|\\*)+)?(, *(\\w|\\[|\\]|\\*)+ (\\w|\\[|\\]|\\*)+)*)?\\) *\\{?$";
  // TODO: MAKE MACOS COMPATIBLE
  const char FUNCTION_REGEX[] = "^(\\w|\\[|\\]|\\*)+ +(\\w|\\*)+\\((( *(\\w|\\[|\\]|\\*)+ +(\\w|\\[|\\]|\\*)+)?( *, *(\\w|\\[|\\]|\\*)+ +(\\w|\\[|\\]|\\*)+)*)? *\\) *\\{?$";
  printf("reg: %s\n", FUNCTION_REGEX);
  // Regex intialization

  // Define regex
  regex_t define_re;
  if (regcomp(&define_re, DEFINE_REGEX, REG_EXTENDED | REG_NOSUB) == -1) {
    return -1;
  }

  // Include regex
  regex_t include_re;
  if (regcomp(&include_re, INCLUDE_REGEX, REG_EXTENDED | REG_NOSUB) == -1) {
    return -1;
  }

  // Function regex
  regex_t function_re;
  if (regcomp(&function_re, FUNCTION_REGEX, REG_EXTENDED | REG_NOSUB) == -1) {
    return -1;
  }

  // Parsing

  char line[MAX_LINE_SIZE];
  while (fscanf(in_file, "%[^\n]\n", line) == 1) {
    printf("%s\n", line);

    // Match defines
    if (regexec(&define_re, line, 0, NULL, 0) == 0) {
      printf("-----DEF detected\n");
    }

    // Match includes
    if (regexec(&include_re, line, 0, NULL, 0) == 0) {
      printf("-----INCLD detected\n");
    }

    // Match functions
    if (regexec(&function_re, line, 1, NULL, 0) == 0) {
      printf("-----FUNC detected\n");
    }
  }

  return 1;
}
