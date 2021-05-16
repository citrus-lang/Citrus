#include "lex.h"
#include "debug.h"
#include "stream.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

Token *new_token(TokenKind kind, Token *cur, Range range) {
  Token *tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  tok->range = range;
  cur->next = tok;
  return tok;
}

int lex_space(Stream **buf) {
  char c = peek(*buf);
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
  Range range;
  range.start = **buf;
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
  range.end = **buf;
  debug("Tokenized number '%d'", val);
  *cur = new_token(TK_NUM, *cur, range);
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
      char c = peek(buf);
      Range range;
      range.start = *buf;
      consume(buf);
      range.end = *buf;
      error(&range, "Unnexpected char '%c'.", c);
    }
  }
  Range range;
  range.start = *buf;
  range.end = *buf;
  cur = new_token(TK_EOF, cur, range);
  return head.next;
}

#ifdef UNIT_TEST
#include "test.h"
int main() {
  Token *a = lex(" 1 \n 42 ");
  assert_int(a->kind, TK_NUM);
  assert_int(a->val, 1);
  assert_int(a->next->kind, TK_NUM);
  assert_int(a->next->val, 42);
  assert_int(a->next->next->kind, TK_EOF);
}
#endif
