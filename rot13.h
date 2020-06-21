// © Richard Kettewell. See README.md for more info.
#ifndef ROT13_H
#define ROT13_H

#include <sys/types.h>

/* Overkill but fun */
#if __AVX__
typedef unsigned char vector __attribute__((vector_size(32)));
#define V(N)                                                                   \
  {                                                                            \
    N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, \
      N, N, N, N, N, N, N                                                      \
  }
#else
typedef unsigned char vector __attribute__((vector_size(16)));
#define V(N)                                                                   \
  { N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N }
#endif

#define STEP()                                                                 \
  do {                                                                         \
    vector *d = (vector *)buffer;                                              \
    const vector v = *d;                                                       \
    const vector bupl = (v >= v_A);                                            \
    const vector buph = (v <= v_M);                                            \
    const vector blpl = (v >= v_a);                                            \
    const vector blph = (v <= v_m);                                            \
    const vector bp = (bupl & buph) | (blpl & blph);                           \
    const vector bunl = (v >= v_N);                                            \
    const vector bunh = (v <= v_Z);                                            \
    const vector blnl = (v >= v_n);                                            \
    const vector blnh = (v <= v_z);                                            \
    const vector bn = (bunl & bunh) | (blnl & blnh);                           \
    *d = v + (bp & v_13) - (bn & v_13);                                        \
    buffer += sizeof(vector);                                                  \
    n -= sizeof(vector);                                                       \
  } while(0)

static void rot13(char *buffer, ssize_t n) {
  const vector v_A = V('A'), v_M = V('M'), v_N = V('N'), v_Z = V('Z');
  const vector v_a = V('a'), v_m = V('m'), v_n = V('n'), v_z = V('z');
  const vector v_13 = V(13);
  while(n > 0) {
    STEP();
    STEP();
    STEP();
    STEP();
  }
}

#endif
