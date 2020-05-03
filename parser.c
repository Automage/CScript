#include <sys/types.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#include "parser.h"

#define MAX_LINE_SIZE 150
#define FUNC_BUF_INIT_SIZE 150

/*
 * Regex string constants
 */
static const char DEFINE_REGEX[] = "^#define .*$";
static const char INCLUDE_REGEX[] = "^#include .*$";
static const char SHEBANG_REGEX[] = "^#!.*$";
//const char FUNCTION_REGEX[] = "^\\w+ \\w+\\((( *\\w+ \\w+)?(, *\\w+ (\\w|\\[|\\])+)*)?\\) *\\{?$";
//const char FUNCTION_REGEX[] = "^(\\w|\\[|\\]|\\*)+ (\\w|\\*)+\\((( *(\\w|\\[|\\]|\\*)+ (\\w|\\[|\\]|\\*)+)?(, *(\\w|\\[|\\]|\\*)+ (\\w|\\[|\\]|\\*)+)*)?\\) *\\{?$";
// TODO: MAKE MACOS COMPATIBLE
static const char FUNCTION_REGEX[] = "^(\\w|\\[|\\]|\\*)+[ *]+(\\w|\\*)+\\((( *(\\w|\\[|\\]|\\*)+ +(\\w|\\[|\\]|\\*)+)?( *, *(\\w|\\[|\\]|\\*)+ +(\\w|\\[|\\]|\\*)+)*)? *\\) *\\{?$";

/*
 * Regex structures
 */
static regex_t define_re;
static regex_t include_re;
static regex_t shebang_re;
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

  // Shebang regex
  if (regcomp(&shebang_re, SHEBANG_REGEX, REG_EXTENDED | REG_NOSUB) == -1) {
    return -1;
  }

  // Function regex
  if (regcomp(&function_re, FUNCTION_REGEX, REG_EXTENDED | REG_NOSUB) == -1) {
    return -1;
  }

  return 0;
}

/*
 * Helper: calculate bracket Sum
 */
static int calc_bracket_sum(char *line) {
  int sum = 0;
  for (int i = 0; i < strlen(line); i++) {
    if (line[i] == '{') {
      sum++;
    } else if (line[i] == '}') {
      sum--;
    }
  }
  return sum;
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
  // seqeunces such as '{{}}}{' - although this is invalid C syntax and will
  // be detected by the compiler.

  int function_lock = 0;
  int bracket_sum = 0;
  char line[MAX_LINE_SIZE];
  int func_buf_size = FUNC_BUF_INIT_SIZE;
  char *func_content = malloc(func_buf_size * sizeof(char));
  func_content[0] = '\0';

  while (fscanf(in_file, "%[^\n]\n", line) == 1) {
    printf("%s\n", line);
    // If not adding to a function
    if (!function_lock) {
      if (regexec(&function_re, line, 0, NULL, 0) == 0) {
        // Match function
        function_lock = 1;
      } else if (regexec(&define_re, line, 0, NULL, 0) == 0) {
        // Match defines
        add_define(script, line);
      } else if (regexec(&include_re, line, 0, NULL, 0) == 0) {
        // Match includes
        add_include(script, line);
      } else if (regexec(&shebang_re, line, 0, NULL, 0) == 0) {
        // Match shebang
        // Do nothing
      } else {
        // Main body
        append_main(script, line);
      }
    }

    // Add line to function
    if (function_lock) {
      // Reallocation if func_buf is not large enough
      if (strlen(line) + strlen(func_content) + 2 > func_buf_size) {
        func_buf_size = func_buf_size * 2;
        func_content = realloc(func_content, func_buf_size);
      }
      strcat(func_content, line);

      // End function when bracket sum is 0
      bracket_sum += calc_bracket_sum(line);
      if (bracket_sum == 0) {
        add_function(script, func_content);
        func_buf_size = FUNC_BUF_INIT_SIZE;
        func_content = realloc(func_content, func_buf_size);
        func_content[0] = '\0';
        function_lock = 0;
      }
    }
  }
  free(func_content);

  // Return error if bracket sum is not 0
  if (bracket_sum != 0) {
    fprintf(stderr, "Invalid function syntax");
    return -1;
  }

  return 0;
}

