// #include "sysdep1.h"	/* here to get stat64 on some badly designed Linux systems */
#include "f2c.h"
#include "fio.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef __cplusplus
extern "C"
{
#endif
#define Const const
    void g_char(const char *a, ftnlen alen, char *b)

    {
        Const char *x = a + alen;
        char *y = b + alen;

        for (;; y--)
        {
            if (x <= a)
            {
                *b = 0;
                return;
            }
            if (*--x != ' ')
                break;
        }
        *y-- = 0;
        do
            *y-- = *x;
        while (x-- > a);
    }

    VOID

    b_char(const char *a, char *b, ftnlen blen)

    {
        int i;
        for (i = 0; i < blen && *a != 0; i++)
            *b++ = *a++;
        for (; i < blen; i++)
            *b++ = ' ';
    }
#ifndef NON_UNIX_STDIO

    long f__inode(char *a, int *dev)
#endif
    {

        int fd, inode;
        struct stat file_stat;
        int ret;
        ret = fstat(fd, &file_stat);
        if (ret < 0)
        {
            // error getting file stat
            return -1;
        }

        inode = file_stat.st_ino;
        return inode;
    }
#ifdef __cplusplus
}
#endif
