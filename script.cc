#include "script.h"

#define MAIN_BUF_SIZE 1000

void layout_init(struct script_layout *layout) {
  if (layout == NULL) {
    return;
  }

  layout->main_body = malloc(sizeof(char) * FUNCTION_BUF_SIZE);
}
