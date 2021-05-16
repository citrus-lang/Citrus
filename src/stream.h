#ifndef _STREAM_H_
#define _STREAM_H_

#include <stdlib.h>

typedef struct {
  char *input;
  char *cur;
  size_t col;
  size_t line;
} Stream;

Stream *new_stream(char *input);

int peek(Stream *buf);

void consume(Stream *buf);

void error(Stream *buf, char *fmt, ...);

#endif
