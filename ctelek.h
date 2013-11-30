#ifndef _CTELEK_H
#define _CTELEK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <time.h>

inline float Random(void)
{
    return (rand() % 10000) * 0.0001;
    //return (float) rand() / (float) INT_MAX;
    //return rand() * 4.656612875245796924105750827168e-10;
}

inline void generacja(int n, int z, int *a)
{
    for (int i = 0; i < n; i++)
        a[i] = (rand() % z) + 1;
}

inline clock_t pomiar(void)
{
    return (clock_t) clock();
}

inline int random(int n)
{
    return rand() % n;
}

#ifdef __cplusplus
}
#endif
#endif //_CTELEK_H
