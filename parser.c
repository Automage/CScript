#include <sys/types.h>
#include <stdlib.h>
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
static const char FUNCTION_REGEX[] = "^(\\w|\\[|\\]|\\*)+[ *]+(\\w|\\*)+\\((( *(\\w|\\[|\\]|\\*)+ +(\\w|\\[|\\]|\\*)+)?( *, *(\\w|\\[|\\]|\\*)+ +(\\w|\\[|\\]|\\*)+)*)? *\\) *\\{?$";

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

  // Read script line by line. If a function is detected, keeping reading
  // into that function until the brack count is equalized (where { is +1
  // and } is -1).
  //
  // This is a naive implementation which does not catch unmatched bracket
  // seqeunces such as {{}}}{ - although this is invalid C syntax and will
  // be detected by the compiler.

  int function_lock = 0;
  int bracket_sum = 0;
  char line[MAX_LINE_SIZE];
  char *func_content = malloc();
  while (fscanf(in_file, "%[^\n]\n", line) == 1) {
    // Bracket counting for functions
    if (function_lock) {

    } else if (regexec(&function_re, line, 0, NULL, 0) == 0) {
      // Match function
      printf("-----FUNC detected\n");
      function_lock = 1;
    } else if (regexec(&define_re, line, 0, NULL, 0) == 0) {
      // Match defines
      printf("-----DEF detected\n");
      add_define(script, line);
    } else if (regexec(&include_re, line, 0, NULL, 0) == 0) {
      // Match includes
      printf("-----INCLD detected\n");
      add_include(script, line);
    }
  }

  return 1;
}
