#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int puts(const char *str) {
    int len = 0;
    const char *s = str;

    while (*s++) len++;

    write(1, str, len);
    write(1, "\n", 1);

    return len + 1;
}
