#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int p[2], c[2];
    pipe(p);
    pipe(c);
    char buffer[10];

    if (fork() == 0)
    {
        close(0);
        read(p[0], buffer, 5);
        close(p[0]);

        printf("%d: received %s\n", getpid(), buffer);

        write(c[1], "pong", 5);
        close(c[1]);
    }
    else
    {
        write(p[1], "ping", 5);
        close(p[1]);
        read(c[0], buffer, 5);
        close(c[0]);
        printf("%d: received %s\n", getpid(), buffer);
    }

    exit(0);
}