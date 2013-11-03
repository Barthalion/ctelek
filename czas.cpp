//program p2	KTB Oct 7,1996
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <limits.h>

#define randomize() srand(unsigned(time(NULL)))
#define random(a) rand()%a
#define nmax 101

typedef int t[nmax]; //a

void czyt(int *n, int *z);
void czyt1(int *n, int *z, int *rep);
void generacja(int n, int z, t a);
void druk(int n, t a);
void sort(int n, t a);
void maxindeks(int n,int integer, t a, int *k);
void sort1(int n,t a);
void druk1(int n, int z, t a);
void druk2(int n, t a);
clock_t pomiar(void);
void kopiuj_tablice(int n, t b, t a);

int main()
{
    int i,j,n,z,rep,wariant;
    t a,b;
    clock_t czas1, czas2;


    randomize();
    do {
        printf("Info INT_MAX: %d\n",INT_MAX);
        printf("Wariant: (1/2)");
        scanf("%d",&wariant);
        switch(wariant) {
        case 1: { //sort i sort1
            czyt(&n,&z);
            generacja(n,z,a);
            kopiuj_tablice(n,b,a);
            druk1(n,z,a);
            sort(n,a);
            druk2(n,a);
            sort1(n,b);
            druk2(n,b);
            break;
        } // 1
        case 2: { //czas
            czyt1(&n,&z,&rep);
            czas1=pomiar();
            //for(j=1;j<=100;j++)
            for(i=1; i<=rep; i++) {
                generacja(n,z,a);
                sort(n,a);
            }
            czas2=pomiar();

            /* printf("clock: %d\n", czas2 - czas1); */

            printf("czas: %f\n", (float)(czas2 - czas1) / (float)CLK_TCK);
            break;
        } //2
        default: {
            printf("Taki wariant nie istnieje!\n");
        }
        } // switch
        printf("koniec? 0/1\n");
    } while (getch()!='1');
    return 0;
} //main


void czyt(int *n, int *z)
{
    do {
        printf("n,z= ");
        scanf("%d%d",n,z);
    } while (*n > nmax);

} //czyt

void czyt1(int *n, int *z, int *rep)
{
    do {
        printf("n,z,rep= ");
        scanf("%d%d%d",n,z,rep);
    } while ((*n > nmax) && (*z > 32000) && (*rep > 100000));
} //czyt1

void generacja(int n, int z, t a)
{
    int i;
    for(i=1; i<=n; i++)
        a[i]=random(z)+1;
} //generacja

void druk(int n, t a)
{
    int i;
    for(i=1; i<=n; i++) {
        printf("%6d", a[i]);
        if(i % 10==0)
            printf("\n");
    }
} //druk

void sort(int n, t a)
{
    int i,j,k, naj;
    for(i=1; i<=n-1; i++) {
        naj=a[i];
        k=i;
        for(j=i+1; j<=n; j++)
            if (a[j]>naj) {
                naj=a[j];
                k=j;
            }	//popraw
        if (i!=k) {
            //zamien
            a[k]=a[i];
            a[i]=naj;
        }
        /*printf("\n");
        printf("i= %3d",i);
        druk(n,a); */
    } // i
} //sort

void maxindeks(int n,int first, t a, int *k)
//k jest indeksem najwiekszego elementu ciagu o indeksach od first do n
{
    int j,x;
    x=a[first];
    *k=first;
    for(j=first+1; j<=n; j++)
        if (a[j]>x) {
            x=a[j];
            *k=j;
        }
} //maxindeks

void sort1(int n,t a)
{
    int i,k,naj;
    for(i=1; i<=n-1; i++) {
        maxindeks(n,i,a,&k);
        if (i!=k) {
            naj=a[k];
            a[k]=a[i];
            a[i]=naj;
        }
    } // i
} // sort1

void druk1(int n, int z, t a)
{
    printf("\n");
    printf("Sortowanie tablicy, n= %3d,z= %5d\n",n,z);
    printf("Elementy: \n");
    druk(n,a);
} //druk1

void druk2(int n, t a)
{
    printf("Posortowane: \n");
    druk(n,a);
    printf("\n");
} //druk2

clock_t pomiar(void)
{
    clock_t czas;
    czas = clock();
    return czas;
}//pomiar1

void kopiuj_tablice(int n, t b, t a)
{
    int i;
    for(i=1; i<=n; i++)
        b[i]=a[i];
} //kopiuj_tablice

