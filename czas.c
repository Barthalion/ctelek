#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define nmax 101
typedef int t[nmax];

clock_t pomiar(void);
void czyt1(int *n, int *z, int *rep);
void czyt(int *n, int *z);
void druk1(int n, int z, t a);
void druk2(int n, t a);
void druk(int n, t a);
void generacja(int n, int z, t a);
void kopiuj_tablice(int n, t b, t a);
void maxindeks(int n, int integer, t a, int *k);
void sort1(int n, t a);
void sort(int n, t a);

int main(void)
{
    int n, z, rep, wariant;
    t a, b;
    clock_t czas1, czas2;

    srand((unsigned) time(NULL))

    printf("Info INT_MAX: %d\n", INT_MAX);

    do {
        printf("Wariant: (0/1/2) ");
        scanf("%d",&wariant);

        switch (wariant) {
            case 0:
                exit(EXIT_SUCCESS);
            case 1: //sort i sort1
                czyt(&n, &z);
                generacja(n, z, a);
                kopiuj_tablice(n, b, a);
                druk1(n, z, a);
                sort(n, a);
                druk2(n, a);
                sort1(n, b);
                druk2(n, b);
                break;
            case 2: //czas
                czyt1(&n, &z, &rep);
                czas1 = pomiar();
                for (int i = 1; i <= rep; i++) {
                    generacja(n, z, a);
                    sort(n, a);
                }
                czas2=pomiar();

                printf("czas: %lf\n", (double) (czas2 - czas1) / (double) CLOCKS_PER_SEC);
                break;
            default:
                printf("Taki wariant nie istnieje!\n");
        }
    } while (1);
}


void czyt(int *n, int *z)
{
    do {
        printf("n,z = ");
        scanf("%d %d", n, z);
    } while (*n > nmax);

}

void czyt1(int *n, int *z, int *rep)
{
    do {
        printf("n,z,rep = ");
        scanf("%d %d %d", n, z, rep);
    } while ((*n > nmax) && (*z > 32000) && (*rep > 100000));
}

void generacja(int n, int z, t a)
{
    for (int i = 1; i <= n; i++)
        a[i] = (rand() % z) + 1;
}

void druk(int n, t a)
{
    for (int i = 1; i <= n; i++) {
        printf("%6d", a[i]);
        if (i % 10 == 0)
            printf("\n");
    }
}

void sort(int n, t a)
{
    int k, naj;
    for (int i = 1; i <= n - 1; i++) {
        naj = a[i];
        k = i;
        for (int j = i+1; j <= n; j++)
            if (a[j] > naj) {
                naj = a[j];
                k = j;
            } //popraw
        if (i != k) {
            //zamien
            a[k]=a[i];
            a[i]=naj;
        }
        /*printf("\n");
        printf("i= %3d",i);
        druk(n,a); */
    }
}

void maxindeks(int n, int first, t a, int *k)
//k jest indeksem najwiekszego elementu ciagu o indeksach od first do n
{
    int x = a[first];
    *k = first;

    for (int i = first + 1; i <= n; i++)
        if (a[i] > x) {
            x = a[i];
            *k = i;
        }
}

void sort1(int n, t a)
{
    int k, naj;
    for (int i = 1; i<= n - 1; i++) {
        maxindeks(n, i, a, &k);
        if (i != k) {
            naj = a[k];
            a[k] = a[i];
            a[i] = naj;
        }
    }
}

void druk1(int n, int z, t a)
{
    printf("\n");
    printf("Sortowanie tablicy, n = %3d, z = %5d\n", n, z);
    printf("Elementy: \n");
    druk(n, a);
}

void druk2(int n, t a)
{
    printf("Posortowane: \n");
    druk(n, a);
    printf("\n");
}

clock_t pomiar(void)
{
    return (clock_t) clock();
}

void kopiuj_tablice(int n, t b, t a)
{
    for (int i = 1; i <= n; i++)
        b[i] = a[i];
}

