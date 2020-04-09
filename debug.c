#include "debug.h"

/*
 * Print Script
 *
 * Print the contents of the script layout passed 
 * as the arguement.
 */
void print_script(struct script_layout *script) {
  printf("###### Script Layout ######\n\n");

  // Main
  printf("Main body:\n%s\n\n", script->main_body);

  // Defines
  printf("Defines:\n");
  for (int i = 0; i < script->n_defines; i++) {
    printf("(%d) %s\n", i, script->defines[i]);
  }
  printf("\n");

  // Includes
  printf("Includes:\n");
  for (int i = 0; i < script->n_includes; i++) {
    printf("(%d) %s\n", i, script->includes[i]);
  }
  printf("\n");

  // Functions
  printf("Functions:\n");
  for (int i = 0; i < script->n_functions; i++) {
    printf("(%d)\n %s\n\n", i, script->functions[i]);
  }
}
