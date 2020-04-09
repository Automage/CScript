#ifndef PARSER_H
#define PARSER_H

#include "script.h"

int parser_init(void);
int parse_script(struct script_layout *, FILE *);

#endif
