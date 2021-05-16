#include "stream.h"
#include "debug.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

Stream *new_stream(char *input) {
  Stream *stream = calloc(1, sizeof(Stream));
  stream->pos = input;
  stream->col = 1;
  stream->line = 1;
  return stream;
}

char peek(Stream *buf) { return *buf->pos; }

void consume(Stream *buf) {
  int c = peek(buf);
  buf->pos += 1;
  if (c == '\n') {
    buf->line += 1;
    buf->col = 1;
  } else {
    buf->col += 1;
  }
}

void error(Range *range, char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  debug("start.line = %d", range->start.line);
  debug("start.col  = %d", range->start.col);
  debug("end.line   = %d", range->end.line);
  debug("end.col    = %d", range->end.col);
  int linenum = range->end.line;
  int linenum_len = 1;
  while (linenum >= 10) {
    linenum /= 10;
    linenum_len += 1;
  }
  fprintf(stderr, " %*s |\n", linenum_len, "");
  fprintf(stderr, " %*d | ", linenum_len, range->start.line);
  char *line_start = range->start.pos - range->start.col + 1;
  int line_len = 0;
  while (*line_start != '\n' && *line_start) {
    fputc(*line_start, stderr);
    line_start += 1;
    line_len += 1;
  }
  line_start += 1;
  fprintf(stderr, "\n %*s | %*s", linenum_len, "", range->start.col - 1, "");
  if (range->start.line == range->end.line) {
    int c = range->start.col;
    while (c < range->end.col) {
      fputc('^', stderr);
      c += 1;
    }
  } else {
    int c = range->start.col;
    while (c <= line_len) {
      fputc('^', stderr);
      c += 1;
    }
    int l = range->start.line + 1;
    while (l < range->end.line) {
      fprintf(stderr, "\n %*d | ", linenum_len, l);
      line_len = 0;
      while (*line_start != '\n' && *line_start) {
        fputc(*line_start, stderr);
        line_start += 1;
        line_len += 1;
      }
      line_start += 1;
      fprintf(stderr, "\n %*s | ", linenum_len, "");
      c = 1;
      while (c <= line_len) {
        fputc('^', stderr);
        c += 1;
      }
      l += 1;
    }
    fprintf(stderr, "\n %*d | ", linenum_len, l);
    line_len = 0;
    while (*line_start != '\n' && *line_start) {
      fputc(*line_start, stderr);
      line_start += 1;
      line_len += 1;
    }
    line_start += 1;
    fprintf(stderr, "\n %*s | ", linenum_len, "");
    c = 1;
    while (c <= range->end.col) {
      fputc('^', stderr);
      c += 1;
    }
  }
  fputc(' ', stderr);
  vfprintf(stderr, fmt, ap);
  fputc('\n', stderr);
  exit(1);
}

#ifdef UNIT_TEST
#include "test.h"
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
