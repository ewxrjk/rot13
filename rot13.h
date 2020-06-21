#ifndef ROT13_H
#define ROT13_H

#include <sys/types.h>

typedef unsigned char vector __attribute__((vector_size(16)));

static inline void rot13_simd(vector *d) {
  vector v = *d;

  vector upl = (v >= 'A');
  vector uph = (v <= 'M');
  vector lpl = (v >= 'a');
  vector lph = (v <= 'm');
  vector p = (upl & uph) | (lpl & lph);

  vector unl = (v >= 'N');
  vector unh = (v <= 'Z');
  vector lnl = (v >= 'n');
  vector lnh = (v <= 'z');
  vector n = (unl & unh) | (lnl & lnh);

  *d = v + (p & 13) + (n & (unsigned char)(-13));
}

static void rot13(char *buffer, ssize_t n) {
  while((size_t)n >= sizeof(vector)) {
    rot13_simd((vector *)buffer);
    buffer += sizeof(vector);
    n -= sizeof(vector);
  }
  while(n > 0) {
    int ch = *buffer;
    if((ch >= 'A' && ch <= 'M') || (ch >= 'a' && ch <= 'm'))
      ch += 13;
    else if((ch >= 'N' && ch <= 'Z') || (ch >= 'n' && ch <= 'z'))
      ch -= 13;
    *buffer++ = ch;
    --n;
  }
}

#endif
