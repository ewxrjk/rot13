// © Richard Kettewell. See README.md for more info.
#include <config.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "rot13.h"

static struct {
  const char *input, *output;
} cases[] = {
  { "abcdefghijklmnopqrstuvwxyz", "nopqrstuvwxyzabcdefghijklm" },
  { "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "NOPQRSTUVWXYZABCDEFGHIJKLM" },
  { "a0b1c2d3e4f5g6h7i8j9klmnopqrstuvwxyz",
    "n0o1p2q3r4s5t6u7v8w9xyzabcdefghijklm" },
  { NULL, NULL },
};

int main() {
  static char buffer[4096];
  size_t i;

  for(i = 0; cases[i].input; i++) {
    printf("buffer=%p\n", buffer);
    strcpy(buffer, cases[i].input);
    rot13(buffer, strlen(buffer));
    printf("Case %zu:\n   input: %s\n  expect: %s\n     got: %s\n\n", i,
           cases[i].input, cases[i].output, buffer);
    assert(!strcmp(buffer, cases[i].output));
  }
  return 0;
}
