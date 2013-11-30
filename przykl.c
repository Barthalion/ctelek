#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ctelek.h"

#define nmax 100
typedef int t[nmax];

/* int Max(int n, t a);
 * int Max1(int n, t a, int * poz);
 * loat Srednia(int n, t a); */
extern void generacja(int n, int z, t a);
int Min(int n, t a);
void czyt(int *n, int *z);
void druk(int n, int z, t a, int m);
void obl(int n, t a, int *m);

int main(void)
{
    int m, n, z, wariant;
    t a;

    while (1) {
        printf("Wybierz wariant (0/1): ");
        scanf("%d", &wariant);

        switch (wariant) {
            case 0:
                exit(EXIT_SUCCESS);
            case 1:
                srand((unsigned) time(NULL));
                czyt(&n, &z);
                generacja(n, z, a);
                obl(n, a, &m);
                druk(n, z, a, m);
                break;
            default:
                printf("taki wariant nie istnieje!\n");
                exit(EXIT_FAILURE);
}
    }

    exit(EXIT_SUCCESS);
}

void czyt(int *n, int *z)
{
    do {
        printf("n,z= ");
        scanf("%d %d", n, z);
    } while (*n > nmax);
}

int Min(int n, t a)
{
    int x = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] < x)
            x = a[i];
    return x;
}

void obl(int n, t a, int *m)
{
    *m = Min(n, a);
}

void druk(int n, int z, t a, int m)
{
    printf("\nElementy ciagu, n=%d, z=%d\n", n, z);
    for (int i = 0; i < n; i++) {
        printf("%4d", a[i]);
        if ((i % 10 == 0) && (i != 0))
            printf("\n");
    }
    printf("\n");

    printf("Element minimalny: %d\n", m);
}

