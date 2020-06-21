#include <config.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "rot13.h"

int main() {
  char buffer[64];

  snprintf(buffer, sizeof buffer, "abcdefghijklmnopqrstuvwxyz");
  rot13(buffer, strlen(buffer));
  assert(!strcmp(buffer, "nopqrstuvwxyzabcdefghijklm"));
  snprintf(buffer, sizeof buffer, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  rot13(buffer, strlen(buffer));
  assert(!strcmp(buffer, "NOPQRSTUVWXYZABCDEFGHIJKLM"));
  snprintf(buffer, sizeof buffer, "a0b1c2d3e4f5g6h7i8j9klmnopqrstuvwxyz");
  rot13(buffer, strlen(buffer));
  assert(!strcmp(buffer, "n0o1p2q3r4s5t6u7v8w9xyzabcdefghijklm"));
  return 0;
}
