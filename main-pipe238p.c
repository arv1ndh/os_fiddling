#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#define STDIN 0
#define STDOUT 1

int
main(void)
{
    int pipe_0[2];
    int pipe_1[2];
    char *argv_ls[2];
    char *argv_grep[3];
    char *argv_wc[2];
    pipe(pipe_0);
    pipe(pipe_1);
    if (fork() == 0) {
        argv_ls[0] = "ls";
        argv_ls[1] = 0;
        close(STDOUT);
        dup2(pipe_0[1],STDOUT);
        execv("/bin/ls", argv_ls);
    }
    if (fork() == 0) {
        argv_grep[0] = "grep";
        argv_grep[1] = "main";
        argv_grep[2] = 0;
        close(pipe_0[1]);
        close(STDIN);
        close(STDOUT);
        dup2(pipe_0[0], STDIN);
        dup2(pipe_1[1], STDOUT);
        execv("/bin/grep", argv_grep);
        close(pipe_1[1]);
    }
#if 0
    close(pipe_1[1]);
    close(pipe_0[1]);
    char buf[100];
    read(pipe_1[0],buf,75);
    printf("VALUE IS --> %s", buf);
#endif
    if (fork() == 0) {
        argv_wc[0] = "wc";
        argv_wc[1] = 0;
        close(pipe_0[1]);
        close(pipe_1[1]);
        close(STDIN);
        dup2(pipe_1[0], STDIN);
        execv("/usr/bin/wc", argv_wc);
    }
    close(pipe_0[1]);
    close(pipe_1[1]);
    sleep(1);
    exit(0);
}
