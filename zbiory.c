#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ctelek.h"

#define NMAX 100

typedef bool t2[NMAX][NMAX]; // A
typedef bool t3[NMAX]; // x
typedef bool zbior[NMAX];
typedef struct {
    int a, b;
    bool code;
} r;
typedef r t1[NMAX]; // E
typedef struct {
    zbior w;
    int l;
} rs;
typedef rs ts[NMAX]; // S

bool spojny1(int n, t2 A);
bool spojny(int n, t2 A);
extern float Random(void);
extern clock_t pomiar(void);
extern int random(int n);
void czyt(int *n, int *rep, float *p);
void druk1(int n, int rep, float p);
void drukA(int n, t2 A);
void drukE(int total, t1 E);
void drukS1(int n, ts S);
void drukS(int n, ts S);
void drukx(int n, t3 x);
void drukzbior(int first, int n, zbior z);
void GnpE(int total, float p, t1 E);
void Gnp (int n, float p, t2 A);
void init(int n, t1 E, int * total);
void skladowa1(int n, int v, t2 A, t3 x);
void skladowa(int n, int v, t2 A, t3 x);
void transAS(int n, t2 A, ts S);
void transES(int n, int total, t1 E, ts S);

int main(void)
{
    int c, n, rep, total, wariant;
    float p;
    t1 E;
    ts S;
    t2 A;
    clock_t czas1, czas2;

    srand((unsigned) (time(NULL)));
    do {
        printf("Wariant: (0/1/2/3/4/5) ");
        scanf("%d", &wariant);
        switch (wariant) {
            case 0:
                exit(EXIT_SUCCESS);
            case 1: // Gnp w E, transES
                czyt(&n, &rep, &p);
                druk1(n, rep, p);
                init(n, E, &total);
                for (int i = 1; i <= rep; i++) {
                    GnpE(total, p, E);
                    drukE(total, E);
                    transES(n, total, E, S);
                    drukS(n, S);
                    drukS1(n, S);
                }
                break;
            case 2: // Gnp w A, transAS
                czyt(&n, &rep, &p);
                druk1(n, rep, p);
                for (int i = 1; i <= rep; i++) {
                    Gnp(n, p, A);
                    drukA(n, A);
                    transAS(n, A, S);
                    drukS(n, S);
                    drukS1(n, S);
                    break;
                }
            case 3: //Gnp w A, czy spojny?
                czyt(&n, &rep, &p);
                c = 0;
                for (int i = 1; i <= rep; i++) {
                    Gnp(n, p, A);
                    drukA(n, A);
                    if (spojny(n, A)) {
                        c++;
                        printf(" spojny");
                    }
                }
                printf("\n\nliczba grafow spojnych w probce, c=%d\n", c);
                break;
            case 4: // czas Gnp + spojnosc
                czyt(&n, &rep, &p);
                czas1 = pomiar();
                c = 0;
                for (int i = 1; i <= rep; i++) {
                    Gnp(n, p, A);
                    if (spojny1(n, A))
                        c++;
                }
                czas2 = pomiar();
                printf("\nliczba grafow spojnych w probce, c=%d\n", c);

                printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLOCKS_PER_SEC);
                break;
            case 5: // czas Gnp
                czyt(&n, &rep, &p);
                czas1 = pomiar();
                for (int i = 1; i <= rep; i++) Gnp(n, p, A);
                czas2 = pomiar();
                printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLOCKS_PER_SEC);
                break;
            default:
                printf("Taki wariant nie istnieje!\n");
                exit(EXIT_FAILURE);
        }
    } while (true);
}

void czyt(int *n, int *rep, float *p)
{
    do {
        printf("n, p, rep= ");
        scanf("%d %f %d", n, p, rep);
    } while ((*n > NMAX) && (*p > 1) && (*rep > 100000));
}

void init(int n, t1 E, int *total)
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

void GnpE(int total, float p, t1 E)
{
    for (int h = 1; h <= total; h++)
        E[h].code = Random() <= p;
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

void transES(int n, int total, t1 E, ts S)
{
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            S[i].w[j] = false;
        S[i].l = 0;
    }
    for (int h = 1; h <= total; h++)
        if (E[h].code) {
            S[E[h].a].w[E[h].b] = true;
            S[E[h].b].l++;
            S[E[h].b].w[E[h].a] = true;
            S[E[h].b].l++;
        }
}

void transAS(int n, t2 A, ts S)
{
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            S[i].w[j] = false;
        S[i].l = 0;
    }
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            if (A[i][j]) {
                S[i].w[j] = true;
                S[i].l++;
                S[j].w[i] = true;
                S[j].l++;
            }
}

void drukx(int n, t3 x)
{
    printf("x: ");
    for (int i = 1; i <= n; i++)
        printf("%d ", x[i]);
    printf("\n");
}

void skladowa(int n, int v, t2 A, t3 x)//x jest wynikiem
{
     /* przeglada sie graf odwiedzajac wierzcholki */
    for (int j = 1; j <= n; j++)
        if (A[v][j] && !x[j]) { // jezeli "j" jest sasiadem "v"
            //jeszcze nie odwiedzonym
            x[j] = true; // to odwiedz "j"
            drukx(n, x);
            skladowa(n, j, A, x);
        }
}

bool spojny(int n, t2 A) // czy spojny
{
    int i;
    t3 x;
    bool b;

    for (int i = 1; i <= n; i++)
        x[i] = false; // przygotowanie tablicy x
    x[1] = true;  //odwiedzamy wierzcholek numer 1
    drukx(n, x);
    skladowa(n, 1, A, x); /* x jest wynikiem: ktore wierzcholki naleza do te samej
                           * skladowej co wierzcholek nr 1*/
    b = true;     /* zakladamy poczatkowo, ze wszystkie do niej naleza,
                   * przegladamy tablice x od 1 do konca jesli nie bylo w niej
                   * wczesniej wartosci "false" */
    i = 1;
    while (i <= n && b) {
        b = x[i];
        i++;
    }

    return b;
}

void skladowa1(int n, int v, t2 A, t3 x)
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
    t3 x;
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

void druk1(int n, int rep, float p)
{
    printf("\nGnp, n= %3d,p= %7.4f, rep= %5d\n", n, p, rep);
}

void drukE(int total, t1 E)
{
    int h = 0;

    printf("\nKrawedzie z E:\n");
    for (int l = 1; l <= total; l++) {
        if (E[l].code) {
            h++;
            printf("%4d %3d", E[l].a, E[l].b);
            if (h % 10 == 0)
                printf("\n");
        }
    }
    printf("\n");
}

void drukA(int n, t2 A)
{
    int h = 0;

    printf("\nKrawedzie z A:\n");
    for (int i = 1; i <= n - 1; i++)
        for (int j = i + 1; j <= n; j++) {
            if (A[i][j]) {
                h++;
                printf("%4d %3d", i, j);
                if (h % 10 == 0)
                    printf("\n");
            }
        }
    printf("\n\n");
}

void drukS(int n, ts S)
{
    int h = 0; // licznik krawedzi

    printf("Krawedzie z S:\n");
    for (int i = 1; i <= n - 1; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (S[i].w[j]) {
                printf("%4d %3d", i, j);
                h++;
                if (h % 10 == 0)
                    printf("\n");
            }
        }
    }
    printf("\n\n");
}
void drukzbior(int first, int n, zbior z)
{
    int x = first;

    while (z[x] || x <= n) {
        if (z[x]) {
            printf("%3d,", x);
            z[x] = false;
        }
        x++;
    }
}

void drukS1(int n, ts S)
{
    printf("Tablica S: \n");
    for (int i = 1; i <= n; i++) {
        printf("%3d:", i);
        drukzbior(1, n, S[i].w);
        printf("\n");
    }
    printf("\n");
}
