//program p6, KTB Nov 4, 1996, Oct 15, 1998
# include <stdio.h>
# include <stdlib.h>
# include <conio.h>
# include <time.h>
# include <math.h>
# include <limits.h>

#define randomize() srand(unsigned(time(NULL)))
#define random(a) rand()%a
#define Random() (rand()%10000)*0.0001

# define nmax 51
# define kmax nmax*(nmax-1)/2
# define trmax kmax*(nmax-2)/3

enum Boolean {falsz=0, prawda=1};
typedef struct {
    int a, b;
} r;
typedef r t1[kmax];     					// E
typedef enum Boolean t2[nmax][nmax]; 	// A
typedef int t3[trmax+1]; 					//Q
typedef enum Boolean tx[nmax]; 			// x
typedef int t4[721]; 						//FOUR


void czyt(int *n, int *rep, float *p);
void czyt1(int *n, int * k, int *rep);
void Gnp (int n, float p, t2 A);
void init(int n, t1 E, int * total);
void Gnk(int k, int total, t1 E);
void transEA(int n, int k, int total, t1 E, t2 A);
void skladowa1(int n, int v, t2 A, tx x);
enum Boolean spojny1(int n, t2 A);
int triangles(int n,t2 A);
int cykl4(int n, t2 A);
int cykl4_1(int n,t2 A);
int cykl4TF(int n, t2 A);
void stat(int alltr, int rep, t3 Q, float *x,float *y);
void druk1(int n,int rep, float p);
void druk1a(int n, int k, int rep);
void drukA(int n, t2 A);
void druk2(int alltr, int rep, t3 Q, float x, float y);
clock_t pomiar(void);





int main()
{
    int c,cz,cz1,czTF,h,i,k,n,tr,rep,alltr,total,wariant;
    float p,x,y;
    t2 A;
    t1 E;
    clock_t czas1, czas2;
    t3 Q;
    randomize();
    do {
        printf("Wariant: (1/2/3/31/4/5)");
        scanf("%d",&wariant);
        switch(wariant) {
        case 1: { //Gnp w A, spojnosc, trojkaty, czworokaty
            czyt(&n,&rep,&p);
            druk1(n,rep,p);
            c=0;
            for(i=1; i<=rep; i++) {
                Gnp(n,p,A);
                tr=triangles(n,A);
                cz=cykl4(n,A);
                cz1=cykl4_1(n,A);
                czTF=cykl4TF(n,A);
                drukA(n,A);
                if (spojny1(n,A)) {
                    c++;
                    printf("\tspojny\n");
                }
                printf("tr=%6d, cz=%7d, cz1=%7d, czTF=%7d\n\n",tr,cz, cz1, czTF);
            }
            printf("\nliczba grafow spojnych w probce, c=%3d",c );
            break;
        } // 1
        case 2: { //Gnk w E, spojnosc, trojkaty, czworokaty
            czyt1(&n,&k,&rep);
            init(n,E,&total);
            for(i=1; i<=rep; i++) {
                Gnk(k,total,E);
                transEA(n,k,total,E,A);
                tr=triangles(n,A);
                czTF=cykl4TF(n,A);
                drukA(n,A);
                if(spojny1(n,A)) {
                    c++;
                    printf("\tspojny\n");
                }
                printf("tr=%3d, cz=%7d",tr,czTF);
            }
            break;
        } //2
        case 3: { //czas Gnp, trojkaty
            czyt(&n,&rep,&p);
            druk1(n,rep,p);
            czas1=pomiar();
            for(i=1; i<rep; i++) {
                Gnp(n,p,A);
                tr=triangles(n,A);
            }
            czas2=pomiar();
            printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLK_TCK);
            break;
        } //3
        case 31: { //czas Gnp, czworokaty
            czyt(&n,&rep,&p);
            druk1(n,rep,p);
            czas1=pomiar();
            for(i=1; i<rep; i++) {
                Gnp(n,p,A);
                czTF=cykl4TF(n,A);
            }
            czas2=pomiar();
            printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLK_TCK);
            break;
        } //31
        case 4: { // Gnp, rozklad liczby trojkatow
            czyt(&n,&rep,&p);
            druk1(n,rep,p);
            alltr=n*(n-1)*(n-2)/6;
            for(h=0; h<=alltr; h++)
                Q[h]=0;
            for(h=1; h<=rep; h++) {
                Gnp(n,p,A);
                tr=triangles(n,A);
                Q[tr]++;
            }
            stat(alltr,rep,Q,&x,&y);
            druk2(alltr,rep,Q,x,y);
            break;
        } //4
        case 5: { //Gnk, rozklad liczby trojkatow
            czyt1(&n,&k,&rep);
            druk1a(n,k,rep);
            init(n,E,&total);
            alltr=n*(n-1)*(n-2)/6;
            for(h=0; h<=alltr; h++)
                Q[h]=0;
            for(h=1; h<=rep; h++) {
                Gnk(k, total,E);
                transEA(n,k,total,E,A);
                tr=triangles(n,A);
                Q[tr]++;
            }
            stat(alltr,rep,Q,&x,&y);
            druk2(alltr,rep,Q,x,y);
            break;
        } //5
        default: {
            printf("Taki wariant nie istnieje!\n");
        }
        } // switch
        printf("koniec? 0/1\n");
    } while (getch()!='1');
    return 0;


}  //main


void czyt(int *n, int *rep, float *p)
{
    do {
        printf("n, p, rep= ");
        scanf("%d%f%d",n,p,rep);
    } while ((*n > nmax) && (*p > 1) && (*rep > 100000));
} //czyt

void czyt1(int *n, int * k, int *rep)
{
    do {
        printf("n, k, rep= ");
        scanf("%d%d%d",n,k,rep);
    } while ((*n > nmax) && (*k > kmax) && (*rep > 100000));
} //czyt1

void Gnp (int n, float p, t2 A)
{
    int i,j;
    enum Boolean x;

    for(i=1; i<=n; i++)
        A[i][i]=falsz;
    for(i=1; i<=n-1; i++)
        for(j=i+1; j<=n; j++) {
            x=Boolean(Random()<=p);
            A[i][j]=x;
            A[j][i]=x;
        }
} //Gnp

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

void skladowa1(int n, int v, t2 A, tx x)
{
    int j;
    for(j=1; j<=n; j++)
        if(A[v][j] && !x[j]) {
            x[j]=prawda;
            skladowa1(n,j,A,x);
        }
} //skladowa1

enum Boolean spojny1(int n, t2 A)
{
    int i;
    tx x;
    enum Boolean b;
    for(i=1; i<=n; i++)
        x[i]=falsz;
    x[1]=prawda;
    skladowa1(n,1,A,x);
    b=prawda;
    i=1;
    while(i<=n && b) {
        b=x[i];
        i++;
    }
    return b;
} // spojny1

int triangles(int n,t2 A)
{
    int i,j,h,x;
    x=0;
    for(i=1; i<=n-2; i++)
        for(j=i+1; j<=n; j++)
            if(A[i][j])
                for(h=j+1; h<=n; h++)
                    if(A[i][h] && A[j][h])
                        x++;
    return x;
}//triangles

int cykl4(int n, t2 A)
//Miroslaw Kupczyk, Inf III, Oct, 96
{
    int i,j,k,h,x;
    x=0;
    if (n>=4)
        for(i=1; i<=n-2; i++)
            for(j=i+1; j<=n-1; j++)
                if(A[i][j])
                    for(k=j+1; k<=n; k++)
                        if(A[i][k])
                            for(h=i; h<=n; h++)
                                if((h!=j)&&(h!=i)&&(h!=k))
                                    if((A[j][h])&&(A[k][h]))
                                        x++;
    return x;
} //cykl4

int cykl4_1(int n,t2 A)
// Miroslaw Kupczyk, Inf III, Oct 96
// ulepszone Rafal Kowalski, Inf IV/ISI, Oct 96
{
    int i,j,k,h,x;
    x=0;
    if (n>=4)
        for(i=1; i<=n-3; i++)
            for(j=i+1; j<=n-1; j++)
                if(A[i][j])
                    for(k=j+1; k<=n; k++)
                        if(A[i][k])
                            for(h=i+1; h<=n; h++)
                                if((h!=j)&& (h!=k))
                                    if((A[j][h])&&(A[k][h]))
                                        x++;
    return x;
} //cykl4_1

int cykl4TF(int n, t2 A) //Tomasz Fitzerman, Tel. II, Oct 1998
{
    int c,i,j,k,x;
    x=0;
    if(n>=4)
        for(i=1; i<=n-1; i++)
            for(j=i+1; j<=n; j++) {
                c=0;
                for(k=i+1; k<=n; k++)
                    if((A[i][k])&& (A[j][k]))
                        c++;
                if(c>=2)
                    x+=c*(c-1)/2;
            }
    return x;
} //cyklTF

void stat(int alltr, int rep, t3 Q, float *x,float *y)
{
    int i;
    float s;
    s=0;
    for(i=0; i<=alltr; i++)
        s+=(Q[i]/(float)rep)*i;
    *x=s;
    s=0;
    for(i=0; i<=alltr; i++)
        s+=(Q[i]/(float)rep)*(i-*x)*(i-*x);    //sqr(i-*x);
    *y=s;
    // printf("%10.3f%10.3f",x,y);
} //stat

void druk1(int n,int rep, float p)
{
    printf("\nGnp, n= %3d,p= %7.4f, rep= %5d\n", n, p, rep);
} //druk1

void druk1a(int n, int k, int rep)
{
    printf("\nGnk, n= %3d, k= %d, rep= %5d \n",n,k,rep);
} //druk1a

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

void druk2(int alltr, int rep, t3 Q, float x, float y)
{
    int i,j;
    printf("Distibution of triangles:\n");
    printf("     ");
    for(i=0; i<=9; i++)
        printf("%7d",i);
    printf("\n-----");
    for(i=0; i<=9; i++)
        printf("-------");
    for(i=0; i<=alltr; i++) {
        j=i%10;
        if(j==0)
            printf("\n%3d\t",i);
        printf("%7.4f", Q[i]/(float)rep);
    }
    printf("\nE(tr)=%8.2f\tV(tr)=%8.2f\n", x,y);
}//druk2

clock_t pomiar(void)
{
    clock_t czas;
    czas = clock();
    return czas;
}//pomiar



