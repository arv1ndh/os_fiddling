#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int
main(void)
{
    if (fork() == 0) {
        char *argv[2];
        argv[0] = "ls";
        argv[1] = 0;
        close(1);
        open("y", O_WRONLY | O_CREAT);
        execv("/bin/ls", argv);
    }
    exit(0);
}
