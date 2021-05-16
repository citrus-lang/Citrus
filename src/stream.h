#ifndef _STREAM_H_
#define _STREAM_H_

typedef struct {
  char *pos;
  int col;
  int line;
} Stream;

typedef struct {
  Stream start;
  Stream end;
} Range;

Stream *new_stream(char *input);

char peek(Stream *buf);

void consume(Stream *buf);

void error(Range *range, char *fmt, ...);

#endif
