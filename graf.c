//program p3	KTB Oct 11, 1996
# include <stdio.h>
# include <stdlib.h>
# include <conio.h>
# include <time.h>
# include <limits.h>

#define randomize() srand(unsigned(time(NULL)))
#define random(a) rand()%a
#define Random() (rand()%10000)*0.0001
//#define Random()  (float)rand()/(float)INT_MAX
//#define Random()  rand()*4.656612875245796924105750827168e-10


# define nmax 101
# define kmax nmax*(nmax-1)/2

enum Boolean {falsz=0, prawda=1};
typedef int t[nmax];
typedef struct {
    int a, b;
} r;
typedef r t1[kmax];     // E
typedef enum Boolean t2[nmax][nmax]; // A


void czyt(int *n, int *rep, float *p);
void Gnp (int n, float p, t2 A);
void czyt1(int *n, int * k, int *rep);
void init(int n, t1 E, int * total);
void Gnk(int k, int total, t1 E);
void transEA(int n, int k, int total, t1 E, t2 A);
void druk1(int n, int rep, float p);
void druk1a(int n, int k, int rep);
void drukE(int k, int total, t1 E);
void drukA(int n, t2 A);
clock_t pomiar(void);

int main()
{
    int i,k,n,rep,total,wariant;
    float p;
    t2 A;
    t1 E;
    clock_t czas1, czas2;

    randomize();
    do {
        printf("Wariant: (1/2/3)");
        scanf("%d",&wariant);
        switch(wariant) {
        case 1: { //Gnp
            czyt(&n, &rep, &p);
            druk1(n,rep,p);
            for(i=1; i<= rep; i++) {
                Gnp(n,p,A);
                drukA(n,A);
            }
            break;
        } // 1
        case 2: { //czas Gnp
            czyt(&n, &rep, &p);
            czas1=pomiar();
            for(i=1; i<=rep; i++)
                Gnp(n,p,A);
            czas2=pomiar();
            printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLK_TCK);
            break;
        } //2
        case 3: { //Gnk, transEA
            czyt1(&n,&k,&rep);
            druk1a(n,k,rep);
            init(n,E,&total);
            for(i=1; i<=rep; i++) {
                Gnk(k,total,E);
                drukE(k,total, E);
                transEA(n,k,total,E,A);
                drukA(n,A);
            }
            break;
        } //3
        /*
         case 4: //czas Gnk
         {

          break;
          } //4
        */
        /*
         case 5: //czas Gnp w E
         {

          break;
          } //5
        */

        default: {
            printf("Taki wariant nie istnieje!\n");
        }
        } // switch
        printf("koniec? 0/1\n");
    } while (getch()!='1');
    return 0;
} //main

void czyt(int *n, int *rep, float *p)
{
    do {
        printf("n, p, rep= ");
        scanf("%d%f%d",n,p,rep);
    } while ((*n > nmax) && (*p > 1) && (*rep > 100000));
} //czyt

void Gnp (int n, float p, t2 A)
{
    int i,j;
    enum Boolean x;

    for(i=1; i<=n; i++)
        A[i][i]=falsz;
    for(i=1; i<=n-1; i++)
        for(j=i+1; j<=n; j++) {
            //x=Boolean((random(1001)*0.001)<=p);
            x=Boolean(Random()<=p);

            A[i][j]=x;
            A[j][i]=x;
        }
} //Gnp

void czyt1(int *n, int * k, int *rep)
{
    do {
        printf("n, k, rep= ");
        scanf("%d%d%d",n,k,rep);
    } while ((*n > nmax) && (*k > kmax) && (*rep > 100000));
} //czyt1

void init(int n, t1 E, int * total)
{
    int i,j,h;
    h=0;
    for(i=1; i<=n-1; i++)
        for(j=i+1; j<=n; j++) {
            h++;
            E[h].a=i;
            E[h].b=j;
        }
    *total=h;
} //init

void Gnk(int k, int total, t1 E)
{
    int i,l,z;
    r x;
    l=total;
    for(i=1; i<=k; i++) {
        z=random(l)+1;
        x=E[z];
        E[z]=E[l];
        E[l]=x;
        l--;
    }
} //Gnk

void transEA(int n, int k, int total, t1 E, t2 A)
{
    int i,j,l;

    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
            A[i][j]=falsz;
    for(l=total; l>=total-k+1; l--) {
        i=E[l].a;
        j=E[l].b;
        A[i][j]=prawda;
        A[j][i]=prawda;
    }
} //transEA

void druk1(int n, int rep, float p)
{
    printf("\nGnp, n= %3d, p= %7.4f, rep= %5d \n",n,p,rep);
} //druk1

void druk1a(int n, int k, int rep)
{
    printf("\nGnk, n= %3d, k= %d, rep= %5d \n",n,k,rep);
} //druk1a

void drukE(int k, int total, t1 E)
{
    int h,l;
    printf("\nKrawedzie z E:\n");
    h=0;
    for(l=total; l>=total-k+1; l--) {
        h++;
        printf("%4d%3d",E[l].a,E[l].b);
        if(h%10==0)
            printf("\n");
    }
} //drukE

void drukA(int n, t2 A)
{
    int i,j,h;
    printf("\nKrawedzie z A:\n");
    h=0;
    for(i=1; i<=n-1; i++)
        for(j=i+1; j<=n; j++) {
            if(A[i][j]) {
                h++;
                printf("%4d%3d", i,j);
                if(h%10==0)
                    printf("\n");
            }
        }
    printf("\n\n");
} //drukA

clock_t pomiar(void)
{
    clock_t czas;
    czas = clock();
    return czas;
}//pomiar


