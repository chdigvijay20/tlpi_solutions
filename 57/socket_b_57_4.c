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
    strncpy(addr.sun_path, SOMEPATH_B, sizeof(addr.sun_path) - 1);

    if (-1 == remove(SOMEPATH_B) && errno != ENOENT)
    {
        errExit("remove-%s", SOMEPATH_B);
    }

    if (0 != bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)))
    {
        errExit("bind");
    }

    while (1)
    {
        buf_len = recv(sfd, buf, BUF_SIZE, 0);
        if (buf_len < 0)
        {
            errExit("recv");
        }

        printf("sock_b: received %s\n", buf);
    }
}
