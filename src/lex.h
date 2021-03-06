#ifndef _LEX_H_
#define _LEX_H_

#include "stream.h"

typedef enum {
  TK_NUM,
  TK_EOF,
} TokenKind;

typedef struct Token Token;

struct Token {
  TokenKind kind;
  Token *next;
  Range range;
  int val;
};

Token *lex(char *input);

#endif
