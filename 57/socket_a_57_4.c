#include "three_sock.h"

int main(int argc, char *argv[])
{
    int sfd;
    struct sockaddr_un addr;
    char buf[BUF_SIZE];
    int buf_len;
    int cfd;

    sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sfd < 0)
    {
        errExit("socket");
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOMEPATH_A, sizeof(addr.sun_path) - 1);

    if (-1 == remove(SOMEPATH_A) && errno != ENOENT)
    {
        errExit("remove-%s", SOMEPATH_A);
    }

    if (0 != bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)))
    {
        errExit("bind");
    }

    struct sockaddr_un addr_b;
    memset(&addr_b, 0, sizeof(struct sockaddr_un));
    addr_b.sun_family = AF_UNIX;
    strncpy(addr_b.sun_path, SOMEPATH_B, sizeof(addr_b.sun_path) - 1);
    if (0 != connect(sfd, (struct sockaddr *)&addr_b, sizeof(struct sockaddr_un)))
    {
        errExit("connect");
    }

    while (1)
    {
        sleep(10);
    }
}
