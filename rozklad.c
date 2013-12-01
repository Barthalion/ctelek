#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

#define NMAX 11
#define KMAX NMAX*(NMAX-1)/2
#define PMAX 9 //max liczba roznych wartosci p w tablicy PR

typedef bool t2[NMAX][NMAX]; // A
typedef int t3[KMAX]; // R
typedef int t4[KMAX][PMAX + 1]; // PR
typedef int t5[12]; // Q, n=4
typedef int t[NMAX];
typedef struct {
    int a, b;
} r;
typedef r t1[KMAX]; // E

clock_t pomiar(void);
static inline float Random(void);
static inline int random(int n);
void czyt1(int *n, int *rep, float *p1, float *p2, float *p3, int *total);
void czyt(int *n, int *rep, float *p);
void druk1(int n, int rep, float p);
void drukA(int n, int k, t2 A);
void druk(int n, float p1, float p2, float p3, int *l); //naglowek
void drukPR(int l, int total, int rep, t4 PR); //rozklad
void drukQ(int n, int rep, float p, t5 Q);
void Gnp(int n, float p, t2 A, int *k);
void kraw(int n, int rep, int total, float p1, float p2, float p3, t4 PR);
void strukt(int n, int rep, float p, t5 Q);  //n=4

int main(void)
{
    int  k, l, n, rep, total, wariant;
    float p, p1, p2, p3;
    t2 A;
    t4 PR;
    t5 Q;
    clock_t czas1, czas2;

    srand((unsigned) time(NULL));

    do {
        printf("Wariant: (0/1/2/3/4) ");
        scanf("%d", &wariant);
        switch (wariant) {
            case 0:
                exit(EXIT_SUCCESS);
            case 1: //Gnp
                czyt(&n, &rep, &p);
                druk1(n, rep, p);
                for (int i = 1; i <= rep; i++) {
                    Gnp(n, p, A, &k);
                    drukA(n, k, A);
                }
                break;
            case 2: // czas kraw
                czyt1(&n, &rep, &p1, &p2, &p3, &total);
                czas1 = pomiar();
                kraw(n, rep, total, p1, p2, p3, PR);
                czas2 = pomiar();
                printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLOCKS_PER_SEC);
                break;
            case 3:
                czyt1(&n, &rep, &p1, &p2, &p3, &total);
                druk(n, p1, p2, p3, &l); //naglowek
                kraw(n, rep, total, p1, p2, p3, PR);
                drukPR(l, total, rep, PR); //rozklad
                break;
            case 4:
                // n = 4
                czyt(&n, &rep, &p);
                n = 4;
                strukt(n, rep, p, Q);
                drukQ(n, rep, p, Q);
                break;
            default:
                printf("Taki wariant nie istnieje!\n");
                exit(EXIT_FAILURE);
        }
    } while (true);
}

static inline float Random(void)
{
    return (rand() % 10000) * 0.0001;
}

static inline int random(int n)
{
    return rand() % n;
}

void czyt(int *n, int *rep, float *p)
{
    do {
        printf("n, p, rep= ");
        scanf("%d %f %d", n, p, rep);
    } while ((*n > NMAX) && (*p > 1) && (*rep > 100000));
}

void czyt1(int *n, int *rep, float *p1, float *p2, float *p3, int *total)
{
    int x;
    printf("n,rep, p1, p2, p3= ");
    scanf("%d %d %f %f %f", n, rep, p1, p2, p3);
    x = *n;
    *total = x * (x - 1) / 2;
}

void Gnp(int n, float p, t2 A, int *k)
{
    bool x;
    int h = 0;

    for (int i = 1; i <= n; i++)
        A[i][i] = false; // przygotowanie A
    for (int i = 1; i <= n - 1; i++) //generacja Gnp
        for (int j = i + 1; j <= n; j++) {
            x = Random() <= p;
            A[i][j] = x;
            A[j][i] = x;
            if (x)
                h++;
        }
    *k = h; //liczba krawedzi
}

void kraw(int n, int rep, int total, float p1, float p2, float p3, t4 PR)
{
    t2 A;
    t3 R;
    float p = p1;
    int i = 1, k;

    while (p <= p3) {
        for (int j = 0; j <= total; j++)
            R[j] = 0;
        for (int j = 1; j <= rep; j++) {
            Gnp(n, p, A, &k); //k jest liczba krawedzi grafu
            R[k] += 1;
        }
        for (int k = 0; k <= total; k++)
            PR[k][i] = R[k];
        p += p2;
        i++;
    }
}

void strukt(int n, int rep, float p, t5 Q) //n=4
{
    t2 A;
    t deg;
    int k, s, nr;

    for (int i = 1; i <= 11; i++)
        Q[i] = 0;
    for (int h = 1; h <= rep; h++) {
        Gnp(n, p, A, &k);
        for (int i = 1; i <= n; i++) {
            s = 0;
            for (int j = 1; j <= n; j++)
                if (A[i][j])
                    s++;
            deg[i] = s;
        }
        int w = 0;
        for (int i = 1; i <= n; i++)
            if (deg[i] == 2)
                w++;
        switch (k) {
            case 0:
                nr = 1;
                break;
            case 1:
                nr = 2;
                break;
            case 2:
                if (w == 0)
                    nr = 3;
                else
                    nr = 4;
                break;
            case 3:
                switch (w) {
                    case 0:
                        nr = 7;
                        break;
                    case 2:
                        nr = 5;
                        break;
                    case 3:
                        nr = 6;
                        break;
                }
                break;
            case 4:
                if (w == 4) nr = 8;
                else nr = 9;
                break;
            case 5:
                nr = 10;
                break;
            case 6:
                nr = 11;
                break;
        }
        Q[nr]++;
    }
}

void druk1(int n, int rep, float p)
{
    printf("\nGnp, n= %3d,p= %7.4f, rep= %5d\n", n, p, rep);
}

void drukA(int n, int k, t2 A)
{
    int h = 0;

    printf("Krawedzie z A, k=%3d:\n", k);
    for (int i = 1; i <= n - 1; i++)
        for (int j = i + 1; j <= n; j++) {
            if (A[i][j]) {
                h++;
                printf("%4d%3d", i, j);
                if (h % 10 == 0)
                    printf("\n");
            }
        }
    printf("\n\n");
}

void druk(int n, float p1, float p2, float p3, int *l) //naglowek
{
    int i = 1, x;
    float p = p1;

    printf("\nGnp, rozklad liczby krawedzi, n=%d\n", n);
    printf(" k p=");
    while (p <= p3) {
        printf("%7.4f", p);
        p += p2;
        i++;
    }
    x = i - 1;
    printf("\n");
    for (int j = 1; j <= 7 * (x + 1); j++)
        printf("-");
    printf("\n");
    *l = x;
}

void drukPR(int l, int total, int rep, t4 PR) //rozklad
{
    for (int k = 0; k <= total; k++) {
        printf("%2d   ", k);
        for (int i = 1; i <= l; i++)
            printf("%7.4f", PR[k][i] / (float)rep);
        printf("\n");
    }
}

void drukQ(int n, int rep, float p, t5 Q)
{
    int s;
    printf("\nGnp, rozklad struktur, n=%2d", n);
    printf("p=%7.4f rep=%6d\n", p, rep);
    printf("nr    P(G ma nr)\n");
    printf("----------------\n");
    for (int i = 1; i <= 11; i++)
        printf("%3d%11.4f\n", i, Q[i] / (float)rep);
    printf("----------------\n");
    s = 0;
    for (int i = 1; i <= 11; i++)
        s += Q[i];
    printf("test=%7.4f\n", s / (float)rep);
}

clock_t pomiar(void)
{
    return clock();
}

