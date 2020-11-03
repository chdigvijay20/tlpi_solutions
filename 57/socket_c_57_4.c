#include "three_sock.h"

int main(int argc, char *argv[])
{
    int sfd;
    struct sockaddr_un addr;
    char buf[BUF_SIZE];
    int buf_len;
    int cfd;
    int i, j;

    sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sfd < 0)
    {
        errExit("socket");
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOMEPATH_A, sizeof(addr.sun_path) - 1);

    for (i = 0; i < 5; ++i)
    {
        memset(buf, 0, BUF_SIZE);
        buf_len = 0;
        for (j = 0; j < 10; ++j)
        {
            buf[buf_len++] = '!' + 10*i + j;
        }

        cfd = sendto(sfd, buf, buf_len, 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_un));
        if (-1 == cfd)
        {
            errExit("sendto");
        }

        printf("sock_c: sent %s\n", buf);
    }
}
