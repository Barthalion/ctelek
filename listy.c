//program p9, KTB Nov 25,1996
#include<stdio.h>
//#include<alloc.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include "iso.h"
# include <limits.h>

#define randomize() srand(unsigned(time(NULL))) 
#define random(a) rand()%a
#define Random() (rand()%10000)*0.0001

#define nmax 14
#define kmax nmax*(nmax-1)/2

enum Boolean {falsz=0, prawda=1};

typedef struct
        {
        int a, b;
        enum Boolean code;
        }r;
typedef r t1[kmax];     // E - do generacji grafu
typedef int t[nmax];		//c - ciag stopni wierzcholkow
typedef int tQ[nmax];  /*Q-licznik grafow z m wierzcholkami									nienasyconymi (o stopniu <f)*/
typedef struct REF1{
	TGraph G;
	struct REF1 * next;
} ref1;                    // lista grafow



typedef struct REF{
	int a;
	struct REF * next;
} ref;


void czyt2(int *n, int *z);
void push(int x, ref **h);
void konstrlista1(int n,int z, ref **h );
enum Boolean member(int x, ref *h);
void konstrlista2(int n, int z, ref **h, int *l);
void druklista(ref *head);
void sortlista(ref *h);
//------------------------------------------------------------------------------
void czyt(int *n, int *f, int *rep);
void init(int n, t1 E, int *total);
void Gnf(int n, int f, int total, t1 E, t c, int *k);
void transEGr(int n, int total, t1 E, TGraph *Gr);
void drukE(int total, t1 E);
void drukc(int n, t c);
void sort(int n, TByteRow a);
void jeden (int n, TGraph *Gr);
void drukGr(int n, TGraph *Gr);
void push1(TGraph x, ref1 **h,int n);
void konstrflista(int n,int f, int rep, ref1 **h, tQ Q);
void drukQ(int n,int f,int rep,tQ Q);
clock_t pomiar(void);
void kopiuj_strukture(int n,TGraph *Gr2, TGraph *Gr1);

// void usunliste(ref **h); // do zrobienia
// void usunliste1(ref1 **h); // do zrobienia
 

int main ()
{
int f,i,k,l,n,x,rep,total,zakres,wariant;
ref *head=NULL;
ref1 *head1=NULL;
tQ Q;
t1 E;
t c;
clock_t czas1, czas2;

	randomize();
   do
   	{
		printf("Wariant: (1/2/3/4/5/6)");
   	scanf("%d",&wariant);
   	switch(wariant)
   		{
      	case 1:  //konstr listy z dopisywaniem na poczatku
      		{
         	czyt2(&n,&zakres);  //n-dlugosc ciagu, z- zakres  losowania
         	konstrlista1(n,zakres,&head); //budowanie listy z kolejnymi x
         	druklista(head);    //drukowanie zawartosci listy
         	break;
				} // 1
      	case 2: //kontsr listy i sort malejaco
      		{
            czyt2(&n,&zakres);//n-dlugosc ciagu, z- zakres  losowania
            konstrlista1(n,zakres,&head); //budowanie listy z kolejnymi x
            druklista(head);    //drukowanie zawartosci listy
            sortlista(head);    //sortowanie malejaco
            printf("sort \n");
            druklista(head);      //drukowanie zawartosci listy
         	break;
         	} //2
         case 3: //konstr listy i member
      		{
            czyt2(&n,&zakres); //n-dlugosc ciagu, z- zakres  losowania
            konstrlista1(n,zakres,&head); //budowanie listy z kolejnymi x
            druklista(head);   //drukowanie zawartosci listy
            x=random(zakres)+1; //losowanie wartosci x
            printf("czy x=%6d jest na liscie? %d\n",x, member(x,head));
         	break;
         	} //3
         case 4:// konstr listy roznych elementow
      		{
            czyt2(&n,&zakres);//n-dlugosc ciagu, z- zakres  losowania
            konstrlista2(n,zakres, &head, &l); //budowanie listy roznych
            printf("liczba losowan=%d \n", l);
            druklista(head); //drukowanie zawartosci listy
         	break;
         	} //4
         case 5://konstr listy zawierajacej EM f-grafy
      		{
            czyt(&n,&f,&rep);
            konstrflista(n,f,rep,&head1,Q);  //lista head1
            drukQ(n,f,rep,Q);

            break;
         	} //5
         case 6://czas Gnf
      		{
            czyt(&n,&f,&rep);
            init(n,E,&total);
            czas1=pomiar();
             for(i=1;i<=rep;i++)
             Gnf(n,f,total,E,c,&k);
            czas2=pomiar();
            printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLK_TCK);
            break;
         	} //6
          default:
          	{
            printf("Taki wariant nie istnieje!\n");
            }
      	} // switch
   printf("koniec? 0/1\n");
   	}
   while (getch()!='1');

	return 0;
}

void czyt2(int *n, int *z)
{
	printf("n-liczba elementow listy, z-zakres losowan =");
	scanf("%d%d",n,z);
}//czyt2

void push(int x, ref **h)
{
ref *p;
   p=(ref*)malloc(sizeof(ref));
   if(p!=NULL)
   	{
   	p->a=x;
   	p->next=*h;
   	*h=p;
      }
} //push

void konstrlista1(int n,int z, ref **h )
{
int i,x;
	printf("kolejne (losowane) wartosci x:\n");
   *h=NULL;
   for(i=1;i<=n;i++)
   	{
      x=random(z)+1;
      printf("%5d",x);
      if(i%10==0)
          printf("\n");
      push(x,h);
      }
    printf("\n");
} //konstrlista1

/*
void usunliste(ref **h) // do zrobienia 
 {   
 } //usunliste
*/


enum Boolean member(int x, ref *h)
{
enum Boolean jest;
	jest=falsz;
   while((h!=NULL)&& (!jest))
   	if(h->a==x)
      	jest=prawda;
      else h=h->next;
    return jest;
} //member

//konstr listy z roznych elementow, l losowan
void konstrlista2(int n, int z, ref **h, int *l)
{
int i,j,x;
	printf("kolejne (losowane) wartosci x:\n");
   *h=NULL;
   i=0;
   j=0;
   while(j<n)
   	{
      x=random(z)+1;
      printf("%5d",x);
      i++;
      if(i%10==0)
      	printf("\n");
      if (!member(x,*h))
      	{
         push(x,h);
         j++;
         }
		}
   printf("\n");
   *l=i;
}// konstrlista2

void druklista(ref *h)
{
int i;
	printf("lista:\n");
   i=0;
   while(h!=NULL)
   	{
      printf("%5d",h->a);
      i++;
      if(i%10==0)
      	printf("\n");
      h=h->next;
      }
   printf("\n");
}//druklista

void sortlista(ref *h)//z zamiana informacji
{
ref *p,*r;
int naj;
	while(h!=NULL)
   	{
      naj=h->a;
      r=h;
      p=h->next;
      while(p!=NULL)
      	{
         if(p->a > naj)
         	{
            naj=p->a;
            r=p;
            }
         p=p->next;
         }
      if(r!=h)
      	{
         r->a=h->a;
         h->a=naj;
         }
      h=h->next;
      }
}//sortlista

//-----czesc druga, lista grafow, warianty 5,6

void czyt(int *n, int *f, int *rep)
{
printf("n, f, rep= ");
scanf("%d%d%d", n, f, rep);
}// czyt

void init(int n, t1 E, int *total)
{
int i,j,h;
	h=0;
   for(i=1;i<=n-1;i++)
   	for(j=i+1;j<=n;j++)
      	{
         h++;
         E[h].a=i;
         E[h].b=j;
         }
   *total=h;
} // init

void Gnf(int n, int f, int total, t1 E, t c, int *k) //EM f-graf
{
int i,h,l,z;
r x;
	for(i=1;i<=n;i++)
   	c[i]=0;
   for(i=1;i<=total;i++)
   	E[i].code=falsz;
   h=0;
   for(l=total;l>=1;l--)
		{
      z=random(l)+1;
      if((c[E[z].a]<f)&&(c[E[z].b]<f))
      	{
         E[z].code=prawda;
         h++;
         c[E[z].a]++;
         c[E[z].b]++;
         }
      x=E[z];
      E[z]=E[l];
      E[l]=x;
      }
   *k=h;
} //Gnf

void transEGr(int n, int total, t1 E, TGraph *Gr) //dla Gnf
{
int i,j,l;
enum Boolean x;
    for(i=1;i<=n;i++)
        Gr->A[i][i]=falsz;
    for(l=total; l>=1;l--)
        {
        i=E[l].a;
        j=E[l].b;
        x=E[l].code;
        Gr->A[i][j]=x;
        Gr->A[j][i]=x;
        }

} //transEGr

void drukE(int total, t1 E)  // dla Gnf
{
int h,l;
    printf("\nKrawedzie z E:\n");
    h=0;
    for(l=total;l>=1;l--)
        {
        if (E[l].code)
            {
            h++;
            printf("%4d%2d",E[l].a,E[l].b);
            if(h%10==0)
                printf("\n");
            }
        }
    printf("\n");
} //drukE

void drukc(int n, t c)
{
int i;
    printf("  c:");
    for(i=1;i<=n;i++)
        printf("%3d",c[i]);
    printf("\n");
} //drukc

void sort(int n, TByteRow a)
{
int i,j,k, naj;
	for(i=1;i<=n-1;i++)
      {
      naj=a[i];
      k=i;
      for(j=i+1;j<=n;j++)
         if (a[j]>naj)
         	{
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
    for(i=1;i<=n;i++)
        {
        s=0;
        for(j=1;j<=n;j++)
            if(Gr->A[i][j])
                s++;
        Gr->Deg[i]=s;
        Gr->DegSort[i]=s;
        }
    sort(n,Gr->DegSort);
}//jeden

void drukGr(int n, TGraph *Gr)
{
int i,j,h;
    for(i=1;i<=n;i++)
        {
        printf("\n");
        for(j=1;j<=n;j++)
            {
            if (Gr->A[i][j])
                h=1;
            else h=0;
            printf("%2d",h);
            }
        } //A
    printf("   Deg:");
    for(i=1;i<=n;i++)
        printf("% d",Gr->Deg[i]);
    printf("   DegSort:");
    for(i=1;i<=n;i++)
        printf("% d",Gr->DegSort[i]);
    printf("\n");
} //drukGr

void push1(TGraph x, ref1 **h,int n)
{
ref1 *p;
   p=(ref1*)malloc(sizeof(ref1));
   if(p!=NULL)
   	{
   	kopiuj_strukture(n,&p->G,&x);
   	p->next=*h;
   	*h=p;
      }
}  //push1

void konstrflista(int n,int f, int rep, ref1 **h, tQ Q)
//wynik lista h o dlugosci rep
{
int i,j,k,m,total;
t c;
t1 E;
TGraph G1;
    for(m=0;m<=f;m++)//przygotowanie Q licznika grafow z m wierzcholkami
        Q[m]=0;       //nienasyconymi
    *h=NULL;        //przygotowanie h
    init(n,E,&total); //inicjalizacja tablicy E
    for(i=1;i<=rep;i++)
        {
        Gnf(n,f,total,E,c,&k);  //generacja Gnf
        m=0;                  //m- liczba wierzcholkow nienasyconych
        for(j=1;j<=n;j++)
            if(c[j]<f)
                m++;
        Q[m]++;  //aktualizacja Q
        transEGr(n,total,E,&G1);//transformacja do pola A w G1
        jeden(n,&G1); //wypelnienie pol Deg i DegSort w G1
        push1(G1,h,n); //G1 na poczatek listy
        }
}//konstrflista

/* 
void usunliste1(ref1 **h) // do zrobienia 
 {
 } //usunliste1 
*/


void drukQ(int n,int f,int rep,tQ Q)
{
int m;
    printf("\nn= %d, f= %d, rep=% d\n",n,f,rep);
    printf("Q-liczba grafow z m wierzcholkami nienasyconymi:\n");
    printf("m= ");
    for(m=0;m<=f;m++)
        printf("%7d",m);
    printf("\n");
    for(m=0;m<=f+1;m++)
        printf("-------");
    printf("\n");
    printf("Q= ");
    for(m=0;m<=f;m++)
        printf("%7d",Q[m]);
    printf("\n");
}//drukQ

clock_t pomiar(void)
{
clock_t czas;
    czas = clock();
    return czas;
}//pomiar

void kopiuj_strukture(int n,TGraph *Gr2, TGraph *Gr1)
{
int i,j;
    for (i=0;i<= n;i++)
      for (j=0;j<= n;j++)
        {
        Gr2->A[i][j]= Gr1->A[i][j];
        Gr2->A[j][i]= Gr1->A[j][i];
        }
    for(i=0;i<=n;i++)
        Gr2->Deg[i]= Gr1->Deg[i];
    for(i=0;i<=n;i++)
        Gr2->DegSort[i]= Gr1->DegSort[i];
}// kopiuj_strukture





