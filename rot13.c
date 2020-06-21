// © Richard Kettewell. See README.md for more info.
#include <config.h>

#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "rot13.h"

enum {
  OPT_HELP = UCHAR_MAX + 1,
  OPT_VERSION,
};

static const struct option options[] = {
  { "help", no_argument, NULL, OPT_HELP },
  { "version", no_argument, NULL, OPT_VERSION },
  { NULL, 0, NULL, 0 },
};

static void help(void) {
  printf("rot13 -- caesar cipher\n"
         "\n"
         "Usage:\n"
         "  rot13 [--] [PATH ...]\n"
         "Options:\n"
         "  --help                     Display usage message\n"
         "  --version                  Display version string\n");
}

#ifndef TAG
#define TAG "unknown"
#endif

static void version(void) {
  printf("version %s tag %s\n", PACKAGE_VERSION, TAG);
}

static ssize_t read_bytes(int fdin, char buffer[], size_t bufsize) {
  for(;;) {
    ssize_t n = read(fdin, buffer, bufsize);
    if(n < 0) {
      if(errno != EINTR)
        return -1;
    } else
      return n;
  }
}

static int write_bytes(int fdout, const char *buffer, size_t bytes) {
  while(bytes > 0) {
    ssize_t n = write(fdout, buffer, bytes);
    if(n < 0) {
      if(errno != EINTR)
        return -1;
    } else {
      buffer += n;
      bytes -= n;
    }
  }
  return 0;
}

static int rot13_stream(const char *path, int fdin, int fdout) {
  static char buffer[4096];
  ssize_t n;

  while((n = read_bytes(fdin, buffer, sizeof buffer)) > 0) {
    rot13(buffer, n);
    if(write_bytes(fdout, buffer, n) < 0) {
      perror("stdout");
      return 1;
    }
  }
  if(n < 0) {
    perror(path);
    return -1;
  }
  return 0;
}

int main(int argc, char **argv) {
  int n;
  while((n = getopt_long(argc, argv, "", options, NULL)) >= 0) {
    switch(n) {
    case OPT_HELP: help(); return 0;
    case OPT_VERSION: version(); return 0;
    default: return 1;
    }
  }
  if(argc == optind) {
    if(rot13_stream("stdin", 0, 1))
      return 1;
  } else {
    for(n = optind; n < argc; n++) {
      if(!strcmp(argv[n], "-")) {
        if(rot13_stream("stdin", 0, 1))
          return 1;
      } else {
        int fd = open(argv[n], O_RDONLY);
        if(fd < 0) {
          perror(argv[n]);
          return 1;
        }
        if(rot13_stream(argv[n], fd, 1))
          return 1;
        close(fd);
      }
    }
  }
  return 0;
}
