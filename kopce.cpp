//program p14, KTB Jan 2, 1997
#include <stdio.h>
#include <stdlib.h>
//#include <alloc.h>
#include <time.h>
#include <conio.h>
# include <limits.h>

#define randomize() srand(unsigned(time(NULL)))
#define random(a) rand()%a
#define Random() (rand()%10000)*0.0001

#define nmax 101

typedef int t[nmax];

typedef struct REF {
    int a;
    struct REF * left;
    struct REF * right;
} ref;                     // drzewo BST

enum Boolean {falsz=0, prawda=1};

void czyt2(int *n,int * z);
void czyt3(int *n,int * z, int *rep);
void konstr(int n,int z, t a);
void popraw(int l, int r,t a);
void heapsort(int n, t a);
void heapify(int l, int r,t a);
void heapsort1(int n, t a);
void insert(int x,ref **t);
void konstr1(int n, int z,ref **t);
void konstr1a(int n, int z,ref **t);
void inorder(ref *t);
void zwolnij(ref *t);
void druk(int n, t a);
void druk3(ref *t, int h);
clock_t pomiar(void);
void kopiuj_tablice(int n,t b, t a);

int main ()
{
    int i,n,rep,zakres,wariant;
    t a,b;
    ref *BST;
    clock_t czas1, czas2;

    randomize();
    do {
        printf("Wariant: (1/2/3/4/5/6/7/8)");
        scanf("%d",&wariant);
        switch(wariant) {
        case 1: { // heapsort i heapsort1
            czyt2(&n, &zakres); // dlugosc ciagu danych i zakres losowania
            konstr(n, zakres, a);// losowanie danych w tablicy
            kopiuj_tablice(n,b,a);//kopia tablicy "a" w tablicy "b"
            printf("dane:\n");
            druk(n, a);
            printf("\n");
            heapsort(n, a);
            printf("heapsort:\n");
            druk(n, a);
            printf("\n");
            heapsort1(n, b);
            printf("heapsort1:\n");
            druk(n, b);
            printf("\n");
            break;
        } // 1
        case 2: { //losowe BST, sortowanie
            czyt2(&n, &zakres);  //dlugosc ciagu danych i zakres losowania
            printf("kolejno losowane wartosci x: ");
            konstr1(n, zakres, &BST);   //losowanie BST
            printf("\ndruk wg Wirtha:  \n");
            druk3(BST,0); // druk wg Wirtha
            inorder(BST);
            break;
        } //2
        case 3: { // czas sortowania heapsort w zaleznosci od n
            czyt3(&n, &zakres, &rep);
            czas1=pomiar();
            for (i=1; i<=rep; i++) {
                konstr(n, zakres, a);// losowanie danych w tablicy
                heapsort(n, a);
            }
            czas2= pomiar();
            printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLK_TCK);
            break;
        } //3
        case 4: { //czas sortowania heapsort1 w zaleznosci od n
            czyt3(&n, &zakres,&rep);
            czas1=pomiar();
            for (i=1; i<=n; i++) {
                konstr(n, zakres, a); // losowanie danych w tablicy
                heapsort1(n, a);
            }
            czas2= pomiar();
            printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLK_TCK);
            break;
        } //4
        case 5: {
            /*czas sortowania BST+inorder w zaleznosci od n, zadanie domowe
            Uwaga: BST musi miec dokladnie n wierzcholkow*/
            czyt3(&n, &zakres, &rep);
            czas1=pomiar();
            for (i=1; i<=rep; i++) {
                //generacja drzewa BST
                //inorder bez drukowania
                //zwalnianie pamieci
            }
            czas2= pomiar();
            printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLK_TCK);
            break;
        } //5
        case 6: {
            /*czas sortowania z prostym wybieraniem w zaleznosci od n,
            zadanie domowe*/
            czyt3(&n, &zakres, &rep);
            czas1=pomiar();
            for (i=1; i<= rep; i++) {
                //generacja ciagu losowego w tablicy
                // sortowanie
            }
            czas2= pomiar();
            printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLK_TCK);
            break;
        } //6
        case 7: {
            /*algorytmy transformacji: tablica, lista, plik, BST --> kopiec
             (kopiec zrealizowany jako drzewo binarne) - zadanie wlasne*/
            break;
        } //7
        case 8: {
            /* algorytmy transformacji: kopiec --> tablica, lista, plik, BST
            (kopiec zrealizowany jako drzewo binarne) - zadanie wlasne*/
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


void czyt2(int *n,int * z) // n = dlugosc ciagu, z = zakres
{
    printf("n,z = ");
    scanf("%d%d", n,z);
} // czyt2

void czyt3(int *n,int * z, int *rep) // dlugosc ciagu,zakres,rozmiar proby
{
    printf("n,z,rep = ");
    scanf("%d%d%d", n,z,rep);
} // czyt3

void konstr(int n,int z, t a)
{
    int i;
    for(i=1; i<=n; i++)
        a[i]=random(z)+1;
}  //konstr

void popraw(int l, int r,t a)
{
    int k,x;
    enum Boolean b;
    x=a[l];
    b=falsz;
    k=2*l; //indeks lewego nastepnika
    while((k<=r)&& !b) {
        if(k+1<=r) //prawy nastepnik jeszcze dostepny
            if(a[k+1]>a[k])
                k++; // nowe k jesli prawy wiekszy
        if(a[k]>x) { //nastepnik jest lepszy niz x
            a[l]=a[k]; //wiekszy wyzej
            l=k; //przygotowanie nowego polozenia elementu
            k=2*l; //indeks lewego nastepnika
        } else b=prawda; // wyjscie z petli
    }
    a[l]=x;
}//popraw

void heapsort(int n, t a) // z iteracyjnym poprawianiem kopca
{
    int i,x;
    for (i=n / 2; i>= 1; i--)
        popraw(i,n,a); // pierwszy kopiec
    for (i=n; i>=2; i--) {
        x=a[i];
        a[i]=a[1];
        a[1]=x; // zamiana pierwsz. z ost. nieposort.
        popraw(1, i - 1,a);
    }
} // heapsort

void heapify(int l, int r,t a)
{
    int k,x;
    if(l<=r/2) { //jesli a[l] nie jest lisciem
        k=2*l; //indeks lewego nastepnika
        if(k+1<=r)
            if(a[k+1]>a[k])
                k++;
        if(a[k]>a[l]) { //zamiana a[k] z a[l]
            x=a[l];
            a[l]=a[k];
            a[k]=x;
        }
        heapify(k,r,a);
    }
}//heapify

void heapsort1(int n, t a) // z rekurencyjnym poprawianiem kopca
{
    int i,x;
    for (i=n / 2; i>= 1; i--)
        heapify(i,n,a); // pierwszy kopiec
    for (i=n; i>=2; i--) {
        x=a[i];
        a[i]=a[1];
        a[1]=x; // zamiana pierwsz. z ost. nieposort.
        heapify(1, i - 1,a);
    }
} // heapsort1

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

void konstr1(int n, int z,ref **t) // losowe BST na n wierzcholkach
{
    int x,i;
    *t=NULL;
    for (i=1; i<=n; i++) {
        x=random(z) + 1;
        printf("%d  ",x);
        if (i % 10 == 0)
            printf("\n");
        insert(x,t);
    }
}// konstr1

void konstr1a(int n, int z,ref **t) // losowe BST na n wierzcholkach, bez drukowania
{
    int x,i;
    *t=NULL;
    for (i=1; i<=n; i++) {
        x=random(z) + 1;
        insert(x,t);
    }
}// konstr1a

void inorder(ref *t)
{
    if(t!=NULL) {
        inorder(t->left);
        printf("%d ",t->a);
        inorder(t->right);
    }
} //inorder

void zwolnij(ref *t)
{
    if(t!=NULL) {
        zwolnij(t->left);
        zwolnij(t->right);
        free(t);
    }
} //zwolnij

void druk(int n, t a)
{
    int i;
    for (i=1; i<=n; i++) {
        printf("%7d",a[i]);
        if (i% 10 == 0 )printf("\n");
    }
}// druk

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

void kopiuj_tablice(int n,t b, t a)
{
    int i;
    for(i=1; i<=n+1; i++)
        b[i]=a[i];
}  //kopiuj_tablice

