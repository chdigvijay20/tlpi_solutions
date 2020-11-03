#include "seq_num_stream.h"

int main(int argc, char *argv[])
{
    struct sockaddr_un addr;
    int sfd;
    int cfd;
    struct response resp;
    struct request req;
    int rcv_len;

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        errExit("socket");
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SEQ_STREAM_PATH, sizeof(addr.sun_path) - 1);

    if (remove(SEQ_STREAM_PATH) == -1 && errno != ENOENT)
    {
        errExit("remove-%s", SEQ_STREAM_PATH);
    }

    if (0 != bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)))
    {
        errExit("bind");
    }

    if (0 != listen(sfd, SEQ_BACKLOG))
    {
        errExit("listen");
    }

    memset(&resp, 0, sizeof(struct response));
    while (1)
    {
        cfd = accept(sfd, NULL, NULL);

        rcv_len = recv(cfd, &req, sizeof(struct request), 0);
        if (-1 == rcv_len)
        {
            errExit("recv");
        }

        if (-1 == send(cfd, &resp, sizeof(struct response), 0))
        {
            errExit("send");
        }

        resp.seqNum += req.seqLen;

        if (0 != close(cfd))
        {
            errMsg("close");
        }
    }
}
