#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
#include <string.h>
#include "file_perms.h"

typedef enum
{
    ATTR_ADD,
    ATTR_REMOVE,
    ATTR_SET
} chattr_op;

int main(int argc, char *argv[])
{
    int fd;
    int cur_attrs;
    int new_attrs;
    chattr_op op;
    int i;

    if (argc < 3)
    {
        usageErr("%s <-+=aAcCdDeijsStTu> <file>\n", argv[0]);
    }

    switch(argv[1][0])
    {
        case '+':
            op = ATTR_ADD;
            break;

        case '-':
            op = ATTR_REMOVE;
            break;

        case '=':
            op = ATTR_SET;
            break;

        default:
            usageErr("%s <-+=aAcCdDeijsStTu> <file>\n", argv[0]);
    }

    fd = open(argv[2], O_RDONLY);
    if (fd == -1)
    {
        errExit("open");
    }

    if (ioctl(fd, FS_IOC_GETFLAGS, &cur_attrs) == -1)
    {
        errExit("ioctl get");
    }

    for (i = 1; i < strlen(argv[1]); ++i)
    {
        switch(argv[1][i])
        {
            case 'a':
                new_attrs |= FS_APPEND_FL;
                break;

            case 'c':
                new_attrs |= FS_COMPR_FL;
                break;

            case 'D':
                new_attrs |= FS_DIRSYNC_FL;
                break;

            case 'i':
                new_attrs |= FS_IMMUTABLE_FL;
                break;

            case 'j':
                new_attrs |= FS_JOURNAL_DATA_FL;
                break;

            case 'A':
                new_attrs |= FS_NOATIME_FL;
                break;

            case 'd':
                new_attrs |= FS_NODUMP_FL;
                break;

            case 't':
                new_attrs |= FS_NOTAIL_FL;
                break;

            case 's':
                new_attrs |= FS_SECRM_FL;
                break;

            case 'S':
                new_attrs |= FS_SYNC_FL;
                break;

            case 'T':
                new_attrs |= FS_TOPDIR_FL;
                break;

            case 'u':
                new_attrs |= FS_UNRM_FL;
                break;

            default:
                usageErr("%s <-+=aAcCdDeijsStTu> <file>\n", argv[0]);
        }
    }

    switch (op)
    {
        case ATTR_ADD:
            new_attrs |= cur_attrs;
            break;

        case ATTR_REMOVE:
            new_attrs = cur_attrs & ~new_attrs;
            break;

        case ATTR_SET:
            break;
    }

    if (ioctl(fd, FS_IOC_SETFLAGS, &new_attrs) == -1)
    {
        errExit("ioctl set");
    }

    if (close(fd) == -1)
    {
        errExit("close");
    }

    return EXIT_SUCCESS;
}
