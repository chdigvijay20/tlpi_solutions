#include <stdio.h>
#include <sys/xattr.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        usageErr("%s file ea_name value\n", argv[0]);
    }

    char attr_name[255] = {0};

    snprintf(attr_name, 255, "user.%s", argv[2]);
    if (setxattr(argv[1], attr_name, argv[3], strlen(argv[3]), 0) == -1)
    {
        errExit("setxattr");
    }

    exit(EXIT_SUCCESS);
}
