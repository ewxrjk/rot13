// © Richard Kettewell. See README.md for more info.
#ifndef ROT13_H
#define ROT13_H

#include <sys/types.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* Fast rot13 implementation */

#ifndef VECTORIZE
#if __GNUC__
#define VECTORIZE 1
#else
#define VECTORIZE 0
#endif
#endif

#if VECTORIZE
/* Overkill but fun */
#if __AVX__
typedef unsigned char vector __attribute__((vector_size(32)));
#else
typedef unsigned char vector __attribute__((vector_size(16)));
#endif

#define STEP()                                                                 \
  do {                                                                         \
    vector *d = (vector *)buffer;                                              \
    const vector v = *d;                                                       \
    const vector bupl = (v >= 'A');                                            \
    const vector buph = (v <= 'M');                                            \
    const vector blpl = (v >= 'a');                                            \
    const vector blph = (v <= 'm');                                            \
    const vector bp = (bupl & buph) | (blpl & blph);                           \
    const vector bunl = ~buph;                                                 \
    const vector bunh = (v <= 'Z');                                            \
    const vector blnl = ~blph;                                                 \
    const vector blnh = (v <= 'z');                                            \
    const vector bn = (bunl & bunh) | (blnl & blnh);                           \
    *d = v + (bp & 13) - (bn & 13);                                            \
    buffer += sizeof(vector);                                                  \
    n -= sizeof(vector);                                                       \
  } while(0)
#else
#define STEP()                                                                 \
  do {                                                                         \
    int v = *buffer;                                                           \
    if((v >= 'A' && v <= 'M') || (v >= 'a' && v <= 'm'))                       \
      v += 13;                                                                 \
    else if((v >= 'N' && v <= 'Z') || (v >= 'n' && v <= 'z'))                  \
      v -= 13;                                                                 \
    *buffer = v;                                                               \
    buffer++;                                                                  \
    n--;                                                                       \
  } while(0)
#endif

static void rot13(char *buffer, ssize_t n) {
  while(n > 0) {
    STEP();
    STEP();
  }
}

#endif
