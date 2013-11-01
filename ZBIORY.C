//program p5, KTB Oct 28, 1996
# include <stdio.h>
# include <stdlib.h>
# include <conio.h>
# include <time.h>
# include <limits.h>

#define randomize() srand(unsigned(time(NULL))) 
#define random(a) rand()%a
#define Random() (rand()%10000)*0.0001

# define nmax 101
# define kmax nmax*(nmax-1)/2


enum Boolean {falsz=0, prawda=1};
typedef struct
        {
        int a, b;
        enum Boolean code;
        }r;
typedef r t1[nmax];     // E
typedef enum Boolean zbior[nmax];
typedef struct
        {
        zbior w;
        int l;
        }rs;
typedef rs ts[nmax]; // S
typedef enum Boolean t2[nmax][nmax]; // A
typedef enum Boolean t3[nmax]; // x


void czyt(int *n, int *rep, float *p);
void init(int n, t1 E, int * total);
void GnpE(int total, float p, t1 E);
void Gnp (int n, float p, t2 A);
void transES(int n, int total, t1 E, ts S);
void transAS(int n, t2 A, ts S);
void drukx(int n,t3 x);
void skladowa(int n, int v, t2 A, t3 x);
enum Boolean spojny(int n, t2 A);
void skladowa1(int n, int v, t2 A, t3 x);
enum Boolean spojny1(int n, t2 A);
void druk1(int n,int rep, float p);
void drukE(int total, t1 E);
void drukA(int n, t2 A);
void drukS(int n, ts S);
void drukzbior(int first,int n, zbior z);
void drukS1(int n,ts S);
clock_t pomiar(void);




int main()
{
int c,i,n,rep,total,wariant;
float p;
t1 E;
ts S;
t2 A;
clock_t czas1, czas2;

	randomize();
	do
   	{
      printf("Wariant: (1/2/3/4/5)");
      scanf("%d",&wariant);
      switch(wariant)
      	{
      	case 1: // Gnp w E, transES
         	{
            czyt(&n,&rep,&p);
            druk1(n,rep,p);
            init(n,E,&total);
            for(i=1;i<=rep;i++)
                {
                GnpE(total,p,E);
                drukE(total,E);
                transES(n,total,E,S);
                drukS(n,S);
                drukS1(n,S);
                }
            break;
            } // 1
         case 2: // Gnp w A, transAS
         	{
            czyt(&n,&rep,&p);
            druk1(n,rep,p);
            for(i=1;i<=rep;i++)
                {
                Gnp(n,p,A);
                drukA(n,A);
                transAS(n,A,S);
                drukS(n,S);
                drukS1(n,S);
                }
            break;
            } //2
         case 3: //Gnp w A, czy spojny?
            {
            czyt(&n,&rep,&p);
            c=0;
            for(i=1;i<=rep;i++)
                {
                Gnp(n,p,A);
                drukA(n,A);
                if (spojny(n,A))
                    {
                    c++;
                    printf(" spojny");
                    }
                }
            printf("\n\nliczba grafow spojnych w probce, c=%d\n",c);
            break;
            } //3
         case 4: // czas Gnp + spojnosc
            {
            czyt(&n,&rep,&p);
            czas1=pomiar();
            c=0;
            for(i=1;i<=rep;i++)
                {
                Gnp(n,p,A);
                if (spojny1(n,A))
                    c++;
                }
            czas2=pomiar();
            printf("\nliczba grafow spojnych w probce, c=%d\n",c);
            
            printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLK_TCK);
   			break;
            } //4
         case 5:   // czas Gnp
            {
            czyt(&n,&rep,&p);
            czas1=pomiar();
            for(i=1;i<=rep;i++) Gnp(n,p,A);
            czas2=pomiar();
            printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLK_TCK);
			break;
            } //5
        default:
            {
            printf("Taki wariant nie istnieje!\n");
            }
          } // switch
	   printf("koniec? 0/1\n");
   }
   while (getch()!='1');
   return 0;


}  //main


void czyt(int *n, int *rep, float *p)
{
  do
   {
   	printf("n, p, rep= ");
    scanf("%d%f%d",n,p,rep);
   }
   while ((*n > nmax) && (*p > 1) && (*rep > 100000));
}

void init(int n, t1 E, int * total)
{
int i,j,h;
    h=0;
    for(i=1;i<=n-1; i++)
        for(j=i+1; j<=n;j++)
            {
             h++;
             E[h].a=i;
             E[h].b=j;
            }
    *total=h;
} //init

void GnpE(int total, float p, t1 E)
{
int h;
    for(h=1;h<=total;h++)
        E[h].code=Boolean(Random()<=p);
} //GnpE

void Gnp (int n, float p, t2 A)
{
int i,j;
enum Boolean x;

    for(i=1; i<=n; i++)
        A[i][i]=falsz;
    for(i=1; i<=n-1; i++)
        for(j=i+1; j<=n; j++)
            {
             x=Boolean(Random()<=p);
             A[i][j]=x;
             A[j][i]=x;
            }
} //Gnp

void transES(int n, int total, t1 E, ts S)
{
int i,j,h;
    for(i=1;i<=n;i++)
        {
        for(j=1;j<=n;j++)
            S[i].w[j]=falsz;
        S[i].l=0;
        }
    for(h=1;h<=total;h++)
        if(E[h].code)
            {
            S[E[h].a].w[E[h].b]=prawda;
            S[E[h].b].l++;
            S[E[h].b].w[E[h].a]=prawda;
            S[E[h].b].l++;
            }
}//transES

void transAS(int n, t2 A, ts S)
{
int i,j;
    for(i=1;i<=n;i++)
        {
        for(j=1;j<=n;j++)
            S[i].w[j]=falsz;
        S[i].l=0;
        }
    for(i=1;i<n;i++)
        for(j=i+1;j<=n;j++)
            if (A[i][j])
                {
                S[i].w[j]=prawda;
                S[i].l++;
                S[j].w[i]=prawda;
                S[j].l++;
                }
}// transAS

void drukx(int n,t3 x)
{
int i;
    printf("x: ");
    for(i=1;i<=n;i++)
        printf("%d ", x[i]);
    printf("\n");
}  //drukx

void skladowa(int n, int v, t2 A, t3 x)//x jest wynikiem
{
int j; //przeglada sie graf odwiedzajac wierzcholki
    for(j=1;j<=n;j++)
        if(A[v][j] && !x[j])// jezeli "j" jest sasiadem "v"
            {                  //jeszcze nie odwiedzonym
            x[j]=prawda; // to odwiedz "j"
            drukx(n,x);
            skladowa(n,j,A,x);
            }
} // skladowa

enum Boolean spojny(int n, t2 A) // czy spojny
{
int i;
t3 x;
enum Boolean b;
    for(i=1;i<=n;i++)
        x[i]=falsz; // przygotowanie tablicy x
    x[1]=prawda;    //odwiedzamy wierzcholek numer 1
    drukx(n,x);
    skladowa(n,1,A,x); /* x jest wynikiem: ktore wierzcholki naleza do te samej
                       skladowej co wierzcholek nr 1*/
    b=prawda;     /*zakladamy poczatkowo, ze wszystkie do niej naleza,
    				przegladamy tablice x od 1 do konca jesli nie bylo w niej
               wczesniej wartosci "false" */
    i=1;
    while(i<=n && b)
        {
        b=x[i];
        i++;
        }
    return b;
} //spojny

void skladowa1(int n, int v, t2 A, t3 x)
{
int j;
    for(j=1;j<=n;j++)
        if(A[v][j] && !x[j])
            {
            x[j]=prawda;
            skladowa1(n,j,A,x);
            }
} //skladowa1

enum Boolean spojny1(int n, t2 A)
{
int i;
t3 x;
enum Boolean b;
    for(i=1;i<=n;i++)
        x[i]=falsz;
    x[1]=prawda;
    skladowa1(n,1,A,x);
    b=prawda;
    i=1;
    while(i<=n && b)
        {
        b=x[i];
        i++;
        }
    return b;
} // spojny1

void druk1(int n,int rep, float p)
{
printf("\nGnp, n= %3d,p= %7.4f, rep= %5d\n", n, p, rep);
} //druk1

void drukE(int total, t1 E)
{
int h,l;
    printf("\nKrawedzie z E:\n");
    h=0;
    for(l=1;l<=total;l++)
        {
        if (E[l].code)
            {
            h++;
            printf("%4d%3d",E[l].a,E[l].b);
            if(h%10==0)
                printf("\n");
            }
        }
    printf("\n");
} //drukE

void drukA(int n, t2 A)
{
int i,j,h;
    printf("\nKrawedzie z A:\n");
    h=0;
    for(i=1;i<=n-1;i++)
        for(j=i+1;j<=n; j++)
            {
            if(A[i][j])
                {
                h++;
                printf("%4d%3d", i,j);
                if(h%10==0)
                    printf("\n");
                }
            }
    printf("\n\n");
} //drukA

void drukS(int n, ts S)
{
int i,j,h;
    printf("Krawedzie z S:\n");
    h=0;  //licznik krawedzi
    for(i=1;i<=n-1;i++)
        {
        for(j=i+1;j<=n;j++)
            {
            if(S[i].w[j])
                {
                printf("%4d%3d",i,j);
                h++;
                if(h%10==0)
                    printf("\n");
                }
            }
        }
    printf("\n\n");
}
void drukzbior(int first,int n, zbior z)
{
int x;
    x=first;
    while(z[x] || x<=n)
        {
        if (z[x])
            {
            printf("%3d,",x);
            z[x]=falsz;
            }
        x++;
        }
} //drukzbior

void drukS1(int n,ts S)
{
int i;
    printf("Tablica S: \n");
    for(i=1;i<=n;i++)
        {
        printf("%3d:",i);
        drukzbior(1,n, S[i].w);
        printf("\n");
        }
    printf("\n");
}  //druk S1

clock_t pomiar(void)
{
clock_t czas;
    czas = clock();
    return czas;
}//pomiar


