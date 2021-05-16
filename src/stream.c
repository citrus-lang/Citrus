#include "stream.h"
#include "citrus.h"
#include <stdarg.h>
#include <stdio.h>

Stream *new_stream(char *input) {
  Stream *stream = calloc(1, sizeof(Stream));
  stream->input = input;
  stream->cur = input;
  stream->col = 1;
  stream->line = 1;
  return stream;
}

int peek(Stream *buf) { return *buf->cur; }

void consume(Stream *buf) {
  int c = peek(buf);
  buf->cur += 1;
  if (c == '\n') {
    buf->line += 1;
    buf->col = 1;
  } else {
    buf->col += 1;
  }
}

void error(Stream *buf, char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  fprintf(stderr, "[%lu,%lu] ", buf->line, buf->col);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

#ifdef UNIT_TEST
int main() {
  Stream *buf = new_stream("a\nb");
  assert_int(buf->line, 1);
  assert_int(buf->col, 1);
  assert_char(peek(buf), 'a');
  consume(buf);
  assert_int(buf->line, 1);
  assert_int(buf->col, 2);
  assert_char(peek(buf), '\n');
  consume(buf);
  assert_int(buf->line, 2);
  assert_int(buf->col, 1);
  assert_char(peek(buf), 'b');
}
#endif
