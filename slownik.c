//program p11, KTB Dec 10, 1996
#include <stdio.h>
//#include <alloc.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
# include <limits.h>

#define randomize() srand(unsigned(time(NULL)))
#define random(a) rand()%a
#define Random() (rand()%10000)*0.0001

# define cmax 16

typedef char t[cmax];   //slowo

typedef struct REF {
    t a;
    struct REF * next;
} ref;                        // lista slow

typedef struct R {
    char a;
    ref *next;
    struct R * nextpion;
} refpion;                    // lista krawedzi
enum Boolean {falsz=0, prawda=1};


void czyt1(int *n, int *c);
void czyt(int nr, int c, t x);
void pushpion(char x, refpion **h);
void push(int c,t x, ref **h);
void memberpion(char x, refpion *h, refpion **gdzie);
enum Boolean member(t x, ref *h);
void intopion(char x, refpion **s, refpion **);
void skorowidz1(int n, int c, refpion **H);
void skorowidz2(int n, int c,refpion **S, refpion **H);
void druklista(int c,char x,ref *h);
void drukH(int c,refpion *H);
void zwolnij(ref *head);
clock_t pomiar(void);
void kopiuj_tablice(int c,t b, t a);


int main ()
{
    int c,n,wariant;
    refpion *H, *S;
    clock_t czas1, czas2;

    randomize();
    do {
        printf("Wariant: (1/2/3/4/5)");
        scanf("%d",&wariant);
        switch(wariant) {
        case 1: { //konstr i druk skorowidza z dopisywaniem na poczatku
            czyt1(&n,&c);//n-liczba slow, c-dlugosc slowa
            skorowidz1(n,c,&H);//konstr z pushpion
            drukH(c,H); //drukowanie skorowidza
            break;
        } // 1
        case 2: { //konstr i druk skorowidza z dopisywaniem na koncu
            czyt1(&n,&c);
            skorowidz2(n,c,&S,&H);//konstr z intopion
            drukH(c,H);
            break;
        } //2
        case 3: { //jak wariant 2 ale rowniez z dopisywaniem slow na koncu listy
            //czyt1(&n,&c);
            //skorowidz3(n,c,&S,&H); //zadanie domowe
            //drukH(c,H);
            break;
        } //3
        case 4: { //jak wariant 3 ale czytanie danych z pliku tekstowego
            //czyt1(&n,&c);
            //skorowidz4(n,c,&S,&H); //zadanie domowe
            //drukH(c,H);
            break;
        } //4
        case 5: { //czas sortowania na liscie poziomej, zadanie domowe
            czas2=pomiar();
            //
            czas1=pomiar();
            printf("czas: %f [s]\n", (float)(czas2 - czas1) / (float)CLK_TCK);
            break;
        } //5
        default: {
            printf("Taki wariant nie istnieje!\n");
        }
        } // switch
        printf("koniec? 0/1\n");
    } while (getch()!='1');

    return 0;
}


void czyt1(int *n, int *c)
{
    printf("n,c (n slow, c znakow kazde) : ");
    scanf("%d%d",n,c);
} //czyt1

void czyt(int nr, int c, t x)
{
    int i;
    t pom;
    printf("nr= %d  ",nr);
    scanf("%s",pom);
    for(i=1; i<=c+1; i++)
        //scanf("%c",&x[i]);
        x[i]=pom[i-1];
} //czyt

void pushpion(char x, refpion **h)
{
    refpion *p;
    p=(refpion*)malloc(sizeof(refpion));
    if(p!=NULL) {
        p->a=x;
        p->next=NULL;
        p->nextpion=*h;
        *h=p;
    }
} //pushpion

void push(int c,t x, ref **h)
{
    ref *p;
    p=(ref*)malloc(sizeof(ref));
    if(p!=NULL) {
        kopiuj_tablice(c,p->a,x);
        p->next=*h;
        *h=p;
    }
}  //push

void memberpion(char x, refpion *h, refpion **gdzie)
{
    *gdzie=NULL; //nie znaleziono na liscie pionowej
    while((h!=NULL)&& (*gdzie==NULL))
        if(h->a==x)
            *gdzie=h;
        else
            h=h->nextpion;
}// memberpion

enum Boolean member(t x, ref *h)
{
    enum Boolean jest;
    jest=falsz;
    while((h!=NULL)&& (!jest))
        if(h->a==x)
            jest=prawda;
        else h=h->next;
    return jest;
} //member

void intopion(char x, refpion **s, refpion **h)
{
    refpion *p;
    p=(refpion*)malloc(sizeof(refpion));
    if(p!=NULL) {
        p->a=x;
        p->next=NULL;
        p->nextpion=NULL;
    }
    if(*h!=NULL)
        (*s)->nextpion=p;
    else
        *h=p;
    *s=p;
} //intopion

void skorowidz1(int n, int c, refpion **H)
{
    int i;
    t x;
    refpion *gdzie;
    *H=NULL;
    for(i=1; i<=n; i++) {
        czyt(i,c,x);
        memberpion(x[1],*H,&gdzie);
        if(gdzie==NULL) {
            pushpion(x[1],H);
            push(c,x,&(*H)->next);
        } else if(!member(x,gdzie->next))
            push(c,x,&gdzie->next);
    }
}  //skorowidz1

void skorowidz2(int n, int c,refpion **S, refpion **H)//intopion
{
    int i;
    t x;
    refpion *gdzie;
    *H=NULL;
    for(i=1; i<=n; i++) {
        czyt(i,c,x);
        memberpion(x[1],*H,&gdzie);
        if(gdzie==NULL) {
            intopion(x[1],S,H);
            push(c,x,&(*S)->next);
        } else if(!member(x,gdzie->next))
            push(c,x,&gdzie->next);
    }

} //skorowidz2

void druklista(int c,char x,ref *h)
{
    int i,j;
    printf("  lista %c : ",x);
    i=0; //licznik wydrukowanych elementow listy
    while(h!=NULL) {
        for(j=1; j<=c+1; j++)
            printf("%c",h->a[j]);
        i++;
        if(i%5==0)
            printf("\n");
        h=h->next;
    }
    printf("\n");
}  //druklista

void drukH(int c,refpion *H)
{
    printf("\nSkorowidz : \n");
    while(H!=NULL) {
        druklista(c,H->a,H->next);
        H=H->nextpion;
    }
} // drukH

void zwolnij(ref *h)
{
    ref *p;
    while(h!=NULL) {
        p=h;
        h=h->next;
        p->next=NULL;
        free(p);
    }
} //zwolnij

clock_t pomiar(void)
{
    clock_t czas;
    czas = clock();
    return czas;
}//pomiar

void kopiuj_tablice(int c,t b, t a)
{
    int i;
    for(i=1; i<=c+1; i++)
        b[i]=a[i];
}  //kopiuj_tablice



