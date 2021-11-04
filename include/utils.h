#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_PINK    "\x1b[95m"
#define ANSI_COLOR_BRIGHT_BLUE    "\x1b[36m"
#define ANSI_COLOR_BLUE    "\x1b[34m"

#define ERROR_LOGIC_MESSAGE "FAILED"

#define ASSERT(expr) \
do\
{ \
    	if (!(expr)) \
    		fprintf(stderr, ERROR_LOGIC_MESSAGE); \
} while(0)


#define FREE(p) \
do \
{ \
  free(p); \
  p = NULL; \
} \
while(0)




#define ERROR_ALLOC_MESSAGE "Insufficient memory"
#define ERROR_OPEN_FILE_MESSAGE "Cant open file"

#define MALLOC(p, n) \
do \
{ \
  if ( !( (p) = malloc(sizeof(*(p)) * (n)) ) ) \
  { \
    fprintf(stderr, ERROR_ALLOC_MESSAGE); \
    exit(EXIT_FAILURE); \
  } \
} \
while(0)

#define CALLOC(p, n) \
do \
{ \
  if ( !( (p) = calloc((n), sizeof(*(p))) ) ) \
  { \
    fprintf(stderr, ERROR_ALLOC_MESSAGE); \
    exit(EXIT_FAILURE); \
  } \
} \
while(0)

#define REALLOC(p, n) \
do \
{ \
  if ( !( (p) = realloc((p), sizeof(*(p)) * (n)) ) ) \
  { \
    fprintf(stderr, ERROR_ALLOC_MESSAGE); \
    exit(EXIT_FAILURE); \
  } \
} \
while(0)


#define OPENFILE(p, f, s) \
do \
{ \
  if ( !(  (p) = fopen((f), (s)))) \
  { \
    fprintf(stderr, ERROR_OPEN_FILE_MESSAGE); \
    exit(EXIT_FAILURE); \
  } \
} \
while(0)  

#define UNUSED(x) (void)(x)








#endif
