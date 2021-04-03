#include <iostream>
#include <windows.h>
#include <time.h>
#include <sstream>


using namespace std;

int const ppudlo = -2000000;
int const bomba = -200000;
int const tarcza = -20000;

int** plansza1(int, int, int**);
void menu_dwoch_uzytkonikow_wlasna_gra();
void menu_dwoch_uzytkownikow();
void wyswietlenie_planszy(int**, int, int);
void zwalnianie_pamieci2D(int**, int, int);
int** uzupelnij_dane(int**, int, int, string&);
int przebieg_gry(int**, int**, int, int, string, string);
void legenda();
void szybka_gra();
int** uzupelnij_dane_r(int**, int, int);
void menu_z_botem();
void wlasna_gra_z_botem();
int przebieg_gry_z_botem(int**, int**, int, int, string, int, int);
int** uzupelnij_dane_bota(int** plansza, int k, int w, int, int&);
void szybka_gra_z_botem();
void modyfikacje();
void armagedon(int**, int**, int**, int**, int, int);
void bombaf(int**, int**, int, int, int, int);
void war(int**, int**, int, int);
void czyint(int&);
void czyintmin(int&);

struct modyfikacje {
	int armagedon;
	int war;
};

struct modyfikacje zmienna;

struct statek {
	int X;
	int Y;
	int kierunek;
	int maszty;
};

void czyintmin(int& x)
{
	bool sprawdzacz = false;
	int pauza;
	string wartosci;
	do
	{
		pauza = 2;
		if (sprawdzacz)
			cout << "Podales zla liczbe calkowita\n";
		sprawdzacz = false;
		cin >> wartosci;
		for (int i = 0; i < wartosci.length(); i++)
		{

			if (wartosci[i] > '9' || wartosci[i] < '0')
			{

				if (wartosci[i] == '-')
					pauza--;
				else
					sprawdzacz = true;
			}
		}
		if (pauza < 1)
			sprawdzacz = true;
	} while (sprawdzacz);
	stringstream ss;
	ss << wartosci;
	ss >> x;
}

void czyint(int& x)
{
	bool sprawdzacz = false;
	string wartosci;
	do
	{
		if (sprawdzacz)
			cout << "Podales zla liczbe naturalna\n";
		sprawdzacz = false;
		cin >> wartosci;
		for (int i = 0; i < wartosci.length(); i++)
		{
			if (wartosci[i] > '9' || wartosci[i] < '0')
				sprawdzacz = true;
		}
	} while (sprawdzacz);
	stringstream ss;
	ss << wartosci;
	ss >> x;
}
void modyfikacje()
{
	int x;
	do
	{
		system("cls");
		cout << "Wybierz modyfikacje: " << endl;
		cout << "[0] - Wyjscie z menu modyfikacji: " << endl;
		cout << "[1] ARMAGEDON \t";
		if (zmienna.armagedon == 0)
			cout << "OFF" << endl;
		if (zmienna.armagedon == 1)
			cout << "ON" << endl;
		cout << "[2] WAR \t";
		if (zmienna.war == 0)
			cout << "OFF" << endl;
		if (zmienna.war == 1)
			cout << "ON" << endl;
		czyint(x);
		switch (x)
		{
		case 1:
			if (zmienna.armagedon == 0)
			{
				zmienna.armagedon = 1;
			}
			else if (zmienna.armagedon == 1)
			{
				zmienna.armagedon = 0;
			}
			break;
		case 2:
			if (zmienna.war == 0)
			{
				zmienna.war = 1;
			}
			else if (zmienna.war == 1)
			{
				zmienna.war = 0;
			}
			break;
		}
	} while (x != 0);
}

void bombaf(int** plansza2, int** plansza1_wyswietlenie, int k, int w, int x, int y)
{
	plansza2[x][y] = ppudlo;
	plansza1_wyswietlenie[x][y] = ppudlo;
	if (y - 1 >= 0)
	{
		if (plansza2[x][y - 1] == 0 || plansza2[x][y - 1] == bomba || plansza2[x][y - 1] == tarcza)
		{

			plansza2[x][y - 1] = ppudlo;
			plansza1_wyswietlenie[x][y - 1] = ppudlo;
		}
		else if (plansza2[x][y - 1] > 0)
		{
			plansza2[x][y - 1] *= -1;
			plansza1_wyswietlenie[x][y - 1] *= -1;
		}
	}
	if (x - 1 >= 0)
	{
		if (plansza2[x - 1][y] == 0 || plansza2[x - 1][y] == bomba || plansza2[x - 1][y] == tarcza)
		{
			plansza2[x - 1][y] = ppudlo;
			plansza1_wyswietlenie[x - 1][y] = ppudlo;
		}
		else if (plansza2[x - 1][y] > 0)
		{
			plansza2[x - 1][y] *= -1;
			plansza1_wyswietlenie[x - 1][y] *= -1;
		}
	}
	if (y + 1 < w)
	{
		if (plansza2[x][y + 1] == 0 || plansza2[x][y + 1] == bomba || plansza2[x][y + 1] == tarcza)
		{
			plansza2[x][y + 1] = ppudlo;
			plansza1_wyswietlenie[x][y + 1] = ppudlo;
		}
		else if (plansza2[x][y + 1] > 0)
		{
			plansza2[x][y + 1] *= -1;
			plansza1_wyswietlenie[x][y + 1] *= -1;
		}
	}

	if (x + 1 < k)
	{
		if (plansza2[x + 1][y] == 0 || plansza2[x + 1][y] == bomba || plansza2[x + 1][y] == tarcza)
		{
			plansza2[x + 1][y] = ppudlo;
			plansza1_wyswietlenie[x + 1][y] = ppudlo;
		}
		else if (plansza2[x + 1][y] > 0)
		{
			plansza2[x + 1][y] *= -1;
			plansza1_wyswietlenie[x + 1][y] *= -1;
		}
	}

}
void armagedon(int** plansza1, int** plansza1_wyswietlenie, int** plansza2, int** plansza2_wyswietlenie, int k, int w)
{
	srand(time(NULL));
	int x, y;
	do
	{
		x = rand() % k;
		y = rand() % w;
	} while (plansza1[x][y] < 0);
	if (plansza1[x][y] == 0)
	{
		plansza1[x][y] = ppudlo;
		plansza2_wyswietlenie[x][y] = ppudlo;
	}
	else
	{
		plansza1[x][y] *= -1;
		plansza2_wyswietlenie[x][y] = plansza1[x][y];
	}



	do
	{
		x = rand() % k;
		y = rand() % w;
	} while (plansza2[x][y] < 0);
	if (plansza2[x][y] == 0)
	{
		plansza2[x][y] = ppudlo;
		plansza1_wyswietlenie[x][y] = ppudlo;
	}
	else
	{
		plansza2[x][y] *= -1;
		plansza1_wyswietlenie[x][y] = plansza2[x][y];
	}
}

void war(int** plansza1, int** plansza2, int k, int w, int wartosc)
{
	int statki = 0;
	for (int i = 0; i < w; i++)
	{

		for (int j = 0; j < k; j++)
		{

			if (plansza1[j][i] == 0)
			{
				statki++;
			}
		}
	}
	int proporcja = statki * 5 / 100;
	for (int i = 0; i < proporcja; i++)
	{
		int x, y;
		do
		{
			x = rand() % k;
			y = rand() % w;

		} while (plansza1[x][y] > 0);
		plansza1[x][y] = wartosc;

	}
	statki = 0;
	for (int i = 0; i < w; i++)
	{

		for (int j = 0; j < k; j++)
		{

			if (plansza2[j][i] == 0)
			{
				statki++;
			}
		}
	}
	proporcja = statki * 5 / 100;
	for (int i = 0; i < proporcja; i++)
	{
		int x, y;
		do
		{
			x = rand() % k;
			y = rand() % w;

		} while (plansza2[x][y] > 0);
		plansza2[x][y] = wartosc;

	}
}

void legenda()
{
	cout << "LEGENDA:" << endl;
	cout << "0 - puste miejsce;" << endl;
	cout << "n(liczba wieksza od zera) - miejsce gdzie znajduje sie statek, a zarazem jego numer;" << endl;
	cout << "X - miejsce gdzie zostal trafiony statek;" << endl;
	cout << "! - miejsce nieudanego strzalu(pudlo);" << endl;
	cout << "T - miejsce gdzie znajduje sie tarcza;" << endl;
	cout << "B - miejsce gdzie znajduje sie bomba." << endl;
}

void menu_z_botem()
{
	int a;
	do
	{
		system("cls");
		cout << "Wybierz opcje:" << endl;
		cout << "[0] Wyjscie" << endl;
		cout << "[1] Szybka gra" << endl;
		cout << "[2] Wlasna gra" << endl;


		czyint(a);

		switch (a)
		{
		case 0:
			return;
		case 1:
			szybka_gra_z_botem();
			break;
		case 2:
			wlasna_gra_z_botem();
			break;
		default:
			cout << "Nie ma takiej opcji sprobuj ponownie" << endl;
			a = -1;
			Sleep(2000);
		}
	} while (a == -1);
}

void szybka_gra_z_botem()
{
	int maszty = 0;
	int w, k;

	int i = 0;
	int warunek = 0;
	int trudnosc = 2;

	k = 10;
	w = 10;

	int** plansza = NULL;
	plansza = plansza1(k, w, plansza);
	plansza = uzupelnij_dane_r(plansza, k, w);
	string nick1 = "";
	int max = 0, min = 1000;
	int** plansza2 = NULL;
	plansza2 = plansza1(k, w, plansza2);
	plansza2 = uzupelnij_dane_r(plansza2, k, w);

	for (int f = 1; true; f++)
	{

		for (int i = 0; i < w; i++)
		{

			for (int j = 0; j < k; j++)
			{

				if (plansza[j][i] == f)
				{
					maszty++;
				}
			}
		}

		if (maszty == 0)
			break;
		if (min > maszty && maszty != 0)
			min = maszty;
		if (max == -1)
			f = 0;
		maszty = 0;
	}
	wyswietlenie_planszy(plansza, k, w);
	cout << endl << endl;
	wyswietlenie_planszy(plansza2, k, w);

	system("cls");
	cout << "Gra wystartowala!" << endl;
	int p = przebieg_gry_z_botem(plansza, plansza2, k, w, nick1, trudnosc, min);
	if (p == 1)
	{
		cout << "Wygrywa gracz " << nick1 << "!" << endl;
	}
	else if (p == 2)
	{
		cout << "Wygrywa bot! " << endl;
	}
	cout << endl;
	cout << "Plansza gracza " << nick1 << ":" << endl;
	wyswietlenie_planszy(plansza, k, w);
	cout << endl;
	cout << "Plansza bota " << endl;
	wyswietlenie_planszy(plansza2, k, w);


	zwalnianie_pamieci2D(plansza, k, w);
	zwalnianie_pamieci2D(plansza2, k, w);
	system("pause");
}

int** uzupelnij_dane_bota(int** plansza, int k, int w, int maszty, int os, int& max)
{
	max = 0;
	srand(time(NULL));
	int warunek = 0;
	struct statek sta;

	do
	{


		sta.maszty = maszty;

		sta.X = rand() % k;
		if (sta.X >= k || sta.X < 0)
		{

			continue;
		}
		sta.Y = rand() % w;
		if (sta.Y >= w || sta.Y < 0)
		{

			continue;
		}

		if (sta.maszty != 1)
		{

			sta.kierunek = (rand() % 4) + 1;

			warunek = 0;

			switch (sta.kierunek)
			{
			case 1:
				if (sta.X - sta.maszty >= 0)
					warunek = 1;
				break;
			case 2:
				if (sta.X + sta.maszty <= k)
					warunek = 1;
				break;
			case 3:
				if (sta.Y - sta.maszty >= 0)
					warunek = 1;
				break;
			case 4:
				if (sta.Y + sta.maszty <= w)
					warunek = 1;
				break;
			}

			if (warunek == 0)
			{
				continue;
			}

			for (int i = 0; i < sta.maszty; i++)
			{
				warunek = 0;

				if (sta.kierunek == 1)
					if (plansza[sta.X - i][sta.Y] == 0)
						warunek = 1;
				if (sta.kierunek == 2)
					if (plansza[sta.X + i][sta.Y] == 0)
						warunek = 1;
				if (sta.kierunek == 3)
					if (plansza[sta.X][sta.Y - i] == 0)
						warunek = 1;
				if (sta.kierunek == 4)
					if (plansza[sta.X][sta.Y + i] == 0)
						warunek = 1;

				if (warunek == 0)
				{
					max++;
					if (max > 100) {
						max = -1;
						return plansza;
					}
					break;
				}
			}

			if (warunek == 0)
			{
				continue;
			}

			for (int i = 0; i < sta.maszty; i++)
			{
				if (sta.kierunek == 1)
					plansza[sta.X - i][sta.Y] = os;
				if (sta.kierunek == 2)
					plansza[sta.X + i][sta.Y] = os;
				if (sta.kierunek == 3)
					plansza[sta.X][sta.Y - i] = os;
				if (sta.kierunek == 4)
					plansza[sta.X][sta.Y + i] = os;
			}
		}
		else
		{
			if (plansza[sta.X][sta.Y] != 0)
			{
				continue;
			}
			plansza[sta.X][sta.Y] = os;
		}
		sta.maszty = 0;
	} while (sta.maszty != 0);

	return plansza;
}

void wlasna_gra_z_botem()
{
	int maszty = 0;
	int w, k;

	int i = 0;
	int warunek = 0;
	int trudnosc = 1;
	system("cls");
	do
	{
		if (trudnosc != 1 && trudnosc != 2 && trudnosc != 3)
			cout << "Bledny wybor, sprobuj jeszcze raz!" << endl;

		cout << "Podaj poziom trudnosci bota:" << endl;
		cout << "1 - latwy;" << endl;
		cout << "2 - sredni;" << endl;
		cout << "3 - trudny." << endl;
		czyint(trudnosc);
		system("cls");

	} while (trudnosc != 1 && trudnosc != 2 && trudnosc != 3);
	cout << "Podaj liczbe kolumn planszy: ";
	czyint(k);
	cout << "Podaj liczbe wierszy planszy: ";
	czyint(w);

	int** plansza = NULL;
	plansza = plansza1(k, w, plansza);
	system("cls");
	string nick1;
	int max = 0, min = 1000;
	plansza = uzupelnij_dane(plansza, k, w, nick1);
	int** plansza2 = NULL;
	plansza2 = plansza1(k, w, plansza2);

	for (int f = 1; true; f++)
	{

		for (int i = 0; i < w; i++)
		{

			for (int j = 0; j < k; j++)
			{

				if (plansza[j][i] == f)
				{
					maszty++;
				}
			}
		}

		if (maszty == 0)
			break;
		plansza2 = uzupelnij_dane_bota(plansza2, k, w, maszty, f, max);
		if (min > maszty && maszty != 0)
			min = maszty;
		if (max == -1)
			f = 0;
		maszty = 0;
	}
	wyswietlenie_planszy(plansza, k, w);
	cout << endl << endl;
	wyswietlenie_planszy(plansza2, k, w);
	system("cls");
	cout << "Czy chcesz wlaczyc modyfikacje ?" << endl;
	cout << "[1] - TAK" << endl;
	cout << "[2] - NIE" << endl;
	int mod;
	czyint(mod);
	if (mod == 1)
		modyfikacje();


	system("cls");
	cout << "Gra wystartowala!" << endl;
	int p = przebieg_gry_z_botem(plansza, plansza2, k, w, nick1, trudnosc, min);
	if (p == 1)
	{
		cout << "Wygrywa gracz " << nick1 << "!" << endl;
	}
	else if (p == 2)
	{
		cout << "Wygrywa bot! " << endl;
	}
	else if (p == 3)
	{
		cout << "Remis !" << endl;
	}
	cout << endl;
	cout << "Plansza gracza " << nick1 << ":" << endl;
	wyswietlenie_planszy(plansza, k, w);
	cout << endl;
	cout << "Plansza bota " << endl;
	wyswietlenie_planszy(plansza2, k, w);


	zwalnianie_pamieci2D(plansza, k, w);
	zwalnianie_pamieci2D(plansza2, k, w);
	system("pause");
}

int przebieg_gry_z_botem(int** plansza, int** plansza2, int k, int w, string nick1, int trudnosc, int min)
{
	srand(time(NULL));
	int licznik = 0;
	int x2 = -1, y2 = -1, z[4] = { 0 };
	int ruchy = -1;
	int kierunekb = -1;
	int trafiony = 0;
	int wybor, y;
	int x;
	int xb = -1, yb = 1;
	int koniec, blad;
	int** plansza1_wyswietlenie = NULL;
	plansza1_wyswietlenie = plansza1(k, w, plansza1_wyswietlenie);
	int** plansza2_wyswietlenie = NULL;
	plansza2_wyswietlenie = plansza1(k, w, plansza2_wyswietlenie);
	if (zmienna.war == 1)
	{
		war(plansza, plansza2, k, w, bomba);
		war(plansza, plansza2, k, w, tarcza);
	}
	do
	{
		if (zmienna.armagedon == 1)
		{
			koniec = 1;
			int ww = 0;
			armagedon(plansza, plansza1_wyswietlenie, plansza2, plansza2_wyswietlenie, k, w);
			if (k == 1 && w == 1)
			{
				system("cls");
				koniec = 3;
				break;
			}
			for (int i = 0; i < k; i++)
			{
				for (int j = 0; j < w; j++)
				{
					if (plansza[i][j] > 0)
						koniec = 0;
				}
			}
			ww = koniec;
			koniec = 2;
			for (int i = 0; i < k; i++)
			{
				for (int j = 0; j < w; j++)
				{
					if (plansza2[i][j] > 0)
					{

						koniec = 0;

					}

				}
			}
			if (koniec == 0)
			{
				koniec = ww;
			}
			else if (koniec == 2)
			{
				if (ww == 1)
				{
					koniec = 3;
				}
			}
			if (koniec != 0)
				break;
		}

		system("cls");

		do
		{
			koniec = 1;
			blad = 0;
			cout << "Ruch gracza " << nick1 << ":" << endl;
			do
			{
				cout << "Miejsca gdzie juz strzelales: " << endl;
				wyswietlenie_planszy(plansza1_wyswietlenie, k, w);
				cout << endl << endl;
				cout << "Twoja plansza: " << endl;
				wyswietlenie_planszy(plansza, k, w);
				cout << endl << endl;

				cout << "Prosze podac pierwsza wspolrzedna miejsca strzalu: ";
				czyint(wybor);


				cout << "Prosze podac druga wspolrzedna miejsca strzalu: ";
				czyint(y);
				x = wybor - 1;
				y--;
			} while (y >= w || y < 0 || x >= k || x < 0);
			if (plansza2[x][y] > 0)
			{
				cout << "Statek zostal trafiony!" << endl;

				int warunek = 0;
				int cyferka = plansza2[x][y];
				plansza2[x][y] *= -1;

				plansza1_wyswietlenie[x][y] = plansza2[x][y];
				for (int i = 0; i < k; i++)
				{
					for (int j = 0; j < w; j++)
					{
						if (plansza2[i][j] == cyferka)
							warunek = 1;
					}
				}

				if (warunek != 1)
				{
					cout << "Statkek zostal zatopiony!!!" << endl;
				}

				Sleep(2000);
				system("cls");
				for (int i = 0; i < k; i++)
				{
					for (int j = 0; j < w; j++)
					{
						if (plansza2[i][j] > 0)
							koniec = 0;
					}
				}
				if (koniec != 0)
					break;

				continue;
			}
			else if (plansza2[x][y] == bomba)
			{
				cout << "Udalo ci sie trafic w bombe!" << endl;
				bombaf(plansza2, plansza1_wyswietlenie, k, w, x, y);
				blad = 1;
				Sleep(2000);
				system("cls");
				continue;
			}
			else if (plansza2[x][y] == tarcza)
			{
				cout << "Niestety trafiles w tarcze, twoj strzal zostal odbity." << endl;
				blad = 1;
				if (plansza[x][y] == 0 || plansza[x][y] == bomba)
				{
					plansza[x][y] = ppudlo;
					plansza2_wyswietlenie[x][y] = ppudlo;
					plansza1_wyswietlenie[x][y] = ppudlo;
					plansza2[x][y] = ppudlo;

				}
				else if (plansza[x][y] > 0)
				{
					plansza[x][y] *= -1;
					plansza2_wyswietlenie[x][y] = plansza[x][y];
					plansza1_wyswietlenie[x][y] = plansza[x][y];

				}
				else if (plansza[x][y] == tarcza)
				{
					plansza2[x][y] = ppudlo;
					plansza1_wyswietlenie[x][y] = ppudlo;
					plansza2_wyswietlenie[x][y] = ppudlo;
					plansza[x][y] = ppudlo;
				}
				Sleep(2000);
				system("cls");
				continue;
			}
			else if (plansza2[x][y] < 0)
			{
				cout << "Oddales juz strzal w to miejsce, sprobuj ponownie." << endl;
				blad = 1;
				Sleep(2000);
				system("cls");
				continue;
			}
			else {

				plansza2[x][y] = ppudlo;
				plansza1_wyswietlenie[x][y] = ppudlo;
				cout << "Pudlo!!!" << endl;
				Sleep(2000);
				system("cls");

			}
			for (int i = 0; i < k; i++)
			{
				for (int j = 0; j < w; j++)
				{
					if (plansza2[i][j] > 0)
						koniec = 0;
				}
			}

		} while (plansza2[x][y] != ppudlo || blad);

		system("cls");

		if (koniec != 0)
		{
			koniec = 1;
			break;
		}




		do
		{
			koniec = 2;
			blad = 0;

			do
			{
				int p1 = -1, p2 = -1;
				licznik++;
				if (licznik == 100)
				{
					for (int i = 0; p1 != i; i++)
					{
						for (int j = 0; p2 = !2; j++)
						{
							if (plansza2[i][j] == 0)
							{
								p1 = i;
								p2 = j;
							}
						}
					}
					x = p1;
					y = p2;
					kierunekb = 0;
					z[0] = 0;
					z[1] = 0;
					z[2] = 0;
					z[3] = 0;
					trafiony = 0;
					ruchy = -1;
					licznik = 0;
				}
				if (trudnosc == 1)
				{
					x = (rand() % k);
					y = (rand() % w);
				}
				else if (trudnosc == 2)
				{

					int warunek = 0;
					if (trafiony != 0)
					{
						do
						{
							if (trafiony == 2)
							{
								x = x2;
								y = y2;
								do
								{
									kierunekb = (rand() % 4) + 1;
								} while (kierunekb == z[0] || kierunekb == z[2] || kierunekb == z[1] || kierunekb == z[3]);
							}
							else
							{
								if (ruchy <= 0)
									kierunekb = (rand() % 4) + 1;
							}

							switch (kierunekb)
							{
							case 1:
								if (x - 1 >= 0)
									warunek = 1;
								else
									kierunekb = (rand() % 4) + 1;

								break;
							case 2:
								if (x + 1 < k)
									warunek = 1;
								else
									kierunekb = (rand() % 4) + 1;
								break;
							case 3:
								if (y - 1 >= 0)
									warunek = 1;
								else
									kierunekb = (rand() % 4) + 1;
								break;
							case 4:
								if (y + 1 < w)
									warunek = 1;
								else
									kierunekb = (rand() % 4) + 1;
								break;
							}

						} while (warunek == 0);
						switch (kierunekb)
						{
						case 1:
							x--;
							break;
						case 2:
							x++;
							break;
						case 3:
							y--;
							break;
						case 4:
							y++;
							break;
						}
					}
					else
					{
						x = (rand() % k);
						y = (rand() % w);
					}
				}
				else if (trudnosc == 3)
				{

					int warunek = 0;
					if (trafiony != 0)
					{
						do
						{
							if (trafiony == 2)
							{
								x = x2;
								y = y2;
								do
								{
									kierunekb = (rand() % 4) + 1;
								} while (kierunekb == z[0] || kierunekb == z[2] || kierunekb == z[1] || kierunekb == z[3]);
							}
							else
							{
								if (ruchy <= 0)
									kierunekb = (rand() % 4) + 1;
							}

							switch (kierunekb)
							{
							case 1:
								if (x - 1 >= 0)
									warunek = 1;
								else
									kierunekb = (rand() % 4) + 1;

								break;
							case 2:
								if (x + 1 < k)
									warunek = 1;
								else
									kierunekb = (rand() % 4) + 1;
								break;
							case 3:
								if (y - 1 >= 0)
									warunek = 1;
								else
									kierunekb = (rand() % 4) + 1;
								break;
							case 4:
								if (y + 1 < w)
									warunek = 1;
								else
									kierunekb = (rand() % 4) + 1;
								break;
							}
						} while (warunek == 0);
						switch (kierunekb)
						{
						case 1:
							x--;
							break;
						case 2:
							x++;
							break;
						case 3:
							y--;
							break;
						case 4:
							y++;
							break;
						}
					}
					else
					{
						if (min == 1)
						{
							x = (rand() % k);
							y = (rand() % w);
						}
						else
						{
							x = xb;
							x = x + min;
							y = yb - 1;
							if (x > k)
							{
								yb++;
								y = yb - 1;
								x = (yb - 2) % min;
							}

							xb = x;
						}
					}
				}


			} while (y >= w || y < 0 || x >= k || x < 0);
			if (plansza[x][y] > 0)
			{
				if (trafiony == 0)
				{
					x2 = x;
					y2 = y;
				}
				ruchy++;

				trafiony = 1;
				int warunek = 0;
				int cyferka = plansza[x][y];
				plansza[x][y] *= -1;

				plansza2_wyswietlenie[x][y] = plansza[x][y];
				for (int i = 0; i < k; i++)
				{
					for (int j = 0; j < w; j++)
					{
						if (plansza[i][j] == cyferka)
							warunek = 1;
					}
				}

				if (warunek != 1)
				{
					z[0] = 0;
					z[1] = 0;
					z[2] = 0;
					z[3] = 0;
					trafiony = 0;
					ruchy = -1;
				}



				for (int i = 0; i < k; i++)
				{
					for (int j = 0; j < w; j++)
					{
						if (plansza[i][j] > 0)
							koniec = 0;
					}
				}
				if (koniec != 0)
					break;

				continue;
			}
			else if (plansza[x][y] == bomba)
			{

				bombaf(plansza, plansza2_wyswietlenie, k, w, x, y);
				blad = 1;

				continue;
			}
			else if (plansza[x][y] == tarcza)
			{

				blad = 1;
				if (plansza2[x][y] == 0 || plansza2[x][y] == bomba)
				{
					plansza2[x][y] = ppudlo;
					plansza1_wyswietlenie[x][y] = ppudlo;
					plansza2_wyswietlenie[x][y] = ppudlo;
					plansza[x][y] = ppudlo;
				}
				else if (plansza2[x][y] > 0)
				{
					plansza2[x][y] *= -1;
					plansza1_wyswietlenie[x][y] = plansza2[x][y];
					plansza2_wyswietlenie[x][y] = plansza2[x][y];

				}
				else if (plansza2[x][y] == tarcza)
				{
					plansza[x][y] = ppudlo;
					plansza2_wyswietlenie[x][y] = ppudlo;
					plansza1_wyswietlenie[x][y] = ppudlo;
					plansza2[x][y] = ppudlo;
				}
				continue;
			}
			else if (plansza[x][y] < 0)
			{

				blad = 1;
				if (trafiony >= 1)
				{
					ruchy = 0;
					x = x2;
					y = y2;
				}
				continue;
			}
			else
			{
				plansza[x][y] = ppudlo;
				plansza2_wyswietlenie[x][y] = ppudlo;
				if (trafiony >= 1)
				{
					z[ruchy % 4] = kierunekb;
				}

				if (trafiony == 1)
					trafiony = 2;
			}

			for (int i = 0; i < k; i++)
			{
				for (int j = 0; j < w; j++)
				{
					if (plansza2[i][j] > 0)
						koniec = 0;
				}
			}

		} while (plansza[x][y] != ppudlo || blad);

		if (koniec != 0)
			koniec = 2;

	} while (koniec == 0);


	zwalnianie_pamieci2D(plansza1_wyswietlenie, k, w);
	zwalnianie_pamieci2D(plansza2_wyswietlenie, k, w);
	return koniec;
}

void menu_dwoch_uzytkownikow()
{
	int a;
	do
	{

		system("cls");
		cout << "Wybierz opcje:" << endl;
		cout << "[0] Wyjscie" << endl;
		cout << "[1] Szybka gra." << endl;
		cout << "[2] Wlasna gra." << endl;


		czyint(a);

		switch (a)
		{
		case 0:
			return;
		case 1:
			szybka_gra();
			break;

		case 2:
			menu_dwoch_uzytkonikow_wlasna_gra();
			break;
		default:
			cout << "Nie ma takiej opcji, sprobuj ponownie" << endl;
			Sleep(2000);
			a = -1;
		}
	} while (a == -1);
}

void szybka_gra()
{
	int w = 10, k = 10;
	int i = 0;
	int warunek = 0;
	system("cls");
	string nick1 = "Gracz 1.", nick2 = "Gracz 2.";

	int** plansza = NULL;
	plansza = plansza1(k, w, plansza);
	plansza = uzupelnij_dane_r(plansza, k, w);

	int** plansza2 = NULL;
	plansza2 = plansza1(k, w, plansza2);
	plansza2 = uzupelnij_dane_r(plansza2, k, w);



	cout << "Gra wystartowala!" << endl;
	int p = przebieg_gry(plansza, plansza2, k, w, nick1, nick2);
	if (p == 1)
	{
		cout << "Wygrywa gracz " << nick1 << "!" << endl;
	}
	else if (p == 2)
	{
		cout << "Wygrywa gracz " << nick2 << "!" << endl;
	}
	else if (p == 3)
	{
		cout << "Remis !" << endl;
	}
	cout << endl;
	cout << "Plansza gracza " << nick1 << ":" << endl;
	wyswietlenie_planszy(plansza, k, w);
	cout << endl;
	cout << "Plansza gracza " << nick2 << ":" << endl;
	wyswietlenie_planszy(plansza2, k, w);


	zwalnianie_pamieci2D(plansza, k, w);
	zwalnianie_pamieci2D(plansza2, k, w);
	system("pause");
}

int** uzupelnij_dane(int** plansza, int k, int w, string& nick1)
{
	int licznik = 0;
	int warunek = 0;
	struct statek sta;
	int os = 0;
	cout << "Podaj swoj nick: ";
	cin >> nick1;

	do
	{

		system("cls");
		cout << "Gracz " << nick1 << ":" << endl << endl;
		wyswietlenie_planszy(plansza, k, w);
		cout << endl;
		do
		{
			cout << "Podaj ilosc masztow (0 - konczy wypisywanie): ";
			czyint(sta.maszty);

			if (sta.maszty != 0)
				licznik = 1;

			if (licznik == 0)
				cout << "Nie podales jeszcze zadnego statku! Sprobuj ponownie." << endl;
		} while (!licznik);
		if (sta.maszty == 0)
			break;
		if (sta.maszty > k && sta.maszty > w)
		{

			cout << "Bledne dane! Sprobuj jeszcze raz!" << endl << endl;
			Sleep(2000);
			continue;
		}
		cout << "Podaj wspolzedna X tego statku:";
		czyint(sta.X);
		sta.X--;
		if (sta.X >= k || sta.X < 0)
		{

			cout << "Bledne dane! Sprobuj jeszcze raz!" << endl << endl;
			Sleep(2000);
			continue;
		}
		cout << "Podaj wspolzedna Y tego statku:";
		czyint(sta.Y);
		sta.Y--;
		if (sta.Y >= w || sta.Y < 0)
		{

			cout << "Bledne dane! Sprobuj jeszcze raz!" << endl << endl;
			Sleep(2000);
			continue;
		}
		if (sta.maszty != 1)
		{
			cout << "Podaj w ktorym kierunku ma lezec statek:" << endl;
			cout << "1.W lewo." << endl;
			cout << "2.W prawo." << endl;
			cout << "3.W gore." << endl;
			cout << "4.W dol." << endl;
			czyint(sta.kierunek);
			warunek = 0;
			switch (sta.kierunek)
			{
			case 1:
				if (sta.X - sta.maszty >= -1)
					warunek = 1;
				break;
			case 2:
				if (sta.X + sta.maszty <= k)
					warunek = 1;
				break;
			case 3:
				if (sta.Y - sta.maszty >= -1)
					warunek = 1;
				break;
			case 4:
				if (sta.Y + sta.maszty <= w)
					warunek = 1;
				break;
			}
			if (warunek == 0)
			{
				cout << "Bledne dane! Sprobuj jeszcze raz!" << endl << endl;
				Sleep(2000);
				continue;
			}

			for (int i = 0; i < sta.maszty; i++)
			{
				warunek = 0;

				if (sta.kierunek == 1)
					if (plansza[sta.X - i][sta.Y] == 0)
						warunek = 1;
				if (sta.kierunek == 2)
					if (plansza[sta.X + i][sta.Y] == 0)
						warunek = 1;
				if (sta.kierunek == 3)
					if (plansza[sta.X][sta.Y - i] == 0)
						warunek = 1;
				if (sta.kierunek == 4)
					if (plansza[sta.X][sta.Y + i] == 0)
						warunek = 1;
				if (warunek == 0)
					break;
			}
			if (warunek == 0)
			{
				cout << "Bledne dane! Sprobuj jeszcze raz!" << endl << endl;
				Sleep(2000);
				continue;
			}
			os++;
			for (int i = 0; i < sta.maszty; i++)
			{
				if (sta.kierunek == 1)
					plansza[sta.X - i][sta.Y] = os;
				if (sta.kierunek == 2)
					plansza[sta.X + i][sta.Y] = os;
				if (sta.kierunek == 3)
					plansza[sta.X][sta.Y - i] = os;
				if (sta.kierunek == 4)
					plansza[sta.X][sta.Y + i] = os;
			}
		}
		else
		{
			if (plansza[sta.X][sta.Y] != 0)
			{
				cout << "Bledne dane! Sprobuj jeszcze raz!" << endl << endl;
				Sleep(2000);
				continue;
			}
			os++;
			plansza[sta.X][sta.Y] = os;
		}

	} while (sta.maszty != 0);
	return plansza;
}

int** uzupelnij_dane_r(int** plansza, int k, int w)
{
	srand(time(NULL));
	int i = 0;
	int warunek = 0;
	struct statek sta;
	int os = 0;
	for (int i = 0; i < 10; i++)
	{
		if (i < 3)
		{
			sta.maszty = 2;
		}
		else if (i < 6)
		{
			sta.maszty = 3;
		}
		else if (i < 8)
		{
			sta.maszty = 4;
		}
		else
		{
			sta.maszty = 5;
		}



		sta.X = (rand() % 10);
		sta.Y = (rand() % 10);
		sta.kierunek = (rand() % 4) + 1;
		//cout << sta.X << sta.Y << sta.kierunek;
		//system("pause");

		warunek = 0;
		switch (sta.kierunek)
		{
		case 1:
			if (sta.X - sta.maszty >= -1)
				warunek = 1;
			break;
		case 2:
			if (sta.X + sta.maszty <= k)
				warunek = 1;
			break;
		case 3:
			if (sta.Y - sta.maszty >= -1)
				warunek = 1;
			break;
		case 4:
			if (sta.Y + sta.maszty <= w)
				warunek = 1;
			break;
		}
		if (warunek == 0)
		{
			i--;
			continue;
		}
		for (int i = 0; i < sta.maszty; i++)
		{
			warunek = 0;

			if (sta.kierunek == 1)
				if (plansza[sta.X - i][sta.Y] == 0)
					warunek = 1;
			if (sta.kierunek == 2)
				if (plansza[sta.X + i][sta.Y] == 0)
					warunek = 1;
			if (sta.kierunek == 3)
				if (plansza[sta.X][sta.Y - i] == 0)
					warunek = 1;
			if (sta.kierunek == 4)
				if (plansza[sta.X][sta.Y + i] == 0)
					warunek = 1;
			if (warunek == 0)
				break;
		}
		if (warunek == 0)
		{
			i--;
			continue;
		}
		os++;
		for (int i = 0; i < sta.maszty; i++)
		{
			if (sta.kierunek == 1)
				plansza[sta.X - i][sta.Y] = os;
			if (sta.kierunek == 2)
				plansza[sta.X + i][sta.Y] = os;
			if (sta.kierunek == 3)
				plansza[sta.X][sta.Y - i] = os;
			if (sta.kierunek == 4)
				plansza[sta.X][sta.Y + i] = os;
		}
	}
	return plansza;
}

void menu_dwoch_uzytkonikow_wlasna_gra()
{
	int w, k;
	int i = 0;
	int warunek = 0;
	system("cls");
	cout << "Podaj liczbe kolumn planszy: ";
	czyint(k);
	cout << "Podaj liczbe wierszy planszy: ";
	czyint(w);

	int** plansza = NULL;
	plansza = plansza1(k, w, plansza);
	system("cls");
	cout << "Pierwszy gracz: " << endl;
	string nick1, nick2;
	plansza = uzupelnij_dane(plansza, k, w, nick1);

	int** plansza2 = NULL;
	plansza2 = plansza1(k, w, plansza2);
	system("cls");
	cout << "Drugi gracz: " << endl;
	plansza2 = uzupelnij_dane(plansza2, k, w, nick2);


	system("cls");
	cout << "Czy chcesz wlaczyc modyfikacje ?" << endl;
	cout << "[1] - TAK" << endl;
	cout << "[2] - NIE" << endl;
	int mod;
	czyint(mod);
	if (mod == 1)
		modyfikacje();
	system("cls");
	cout << "Gra wystartowala!" << endl;
	int p = przebieg_gry(plansza, plansza2, k, w, nick1, nick2);
	if (p == 1)
	{
		cout << "Wygrywa gracz " << nick1 << "!" << endl;
	}
	else if (p == 2)
	{
		cout << "Wygrywa gracz " << nick2 << "!" << endl;
	}
	else if (p == 3)
	{
		cout << "Remis ! " << endl;
	}
	cout << endl;
	cout << "Plansza gracza " << nick1 << ":" << endl;
	wyswietlenie_planszy(plansza, k, w);
	cout << endl;
	cout << "Plansza gracza " << nick2 << ":" << endl;
	wyswietlenie_planszy(plansza2, k, w);


	zwalnianie_pamieci2D(plansza, k, w);
	zwalnianie_pamieci2D(plansza2, k, w);
	system("pause");
}

int przebieg_gry(int** plansza, int** plansza2, int k, int w, string nick1, string nick2)
{
	int wybor, y;
	int x;
	int koniec, blad;
	int** plansza1_wyswietlenie = NULL;
	plansza1_wyswietlenie = plansza1(k, w, plansza1_wyswietlenie);
	int** plansza2_wyswietlenie = NULL;
	plansza2_wyswietlenie = plansza1(k, w, plansza2_wyswietlenie);
	if (zmienna.war == 1)
	{
		war(plansza, plansza2, k, w, bomba);
		war(plansza, plansza2, k, w, tarcza);
	}
	do
	{
		if (zmienna.armagedon == 1)
		{
			koniec = 1;
			int ww = 0;
			armagedon(plansza, plansza1_wyswietlenie, plansza2, plansza2_wyswietlenie, k, w);
			if (k == 1 && w == 1)
			{
				system("cls");
				koniec = 3;
				break;
			}
			for (int i = 0; i < k; i++)
			{
				for (int j = 0; j < w; j++)
				{
					if (plansza[i][j] > 0)
						koniec = 0;
				}
			}
			ww = koniec;
			koniec = 2;
			for (int i = 0; i < k; i++)
			{
				for (int j = 0; j < w; j++)
				{
					if (plansza2[i][j] > 0)
					{

						koniec = 0;

					}

				}
			}
			if (koniec == 0)
			{
				koniec = ww;
			}
			else if (koniec == 2)
			{
				if (ww == 1)
				{
					koniec = 3;
				}
			}
			if (koniec != 0)
				break;
		}
		system("cls");
		do
		{
			koniec = 1;
			blad = 0;


			cout << "Ruch gracza " << nick1 << ":" << endl;
			do
			{
				cout << "Miejsca gdzie juz strzelales: " << endl;
				wyswietlenie_planszy(plansza1_wyswietlenie, k, w);
				cout << endl << endl;

				do
				{
					cout << "Prosze podac pierwsza wspolrzedna miejsca strzalu(-1 wyswietla twoja plansze):";
					czyintmin(wybor);
					if (wybor == (-1))
					{
						wyswietlenie_planszy(plansza, k, w);
					}
				} while (wybor == (-1));
				cout << "Prosze podac druga wspolrzedna miejsca strzalu: ";
				czyint(y);
				x = wybor - 1;
				y--;
			} while (y >= w || y < 0 || x >= k || x < 0);
			if (plansza2[x][y] > 0)
			{
				cout << "Statek zostal trafiony!" << endl;

				int warunek = 0;
				int cyferka = plansza2[x][y];
				plansza2[x][y] *= -1;

				plansza1_wyswietlenie[x][y] = plansza2[x][y];
				for (int i = 0; i < k; i++)
				{
					for (int j = 0; j < w; j++)
					{
						if (plansza2[i][j] == cyferka)
							warunek = 1;
					}
				}

				if (warunek != 1)
				{
					cout << "Statkek zostal zatopiony!!!" << endl;
				}

				Sleep(2000);
				system("cls");
				for (int i = 0; i < k; i++)
				{
					for (int j = 0; j < w; j++)
					{
						if (plansza2[i][j] > 0)
							koniec = 0;
					}
				}
				if (koniec != 0)
					break;

				continue;
			}
			else if (plansza2[x][y] == bomba)
			{
				cout << "Udalo ci sie trafic w bombe!" << endl;
				bombaf(plansza2, plansza1_wyswietlenie, k, w, x, y);
				blad = 1;
				Sleep(2000);
				system("cls");
				continue;
			}
			else if (plansza2[x][y] == tarcza)
			{
				cout << "Niestety trafiles w tarcze, twoj strzal zostal odbity." << endl;
				blad = 1;
				if (plansza[x][y] == 0 || plansza[x][y] == bomba)
				{
					plansza[x][y] = ppudlo;
					plansza2_wyswietlenie[x][y] = ppudlo;
					plansza1_wyswietlenie[x][y] = ppudlo;
					plansza2[x][y] = ppudlo;

				}
				else if (plansza[x][y] > 0)
				{
					plansza[x][y] *= -1;
					plansza2_wyswietlenie[x][y] = plansza[x][y];
					plansza1_wyswietlenie[x][y] = plansza[x][y];

				}
				else if (plansza[x][y] == tarcza)
				{
					plansza2[x][y] = ppudlo;
					plansza1_wyswietlenie[x][y] = ppudlo;
					plansza2_wyswietlenie[x][y] = ppudlo;
					plansza[x][y] = ppudlo;
				}
				Sleep(2000);
				system("cls");
				continue;
			}
			else if (plansza2[x][y] < 0)
			{
				cout << "Oddales juz strzal w to miejsce, sprobuj ponownie." << endl;
				blad = 1;
				Sleep(2000);
				system("cls");
				continue;
			}
			else {

				plansza2[x][y] = ppudlo;
				plansza1_wyswietlenie[x][y] = ppudlo;
				cout << "Pudlo!!!" << endl;
				Sleep(2000);
				system("cls");

			}
			for (int i = 0; i < k; i++)
			{
				for (int j = 0; j < w; j++)
				{
					if (plansza2[i][j] > 0)
						koniec = 0;
				}
			}

		} while (plansza2[x][y] != ppudlo || blad);

		system("cls");

		if (koniec != 0)
		{
			koniec = 1;
			break;
		}

		do
		{
			koniec = 2;
			blad = 0;
			cout << "Ruch gracza " << nick2 << ":" << endl;
			do
			{
				cout << "Miejsca gdzie juz strzelales: " << endl;
				wyswietlenie_planszy(plansza2_wyswietlenie, k, w);
				cout << endl << endl;

				do
				{
					cout << "Prosze podac pierwsza wspolrzedna miejsca strzalu(-1 wyswietla twoja plansze):";
					czyintmin(wybor);
					if (wybor == (-1))
					{
						wyswietlenie_planszy(plansza2, k, w);
					}
				} while (wybor == (-1));
				x = wybor;
				cout << "Prosze podac druga wspolrzedna miejsca strzalu: ";
				czyint(y);
				x = wybor - 1;
				y--;
			} while (y >= w || y < 0 || x >= k || x < 0);
			if (plansza[x][y] > 0)
			{
				cout << "Statek zostal trafiony!" << endl;
				int warunek = 0;
				int cyferka = plansza[x][y];
				plansza[x][y] *= -1;

				plansza2_wyswietlenie[x][y] = plansza[x][y];
				for (int i = 0; i < k; i++)
				{
					for (int j = 0; j < w; j++)
					{
						if (plansza[i][j] == cyferka)
							warunek = 1;
					}
				}

				if (warunek != 1)
				{
					cout << "Statkek zostal zatopiony!!!" << endl;
				}

				Sleep(2000);
				system("cls");

				for (int i = 0; i < k; i++)
				{
					for (int j = 0; j < w; j++)
					{
						if (plansza[i][j] > 0)
							koniec = 0;
					}
				}
				if (koniec != 0)
					break;

				continue;
			}
			else if (plansza[x][y] == bomba)
			{
				cout << "Udalo ci sie trafic w bombe!" << endl;
				bombaf(plansza, plansza2_wyswietlenie, k, w, x, y);
				blad = 1;
				Sleep(2000);
				system("cls");
				continue;
			}
			else if (plansza[x][y] == tarcza)
			{
				cout << "Niestety trafiles w tarcze, twoj strzal zostal odbity." << endl;
				blad = 1;
				if (plansza2[x][y] == 0 || plansza2[x][y] == bomba)
				{
					plansza2[x][y] = ppudlo;
					plansza1_wyswietlenie[x][y] = ppudlo;
					plansza2_wyswietlenie[x][y] = ppudlo;
					plansza[x][y] = ppudlo;
				}
				else if (plansza2[x][y] > 0)
				{
					plansza2[x][y] *= -1;
					plansza1_wyswietlenie[x][y] = plansza2[x][y];
					plansza2_wyswietlenie[x][y] = plansza2[x][y];

				}
				else if (plansza2[x][y] == tarcza)
				{
					plansza[x][y] = ppudlo;
					plansza2_wyswietlenie[x][y] = ppudlo;
					plansza1_wyswietlenie[x][y] = ppudlo;
					plansza2[x][y] = ppudlo;
				}
				Sleep(2000);
				system("cls");
				continue;
			}
			else if (plansza[x][y] < 0)
			{
				cout << "Oddales juz strzal w to miejsce, sprobuj ponownie." << endl;
				blad = 1;
				Sleep(2000);
				system("cls");
				continue;
			}
			else
			{
				plansza[x][y] = ppudlo;
				plansza2_wyswietlenie[x][y] = ppudlo;
				cout << "Pudlo!!!" << endl;
				Sleep(2000);
				system("cls");
			}

			for (int i = 0; i < k; i++)
			{
				for (int j = 0; j < w; j++)
				{
					if (plansza2[i][j] > 0)
						koniec = 0;
				}
			}

		} while (plansza[x][y] != ppudlo || blad);

		if (koniec != 0)
			koniec = 2;

	} while (koniec == 0);


	zwalnianie_pamieci2D(plansza1_wyswietlenie, k, w);
	zwalnianie_pamieci2D(plansza2_wyswietlenie, k, w);
	return koniec;
}

void wyswietlenie_planszy(int** plansza, int k, int w)
{

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < k; j++)
		{

			if (plansza[j][i] == ppudlo)
			{
				cout << "|!|\t";
			}
			else if (plansza[j][i] == bomba)
			{
				cout << "|B|\t";
			}
			else if (plansza[j][i] == tarcza)
			{
				cout << "|T|\t";
			}
			else if (plansza[j][i] < 0)
			{
				cout << "|X|\t";
			}
			else if (plansza[j][i] == 0)
			{
				cout << "| |\t";
			}
			else
			{
				cout << "|" << plansza[j][i] << "|\t";
			}
		}
		cout << endl << endl;
	}
	legenda();
}

int** plansza1(int x, int y, int** plansza3)
{
	plansza3 = new int* [x];
	for (int i = 0; i < x; i++)
	{
		plansza3[i] = new int[y];
	}
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			plansza3[i][j] = 0;
		}
	}

	return plansza3;
}

void zwalnianie_pamieci2D(int** plansza, int k, int  w)
{
	for (int i = 0; i < k; i++)
	{
		delete[] plansza[i];
	}
	delete plansza;
}


int main()
{
	int x, warunek = 1;
	do
	{
		zmienna = { 0,0 };
		system("cls");
		cout << "Witaj w grze STATKI!" << endl;
		cout << "Wybierz opcje: " << endl;
		cout << "[1] Gra z botem. " << endl;
		cout << "[2] Gra dwoch uzytkownikow. " << endl;
		cout << "[3] Koniec gry. " << endl;

		czyint(x);
		switch (x)
		{
		case 1:
			menu_z_botem();
			break;

		case 2:
			menu_dwoch_uzytkownikow();
			break;

		case 3:
			warunek = 0;
			break;

		default:
			system("cls");
			cout << "Nie ma takiej opcji w menu." << endl;
			Sleep(2000);
		}
	} while (warunek);
	return 0;
}
