#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int errnum = 127;
    errno = 127;
    printf("strerror: %s\n", strerror(errno));
    strerror(errno);

    perror("perror");
    perror("malloc");
    perror("cd");
    return 0;
}
// #include <stdio.h>
// #include <signal.h>
// #include <setjmp.h>
// #include <signal.h>
// #include <bits/sigaction.h>
// #define SA_NODEFER 0x40000000

// static jmp_buf jump_buffer;

// static void sigsegv_handler(int sig)
// {
//     (void)sig;
//     longjmp(jump_buffer, 1);
// }

// static int is_valid_memory(void *ptr)
// {
//     struct sigaction sa;
//     struct sigaction old_sa;

//     sa.sa_handler = sigsegv_handler;
//     sigemptyset(&sa.sa_mask);
//     sa.sa_flags = SA_NODEFER;
//     sigaction(SIGSEGV, &sa, &old_sa);

//     if (setjmp(jump_buffer) == 0)
//     {
//         volatile char temp = *(volatile char *)ptr;
//         (void)temp;
//         sigaction(SIGSEGV, &old_sa, NULL);
//         return 1; /*valid*/
//     }
//     else
//     {
//         sigaction(SIGSEGV, &old_sa, NULL);
//         return 0; /*invalid*/
//     }
// }

// int main()
// {
//     void *ptr = NULL;
//     int valid_var = 42;
//     // int *invalid_var = (int *)0xDEADBEEF;
//     int *invalid_var = ptr;

//     printf("Checking valid_var: %s\n", is_valid_memory(&valid_var) ? "Valid" : "Invalid");
//     printf("Checking invalid_var: %s\n", is_valid_memory(invalid_var) ? "Valid" : "Invalid");

//     return 0;
// }
