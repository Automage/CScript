#include <sys/types.h>
#include <regex.h>

#include "parser.h"

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
  const char FUNCTION_REGEX[] = "^\w+ \w+\((( *\w+ \w+)?(, *\w+ \w+)*)?\)$";

  // Regex intialization

  // Define regex
  regex_t define_re;

  // Include regex
  regex_t include_re;

  // Function regex
  regex_t function_re;
}
