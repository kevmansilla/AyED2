#ifndef _HELPERS_H
#define _HELPERS_H

#include <stdio.h>

char* readline(FILE* file);
/*
 * Read the user input from specified FILE * until a newline is detected,
 * and return the corresponding (dinamically allocated) string.
 *
 * The caller to this function is responsible for the allocated memory.
 *
 * POST: A new null-terminated string is returned with the content read,
 * or NULL if there was an error.
 */

#endif
