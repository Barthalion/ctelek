//program p10, KTB Dec 3, 1996
#include<stdio.h>
//#include<alloc.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
# include <limits.h>

#define randomize() srand(unsigned(time(NULL))) 
#define random(a) rand()%a
#define Random() (rand()%10000)*0.0001
# define nmax 14
# define kmax nmax*(nmax-1)/2

typedef struct REF{
	int a;
	struct REF * next;
} ref;                        // lista liczb
enum Boolean {falsz=0, prawda=1};

typedef struct
        {
        int a, b;
        enum Boolean code;
        }r;
typedef r t1[kmax];     // E - do generacji grafu
typedef int t[nmax];		//c - ciag stopni wierzcholkow
typedef int tQ[nmax];  /*Q-licznik grafow z m wierzcholkami
									nienasyconymi (o stopniu <f)*/
typedef struct REFK{
	int a,b;
	struct REFK * next;
} refk;                    // lista krawedzi


void czyt2(int *n, int *z);
void push(int x, ref **h);
void pop(ref **h, int *x);
void into(int x,ref **h,ref **s);
void intokonstr1(int n,int z, ref **h,ref **s);
enum Boolean member(int x, ref *h);
void intokonstr2(int n, int z, ref **h, ref **s,int *l);
void druklista(ref *head);
void sortlista(ref *h);
void insert(int x, ref **h);
void Delete(int x, ref **h);
enum Boolean rekmember(int x, ref *h);
void przepisz(ref *h,ref **g);
//----------czesc druga, lista krawedzi grafu Gnf-------------------------------
void czyt(int *n, int *f);
void init(int n, t1 E, int *total);
void Gnf(int n, int f, int total, t1 E, t c, int *k);
void drukE(int total, t1 E);
void pushk(int x, int y, refk **h);
void intok(int x, int y,refk **h,refk **s);
void konstr(int total,t1 E, refk **h );
void konstr1(int total,t1 E, refk **h );
void druklistak(refk *h);
clock_t pomiar(void);


int main ()
{
int f,k,l,n,x,total,zakres,wariant;
ref *head=NULL, *sent=NULL, *nowa=NULL;
enum Boolean boo;
t1 E;
t c;
refk *headk;
clock_t czas1, czas2;



	randomize();
    do
   	{
		printf("Wariant: (1/2/3/4/5/6)");
   	    scanf("%d",&wariant);
   	    switch(wariant)
     		 	{
      	    case 1: //konstr listy z dopisywaniem na koncu
             	{
               czyt2(&n,&zakres);//n-dlugosc ciagu, z-zakres
               intokonstr1(n,zakres,&head,&sent); //budowa listy z kolejnymi x
               druklista(head);// drukowanie zawartosci listy
               break;
            	} // 1
      	    case 2: //konstr listy i sort malejaco
      		    {
                czyt2(&n,&zakres);//n-dlugosc ciagu, z-zakres
                intokonstr1(n,zakres,&head,&sent);//budowanie listy z kolejnymi x
                druklista(head); //drukowanie listy
                sortlista(head);  //sortowanie malejaco
                printf("sort:");
                druklista(head);  //drukowanie listy
                printf("nowa lista:");
                przepisz(head, &nowa);  //wykorzystanie insert
                druklista(head);
         	    break;
         	    } //2
        case 3: //konstr listy i member
      		{
            czyt2(&n,&zakres); //n-dlugosc ciagu, z-zakres
            intokonstr1(n,zakres,&head,&sent);//bud. listy z kolejnymi x
            druklista(head); // druk listy
            x=random(zakres)+1; //losowanie wartosci x
            printf("czy x= %6d jest na liscie? -%d\n",x, member(x,head));
            boo=rekmember(x,head);
            printf("czy x= %6d jest na liscie (alg.rek)? -%d\n",x, boo);
           	if(boo)
                Delete(x,&head);
            druklista(head);
         	break;
         	} //3
      	case 4: //konstr listy n roznych elementow
      		{
            czyt2(&n,&zakres);  //n-dlugosc ciagu, z-zakres
            intokonstr2(n,zakres,&head,&sent,&l);//lista roznych elementow
            printf("liczba losowan = %d",l);
            druklista(head);  //drukowanie listy
				break;
         	} //4
      	case 5: //konstr listy krawedzi grafu Gnf
      		{
            czyt(&n,&f);
            init(n,E,&total);
            Gnf(n,f,total,E,c,&k); //EM f-graph
            drukE(total,E);
            konstr(total,E, &headk);  // lista headk
            printf("\nZ dopisywaniem na poczatku listy:\n");
            druklistak(headk);
           	konstr1(total,E, &headk);
           	printf("\nZ dopisywaniem na koncu listy:\n");
            druklistak(headk);
         	break;
         	} //5
      	case 6: //pomiar czasu wykonania operacji w funkcji rozmiaru zadania
      		{
            czas1=pomiar();
             /*zadanie domowe, porownac czas wykonania tej samej operacji,
             np. sortowania listy, wg roznych algorytmow */

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
} //czyt2

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
}  //push

void pop(ref **h, int *x)
{
ref *p;
	if(*h!=NULL)
   	{
      *x=(*h)->a;
      p=*h;
      *h=(*h)->next;
      p->next=NULL;
      free(p);
      }
}  //pop

void into(int x,ref **h,ref **s)
{
ref *p;

   p=(ref*)malloc(sizeof(ref));
   if(p!=NULL)
   	{
   	p->a=x;
   	p->next=NULL;
    }
   if (*h!=NULL)
    {
    (*s)->next=p;
    }
   else *h=p;
   *s=p;
} //into

void intokonstr1(int n,int z, ref **h,ref **s)   //dopisywanie na koncu
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
      into(x,h,s);
      }
    printf("\n");
} //intokonstr1

enum Boolean member(int x, ref *h)
{
enum Boolean jest;
	jest=falsz;
   while((h!=NULL)&& (!jest))
   	if(h->a==x)
      	jest=prawda;
      else h=h->next;
    return jest;
}//member

//konstrukcja listy roznych elementow z dopisywaniem na koncu
void intokonstr2(int n, int z, ref **h, ref **s, int *l)//l - licznik losowan
{
int i,j,x;
	printf("kolejne (losowane) wartosci x:\n");
   *h=NULL;
   i=0;    //licznik losowan
   j=0;    //licznik elementow listy
   while(j<n)
   	{
      x=random(z)+1;
      printf("%5d",x);
      i++;
      if(i%10==0)
      	printf("\n");
      if (!member(x,*h))
      	{
         into(x,h,s);
         j++;
         }
		}
   printf("\n");
   *l=i;
}  // intokonstr2

void druklista(ref *h)
{
int i;
	printf("\nlista:\n");
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
}  //druklista

void sortlista(ref *h) // z zamiana informacji
{
ref *p,*r;
int naj;
	while(h!=NULL)
   	{
      naj=h->a;     // malejaco
      r=h;
      p=h->next;    //porownuj od nastepnego do konca listy
      while(p!=NULL)
      	{
         if(p->a > naj)
         	{
            naj=p->a;
            r=p;
            }
         p=p->next;
         }
      if(r!=h)      // zamiana
      	{
         r->a=h->a;
         h->a=naj;
         }
      h=h->next;  //skroc nieposortowana czesc listy
      }
} //sortlista

//-----------trzy algorytmy rekurencyjne----------------------------------------
void insert(int x, ref **h)  //do listy posortowanej rosnaco
{
    if(*h==NULL)
        push(x,h);
    else
        if(x<(*h)->a)
            push(x,h);
        else
            insert(x,&(*h)->next);
}

void Delete(int x, ref **h)  //usun x
{
	if(h!=NULL)
   	if(x==(*h)->a)
      	pop(h,&x);
      else
      	Delete(x, &(*h)->next);
} //Delete

enum Boolean rekmember(int x, ref *h)   //rekurencyjny member
{
	if(h==NULL)
   	return falsz;
   else
   	if(x==h->a)
      	return prawda;
      else
      	return rekmember(x,h->next);

} //rekmember

void przepisz(ref *h,ref **g)
{
    *g=NULL;
    while(h!=NULL)
        {
        insert(h->a,g);
        h=h->next;
        }
}// przepisz

//----------czesc druga, lista krawedzi grafu Gnf---

void czyt(int *n, int *f)
{
printf("n, f= ");
scanf("%d%d", n,f);
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

void drukE(int total, t1 E)  // dla Gnf
{
int h,l;
    printf("\nKrawedzie z E w porzadku chronologicznym (od total do 1):\n");
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

// dopisywanie krawedzi na poczatku listy
void pushk(int x, int y, refk **h)
{
refk *p;
	p=(refk*)malloc(sizeof(refk));
   if(p!=NULL)
   	{
   	p->a=x;
      p->b=y;
   	p->next=*h;
   	*h=p;
      }
} //pushk

// dopisywanie krawedzi na koncu listy
void intok(int x, int y,refk **s,refk **h)
{
refk *p;

   p=(refk*)malloc(sizeof(refk));
   if(p!=NULL)
   	{
   	p->a=x;
      p->b=y;
		p->next=NULL;
    	}
   if (*h!=NULL)
    {
    (*s)->next=p;
    }
   else *h=p;
   *s=p;
} //intok

void konstr(int total,t1 E, refk **h )
{
int i;
   *h=NULL;
   for(i=total;i>=1;i--)
      if(E[i].code)
			pushk(E[i].a,E[i].b,h);
} // konstr

void konstr1(int total,t1 E, refk **h )
{
int i;
refk *s;
   *h=NULL;
   for(i=total;i>=1;i--)
      if(E[i].code)
			intok(E[i].a,E[i].b,&s,h);
} // konstr1

void druklistak(refk *h)
{
int i;
   i=0; //licznik wydrukowanych elementow listy
   while(h!=NULL)
   	{
      printf("%4d%2d",h->a,h->b);
      i++;
      if(i%10==0)
      	printf("\n");
      h=h->next;
      }
   printf("\n");
}  //druklistak

clock_t pomiar(void)
{
clock_t czas;
    czas = clock();
    return czas;
}//pomiar


