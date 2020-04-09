#include <sys/types.h>
#include <regex.h>

#include "parser.h"

#define MAX_LINE_SIZE 150

/*
 * Regex string constants
 */
static const char DEFINE_REGEX[] = "^#define .*$";
static const char INCLUDE_REGEX[] = "^#include .*$";
//const char FUNCTION_REGEX[] = "^\\w+ \\w+\\((( *\\w+ \\w+)?(, *\\w+ (\\w|\\[|\\])+)*)?\\) *\\{?$";
//const char FUNCTION_REGEX[] = "^(\\w|\\[|\\]|\\*)+ (\\w|\\*)+\\((( *(\\w|\\[|\\]|\\*)+ (\\w|\\[|\\]|\\*)+)?(, *(\\w|\\[|\\]|\\*)+ (\\w|\\[|\\]|\\*)+)*)?\\) *\\{?$";
// TODO: MAKE MACOS COMPATIBLE
static const char FUNCTION_REGEX[] = "^(\\w|\\[|\\]|\\*)+ +(\\w|\\*)+\\((( *(\\w|\\[|\\]|\\*)+ +(\\w|\\[|\\]|\\*)+)?( *, *(\\w|\\[|\\]|\\*)+ +(\\w|\\[|\\]|\\*)+)*)? *\\) *\\{?$";

/*
 * Regex structures
 */
static regex_t define_re;
static regex_t include_re;
static regex_t function_re;


/*
 * Parser Init
 *
 * Initialize regex structures
 */
int parser_init() {
  // Regex intialization

  // Define regex
  if (regcomp(&define_re, DEFINE_REGEX, REG_EXTENDED | REG_NOSUB) == -1) {
    return -1;
  }

  // Include regex
  if (regcomp(&include_re, INCLUDE_REGEX, REG_EXTENDED | REG_NOSUB) == -1) {
    return -1;
  }

  // Function regex
  if (regcomp(&function_re, FUNCTION_REGEX, REG_EXTENDED | REG_NOSUB) == -1) {
    return -1;
  }

  return 0;
}

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

  printf("reg: %s\n", FUNCTION_REGEX);

  // Parsing

  char line[MAX_LINE_SIZE];
  while (fscanf(in_file, "%[^\n]\n", line) == 1) {
    //printf("%s\n", line);

    // Match defines
    if (regexec(&define_re, line, 0, NULL, 0) == 0) {
      printf("-----DEF detected\n");
      add_define(script, line);
    }

    // Match includes
    if (regexec(&include_re, line, 0, NULL, 0) == 0) {
      printf("-----INCLD detected\n");
      add_include(script, line);
    }

    // Match functions
    if (regexec(&function_re, line, 1, NULL, 0) == 0) {
      printf("-----FUNC detected\n");
    }
  }

  return 1;
}
