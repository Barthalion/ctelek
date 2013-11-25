#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NMAX 51
#define KMAX NMAX*(NMAX-1)/2
#define TRMAX KMAX*(NMAX-2)/3

typedef bool t2[NMAX][NMAX]; // A
typedef bool tx[NMAX]; // x
typedef int t3[TRMAX + 1]; //Q
typedef int t4[721]; //FOUR
typedef struct {
    int a, b;
} r;
typedef r t1[KMAX]; // E

bool spojny1(int n, t2 A);
clock_t pomiar(void);
int cykl4_1(int n, t2 A);
int cykl4(int n, t2 A);
int cykl4TF(int n, t2 A);
int triangles(int n, t2 A);
static inline float Random(void);
static inline int random(int n);
void czyt1(int *n, int * k, int *rep);
void czyt(int *n, int *rep, float *p);
void druk1a(int n, int k, int rep);
void druk1(int n, int rep, float p);
void druk2(int alltr, int rep, t3 Q, float x, float y);
void drukA(int n, t2 A);
void Gnk(int k, int total, t1 E);
void Gnp (int n, float p, t2 A);
void init(int n, t1 E, int * total);
void skladowa1(int n, int v, t2 A, tx x);
void stat(int alltr, int rep, t3 Q, float *x, float *y);
void transEA(int n, int k, int total, t1 E, t2 A);

int main(void)
{
    int c, cz, cz1, czTF, k, n, tr, rep, alltr, total, wariant;
    float p, x, y;
    t2 A;
    t1 E;
    clock_t czas1, czas2;
    t3 Q;
    srand((unsigned) time(NULL));

    do {
        printf("Wariant: (0/1/2/3/31/4/5)");
        scanf("%d", &wariant);
        switch (wariant) {
            case 0:
                exit(EXIT_SUCCESS);
            case 1: //Gnp w A, spojnosc, trojkaty, czworokaty
                czyt(&n, &rep, &p);
                druk1(n, rep, p);
                c = 0;

                for (int i = 1; i <= rep; i++) {
                    Gnp(n, p, A);
                    tr = triangles(n, A);
                    cz = cykl4(n, A);
                    cz1 = cykl4_1(n, A);
                    czTF = cykl4TF(n, A);
                    drukA(n, A);
                    if (spojny1(n, A)) {
                        c++;
                        printf("\tspojny\n");
                    }
                    printf("tr=%6d, cz=%7d, cz1=%7d, czTF=%7d\n\n", tr, cz, cz1, czTF);
                }
                printf("\nliczba grafow spojnych w probce, c=%3d", c );
                break;
            case 2: //Gnk w E, spojnosc, trojkaty, czworokaty
                czyt1(&n, &k, &rep);
                init(n, E, &total);

                for (int i = 1; i <= rep; i++) {
                    Gnk(k, total, E);
                    transEA(n, k, total, E, A);
                    tr = triangles(n, A);
                    czTF = cykl4TF(n, A);
                    drukA(n, A);
                    if (spojny1(n, A)) {
                        c++;
                        printf("\tspojny\n");
                    }
                    printf("tr=%3d, cz=%7d", tr, czTF);
                }
                break;
            case 3: //czas Gnp, trojkaty
                czyt(&n, &rep, &p);
                druk1(n, rep, p);
                czas1 = pomiar();
                for (int i = 1; i < rep; i++) {
                    Gnp(n, p, A);
                    tr = triangles(n, A);
                }
                czas2 = pomiar();
                printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLOCKS_PER_SEC);
                break;
            case 31: //czas Gnp, czworokaty
                czyt(&n, &rep, &p);
                druk1(n, rep, p);
                czas1 = pomiar();
                for (int i = 1; i < rep; i++) {
                    Gnp(n, p, A);
                    czTF = cykl4TF(n, A);
                }
                czas2 = pomiar();
                printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLOCKS_PER_SEC);
                break;
            case 4: // Gnp, rozklad liczby trojkatow
                czyt(&n, &rep, &p);
                druk1(n, rep, p);
                alltr = n * (n - 1) * (n - 2) / 6;
                for (int h = 0; h <= alltr; h++)
                    Q[h] = 0;
                for (int h = 1; h <= rep; h++) {
                    Gnp(n, p, A);
                    tr = triangles(n, A);
                    Q[tr]++;
                }
                stat(alltr, rep, Q, &x, &y);
                druk2(alltr, rep, Q, x, y);
                break;
            case 5: //Gnk, rozklad liczby trojkatow
                czyt1(&n, &k, &rep);
                druk1a(n, k, rep);
                init(n, E, &total);
                alltr = n * (n - 1) * (n - 2) / 6;
                for (int h = 0; h <= alltr; h++)
                    Q[h] = 0;
                for (int h = 1; h <= rep; h++) {
                    Gnk(k, total, E);
                    transEA(n, k, total, E, A);
                    tr = triangles(n, A);
                    Q[tr]++;
                }
                stat(alltr, rep, Q, &x, &y);
                druk2(alltr, rep, Q, x, y);
                break;
            default:
                printf("Taki wariant nie istnieje!\n");
                exit(EXIT_FAILURE);
        }
    } while (true);
}

static inline int random(int n)
{
    return rand() % n;
}

static inline float Random(void)
{
    return (rand() % 10000) * 0.0001;

}

void czyt(int *n, int *rep, float *p)
{
    do {
        printf("n, p, rep= ");
        scanf("%d%f%d", n, p, rep);
    } while (*n > NMAX && *p > 1 && *rep > 100000);
}

void czyt1(int *n, int * k, int *rep)
{
    do {
        printf("n, k, rep= ");
        scanf("%d%d%d", n, k, rep);
    } while ((*n > NMAX) && (*k > KMAX) && (*rep > 100000));
}

void Gnp (int n, float p, t2 A)
{
    bool x;

    for (int i = 1; i <= n; i++)
        A[i][i] = false;
    for (int i = 1; i <= n - 1; i++)
        for (int j = i + 1; j <= n; j++) {
            x = Random() <= p;
            A[i][j] = x;
            A[j][i] = x;
        }
}

void init(int n, t1 E, int * total)
{
    int h = 0;

    for (int i = 1; i <= n - 1; i++)
        for (int j = i + 1; j <= n; j++) {
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

    for (int i = 1; i <= k; i++) {
        z = random(l) + 1;
        x = E[z];
        E[z] = E[l];
        E[l] = x;
        l--;
    }
}

void transEA(int n, int k, int total, t1 E, t2 A)
{
    int i, j;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            A[i][j] = false;

    for (int l = total; l >= total - k + 1; l--) {
        i = E[l].a;
        j = E[l].b;
        A[i][j] = true;
        A[j][i] = true;
    }
}

void skladowa1(int n, int v, t2 A, tx x)
{
    for (int j = 1; j <= n; j++)
        if (A[v][j] && !x[j]) {
            x[j] = true;
            skladowa1(n, j, A, x);
        }
}

bool spojny1(int n, t2 A)
{
    int i;
    tx x;
    bool b;
    for (int i = 1; i <= n; i++)
        x[i] = false;
    x[1] = true;
    skladowa1(n, 1, A, x);
    b = true;
    i = 1;
    while (i <= n && b) {
        b = x[i];
        i++;
    }
    return b;
}

int triangles(int n, t2 A)
{
    int x = 0;
    for (int i = 1; i <= n - 2; i++)
        for (int j = i + 1; j <= n; j++)
            if (A[i][j])
                for (int h = j + 1; h <= n; h++)
                    if (A[i][h] && A[j][h])
                        x++;
    return x;
}

int cykl4(int n, t2 A)
{
    int x = 0;
    if (n >= 4)
        for (int i = 1; i <= n - 2; i++)
            for (int j = i + 1; j <= n - 1; j++)
                if (A[i][j])
                    for (int k = j + 1; k <= n; k++)
                        if (A[i][k])
                            for (int h = i; h <= n; h++)
                                if ((h != j) && (h != i) && (h != k))
                                    if ((A[j][h]) && (A[k][h]))
                                        x++;
    return x;
}

int cykl4_1(int n, t2 A)
{
    int x = 0;
    if (n >= 4)
        for (int i = 1; i <= n - 3; i++)
            for (int j = i + 1; j <= n - 1; j++)
                if (A[i][j])
                    for (int k = j + 1; k <= n; k++)
                        if (A[i][k])
                            for (int h = i + 1; h <= n; h++)
                                if ((h != j) && (h != k))
                                    if ((A[j][h]) && (A[k][h]))
                                        x++;
    return x;
}

int cykl4TF(int n, t2 A)
{
    int c,
        x = 0;

    if (n >= 4)
        for (int i = 1; i <= n - 1; i++)
            for (int j = i + 1; j <= n; j++) {
                c = 0;
                for (int k = i + 1; k <= n; k++)
                    if (A[i][k] && A[j][k])
                        c++;
                if (c >= 2)
                    x += c * (c - 1) / 2;
            }

    return x;
}

void stat(int alltr, int rep, t3 Q, float *x, float *y)
{
    float s = 0;

    for (int i = 0; i <= alltr; i++)
        s += (Q[i] / (float)rep) * i;

    *x = s;
    s = 0;

    for (int i = 0; i <= alltr; i++)
        s += (Q[i] / (float)rep) * (i - *x) * (i - *x); //sqr(i-*x);

    *y = s;
    // printf("%10.3f%10.3f",x,y);
}

void druk1(int n, int rep, float p)
{
    printf("\nGnp, n= %3d,p= %7.4f, rep= %5d\n", n, p, rep);
}

void druk1a(int n, int k, int rep)
{
    printf("\nGnk, n= %3d, k= %d, rep= %5d \n", n, k, rep);
}

void drukA(int n, t2 A)
{
    int h = 0;

    printf("\nKrawedzie z A:\n");
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

void druk2(int alltr, int rep, t3 Q, float x, float y)
{
    int j;

    printf("Distibution of triangles:\n");
    printf("     ");
    for (int i = 0; i <= 9; i++)
        printf("%7d", i);
    printf("\n-----");
    for (int i = 0; i <= 9; i++)
        printf("-------");
    for (int i = 0; i <= alltr; i++) {
        j = i % 10;
        if (j == 0)
            printf("\n%3d\t", i);
        printf("%7.4f", Q[i] / (float)rep);
    }
    printf("\nE(tr)=%8.2f\tV(tr)=%8.2f\n", x, y);
}

clock_t pomiar(void)
{
    return clock();
}//pomiar

