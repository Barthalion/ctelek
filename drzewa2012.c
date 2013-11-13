// program p12 KTB Dec 17, 1996,  KTZ 2013

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
//#include <alloc.h>
#include <time.h>
#include <conio.h>
# include <limits.h>

#define randomize() srand(unsigned(time(NULL)))
#define random(a) rand()%a
#define Random() (rand()%10000)*0.0001

typedef struct REF{
int a;
struct REF * left;
    struct REF * right;
} ref;                    // drzewo BST

typedef struct REF1{
int a;
struct REF1 * next;
} ref1;                        // lista

typedef struct REF2{
    char a;
struct REF2 * left;
    struct REF2 * right;
} ref2;                    // drzewo Wirtha

enum Boolean {falsz=0, prawda=1};


void czyt1(int *n);
void czyt2(int *n, int *z);
void czyt3(int *n, int *z, int *rep);
void push(int x, ref1 **h);
void konstrlista(int n,int z, ref1 **h );
void druklista(ref1 *h);
void insert(int x,ref **t);
void konstr(int n, ref ** t);
void konstr1(int n,int z, ref ** t);
void konstr1a(int n,int z, ref ** t);
void konstr2(ref1 *h, ref ** t);
void memberiter(int x, ref *h,enum Boolean *jest);
void member(int x, ref *t,enum Boolean *jest);
void maxiter(ref *t, int *m);
void Max(ref *t, int *m);
void preorder(ref *t);
void inorder(ref *t);
void inorder1(ref *t);
void postorder(ref *t);
void druk1(ref *t);
void druk2(ref *t);
void druk3(ref *t);
void druk4(ref *t, int h);
void enter(ref2 **t);
void zwolnij(ref1 **h);
//void zwolnijBST(ref2 **t);
clock_t pomiar(void);


int _tmain(int argc, _TCHAR* argv[])
{
int i,M,n,x,rep,zakres,wariant;
ref *BST = NULL;
enum Boolean jest;
ref1 *head;
clock_t czas1, czas2;

    randomize();
    do
  {
printf("Wariant: (1/2/3/4/5/6/7/8/9)");
      scanf_s("%d",&wariant);
      switch(wariant)
  {
            case 1: //konstr z danych wprowadzonych z konsoli,
                    //druk i odwiedzanie drzewa BST
                {
                czyt1(&n); //n- dlugosc ciagu danych
                konstr(n,&BST); //konstr
                printf("druk BST w preorder:  ");
                druk1(BST); //drukowanie BST w preorder
                printf("\ndruk BST w inorder:  ");
                druk2(BST);  //drukowanie BSt w inorder
                printf("\ndruk BST w postorder:  ");
                druk3(BST);  //drukowanie BST w postorder
                printf("\ndruk wg Wirtha:  \n");
                druk4(BST,0);
                printf("trzy porzadki : \n");
                printf(" preorder:  ");
                preorder(BST);
                printf("\n");
                printf(" inorder:  ");
                inorder(BST);
                printf("\n");
                printf(" postorder: ");
                postorder(BST);
                printf("\n");
                Max(BST,&M);
                printf("max= %d rekurencyjnie\n",M);
                maxiter(BST,&M);
                printf("max= %d iteracyjnie\n",M);
                printf("x= ");
                scanf_s("%d",&x);
                member(x,BST, &jest);
                printf("x= %d jest w drzewie: %d (rek)\n",x,jest);
                memberiter(x,BST,&jest);
                printf("x= %d jest w drzewie: %d (iter)\n",x,jest);
                // zwolnijBST(&BST);
              break;
            } // 1
            case 2:  //konstr z listy, druk i odwiedzanie drzewa BST
            {
                czyt2(&n, &zakres); //dlugosc ciagu danych i zakres losowania
                konstrlista(n,zakres,&head);
                druklista(head);
                konstr2(head,&BST); //konstr BST z listy
                printf("druk BST w preorder:  ");
                druk1(BST); //drukowanie BST w preorder
                printf("\ndruk BST w inorder:  ");
                druk2(BST);  //drukowanie BST w inorder
                printf("\ndruk wg Wirtha:  \n");
                printf("\ndruk BST w postorder:  ");
                druk3(BST);  //drukowanie BST w postorder
                druk4(BST,0);
                printf("trzy porzadki : \n");
                printf(" preorder:  ");
                preorder(BST);
                printf("\n");
                printf(" inorder:  ");
                inorder(BST);
                printf("\n");
                printf(" postorder: ");
                postorder(BST);
                printf("\n");
                Max(BST,&M);
                printf("max= %d \n",M);
                // zwolnijBST(&BST);
                break;
                } //2
        case 3: //losowe BST
      {
                czyt2(&n, &zakres); //dlugosc ciagu danych i zakres losowania
                printf("kolejno losowane wartosci x:");
                konstr1(n,zakres,&BST); //losowe BST
                printf("druk BST w preorder:  \n");
                druk1(BST); //drukowanie BST w preorder
                printf("\ndruk BST w inorder:  ");
                druk2(BST);  //drukowanie BST w inorder
                printf("\ndruk BST w postorder:  ");
                druk3(BST);  //drukowanie BST w postorder
                printf("\ndruk wg Wirtha:  \n");
                druk4(BST,0);
                printf("trzy porzadki : \n");
                printf(" preorder:  ");
                preorder(BST);
                printf("\n");
                printf(" inorder:  ");
                inorder(BST);
                printf("\n");
                printf(" postorder: ");
                postorder(BST);
                printf("\n");
                Max(BST,&M);
                printf("max= %d \n",M);
                // zwolnijBST(&BST);
                break;
        } //3
      case 4:  //jak wariant drugi ale konstr BST z dowolnego pliku
      {
                czyt2(&n,&zakres);
                //dopisac kod
                druk4(BST,0);
              break;
        } //4
      case 5: //jak wariant 4 ale konstr BST z elementow tablicy
      {
                czyt2(&n, &zakres);
                //dopisac kod
                druk4(BST,0);
                // zwolnijBST(&BST);
              break;
        } //5
            case 6:
      {
                czyt3(&n, &zakres,&rep);//dlugosc ciagu,zakres,rozmiar proby
                czas1=pomiar();
                for(i=1;i<=rep;i++)
                    {
                    konstr1a(n,zakres,&BST); //losowanie BST
                    inorder1(BST); //inorder bez drukowania
                    //dopisac zwalnianie pamieci
                    // zwolnijBST(&BST);
                    }
                czas2=pomiar();
                printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLK_TCK);
              break;
        } //6
            case 7:
      {
                //dopisac obsluge usuwania wierzcholkow z BST
                //czyli algorytm delete z ksiazki N. Wirtha, zadanie samodzielne
              break;
        } //7
            case 8:
      {
                //wykonac generacje i odwiedzanie drzewa Wirtha, zadanie domowe
              break;
        } //8
          case 9:
      {
                /*zaprojektowac algorytm generacji losowego drzewa Wirtha,
                zadanie domowe  */
              break;
        } //9
              default:
            {
            printf("Taki wariant nie istnieje!\n");
            }
      } // switch
  printf("koniec? 0/1\n");
  }
  while (_getch()!='1');

return 0;
}


void czyt1(int *n) //n- dlugosc ciagu
{
printf("n=  ");
  scanf_s("%d",n);
} //czyt1

void czyt2(int *n, int *z)
{
    printf("n,z =  ");
    scanf_s("%d%d",n,z);
} //czyt2

void czyt3(int *n, int *z, int *rep)
{
    printf("n,z,rep =  ");
    scanf_s("%d%d%d",n,z,rep);
} //czyt3

void push(int x, ref1 **h)
{
  ref1 *p;
  p=(ref1*)malloc(sizeof(ref1));
  if(p!=NULL)
  {
    p->a=x;
    p->next=*h;
    *h=p;
    }
}//push

void konstrlista(int n, int z, ref1 **h)
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
} //konstrlista

void druklista(ref1 *h)
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
} //druklista

void insert(int x, ref **t)
{
  if(*t==NULL)
  {
        *t=(ref*)malloc(sizeof(ref));
        if(t!=NULL)
          {
          (*t)->a=x;
            (*t)->left=NULL;
            (*t)->right=NULL;
            }
      //else;
  }
  else
        if(x!=(*t)->a)
            if(x<(*t)->a) insert(x,&(*t)->left);
            else insert(x,&(*t)->right);

}//insert

void konstr(int n, ref ** t)// BST
{
    int i,x;
    *t=NULL;
    printf("%d liczb calkowitych: ",n);
    for(i=1;i<=n;i++)
        {
        scanf_s("%d",&x);
        insert(x,t);
        }
}  //konstr

void konstr1(int n, int z, ref ** t)// losowe BST na n wierzcholkach
{
  int i,x;
    *t=NULL;
    for(i=1;i<=n;i++)
        {
        x=random(z)+1;
        printf("%d ",x);
        if(i % 10==0) printf("\n");
        insert(x,t);
        }
}  //konstr1

void konstr1a(int n,int z, ref ** t)// konstr1 bez drukowania x
{
  int i,x;
    *t=NULL;
    for(i=1;i<=n;i++)
        {
          x=random(z)+1;
          insert(x,t);
        }
}  //konstr1a

void konstr2(ref1 *h, ref ** t)// BST z listy liczb calkowitych
{
    *t=NULL;
        while(h!=NULL)
        {
          insert(h->a,t);
          h=h->next;
        }
}  //konstr2

void memberiter(int x, ref *t,enum Boolean *jest)
{
  *jest=falsz;
  while((t!=NULL)&& (!(*jest)))
  if(x==t->a) *jest=prawda;
      else
            if (x<t->a) t=t->left;
            else t=t->right;
} //memberiter

void member(int x, ref *t,enum Boolean *jest)  //rekurencyjnie
{
    *jest=falsz;
    if(t!=NULL)
      if(x==t->a) *jest=prawda;
        else
            if (x<t->a) member(x,t->left, jest);
            else member(x,t->right, jest);
} //member

void maxiter(ref *t, int *m)//max element w BST, iteracyjnie
{
    if (t==NULL) *m=-1; else
    {
      while(t->right!=NULL) t=t->right;
      *m=t->a;
    }
} //maxiter

void Max(ref *t, int *m)//max element w BST, rekurencyjnie
{
    if (t==NULL) *m=-1; else
    { 
    if(t->right==NULL) *m=t->a;
    else Max(t->right,m);
    }
} //Max

void preorder(ref *t)
{
    if(t!=NULL)
        {
        printf("%d ",t->a);
        preorder(t->left);
        preorder(t->right);
        }
}  //preorder

void inorder(ref *t)
{
    if(t!=NULL)
        {
        inorder(t->left);
        printf("%d ",t->a);
        inorder(t->right);
        }
} //inorder

void inorder1(ref *t)  //bez drukowania do pomiaru czasu
{
    if(t!=NULL)
        {
        inorder(t->left);
//        printf("%d ",t->a);
        inorder(t->right);
        }
} //inorder1

void postorder(ref *t)
{
    if(t!=NULL)
        {
        postorder(t->left);
        postorder(t->right);
        printf("%d ",t->a);
        }
} //postorder

void druk1(ref *t) //w preorder
{
    if(t!=NULL)
        {
        printf(" %d ",t->a);
        printf("[");
        druk1(t->left);
        printf(";");
        druk1(t->right);
        printf("]");
        }
} //druk1

void druk2(ref *t) //inorder
{
    if(t!=NULL)
        {
        printf("(");
        druk2(t->left);
        printf(" %d ",t->a);
        druk2(t->right);
        printf(")");
        }
    else
        printf("*");
}  //druk2


void druk3(ref *t) //w postorder
{
    if(t!=NULL)
        {
        printf("[");
        druk3(t->left);
        printf(";");
        druk3(t->right);
        printf("]");
        printf(" %d ",t->a);
        }
} //druk3

void druk4(ref *t, int h)// N. Wirth, h- wciecie
{
  int i;
    if(t!=NULL)
        {
        druk4(t->right, h+3);
        for(i=1;i<=h;i++) printf(" ");
        printf(" %d \n",t->a);
        druk4(t->left,h+3);
        }
} //druk4

void enter(ref2 **t)//drzewo Wirtha, elementy sa znakami
{
  char x;
    scanf_s("%c",&x,1);
    if(x!='*')
        {
        *t=(ref2*)malloc(sizeof(ref2));
        (*t)->a=x;
        enter(&(*t)->left);
        enter(&(*t)->right);
        }
    else *t=NULL;
} //enter

void zwolnij(ref1 **h) //zwalnianie pamieci zajetej przez liste
{
ref1 *p;
while((*h)!=NULL)
  {
      p=*h;
      *h=(*h)->next;
      p->next=NULL;
      free(p);
      }
} //zwolnij

clock_t pomiar(void)
{
    clock_t czas;
    czas = clock();
    return czas;
} //pomiar
