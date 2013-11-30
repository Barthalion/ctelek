#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ctelek.h"

#define NMAX 100
#define KMAX NMAX*(NMAX)/2

typedef bool t2[NMAX][NMAX]; // A
typedef int t[NMAX];
typedef struct {
    int a, b;
} r;
typedef r t1[KMAX]; // E

extern float Random(void);
extern clock_t pomiar(void);
extern int random(int n);
void czyt(int *n, int *rep, float *p);
void czyt1(int *n, int * k, int *rep);
void druk1a(int n, int k, int rep);
void druk1(int n, int rep, float p);
void drukA(int n, t2 A);
void drukE(int k, int total, t1 E);
void Gnk(int k, int total, t1 E);
void Gnp (int n, float p, t2 A);
void init(int n, t1 E, int * total);
void transEA(int n, int k, int total, t1 E, t2 A);

int main(void)
{
    int k, n, rep, total, wariant;
    float p;
    t2 A;
    t1 E;
    clock_t czas1, czas2;

    srand((unsigned) time(NULL));

    do {
        printf("Wariant: (0/1/2/3) ");
        scanf("%d", &wariant);
        switch (wariant) {
            case 0:
                exit(EXIT_SUCCESS);
            case 1: //Gnp
                czyt(&n, &rep, &p);
                druk1(n, rep, p);
                for (int i = 0; i < rep; i++) {
                    Gnp(n, p, A);
                    drukA(n, A);
                }
                break;
            case 2: //czas Gnp
                czyt(&n, &rep, &p);
                czas1 = pomiar();
                for (int i = 0; i < rep; i++)
                    Gnp(n, p, A);
                czas2 = pomiar();
                printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLOCKS_PER_SEC);
                break;
            case 3: //Gnk, transEA
                czyt1(&n, &k, &rep);
                druk1a(n, k, rep);
                init(n, E, &total);
                for (int i = 0; i < rep; i++) {
                    Gnk(k, total, E);
                    drukE(k, total, E);
                    transEA(n, k, total, E, A);
                    drukA(n, A);
                }
                break;
          /*case 4: //czas Gnk
                break;
            case 5: //czas Gnp w E
                break;
          */
            default:
                printf("Taki wariant nie istnieje!\n");
                exit(EXIT_FAILURE);
        } // switch
    } while (true);
}

void czyt(int *n, int *rep, float *p)
{
    do {
        printf("n, p, rep= ");
        scanf("%d %f %d", n, p, rep);
    } while ((*n > NMAX) && (*p > 1) && (*rep > 100000));
}

void Gnp (int n, float p, t2 A)
{
    bool x;

    for (int i = 0; i < n; i++)
        A[i][i] = false;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++) {
            //x = (random(1001) * 0.001) <= p;
            x = Random() <= p;

            A[i][j] = x;
            A[j][i] = x;
        }
}

void czyt1(int *n, int * k, int *rep)
{
    do {
        printf("n, k, rep= ");
        scanf("%d %d %d", n, k, rep);
    } while ((*n > NMAX) && (*k > KMAX) && (*rep > 100000));
}

void init(int n, t1 E, int * total)
{
    int h = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++) {
            h++;
            E[h].a = i;
            E[h].b = j;
        }
    *total = h;
}

void Gnk(int k, int total, t1 E)
{
    int l, z;
    r x;
    l = total;
    for (int i = 0; i < k; i++) {
        z = random(l) + 1;
        x = E[z];
        E[z] = E[l];
        E[l] = x;
        l--;
    }
}

void transEA(int n, int k, int total, t1 E, t2 A)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = false;
    for (int l = total; l >= total - k + 1; l--) {
        int i = E[l].a;
        int j = E[l].b;
        A[i][j] = true;
        A[j][i] = true;
    }
}

void druk1(int n, int rep, float p)
{
    printf("\nGnp, n= %3d, p= %7.4f, rep= %5d \n", n, p, rep);
}

void druk1a(int n, int k, int rep)
{
    printf("\nGnk, n= %3d, k= %d, rep= %5d \n", n, k, rep);
}

void drukE(int k, int total, t1 E)
{
    int h = 0;
    printf("\nKrawedzie z E:\n");
    for (int l = total; l >= total - k + 1; l--) {
        h++;
        printf("%4d%3d", E[l].a, E[l].b);
        if (h % 10 == 0)
            printf("\n");
    }
}

void drukA(int n, t2 A)
{
    int h = 0;
    printf("\nKrawedzie z A:\n");
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++) {
            if (A[i][j]) {
                h++;
                printf("%4d%3d", i, j);
                if (h % 10 == 0)
                    printf("\n");
            }
        }
    printf("\n\n");
}

