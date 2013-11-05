//iso
#ifndef __ISO_H__
#define __ISO_H__

/****************************************************************

iso.h

PLIK NAGLOWKOWY IMPLEMENTACJI ALGORYTMU DO BADANIA IZOMORFIZMU
DWOCH GRAFOW

*****************************************************************/

#define  MaxNodeNo   20

#define  true        1
#define  false       0
#define  MaxEdgeNo   (MaxNodeNo * (MaxNodeNo - 1) / 2)

typedef char boolean;

typedef char TByteRow[MaxNodeNo];

typedef struct _REC_TBoolRecArray {
    boolean Left, Right;
} _REC_TBoolRecArray;

typedef struct _REC_TByteRecArray {
    char Left, Right;
} _REC_TByteRecArray;

typedef _REC_TBoolRecArray TBoolRecArray[MaxNodeNo];
typedef _REC_TByteRecArray TByteRecArray[MaxNodeNo];


typedef boolean TAlTable[MaxNodeNo][MaxNodeNo];


typedef struct TGraph {
    TAlTable A;
    TByteRow Deg, DegSort;
} TGraph;

/* externals */
/*
void ConvertToComplement(TGraph *,
								 TGraph *,
								 int       );
*/
#endif


boolean EqualGraphs(int N, TGraph *G1,TGraph *G2);




/* end of iso.h */
/*Badanie iso.*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdio.h>

#include <stdlib.h>

#include <string.h>
#include "iso.h"



#define TRUE  1
#define FALSE 0

/*****************************************/

void ConvertToComplement(TGraph *G1, TGraph *G2, int N)
{
    int I,J;

    for (I=0; I<N; I++) {
        for (J=I+1; J<N; J++) {
            G1->A[I][J] =!G1->A[I][J];
            G1->A[J][I] = G1->A[I][J];
            G2->A[I][J] =!G2->A[I][J];
            G2->A[J][I] = G2->A[I][J];
        }
        G1->Deg[I]= N-G1->Deg[I]-1;
        G2->Deg[I]= N-G2->Deg[I]-1;
    }
}


boolean EqualNodes(int N, const TGraph Graph1,const TGraph Graph2, int N1, int N2, _REC_TBoolRecArray *Tree, _REC_TByteRecArray *Levels, char Level)
{
    int I,J,K,Up;
    boolean EquLev, Found;
    _REC_TBoolRecArray *LTree;
    _REC_TByteRecArray *WITH;

    LTree=(_REC_TBoolRecArray *)malloc(N*2*sizeof(boolean));

    memmove(LTree,Tree, N*2*sizeof(boolean));
    I=1;
    Found=true;
    while (Found && I<=N) {
        if (Graph1.A[N1-1][I-1] && !LTree[I-1].Left) {
            LTree[I-1].Left=true;
            Levels[Level-1].Left=I;
            Found=false;
            J=1;
            while (!Found && J<=N) {
                if (Graph2.A[N2-1][J-1] && !LTree[J-1].Right)

                {
                    if (Graph1.Deg[I-1]==Graph2.Deg[J-1])

                    {
                        K=1;
                        Up=0;
                        EquLev=true;
                        while (EquLev && K<Level) {
                            WITH=&Levels[K-1];
                            EquLev=(Graph1.A[I-1][WITH->Left-1]==Graph2.A[J-1]
                                    [WITH->Right-1]);
                            if (Graph1.A[I-1][WITH->Left-1])
                                Up++;
                            K++;
                        }
                        if(EquLev) {
                            LTree[J-1].Right=true;
                            Levels[Level-1].Right=J;

                            if (Up==Graph1.Deg[I-1])
                                Found=true;
                            else
                                Found=EqualNodes(N, Graph1, Graph2, I, J, LTree, Levels,
                                                 Level+1);
                            if (!Found)
                                LTree[J-1].Right=false;
                        }
                    }
                }
                J++;
            }

        }
        I++;
    }
    if (Found)

        memmove(Tree, LTree, N*2*sizeof(boolean));

    free(LTree);
    return Found;
}


boolean EqualGraphs(int N, TGraph *G1,TGraph *G2)
{
    boolean Result;
    TBoolRecArray Tree;
    TByteRecArray Levels;
    int I,J,Total,MaxEdge;
    boolean Found;

    Result=false;
    for (I=0; I<N; I++) {
        if (G1->DegSort[I]!=G2->DegSort[I])
            return Result;
    }
    Total=0;
    for (I=0; I<N; I++)
        Total+=G1->Deg[I];
    MaxEdge =N*(N-1) /2;
    if (Total > MaxEdge)
        ConvertToComplement(G1, G2, N);
    memset(Tree, false, N*2*sizeof(boolean));

    I=1;
    Found=true;
    while (Found && I<=N) {
        if (!Tree[I-1].Left) {
            Tree[I-1].Left=true;
            Levels[0].Left=I;
            Found=false;
            J=1;
            while (!Found && J<=N) {
                if (!Tree[J-1].Right) {
                    if (G1->Deg[I-1]==G2->Deg[J-1]) {
                        Tree[J-1].Right=true;
                        Levels[0].Right=J;
                        if (G1->Deg[I-1]==0)
                            Found=true;
                        else
                            Found=EqualNodes(N, *G1, *G2,I,J,Tree,Levels, 2);
                        if (!Found)
                            Tree[J-1].Right=false;
                    }
                }
                J++;
            }
        }
        I++;
    }
    if (Total > MaxEdge)
        ConvertToComplement(G1, G2, N);
    return Found;
}


/***************************************************************************/

/*     end isso      */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/






//program p7, KTB Nov 12,1996
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <conio.h>
# include "iso.h"

# include <limits.h>

#define randomize() srand(unsigned(time(NULL)))
#define random(a) rand()%a
#define Random() (rand()%10000)*0.0001

#define nmax 14
#define kmax nmax *(nmax-1)/2

enum Boolean {falsz=0, prawda=1};


typedef int t[nmax];
typedef struct {
    int a, b;
} r;
typedef r t1[nmax];     // E
typedef char nazwa_pliku[15];


void czyt(int *n, int * k, int *rep);
void init(int n, t1 E, int * total);
void Gnk(int k, int total, t1 E);
void transEGr(int n,int k, int total, t1 E, TGraph *Gr);
void drukE(int k, int total, t1 E);
void sort(int n, TByteRow a);
void jeden (int n, TGraph *Gr);
void complement(int n,TGraph *G1,TGraph *G2);
void drukGr(int n, TGraph *Gr);
void konstr(int n,int k, int rep,FILE *W, int *g);
void przesiewanie(int g, FILE *W,FILE * Z,nazwa_pliku devZ,int *sc,int n);
clock_t pomiar(void);
void kopiuj_strukture(int n,TGraph *Gr2, TGraph *Gr1);
void zapisz_do_pliku(int n,FILE *W, TGraph *Gr);
void odczytaj_z_pliku(int n,FILE *W, TGraph *Gr);


int main ()
{
    int g,i,k,l,n,sc,rep,total,wariant;
    t1 E;
    TGraph G1, G2;
    nazwa_pliku devW;
    FILE *W;     //  wszystkie wygenerowane sc-grafy
    nazwa_pliku devZ;
    FILE *Z;     //  przesiane sc-grafy
    clock_t czas1, czas2;


    randomize();
    do {
        printf("Wariant: (1/2/3/4)");
        scanf("%d",&wariant);
        switch(wariant) {
        case 1: { //czy G1 = Gnk i G2 = dopelnienie G1 sa izomorficzne?
            czyt(&n, &k, &rep);
            init(n, E, &total);
            Gnk(k, total, E);
            transEGr(n, k, total, E, &G1);
            jeden(n, &G1);
            complement(n, &G1, &G2);
            jeden(n, &G2);
            drukE(k, total, E);
            printf("G1:");
            drukGr(n, &G1);
            printf("G2:");
            drukGr(n, &G2);
            if (EqualGraphs(n+1, &G1, &G2))
                printf("G1, G2: izomorficzne\n");
            else
                printf("G1, G2: nieizomorficzne\n");
            break;
        } // 1
        case 2: { // konstr pliku W zawierajacego sc-grafy
            printf("nazwa pliku W:");
            scanf("%s",devW);
            W=fopen(devW,"wt");       //przygotowanie pliku W do zapisu
            czyt(&n, &k, &rep);
            konstr(n, k, rep, W, &g); // plik W o dlugosci g
            printf("n= %d, rep= %d, liczba sc-grafow= %d",n,rep,g);
            break;
        } //2
        case 3: { //konstr pliku W i przesiewanie do pliku Z
            printf("nazwa pliku W:");
            scanf("%s",devW);
            W=fopen(devW,"wb");       //przygotowanie pliku W do zapisu
            czyt(&n, &k, &rep);
            konstr(n, k, rep, W, &g); // plik W o dlugosci g
            printf("n= %d, rep= %d, liczba sc-grafow= %d\n",n,rep,g);
            W=fopen(devW,"rb");
            printf("nazwa pliku Z:");
            scanf("%s",devZ);
            Z=fopen(devZ,"wb");
            przesiewanie(g, W, Z, devZ, &sc,n); // plik Z o dlugosci sc
            printf("cs= %d\n",sc);
            break;
        } //3
        case 4: { //czas Gnk + ISO613
            czyt(&n, &k, &rep);
            init(n, E, &total);
            k=total / 2;
            l=0;
            czas1=pomiar();
            for(i=1; i<=rep; i++) {
                Gnk(k, total, E);
                transEGr(n, k, total, E, &G1);
                jeden(n, &G1);
                Gnk(k, total, E);
                transEGr(n, k, total, E, &G2);
                jeden(n, &G2);
                if (EqualGraphs(n+1, &G1, &G2))
                    l++;
            }
            czas2=pomiar();
            printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLK_TCK);
            printf("Gnk:  n= %d, rep= %d", n,rep);
            printf(", liczba par grafow izomorf.= %d\n",l);
            break;
        } //4
        default: {
            printf("Taki wariant nie istnieje!\n");
        }
        } // switch
        printf("koniec? 0/1\n");
    } while (getch()!='1');

    return 0;
}

void czyt(int *n, int * k, int *rep)
{
    do {
        printf("n, k, rep= ");
        scanf("%d%d%d",n,k,rep);
    } while ((*n > nmax) && (*k > kmax) && (*rep > 100000));
} //czyt

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

void transEGr(int n,int k, int total, t1 E, TGraph *Gr)
{
    int i,j,l;
    for(i=0; i<=n; i++)
        for(j=0; j<=n; j++)
            Gr->A[i][j]=falsz;
    for(l=total; l>=total-k+1; l--) {
        i=E[l].a;
        j=E[l].b;
        Gr->A[i][j]=prawda;
        Gr->A[j][i]=prawda;
    }
} //transEGr

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
    printf("\n");
} //drukE

void sort(int n, TByteRow a)
{
    int i,j,k, naj;
    for(i=1; i<=n-1; i++) {
        naj=a[i];
        k=i;
        for(j=i+1; j<=n; j++)
            if (a[j]>naj) {
                naj=a[j];
                k=j;
            }
        a[k]=a[i];
        a[i]=naj;
    }
} //sort

void jeden (int n, TGraph *Gr)//przygotowanie Deg i DegSort
{
    int i,j,s;
    Gr->Deg[0]=0;
    Gr->DegSort[0]=0;
    for(i=1; i<=n; i++) {
        s=0;
        for(j=1; j<=n; j++)
            if(Gr->A[i][j])
                s++;
        Gr->Deg[i]=s;
        Gr->DegSort[i]=s;
    }
    sort(n,Gr->DegSort);
}//jeden

void complement(int n,TGraph *G1, TGraph *G2)
{
    int i,j;
    kopiuj_strukture(n,G2,G1);
    for (i=1; i<= n - 1; i++)
        for (j=i + 1; j<=  n; j++) {
            G2->A[i][j]=!(G2->A[i][j]);
            G2->A[j][i]=!(G2->A[j][i]);
        }
}// complement

void drukGr(int n, TGraph *Gr)
{
    int i,j,h;
    for(i=1; i<=n; i++) {
        printf("\n");
        for(j=1; j<=n; j++) {
            if (Gr->A[i][j]) h=1;
            else h=0;
            printf("%2d",h);
        }
    } //A
    printf("   Deg:");
    for(i=1; i<=n; i++)
        printf("% d",Gr->Deg[i]);
    printf("   DegSort:");
    for(i=1; i<=n; i++)
        printf("% d",Gr->DegSort[i]);
    printf("\n");
} //drukGr

void konstr(int n,int k, int rep,FILE *W, int *g)
//wynik: plik W o dlugosci g
{
    int i,h,total;
    t1 E;
    TGraph G1,G2;

    init(n, E, &total);               //icjalizacja tablicy E
    i=0;                           // licznik wygenerowanych sc-grafow
    for (h=1; h<=rep; h++) {
        Gnk(k, total, E);           //generacja Gnk
        transEGr(n, k, total, E,& G1);   // transformacja do pola A w G1
        jeden(n, &G1);             // wypelnienie pol Deg i DegSort w G1
        complement(n, &G1, &G2);           //G2.A jest dopelnieniem G1.A
        jeden(n, &G2);              //pola Deg, DegSort w G2
        if (EqualGraphs(n+1, &G1, &G2)) { //sprawdzenie czy G1, G2 sa izomorficzne
            i++;
            zapisz_do_pliku(n,W, &G1) ;
        }
    }
    *g=i;
    fclose(W);
} // konstr

void  przesiewanie(int g, FILE *W,FILE * Z,nazwa_pliku devZ,int *sc,int n)
// dane: plik W o dlugosci g, wyniki: plik Z o dlugosci sc
{
    int i,j,l;
    enum Boolean jest;
    TGraph G1, G2;

    odczytaj_z_pliku(n,W,&G1); // pierwszy graf z W do G1
    zapisz_do_pliku(n,Z, &G1); //przepisanie G1 na plik Z
    fclose(Z);
    j=1;       //aktualna dlugosc pliku Z
    for (i=2; i<= g; i++ ) { // przegladanie pliku W
        odczytaj_z_pliku(n,W,&G1); //kolejny graf z W do G1
        //	Z=fopen(devZ,"r+b");
        Z=fopen(devZ,"rb");
        //porownywanie G1 z kolejnymi G2 z pliku Z
        jest=falsz;
        l=1;
        while ((l <= j)&&  (!jest)) {
            odczytaj_z_pliku(n,Z,&G2);
            if (EqualGraphs(n+1, &G1, &G2))
                jest=prawda;
            else l++;
        }
        if (!jest) { // jesli G1  nie ma w pliku Z, to dopisz
            Z=fopen(devZ,"ab");
            zapisz_do_pliku(n,Z, &G1);
            j++;
            fclose(Z);
        }
        fclose(Z);
    } // i
    *sc=j;          //liczba nieizomorficznych sc grafow w pliku Z
    fclose(W);  //zamkniecie pliku W
// fclose(Z);  //zamkniecie pliku W  */
    *sc=j;
}// przesiewanie

clock_t pomiar(void)
{
    clock_t czas;
    czas = clock();
    return czas;
}//pomiar

void kopiuj_strukture(int n,TGraph *Gr2, TGraph *Gr1)
{
    int i,j;
    for (i=0; i<= n; i++)
        for (j=0; j<= n; j++) {
            Gr2->A[i][j]= Gr1->A[i][j];
            Gr2->A[j][i]= Gr1->A[j][i];
        }
    for(i=0; i<=n; i++)
        Gr2->Deg[i]= Gr1->Deg[i];
    for(i=0; i<=n; i++)
        Gr2->DegSort[i]= Gr1->DegSort[i];
}// kopiuj_strukture

void zapisz_do_pliku(int n,FILE *W, TGraph *Gr)
{
    int i,j;
    for (i=1; i<= n; i++) {
        for (j=1; j<= n; j++)
            fprintf(W, "%d ",Gr->A[i][j]);
    }
    for(i=1; i<=n; i++)
        fprintf(W, "%d ", Gr->Deg[i]);
    for(i=1; i<=n; i++)
        fprintf(W, "%d ", Gr->DegSort[i]);
}//zapisz_do_pliku

void odczytaj_z_pliku(int n,FILE *W, TGraph *Gr)
{
    int i,j,k;
    for (i=1; i<= n; i++) {
        for (j=1; j<= n; j++) {
            fscanf(W, "%d ",&k);
            Gr->A[i][j]=k;
        }
    }
    for(i=1; i<=n; i++) {
        fscanf(W, "%d",&k );
        Gr->Deg[i]=k;
    }
    for(i=1; i<=n; i++) {
        fscanf(W, "%d",&k );
        Gr->DegSort[i]=k;
    }
    for(i=0; i<=n; i++) {
        Gr->A[0][i]=0;
        Gr->A[i][0]=0;
    }
    Gr->Deg[0]=0;
    Gr->DegSort[0]=0;
}//odczytaj_z_pliku



