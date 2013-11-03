//program p15,	 KTB Jan 3, 1997
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <limits.h>

#define randomize() srand(unsigned(time(NULL)))
#define random(a) rand()%a
#define Random() (rand()%10000)*0.0001

#define nmax 101
#define kmax nmax *(nmax-1)/2

enum Boolean {falsz=0, prawda=1};

typedef int t[nmax];

typedef struct {
    int a, b;
} r;
typedef r t1[kmax];     // E
typedef enum Boolean t2[nmax][nmax];  //A
typedef int t3[nmax]; //Deg, C
typedef enum Boolean zbior [nmax];
typedef zbior tD[nmax]; //D


void czyt(int *n, float *p, int *rep);
void czyt1(int *n, int * k, int *rep);
void Gnp (int n, float p, t2 A);
void init(int n, t1 E, int * total);
void Gnk(int k, int total, t1 E);
void transEA(int n, int k, int total, t1 E, t2 A);
int Max(int n,t3 x);
void kol(t3 C, int d,int n,t3 Deg,t2 A);
void kolor(int n, t2 A, t3 Deg, t3 C,int *chi, int *delta);
void stat(int alltr, int rep, t3 Q, float *x,float *y);
void druk1(int n, float p, int rep);
void druk1a(int n, int k, int rep);
void drukA(int n, t2 A);
void druk2(int n, int delta, t3 Deg);
void druk2a(int n, int delta, t3 C);
void drukzbior(int first,int n, zbior z);
void druk3(int n, int chi, tD D);
clock_t pomiar(void);
void Kangur(int n,int rep,t2 A,int *ch,tD D);
void MonteCarlo(int n, t2 A,int *ch,t C);


//------------------------------------------------------------------------------
//unit monte
// Badanie dzielnosci grafu metoda JOG MC (c) Piotr Wrzeciono, 1997



void MonteCarlo(int n, t2 A,int *ch,t C)
//kolorowanie wierzch. grafu metoda Monte Carlo, spr. poprawnosci
{
    int i, j, x, s, max;
    t v;
    enum Boolean b;
    for (i=1; i<= n; i++)
        C[i]=0;
    for (i=1; i<= n; i++)
        v[i]=0;
    s=0;
    i=random(n) + 1;        // pierwszy wylosowany wierzcholek
    do {
        if (v[i]== 0) {
            v[i]=1;
            s++;    // odwiedzenie "i", s=licznik odwiedz.
            for (x=1; x<=n; x++) {
                if (A[i][x]) {      // "x" jest sasiadem "i"
                    // kolorowanie grafu
                    if ((C[i] == C[x]) &&(C[x] > 0))
                        C[i]=C[x] + 1;
                    if ((C[i] == 0) &&(C[x] > 0)) {
                        if (C[x] == 1)
                            C[i]=2;
                        if (C[x] > 1)
                            C[i]=1;
                    }
                    if ((C[i] == C[x]) && (C[x] == 0)) {
                        C[i]=1;
                        C[x]=2;
                    }
                }
                if (C[i] == 0)
                    C[i]=1;
            } // for x
            do {
                //sprawdzenie poprawnosci
                b=falsz;
                for (j=1; j<=n; j++)
                    if ((A[i][j]) && (C[i] == C[j])) {
                        C[i]=C[j] + 1;
                        b=prawda;
                    }
            } while( b);     // jest to najszybsze sprawdzenie poprawnosci
        } //if
        i=random(n) + 1;      // kolejny wylosowany wierzcholek
    } while  (s != n);
    max=1;
    for (i=1; i<=n; i++)
        if (C[i] > max)
            max=C[i];
    *ch=max;
} // MonteCarlo

void Kangur(int n,int rep,t2 A,int *ch,tD D)
/*Dane: n - liczba wierzcholkow, rep - liczba powtorzen, A - graf
 Wyniki: ch - liczba chromat., D - tabl. zbiorow wierzch. niezal.*/
{
    int i,j,k,m;
    t C;
    enum Boolean fin;
    //randomize();
    fin=falsz;
    i=0;
    k=1;
    do {
        i++;
        m=k;
        MonteCarlo(n, A, &k, C);    // Kangur Monte Carlo
        if (k < m)
            fin=prawda;
        if (i == rep)
            fin=prawda;        // RS
    } while (!fin);
    *ch=k;
    for (j=1; j<=k; j++)
        for(i=1; i<=n; i++)
            D[j][i]=falsz;	//D[j]:=[];   // D
    for (i=1; i<=n; i++) {
        j= C[i];
        D[j][i]= prawda;
    }
} // Kangur




int main ()
{
    int i,k,n,chi, delta,rep,total,wariant;
    float p;
    t1 E;
    t2 A;
    t3 Deg,C;
    clock_t czas1, czas2;
    tD D; // tD - typ w module monte



    randomize();
    do {
        printf("Wariant: (1/2/3/4/5/6/7)");
        scanf("%d",&wariant);
        switch(wariant) {
        case 1: { // Gnk w E, transEA i kolor
            czyt1(&n, &k, &rep);
            druk1a(n, k, rep);
            init(n, E, &total);
            for (i=1; i<=rep; i++) {
                Gnk(k, total, E);
                transEA(n, k, total, E, A);
                kolor(n, A, Deg, C, &chi, &delta);
                printf("\n");
                drukA(n, A);
                druk2(n, delta, Deg);
                druk2a(n, chi, C);
                Kangur(n, 1, A, &chi, D);
                druk3(n, chi, D);
            }
            break;
        } // 1
        case 2: { // Gnp w A i kolor
            czyt(&n, &p,&rep );
            druk1(n, p,rep);
            for (i=1; i<= rep; i++) {
                Gnp(n, p, A);
                kolor(n, A, Deg, C, &chi, &delta);
                printf("\n");
                drukA(n, A);
                druk2(n, delta, Deg);
                druk2a(n, chi, C);
            }
            printf("\n");
            break;
        } //2
        case 3: { // czas Gnp i kolor
            czyt(&n, &p, &rep);
            druk1(n,p,rep);
            czas1=pomiar();
            for(i=1; i<=rep; i++) {
                Gnp(n,p,A);
                kolor(n, A, Deg, C, &chi, &delta);
            }
            czas2=pomiar();
            printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLK_TCK);
            break;
        } //3
        case 4: //Gnk, rozklad liczby chromatycznej, momenty
            //przy stalym n i roznych k, zadanie domowe
        {
            czyt1(&n, &k, &rep);
            druk1a(n, k, rep);
            init(n, E, &total);//przygotowanie struktury
            for (i=1; i<=  rep; i++) {
                Gnk(k, total, E);
                transEA(n, k, total, E, A);
                kolor(n, A, Deg, C, &chi, &delta);
                //zbieranie informacji
            }
            // momenty
            //druk wynikow
            break;
        } //4
        case 5: /* Gnk, rozklad liczby chromatycznej, momenty
                    w zaleznosci od n oraz k = n*(n-1) div 4, zadanie domowe*/
        {
            czyt1(&n, &k, &rep);
            druk1a(n, k, rep);
            init(n, E, &total);//przygotowanie struktury
            for (i=1; i<= rep; i++) {
                Gnk(k, total, E);
                transEA(n, k, total, E, A);
                kolor(n, A, Deg, C, &chi, &delta);
                //zbieranie informacji
            }
            //momenty
            //druk wynikow
            break;
        } //5
        case 6: /*zmiana rekurencji na iteracje w algorytmie kolor,
            			porownanie czasu wykonania, zadanie domowe*/
        {
            break;
        } //6
        case 7: { // testowanie innych algorytmow kolorowania, zadanie wlasne
            break;
        } //7
        default: {
            printf("Taki wariant nie istnieje!\n");
        }
        } // switch
        printf("koniec? 0/1\n");
    } while (getch()!='1');

    return 0;
}

void czyt(int *n, float *p,int *rep )
{
    do {
        printf("n, p,rep= ");
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

int Max(int n,t3 x)
{
    int i,m;
    m=0;
    for (i=1; i<=n; i++)
        if (x[i] > m)
            m=x[i];
    return m;
} // max

void kol(t3 C, int d,int n,t3 Deg,t2 A)// rekurencyjna
{
    int i,j,k;
    zbior z;
    enum Boolean b;

    if (d >= 0) {
        //kolorowanie wszystkich wierzcholkow o stopniu "d"
        for (i=1; i<=n; i++)
            if (Deg[i] == d) {
                //"z" jest zbiorem kolorow sasiadow wierzcholka "i"
                for(k=1; k<=n; k++)
                    z[k]=falsz;		//z:=[];
                for (j=1; j<= n; j++)
                    if ((A[i][j]) && (C[j]!= 0))
                        z[C[j]]=prawda;	//z:=z + [C[j]];
                /*kolorowanie wierzcholka "i" najmniejszym kolorem
                nie znajdujacym sie w zbiorze "z" */
                j=1;
                b=falsz;
                while ((j <= n)&& ! b)
                    if (z[j])	//j in z
                        j++;
                    else {
                        C[i]=j;
                        b=prawda;
                    }
            }
        kol(C, d - 1,n ,Deg, A);
    }
} // kol

/*operacja kolorowania wierzcholkow grafu minimalna liczba kolorow,
 Krzysztof Krol, Oct.1995, Inf. */

void kolor(int n, t2 A, t3 Deg, t3 C,int *chi, int *delta)
{
//enum Boolean zbior [nmax];
//type zbior=set of 1..nmax;
    int i,j,s;

    for (i=1; i<= n; i++) {	// ciag stopni wierzcholkow grafu
        s=0;
        for (j=1; j<= n; j++)
            if (A[i][j])
                s++;
        Deg[i]=s;
    } // i
    *delta=Max(n, Deg);        // max stopien
    for (i=1; i<= n; i++)
        C[i]=0; // przygotowanie tablicy kolorow
    kol(C, *delta,n,Deg, A); //kolorowanie poczawszy od wierzcholkow o stopniu delta
    *chi=Max(n, C);           // najwiekszy kolor
} // kolor

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
} //stat

void druk1(int n, float p, int rep)
{
    printf("\nGnp, n= %d, p= %7.4f, rep= %d \n",n,p,rep);
} //druk1

void druk1a(int n, int k, int rep)
{
    printf("\nGnk, n= %3d, k= %d, rep= %5d \n",n,k,rep);
} //druk1a

void drukA(int n, t2 A)
{
    int i,j,h;
    printf("\nKrawedzie:\n");
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

void druk2(int n, int delta, t3 Deg)
{
    int i;
    printf("Deg:   ");
    for(i=1; i<=n; i++)
        printf("%3d",Deg[i]);
    printf("  delta=%d \n",delta);
} //druk2

void druk2a(int n, int chi, t3 C)
{
    int i;
    printf("color:  C:  ");
    for(i=1; i<=n; i++)
        printf("%3d",C[i]);
    printf("  chi= %d\n",chi);
} //druk2a

void drukzbior(int first,int n, zbior z)
{
    int x;
    x=first;
    while(z[x] || x<=n) {
        if (z[x]) {
            printf("%3d,",x);
            z[x]=falsz;
        }
        x++;
    }
} //drukzbior

void druk3(int n, int chi, tD D)
{
    int k;
    printf("monte:  D:  ");
    for(k=1; k<=chi; k++) {
        printf("k=%d :",k);
        drukzbior(1,n,D[k]);
    }
    printf("  chi= %d\n",chi);
} //druk3

clock_t pomiar(void)
{
    clock_t czas;
    czas = clock();
    return czas;
}//pomiar



