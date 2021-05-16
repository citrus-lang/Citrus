#include "citrus.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Token *new_token(TokenKind kind, Token *cur) {
  Token *tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  cur->next = tok;
  return tok;
}

int lex_num(Token **cur, char **buf) {
  if (isdigit(**buf)) {
    *cur = new_token(TK_NUM, *cur);
    (*cur)->val = strtol(*buf, buf, 10);
    return true;
  } else {
    return false;
  }
}

Token *lex(char *buf) {
  Token head;
  head.next = NULL;
  Token *cur = &head;
  while (*buf) {
    if (!lex_num(&cur, &buf)) {
      fprintf(stderr, "Cannot lex the input.\n");
      exit(1);
    }
  }
  cur = new_token(TK_EOF, cur);
  return head.next;
}

#ifdef UNIT_TEST
int main() {
  Token *a = lex("");
  assert_int(a->kind, TK_EOF);
  a = lex("1");
  assert_int(a->kind, TK_NUM);
  assert_int(a->val, 1);
  a = lex("42");
  assert_int(a->kind, TK_NUM);
  assert_int(a->val, 42);
}
#endif
