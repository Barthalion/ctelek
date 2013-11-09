//program p2 KTB Oct 7,1996

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const int nmax = 100;

inline int random(int poczatek_zakresu, int koniec_zakresu)
{
	return ((rand() % (koniec_zakresu + 1 + poczatek_zakresu)) - poczatek_zakresu);
}

void czytaj(int &liczba_elementow, int &zakres_wartosci, int &liczba_powtorzen);
void generacja(int wygenerowane[], int liczba_elementow, int zakres_wartosci);
void kopiuj_tablice(int wygenerowane[], int kopia_wygenerowanych[], int liczba_elementow);
void drukuj(int wygenerowane[], int liczba_elementow, int zakres_wartosci = 0);
void sortowanie(int wygenerowane[], int liczba_elementow);
int indeks_najwiekszej_wartosci(int wygenerowane[], int liczba_elementow, int indeks_poczatkowy);
void sortowanie2(int wygenerowane[], int liczba_elementow);
inline clock_t pomiar();

int main()
{
	bool wyjdz = 0;
	short wybor;
	int liczba_elementow, zakres_wartosci, liczba_powtorzen;
	int wygenerowane[nmax], kopia_wygenerowanych[nmax];
	clock_t czas_start, czas_koniec;

	srand(unsigned(time(NULL)));

	while (!wyjdz) {
		cout << "Wybierz wariant (1,2,0 - wyjscie): ";
		cin >> wybor;
		switch (wybor) {
		case 0:
			wyjdz = 1;
			break;
		case 1: //sortowania
			liczba_powtorzen = 0;
			czytaj(liczba_elementow, zakres_wartosci, liczba_powtorzen);
			generacja(wygenerowane, liczba_elementow, zakres_wartosci);
			kopiuj_tablice(wygenerowane, kopia_wygenerowanych, liczba_elementow);
			drukuj(wygenerowane, liczba_elementow, zakres_wartosci);
			sortowanie(wygenerowane, liczba_elementow);
			drukuj(wygenerowane, liczba_elementow);
			sortowanie2(kopia_wygenerowanych, liczba_elementow);
			drukuj(kopia_wygenerowanych, liczba_elementow);
			break;
		case 2: //pomiar czasu sortowań
			czytaj(liczba_elementow, zakres_wartosci, liczba_powtorzen);
			czas_start = pomiar();
			for (int i = 0; i < liczba_powtorzen; i++) {
				generacja(wygenerowane, liczba_elementow, zakres_wartosci);
				sortowanie(wygenerowane, liczba_elementow);
			}
			czas_koniec = pomiar();

			cout << "Zegar: " << (czas_koniec - czas_start) << endl;
			cout << "Czas: " << ((float)(czas_koniec - czas_start) / (float)CLK_TCK) << "s" << endl;
			break;
		default:
			cout << "Taki wariant nie istnieje" << endl;
		}
	}

	return 0;
}

void czytaj(int &liczba_elementow, int &zakres_wartosci, int &liczba_powtorzen)
{
	do {
		if (liczba_powtorzen == 0) {
			cout << "[Wprowadz liczebnosc zbioru oraz zakres wartosci oddzielone spacja] n,z = ";
			cin >> liczba_elementow >> zakres_wartosci;
		} else {
			cout << "[Wprowadz liczebnosc zbioru, zakres wartosci oraz ilosc powtorzen oddzielone spacja] n,z,rep = ";
			cin >> liczba_elementow >> zakres_wartosci >> liczba_powtorzen;
		}
	} while (liczba_elementow > nmax);
}

void generacja(int wygenerowane[], int liczba_elementow, int zakres_wartosci)
{
	int i;
	for (i = 0; i < liczba_elementow; i++) {
		wygenerowane[i] = random(0, zakres_wartosci);
	}
}

void kopiuj_tablice(int wygenerowane[], int kopia_wygenerowanych[], int liczba_elementow)
{
	for (int i = 0; i < liczba_elementow; i++) {
		kopia_wygenerowanych[i] = wygenerowane[i];
	}
}

void drukuj(int wygenerowane[], int liczba_elementow, int zakres_wartosci)
{
	if (zakres_wartosci == 0) {
		cout << "Posortowane: " << endl;
	} else {
		cout << endl << "Sortowanie tablicy, n = " << liczba_elementow << ", z = " << zakres_wartosci << endl << endl << "Wygenerowane elementy: " << endl;
	}

	for (int i = 0; i < liczba_elementow; i++) {
		cout << wygenerowane[i] << " ";
		if ((i % 10 == 0) && (i != 0)) {
			cout << endl;
		}
	}
	cout << endl << endl;
}

void sortowanie(int wygenerowane[], int liczba_elementow)
{
	int indeks_maksymalnej, wartosc_maksymalna;
	for (int i = 0; i < liczba_elementow - 1; i++) {
		wartosc_maksymalna = wygenerowane[i];
		indeks_maksymalnej = i;
		for (int j = i; j < liczba_elementow; j++)
			if (wygenerowane[j] > wartosc_maksymalna) {
				wartosc_maksymalna = wygenerowane[j];
				indeks_maksymalnej = j;
			}
		if (i != indeks_maksymalnej) {
			wygenerowane[indeks_maksymalnej] = wygenerowane[i];
			wygenerowane[i] = wartosc_maksymalna;
		}
	}
}

int indeks_najwiekszej_wartosci(int wygenerowane[], int liczba_elementow, int indeks_poczatkowy)
{
	int wartosc_maksymalna, indeks_maksymalnej;
	wartosc_maksymalna = wygenerowane[indeks_poczatkowy];
	indeks_maksymalnej = indeks_poczatkowy;
	for (int i = indeks_poczatkowy; i < liczba_elementow; i++)
		if (wygenerowane[i] > wartosc_maksymalna) {
			wartosc_maksymalna = wygenerowane[i];
			indeks_maksymalnej = i;
		}
	return indeks_maksymalnej;
}

void sortowanie2(int wygenerowane[], int liczba_elementow)
{
	int indeks_maksymalnej, najwiekszy_element;
	for (int i = 0; i < liczba_elementow; i++) {
		indeks_maksymalnej = indeks_najwiekszej_wartosci(wygenerowane, liczba_elementow, i);
		if (i != indeks_maksymalnej) {
			najwiekszy_element = wygenerowane[indeks_maksymalnej];
			wygenerowane[indeks_maksymalnej] = wygenerowane[i];
			wygenerowane[i] = najwiekszy_element;
		}
	}
}

inline clock_t pomiar()
{
	return clock();
}
