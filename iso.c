/*Badanie iso.*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define  true 1
#define  false 0
#define  MAX_INT 32765

#define  MaxNodeNo       100
#define  NMAX            MaxNodeNo
#define  MaxEdgeNo       (MaxNodeNo * (MaxNodeNo - 1) / 2)

typedef int boolean;

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

/*****************************************/

  /*Elementy wykorzystane w main()*/
  int n;
  TGraph G1, G2;
  boolean pom;
  TAlTable AB;

#define TRUE  1
#define FALSE 0

/*****************************************/

void ConvertToComplement(TGraph *G1, TGraph *G2, int N)
{
  int I,J;

  for (I=0; I<N; I++)
  {
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


static boolean EqualNodes(int N, const TGraph Graph1,const TGraph Graph2, int N1, int N2, _REC_TBoolRecArray *Tree, _REC_TByteRecArray *Levels, char Level)
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
    if (Graph1.A[N1-1][I-1] && !LTree[I-1].Left)
	{
      LTree[I-1].Left=true;
      Levels[Level-1].Left=I;
      Found=false;
      J=1;
      while (!Found && J<=N)
      {
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
	    if(EquLev)
	    {
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


static boolean EqualGraphs(int N, TGraph *G1,TGraph *G2)
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
	  if (G1->Deg[I-1]==G2->Deg[J-1])
	      {
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
void DegSrt(int n, char *DegS)
{
  int i,j,k,naj,x;

  for (i=1;i<n;i++) {
    naj=DegS[i-1];
    k=i;
    for (j= i+1; j<=n;j++) {
      if (DegS[j-1]>naj) {
	naj=DegS[j-1];
	k=j;
      }
    }
    x=DegS[k-1];
    DegS[k-1]=DegS[i-1];
    DegS[i-1]=x;
  }
}  /*sort*/



void InitDeg(char *Deg)
{
  int i;

  for (i=0; i<MaxNodeNo; i++)
    Deg[i]= 0;
}  /*InitDeg*/


void GenDeg(int n, boolean (*A)[MaxNodeNo], char *Deg)
{
  int i,j;

  InitDeg( Deg);
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      if (A[i][j]==true)
	Deg[i]++;
    }
  }
}  /*GenDeg*/


void DrukA(int n1, boolean (*A1)[MaxNodeNo])
{
  int i, j;

  putchar('\n');
  for (i=0; i<n1; i++) {
    for (j=0; j<n1; j++) {
      if (A1[i][j]==true)
	printf("1 ");
      else
	printf("0 ");
    }
    putchar('\n');
  }
  putchar('\n');
}  /*DrukA*/



void  CzytajGraf(int K,int A[NMAX][NMAX])
{int i,j,m;
  for (i=0;i<NMAX;i++) 
    for (j=0;j<NMAX;j++) 
     A[i][j]=0;

   for (i=0;i<K;i++) 
   {
     scanf("%d%d",&j,&m);
     A[j-1][m-1]=1;
     A[m-1][j-1]=1;
   }
}

void InitGrafik(int n,int k, TGraph *Gn)
{
  TAlTable AA;
  TByteRow Degg;

  CzytajGraf(k,AA);
  memcpy(Gn->A, AA, sizeof(TAlTable));

  GenDeg(n, AA, Degg);
  memcpy(Gn->Deg, Degg, sizeof(TByteRow));

  DegSrt(n, Degg);
  memcpy(Gn->DegSort, Degg, sizeof(TByteRow));
}  /*GenDeg*/
/**************************************************************************/

void main(void)
{
  int p1,z,w=0;
  int i,N,K,Lg,Nr,NrF; 
/*Lg 720*/

 scanf("%d%d%d",&N,&K,&Lg);
  
 

  scanf("%d",&NrF);
 
 InitGrafik(N,K,&G1);

  for (i=1;i<Lg;i++)
  {
    scanf("%d",&Nr);
    
    InitGrafik(N,K,&G2);

for( z=0;z<10000;z++)
    {p1=EqualGraphs(N,&G1,&G2);
     if(p1) w++; }

/*   printf("%4d%4d%2c",NrF,Nr,'T');}
   else printf("%4d%4d%2c",NrF,Nr,'N');
*/
    printf("%d",w);
  }

 
}
