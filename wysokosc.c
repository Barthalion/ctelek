//program p13, KTB Dec 18, 1996
#include <stdio.h>
#include <stdlib.h>
//#include <alloc.h>
#include <time.h>
#include <conio.h>
# include <limits.h>

#define randomize() srand(unsigned(time(NULL)))
#define random(a) rand()%a
#define Random() (rand()%10000)*0.0001

typedef struct REF {
    int a;
    struct REF * left;
    struct REF * right;
} ref;                     // drzewo BST, DDW
enum Boolean {falsz=0, prawda=1};

void czyt1(int *n);
void czyt2(int *n,int * z);
void czyt3(int* n,int * z,int* rep);
void insert(int x,ref **t);
void konstr1(int n,int z, ref ** t);
void konstr1a(int n,int z, ref ** t);
ref* DDW(int n);
ref* DDW1(int n,int z);
int wiekszy(int a, int b);
int height(ref *t);
int height1(ref *t);
enum Boolean izo(ref *t1,ref *t2);
void member(int x, ref *t,enum Boolean *jest);
void szukaj(ref *t,int *m);
int Max(ref *t);
void zwolnij(ref **t);
void druk3(ref *t, int h);
clock_t pomiar(void);



int main ()
{
    int i,l,n, rep,zakres,w1,w2, wariant,x;
    ref *BST, *BST1,* BST2, *root;
    enum Boolean jest;
    clock_t czas1, czas2;

    randomize();
    do {
        printf("Wariant: (1/2/3/4/5/6/7/8)");
        scanf("%d",&wariant);
        switch(wariant) {
        case 1: { //   losowe BST, obliczanie wysokosci
            czyt2(&n, &zakres);  //dlugosc ciagu danych i zakres losowania
            printf("kolejno losowane wartosci x: ");
            konstr1(n, zakres, &BST);   // losowanie BST
            printf("\ndruk wg Wirtha:  \n");
            druk3(BST, 0);    // druk wg Wirtha }
            printf("dwa obliczenia wysokosci:");
            printf("  height= %d",height(BST) - 1);
            printf("  height1= %d\n",height1(BST) - 1);
            break;
        } // 1
        case 2: { //losowe BST, izomorfizm
            czyt2(&n, &zakres);  // dlugosc ciagu danych i zakres losowania
            konstr1a(n, zakres, &BST1);   // pierwsze losowane BST
            printf("\ndruk wg Wirtha:  \n");
            druk3(BST1, 0);        // druk wg Wirtha
            konstr1a(n, zakres, &BST2);   // drugie losowane BST
            printf("\ndruk wg Wirtha:  \n");
            druk3(BST2, 0);        // druk wg Wirtha
            w1=height(BST1) - 1;
            w2=height(BST2) - 1;
            printf("wysokosci drzew: w1 = %d, w2 = %d\n",w1, w2);
            printf("drzewa sa izomorficzne  %d\n", izo(BST1, BST2));
            break;
        } //2
        case 3: { //losowe BST, prawdopodobienstwo pary izomorficznych BST
            /*UWAGA: wariant dziala ale nalezy programowo zapewnic
            generacje BST o dokladnie n wierzcholkach
            - wybor duzego zakresu losowania moze nie wystarczyc */
            czyt3(&n,& zakres, &rep);
            l=0; // licznik par izomorficznych drzew
            for (i=1; i<=rep; i++) {
                konstr1a(n, zakres, &BST1);   // pierwsze losowane BST
                konstr1a(n, zakres, &BST2);  // drugie losowane BST
                if (izo(BST1, BST2))
                    l++;
                zwolnij(&BST1);
                zwolnij(&BST2);
            }
            printf("n=%d ,rep=%d, l=%d",n,rep,l);
            break;
        } //3
        case 4: { //Drzewo Dokladnie Wywazone o korzeniu root, z pliku input
            czyt1(&n);
            root=DDW(n);
            printf("\ndruk wg Wirtha:  \n");
            druk3(root, 0);        // druk wg Wirtha
            printf("dwa obliczenia wysokosci:");
            printf("  height= %d",height(root) - 1);
            printf("  height1= %d\n",height1(root) - 1);
            printf("max= %d \n",Max(root));
            printf("dane x= ");
            scanf("%d",&x);
            member(x, root, &jest);
            printf("\nx= %d jest w drzewie: %d\n",x,jest);
            break;
        } //4
        case 5: { //Drzewo Dokladnie Wywazone o korzeniu root, dane losowane
            czyt2(&n, &zakres);
            printf("\nwylosowane wartosci x: ");
            root=DDW1(n, zakres);
            printf("\ndruk wg Wirtha:  \n");
            druk3(root, 0);        // druk wg Wirtha
            printf("dwa obliczenia wysokosci:");
            printf("  height= %d",height(root) - 1);
            printf("  height1= %d\n",height1(root) - 1);
            printf("max= %d \n",Max(root));
            x=random(zakres)+1;
            member(x, root, &jest);
            printf("\nx= %d jest w drzewie: %d\n",x,jest);
            break;
        } //5
        case 6: { //czas generacji DDW w zaleznosci od n, zadanie domowe
            czyt3(&n, &zakres, &rep); // dlugosc ciagu, zakres, rozmiar proby
            czas1=pomiar();
            for (i=1; i<=rep; i++) {
                //losowanie DDW
                //zwalnianie pamieci
            }
            czas2=pomiar();
            printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLK_TCK);
            break;
        } //6
        case 7: { //wysokosc losowego drzewa BST w zaleznosci od n
            czyt3(&n, &zakres, &rep);
            //zadanie domowe
            //licznik drzew o danej wysokosci, oczekiwana wysokosc
            //druk wynikow
            break;
        } //7
        case 8: {
            //reorganizacja BST, zadanie domowe
            break;
        } //8
        default: {
            printf("Taki wariant nie istnieje!\n");
        }
        } // switch
        printf("koniec? 0/1\n");
    } while (getch()!='1');

    return 0;
}

void czyt1(int *n) // n = dlugosc ciagu
{
    printf("n = ");
    scanf("%d", n);
}//czyt1

void czyt2(int *n,int * z) // n = dlugosc ciagu, z = zakres
{
    printf("n,z = ");
    scanf("%d%d", n,z);
} // czyt2

void czyt3(int* n,int * z,int* rep) // dl. ciagu, zakres, rozmiar proby
{
    printf("n,z,rep = ");
    scanf("%d%d%d", n,z,rep);
    //zakres odpowiednio duzy dla danego n, tak aby drzewo BST mialo
    // n wierzcholkow
} // czyt3

void insert(int x,ref **t)
{
    if(*t==NULL) {
        *t=(ref*)malloc(sizeof(ref));
        if(t!=NULL) {
            (*t)->a=x;
            (*t)->left=NULL;
            (*t)->right=NULL;
        } else;
    } else if(x!=(*t)->a)
        if(x<(*t)->a)
            insert(x,&(*t)->left);
        else insert(x,&(*t)->right);

}//insert

void konstr1(int n,int z, ref ** t)// losowe BST na n wierzcholkach
{
    int i,x;
    *t=NULL;
    for(i=1; i<=n; i++) {
        x=random(z)+1;
        printf("%d ",x);
        if(i % 10==0)
            printf("\n");
        insert(x,t);
    }
}  //konstr1

void konstr1a(int n,int z, ref ** t)// konstr1 bez drukowania x
{
    int i,x;
    *t=NULL;
    for(i=1; i<=n; i++) {
        x=random(z)+1;
        insert(x,t);
    }
}  //konstr1a

// operacja konstruowania binarnego drzewa dokladnie wywazonego
ref* DDW(int n) //N. Wirth, str. 209
{
    ref *p;
    int x, nl, np;
    if (n > 0) {
        nl=n/ 2;
        np=n - nl - 1;
        printf("x= ");
        scanf("%d",&x);
        p=(ref*)malloc(sizeof(ref));
        if(p!=NULL) {
            p->a=x;
            p->left=DDW(nl);
            p->right=DDW(np);
        }
        return p;
    } else return NULL;
} // DDW

ref* DDW1(int n,int z)// dane losowane
{
    ref *p;
    int x, nl, np;
    if (n > 0) {
        nl=n / 2;
        np=n - nl - 1;
        x=random(z) + 1;
        printf(" %d",x);
        p=(ref*)malloc(sizeof(ref));
        if(p!=NULL) {
            p->a=x;
            p->left=DDW1(nl,z);
            p->right=DDW1(np,z);
        }
        return p;
    } else return NULL;
}//  DDW1

int wiekszy(int a, int b) // Tomasz Obrebski, Dec. 89, Inf.
{
    if (a > b) return a;
    else return b ;
}// wiekszy

//funkcja height wyznacza liczbe poziomow w drzewie binarnym
int height(ref *t)
{
    if (t!=NULL)
        return (wiekszy(height(t->left), height(t->right))+1);
    else return 0;
}//height

//funkcja height1 wyznacza liczbe poziomow w drzewie binarnym
int height1(ref *t) // Andrzej Urbanski
{
    int l,r;

    if (t!=NULL  ) {
        l=height1(t->left);
        r=height1(t->right);
        if(l>r)
            return(l+1);
        else
            return (r+1);
    } else return 0;
} // height1

//  funkcja izo sprawdza czy drzewa binarne t1, t2 sa izomorficzne
enum Boolean izo(ref *t1,ref *t2) //Robert Jamrozy, 1990, Inf.
{
    if ((t1 == NULL) || (t2 == NULL))
        return Boolean(t1 == t2);
    else if (izo(t1->left, t2->left))
        return izo(t1->right, t2->right);
    else if (izo(t1->right, t2->left))
        return izo(t1->left, t2->right);
    else return falsz;
} // izo

//operacja member w dowolnym drzewie binarnym
void member(int x, ref *t,enum Boolean *jest)
{
    if(t!=NULL)
        if(x==t->a)
            *jest=prawda;
        else {
            member(x, t->left, jest);
            if (!jest)
                member(x,t->right, jest);
        }
    else
        *jest=falsz;
} //member

void szukaj(ref *t,int *m)// w preorder
{
    if (t!=NULL) {
        if (t->a > *m)
            *m=t->a;
        szukaj(t->left, m);
        szukaj(t->right, m);
    }
} // szukaj

//operacja max w dowolnym drzewie binarnym
int Max(ref *t)
{
    int naj;
    if (t!=NULL) {
        naj=t->a;
        szukaj(t, &naj);
    }
    return naj;
} // max

// operacja zwalniania pamieci ( w postorder) zajetej przez drzewo
void zwolnij(ref **t)
{
    if(*t!=NULL) {
        zwolnij(&(*t)->left);
        zwolnij(&(*t)->right);
        free(*t);
    }
} //zwolnij

void druk3(ref *t, int h)// N. Wirth, h- wciecie
{
    int i;
    if(t!=NULL) {
        druk3(t->right, h+3);
        for(i=1; i<=h; i++)
            printf(" ");
        printf(" %d \n",t->a);
        druk3(t->left,h+3);
    }
} //druk3

clock_t pomiar(void)
{
    clock_t czas;
    czas = clock();
    return czas;
}//pomiar

