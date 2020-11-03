#include "seq_num_stream.h"

int main(int argc, char *argv[])
{
    struct sockaddr_un addr;
    int cfd;
    struct response resp;
    struct request req;
    int rcv_len;
    int seg_len;

    if (argc != 2)
    {
        usageErr("%s <segment length>\n", argv[0]);
    }

    cfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (cfd == -1)
    {
        errExit("socket");
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SEQ_STREAM_PATH, sizeof(addr.sun_path) - 1);

    memset(&req, 0, sizeof(struct response));
    seg_len = getInt(argv[1], 0, "sequence client");
    req.seqLen = seg_len;
    if (0 != connect(cfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)))
    {
        errExit("connect");
    }

    if (-1 == send(cfd, &req, sizeof(struct request), 0))
    {
        errExit("send");
    }

    rcv_len = recv(cfd, &resp, sizeof(struct response), 0);
    if (-1 == rcv_len)
    {
        errExit("recv");
    }

    printf("sent length %d, received sequence number %d\n", req.seqLen, resp.seqNum);
}
