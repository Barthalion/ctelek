#ifndef _CTELEK_H
#define _CTELEK_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
# include <intrin.h> // __rdtsc function
#endif

#include <stdint.h> // uint64_t type
#include <stdlib.h>
#include <time.h>

inline float Random(void)
{
    return (rand() % 10000) * 0.0001;
    //return (float) rand() / (float) INT_MAX;
    //return rand() * 4.656612875245796924105750827168e-10;
}

inline clock_t pomiar(void)
{
    return clock();
}

inline int random(int n)
{
    return rand() % n;
}

inline uint64_t pomiarcpu(void)
{
#ifdef _WIN32
    return __rdtsc();
#elif __linux__
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t) hi << 32) | lo;
#endif
}

inline void generacja(int n, int z, int *a)
{
    for (int i = 0; i < n; i++)
        a[i] = (rand() % z) + 1;
}

#ifdef __cplusplus
}
#endif
#endif //_CTELEK_H
