#include <errno.h>
#include <stdio.h>
#include <string.h>

int main() {
    // Using strerror
    int errnum = 127;
    errno = EPERM;
    printf("strerror: %s\n", strerror(errno));

    // Using perror
    errno = EPERM;
    perror("perror");

    return 0;
}

