#ifndef _STREAM_H_
#define _STREAM_H_

typedef struct {
  char *input;
  char *cur;
  int col;
  int line;
} Stream;

Stream *new_stream(char *input);

char peek(Stream *buf);

void consume(Stream *buf);

void error(Stream *buf, char *fmt, ...);

#endif
