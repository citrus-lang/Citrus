#ifndef _LEX_H_
#define _LEX_H_

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

typedef enum {
  TK_NUM,
  TK_EOF,
} TokenKind;

typedef struct Token Token;

struct Token {
  TokenKind kind;
  Token *next;
  int val;
};

Token *lex(char *input);

#endif
