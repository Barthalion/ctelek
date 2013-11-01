//program p4	KTB Oct 21,1996
# include <stdio.h>
# include <stdlib.h>
# include <conio.h>
# include <time.h>
# include <limits.h>

#define randomize() srand(unsigned(time(NULL)))
#define random(a) rand()%a
#define Random() (rand()%10000)*0.0001

# define nmax 11
# define kmax nmax*(nmax-1)/2
# define pmax 9 //max liczba roznych wartosci p w tablicy PR


enum Boolean {falsz=0, prawda=1};
typedef int t[nmax];
typedef struct {
    int a, b;
} r;
typedef r t1[kmax];     					// E
typedef enum Boolean t2[nmax][nmax]; 	// A
typedef int t3[kmax];                  // R
typedef int t4[kmax][pmax+1];          // PR
typedef int t5[12];                    // Q, n=4


void czyt(int *n, int *rep, float *p);
void czyt1(int *n, int *rep, float *p1,float *p2,float *p3, int *total);
void Gnp(int n, float p, t2 A, int *k);
void kraw(int n, int rep,int total, float p1,float p2, float p3, t4 PR);
void strukt(int n, int rep, float p, t5 Q);  //n=4
void druk1(int n,int rep, float p);
void drukA(int n,int k, t2 A);
void druk(int n,float p1,float p2, float p3, int *l); //naglowek
void drukPR(int l,int total,int rep, t4 PR); //rozklad
void drukQ(int n, int rep, float p, t5 Q);
clock_t pomiar(void);



int main()
{
    int i,k,l,n,rep,total,wariant;
    float p,p1,p2,p3;
    t2 A;
    t4 PR;
    t5 Q;
    clock_t czas1, czas2;


    randomize();
    do {
        printf("Wariant: (1/2/3/4)");
        scanf("%d",&wariant);
        switch(wariant) {
        case 1: { //Gnp
            czyt(&n,&rep,&p);
            druk1(n,rep,p);
            for(i=1; i<=rep; i++) {
                Gnp(n,p,A,&k);
                drukA(n,k,A);
            }
            break;
        } // 1
        case 2: { // czas kraw
            czyt1(&n,&rep,&p1,&p2,&p3,&total);
            czas1=pomiar();
            kraw(n,rep,total,p1,p2,p3,PR);
            czas2=pomiar();
            printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLK_TCK);
            break;
        } //2
        case 3: {
            czyt1(&n,&rep,&p1,&p2,&p3,&total);
            druk(n,p1,p2,p3,&l);  //naglowek
            kraw(n,rep,total,p1,p2,p3,PR);
            drukPR(l,total,rep,PR);     //rozklad
            break;
        } //3
        case 4: {
            // n = 4
            czyt(&n,&rep,&p);
            n = 4;
            strukt(n,rep,p,Q);
            drukQ(n,rep,p,Q);
            break;
        } //4
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

void czyt1(int *n, int *rep, float *p1,float *p2,float *p3, int *total)
{
    int x;
    printf("n,rep, p1, p2, p3= ");
    scanf("%d%d%f%f%f",n,rep,p1,p2,p3);
    x=*n;
    *total=x*(x-1)/2;
} //czyt1

void Gnp(int n, float p, t2 A, int *k)
{
    int i,j,h;
    enum Boolean x;
    h=0;
    for(i=1; i<=n; i++)
        A[i][i]=falsz;  // przygotowanie A
    for(i=1; i<=n-1; i++) //generacja Gnp
        for(j=i+1; j<=n; j++) {
            x=Boolean(Random()<=p);
            A[i][j]=x;
            A[j][i]=x;
            if(x)
                h++;
        }
    *k=h;	//liczba krawedzi
} //Gnp

void kraw(int n, int rep,int total, float p1,float p2, float p3, t4 PR)
{
    t2 A;
    t3 R;
    float p;
    int i,j,k;
    p=p1;
    i=1;
    while (p<=p3) {
        for(j=0; j<=total; j++)
            R[j]=0;
        for(j=1; j<=rep; j++) {
            Gnp(n,p,A,&k);   //k jest liczba krawedzi grafu
            R[k]+=1;
        }
        for(k=0; k<=total; k++)
            PR[k][i]=R[k];
        p+=p2;
        i++;
    }
}  //kraw

void strukt(int n, int rep, float p, t5 Q) //n=4
{
    t2 A;
    t deg;
    int i,j,k,h,s,w,nr;

    for(i=1; i<=11; i++)
        Q[i]=0;
    for(h=1; h<=rep; h++) {
        Gnp(n,p,A,&k);
        for(i=1; i<=n; i++) {
            s=0;
            for(j=1; j<=n; j++)
                if(A[i][j])
                    s++;
            deg[i]=s;
        }
        w=0;
        for(i=1; i<=n; i++)
            if(deg[i]==2)
                w++;
        switch(k) {
        case 0: {
            nr=1;
            break;
        } //0
        case 1: {
            nr=2;
            break;
        } //1
        case 5: {
            nr=10;
            break;
        } //5
        case 6: {
            nr=11;
            break;
        } //6
        case 2: {
            if (w==0) nr=3;
            else	nr=4;
            break;
        } //2
        case 4: {
            if (w==4) nr=8;
            else nr=9;
            break;
        } //4
        case 3: {
            switch (w) {
            case 2: {
                nr=5;
                break;
            }// w=2
            case 3: {
                nr=6;
                break;
            } //w=3
            case 0: {
                nr=7;
                break;
            } //w=0
            } //switch w
            break;
        } //3
        }// switch k
        Q[nr]++;
    } //probka
} //strukt

void druk1(int n,int rep, float p)
{
    printf("\nGnp, n= %3d,p= %7.4f, rep= %5d\n", n, p, rep);
} //druk1

void drukA(int n,int k, t2 A)
{
    int i,j,h;
    printf("Krawedzie z A, k=%3d:\n",k);
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

void druk(int n,float p1,float p2, float p3, int *l)//naglowek
{
    int i,j,x;
    float p;
    printf("\nGnp, rozklad liczby krawedzi, n=%d\n",n);
    printf(" k p=");
    p=p1;
    i=1;
    while(p<=p3) {
        printf("%7.4f",p);
        p+=p2;
        i++;
    }
    x=i-1;
    printf("\n");
    for(j=1; j<=7*(x+1); j++)
        printf("-");
    printf("\n");
    *l=x;
} //druk

void drukPR(int l,int total,int rep, t4 PR)//rozklad
{
    int i,k;
    for(k=0; k<=total; k++) {
        printf("%2d   ",k);
        for(i=1; i<=l; i++)
            printf("%7.4f", PR[k][i]/(float)rep);
        printf("\n");
    }
} //drukPR

void drukQ(int n, int rep, float p, t5 Q)
{
    int i,s;
    printf("\nGnp, rozklad struktur, n=%2d",n);
    printf("p=%7.4f rep=%6d\n",p,rep);
    printf("nr    P(G ma nr)\n");
    printf("----------------\n");
    for(i=1; i<=11; i++)
        printf("%3d%11.4f\n",i,Q[i]/(float)rep);
    printf("----------------\n");
    s=0;
    for(i=1; i<=11; i++)
        s+=Q[i];
    printf("test=%7.4f\n",s/(float)rep);
} //drukQ
clock_t pomiar(void)
{
    clock_t czas;
    czas = clock();
    return czas;
}//pomiar



