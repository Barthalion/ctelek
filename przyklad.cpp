//program p1	KTB Oct 1, 1996

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int nmax = 100;

inline int random(int poczatek_zakresu, int koniec_zakresu)
{
	return ((rand() % (koniec_zakresu + 1 + poczatek_zakresu)) - poczatek_zakresu);
}

void czytaj(int &liczba_elementow, int &zakres_wartosci);
void generacja(int tablica[], int liczba_elementow, int zakres_wartosci);
int Min(int tablica[], int liczba_elementow);
/*
 *  int Max(int tablica[], int liczba_elementow);
 *  int Max_z_pozycja(int tablica[], int liczba_elementow, int &pozycja);
 *  float Srednia(int tablica[], int liczba_elementow);
 */
void drukuj(int tablica[], int liczba_elementow, int zakres_wartosci);


int main()
{
	bool wyjdz = 0;
	short wybor;
	int liczba_elementow, zakres_wartosci, liczba_powtorzen;
	int wygenerowane[nmax];

	srand(unsigned(time(NULL)));

	while (!wyjdz) {
		cout << "Wybierz wariant (1,0 - wyjscie): ";
		cin >> wybor;
		switch (wybor) {
		case 0:
			wyjdz = 1;
			break;
		case 1:
			czytaj(liczba_elementow, zakres_wartosci);
			generacja(wygenerowane, liczba_elementow, zakres_wartosci);
			drukuj(wygenerowane, liczba_elementow, zakres_wartosci);
			break;
		default:
			cout << "Taki wariant nie istnieje" << endl;
		}
	}

	return 0;
}

void czytaj(int &liczba_elementow, int &zakres_wartosci)
{
	do {
		cout << "[Wprowadz liczebnosc zbioru oraz zakres wartosci oddzielone spacja] n,z = ";
		cin >> liczba_elementow >> zakres_wartosci;
	} while (liczba_elementow > nmax);
}

void generacja(int tablica[], int liczba_elementow, int zakres_wartosci)
{
	for (int i = 0; i < liczba_elementow; i++) {
		tablica[i] = random(0, zakres_wartosci);
	}
}

int Min(int tablica[], int liczba_elementow)
{
	int wartosc_minimalna;
	wartosc_minimalna = tablica[0];
	for (int i = 1; i < liczba_elementow; i++)
		if (tablica[i] < wartosc_minimalna) {
			wartosc_minimalna = tablica[i];
		}
	return wartosc_minimalna;
}

void drukuj(int tablica[], int liczba_elementow, int zakres_wartosci)
{
	cout << endl << "Elementy ciagu n = " << liczba_elementow << ", z = " << zakres_wartosci << ":" << endl;
	for (int i = 0; i < liczba_elementow; i++) {
		cout << tablica[i] << " ";
		if (((i + 1) % 10 == 0) && (i != 0)) {
			cout << endl;
		}
	}
	cout << endl << endl;

	cout << "Element minimalny: " << Min(tablica, liczba_elementow) << endl << endl;
}
