#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <internal/syscall.h>

unsigned int sleep(unsigned int seconds) {
  struct timespec req;
  struct timespec rem;
  req.seconds = seconds;
  rem.nanoseconds = 0;
  req.nanoseconds = 0;
  if (nanosleep(&req, &rem) < 0) {
    return -1;
  }
  return 0;
}
