#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

void printAllowedPerms(char *file)
{
    int f_ok = 0;
    int r_ok = 0;
    int w_ok = 0;
    int x_ok = 0;
    int euid;
    int egid;
    struct stat sb;

    euid = geteuid();
    egid = getegid();

    if (stat(file, &sb) == -1)
    {
        goto printPerms;        
    }

    f_ok = 1;
    if (sb.st_uid == euid)
    {
        r_ok = sb.st_mode & S_IRUSR;
        w_ok = sb.st_mode & S_IWUSR;
        x_ok = sb.st_mode & S_IXUSR;
    }
    else if (sb.st_gid == egid)
    {
        r_ok = sb.st_mode & S_IRGRP;
        w_ok = sb.st_mode & S_IWGRP;
        x_ok = sb.st_mode & S_IXGRP;
    }
    else
    {
        r_ok = sb.st_mode & S_IROTH;
        w_ok = sb.st_mode & S_IWOTH;
        x_ok = sb.st_mode & S_IXOTH;
    }

printPerms:
    printf("access permission: %s\n", f_ok ? "yes" : "no");
    printf("read permission: %s\n", r_ok ? "yes" : "no");
    printf("write permission: %s\n", w_ok ? "yes" : "no");
    printf("execute permission: %s\n", x_ok ? "yes" : "no");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        usageErr("%s file\n", argv[0]);
    }

    printAllowedPerms(argv[1]);
}
