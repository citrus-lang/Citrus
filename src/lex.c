#include "lex.h"
#include "citrus.h"
#include "stream.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

Token *new_token(TokenKind kind, Token *cur) {
  Token *tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  cur->next = tok;
  return tok;
}

int lex_space(Stream **buf) {
  int c = peek(*buf);
  if (isspace(c)) {
    consume(*buf);
    return true;
  } else {
    return false;
  }
}

int lex_num(Token **cur, Stream **buf) {
  char c = peek(*buf);
  int val = 0;
  if ('1' <= c && c <= '9') {
    while (true) {
      c = peek(*buf);
      if (c < '0' || '9' < c) {
        break;
      }
      consume(*buf);
      val = val * 10 + (c - '0');
    }
  } else if (c == '0') {
    consume(*buf);
  } else {
    return false;
  }

  *cur = new_token(TK_NUM, *cur);
  (*cur)->val = val;
  return true;
}

Token *lex(char *input) {
  Token head;
  head.next = NULL;
  Token *cur = &head;
  Stream *buf = new_stream(input);
  while (peek(buf)) {
    if (!(lex_space(&buf) || lex_num(&cur, &buf))) {
      error(buf, "Unnexpected char '%c'.", peek(buf));
    }
  }
  cur = new_token(TK_EOF, cur);
  return head.next;
}

#ifdef UNIT_TEST
int main() {
  Token *a = lex(" 1 \n 42 ");
  assert_int(a->kind, TK_NUM);
  assert_int(a->val, 1);
  assert_int(a->next->kind, TK_NUM);
  assert_int(a->next->val, 42);
  assert_int(a->next->next->kind, TK_EOF);
}
#endif
