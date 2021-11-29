#include "f2c.h"
#include "fio.h"

#include "stdlib.h"

#ifdef NON_UNIX_STDIO
#else
#ifdef MSDOS
#else
#ifdef __cplusplus
#else
extern int unlink(const char *);
#endif
#endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    integer f_clos(cllist *a)
    {
        unit *b;

        if (a->cunit >= MXUNIT)
            return (0);
        b = &f__units[a->cunit];
        if (b->ufd == NULL)
            goto done;
        if (b->uscrtch == 1)
            goto Delete;
        if (!a->csta)
            goto Keep;
        switch (*a->csta)
        {
        default:
        Keep:
        case 'k':
        case 'K':
            if (b->uwrt == 1)
                t_runc((alist *)a);
            if (b->ufnm)
            {
                fclose(b->ufd);
                free(b->ufnm);
            }
            break;
        case 'd':
        case 'D':
        Delete:
            fclose(b->ufd);
            if (b->ufnm)
            {
                unlink(b->ufnm); /*SYSDEP*/
                free(b->ufnm);
            }
        }
        b->ufd = NULL;
    done:
        b->uend = 0;
        b->ufnm = NULL;
        return (0);
    }
    void
#ifdef KR_headers
    f_exit()
#else
f_exit(void)
#endif
    {
        int i;
        static cllist xx;
        if (!xx.cerr)
        {
            xx.cerr = 1;
            xx.csta = NULL;
            for (i = 0; i < MXUNIT; i++)
            {
                xx.cunit = i;
                (void)f_clos(&xx);
            }
        }
    }
    int

    flush_(void)

    {
        int i;
        for (i = 0; i < MXUNIT; i++)
            if (f__units[i].ufd != NULL && f__units[i].uwrt)
                fflush(f__units[i].ufd);
        return 0;
    }
#ifdef __cplusplus
}
#endif
