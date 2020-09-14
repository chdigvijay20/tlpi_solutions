#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "file_perms.h"

int main(int argc, char *argv[])
{
    int fd;
    struct stat sb;
    int askPermission;
    
    askPermission = S_IRUSR | S_IWUSR | S_IXUSR |
        S_IRGRP | S_IWGRP | S_IXGRP |
        S_IROTH | S_IWOTH | S_IXOTH;

    //umask(0777);
    remove("/tmp/tempzzz.txt");

    fd = open("/tmp/tempzzz.txt", O_CREAT | O_RDONLY, askPermission);
    if (fd == -1)
    {
        errExit("open");
    }
    close(fd);

    stat("/tmp/tempzzz.txt", &sb);

    printf("Asked for permission: %s\n", filePermStr(askPermission, 0));
    printf("Granted permission:   %s\n", filePermStr(sb.st_mode, 0));
    printf("Current umask:        %s\n", filePermStr(~sb.st_mode, 0));

    return EXIT_SUCCESS;
}
