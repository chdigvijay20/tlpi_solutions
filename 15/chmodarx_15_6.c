#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    int i = 0;
    struct stat sb;
    mode_t new_mode;

    if (argc < 2)
    {
        usageErr("%s file1 [file2 file3]\n", argv[0]);
    }

    for (i = 1; i < argc; ++i)
    {
        if (stat(argv[i], &sb) == -1)
        {
            printf("stat failed for %s, skipping\n", argv[i]);
            continue;
        }

        new_mode = sb.st_mode;
        new_mode |= (S_IRUSR | S_IRGRP | S_IROTH);

        if (sb.st_mode & S_IFMT == S_IFDIR)
        {
            new_mode |= (S_IXUSR | S_IXGRP | S_IXOTH);
        }
        else if((sb.st_mode & S_IXUSR) ||
                (sb.st_mode & S_IXGRP) ||
                (sb.st_mode & S_IXOTH))
        {
            new_mode |= (S_IXUSR | S_IXGRP | S_IXOTH);
        }

        if (chmod(argv[i], new_mode) == -1)
        {
            printf("chmod failed for %s\n", argv[i]);
        }
    }

    return EXIT_SUCCESS;
}
