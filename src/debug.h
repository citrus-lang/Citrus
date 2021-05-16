#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef DEBUG_BUILD
#include <stdio.h>
#define debug(fmt, ...)                                                        \
  do {                                                                         \
    fprintf(stderr, "(%s:%d@%s): ", __FILE__, __LINE__, __func__);             \
    fprintf(stderr, fmt, ##__VA_ARGS__);                                       \
  } while (0)
#else
#define debug(fmt, ...)
#endif

#endif
