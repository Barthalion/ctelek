//program p1 KTB Oct 1, 1996
//              KTZ Oct 10, 2013

#include "stdafx.h"


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define random(a) rand() % a
#define randomize() srand(unsigned(time(NULL)))
#define nmax 101

typedef int t[nmax];

void czyt(int *n, int *z);
void generacja(int n, int z, t a);
int Min(int n, t a);
/*
  int Max(int n, t a);
  int Max1(int n, t a, int * poz);
  int Suma(int n, t a);
  float Srednia(int n, t a);
  void generacja2(int n, int z, t a);
*/
void obl(int n, t a, int *m);
void druk(int n, int z, t a, int m);


int _tmain(int argc, _TCHAR* argv[])
{
int m,n,z;
t a;

randomize();
do
  {
  czyt(&n,&z);
  generacja(n,z,a);
  obl(n,a,&m);
  druk(n,z,a,m);
  printf("koniec? 0/1\n");
  }
  while (_getch()!='1');
  return 0;
} //main


void czyt(int *n, int *z)
{
  do
  {
printf("n,z= ");
scanf_s("%d%d",n,z);
  }
  while (*n > nmax);

} //czyt

void generacja(int n, int z, t a)
{
int i;
for(i=1;i<=n;i++)
a[i]=random(z)+1;
} //generacja

int Min(int n, t a)
{
int i,x;
x=a[1];
for(i=2;i<=n;i++)
  if(a[i]<x)
      x=a[i];
  return x;
} //Min

void obl(int n, t a, int *m)
{
  *m=Min(n,a);
} //obl

void druk(int n, int z, t a, int m)
{
int i;
  printf("\n");
  printf("Elementy ciagu, n= %d,z= %d \n",n,z);
  for(i=1;i<=n;i++)
      {
  printf("%4d", a[i]);
      if(i % 10==0)
      printf("\n");
      }
  printf("\n");

  printf("Element minimalny: %d\n",m);
} //druk
