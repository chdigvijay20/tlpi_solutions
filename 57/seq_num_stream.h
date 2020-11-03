#include <sys/socket.h>
#include <sys/un.h>
#include "tlpi_hdr.h"

#define SEQ_STREAM_PATH     "/tmp/seq_stream"
#define SEQ_BACKLOG         10

struct request
{
    pid_t pid;
    int seqLen;
};

struct response
{
    int seqNum;
};
