// © Richard Kettewell. See README.md for more info.
#include <config.h>

#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

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

/* Read from fdin, retrying on EINTR */
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

/* Write to fdout retrying on EINTR and short writes */
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

/* rot13 a file using mmap, starting from pos.
 * pos must be a multiple of the page size. */
static int rot13_mapped(const char *path, int fdin, int fdout, off_t pos,
                        off_t size) {
  while(pos < size) {
    size_t remain = MIN(1024 * 1024 * 128, size - pos);
    void *ptr = mmap(NULL, remain, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_POPULATE, fdin, pos);
    if(ptr == (void *)-1) {
      perror(path);
      return 1;
    }
    rot13(ptr, remain);
    pos += remain;
    /* Seek before output so we're always leaving the
     * file offset in the right place */
    if(lseek(fdin, pos, SEEK_SET) < 0) {
      perror("lseek");
      return 1;
    }
    if(write_bytes(fdout, ptr, remain) < 0) {
      perror("stdout");
      return 1;
    }
    if(munmap(ptr, remain) < 0) {
      perror("munmap");
      return 1;
    }
  }
  return 0;
}

/* rot13 a file by reading and writing */
static int rot13_stream(const char *path, int fdin, int fdout) {
  ssize_t n;
  /* buffer is static so we can safely access all of it even
   * if the first read is short. */
  static char buffer[4096];

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

/* rot13 any file, starting from its current position */
static int rot13_any(const char *path, int fdin, int fdout) {
  struct stat sb;

  if(fstat(fdin, &sb) < 0) {
    perror(path);
    return 1;
  }
  if(S_ISREG(sb.st_mode)) {
    int pagesize = getpagesize();
    off_t pos = lseek(fdin, 0, SEEK_CUR);
    if(pos == (off_t)-1) {
      perror("lseek");
      return 1;
    }
    /* We can only map at page boundary offsets, so if we're
     * not there then fall back to ordinary IO.
     *
     * TODO optimization opportunity: read up to a page boundary
     * and then switch to mmap.
     */
    if(pos % pagesize == 0)
      return rot13_mapped(path, fdin, fdout, pos, sb.st_size);
  }
  return rot13_stream(path, fdin, fdout);
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
    if(rot13_any("stdin", 0, 1))
      return 1;
  } else {
    for(n = optind; n < argc; n++) {
      if(!strcmp(argv[n], "-")) {
        if(rot13_any("stdin", 0, 1))
          return 1;
      } else {
        int fd = open(argv[n], O_RDONLY);
        if(fd < 0) {
          perror(argv[n]);
          return 1;
        }
        if(rot13_any(argv[n], fd, 1))
          return 1;
        close(fd);
      }
    }
  }
  return 0;
}
