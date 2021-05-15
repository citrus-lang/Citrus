#ifndef _CITRUS_H_
#define _CITRUS_H_

// Debug print macros.
#ifdef DEBUG_BUILD
#define debug(fmt, ...)                                                        \
  do {                                                                         \
    fprintf(stderr, "file : %s, line : %d, func : %s, ", __FILE__, __LINE__,   \
            __func__);                                                         \
    fprintf(stderr, fmt, ##__VA_ARGS__);                                       \
  } while (0)
#else
#define debug(fmt, ...)
#endif

#endif
