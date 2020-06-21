#ifndef ROT13_H
#define ROT13_H

#include <sys/types.h>

static void rot13(char *buffer, ssize_t n) {
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
