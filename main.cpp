#include <iostream>
#include <conio.h>
#include <time.h>
#include "ui.h"
#include "swiat.h"
#include "swiatManager.h"

#define LICZBA_GATUNKOW 10
#define WYJSCIE 113 // Q
#define ZAPISZ 115 // S
#define NOWA_GRA 110 // N
#define WCZYTAJ 108 //  L
#define KOLEJNA_TURA 13 // ENTER
#define ILE_PROCENT_ZWIERZAT 50
#define MINIMALNA_WIELKOSC_PLANSZY 100

using namespace std;

int main()
{
	cout << "\033[0m";
	cout << "\033[40m";
	srand(time(NULL));
	Swiat* nowySwiat = NULL;
	SwiatManager* generator = NULL;
	UI* ui = NULL;
	unsigned char wcisnietyKlawisz = NULL;
	bool pomyslnieWczytanoGre = false;
	int szerokosc;
	int wysokosc;
	int liczbaZwierzatJednegoGatunku = 0;
	system("cls");

	ui->narysujDrzewo();
	ui->wypiszMenuGlowne();

	while (wcisnietyKlawisz != NOWA_GRA && pomyslnieWczytanoGre == false)
	{
		wcisnietyKlawisz = _getch();
		switch (wcisnietyKlawisz)
		{
		case NOWA_GRA:
			do
			{
				ui->wyborWymiaruPlanszy();
				cin >> szerokosc >> wysokosc;
				system("cls");
				if (szerokosc * wysokosc < MINIMALNA_WIELKOSC_PLANSZY){

					ui->komunikatZaMalaPlansza(MINIMALNA_WIELKOSC_PLANSZY);
				}
			} while (szerokosc * wysokosc < MINIMALNA_WIELKOSC_PLANSZY); //powtarzamy dopoki gracz nie wybierze prawidlowego wymiaru

			nowySwiat = new Swiat(szerokosc, wysokosc);
			generator = new SwiatManager(nowySwiat);
			liczbaZwierzatJednegoGatunku = (szerokosc * wysokosc) / ILE_PROCENT_ZWIERZAT;
			generator->dodajOrganizmyDoNowegoSwiata(liczbaZwierzatJednegoGatunku);
			break;
		case WCZYTAJ:
			nowySwiat = new Swiat();
			generator = new SwiatManager(nowySwiat);
			if (generator->wczytajStanSwiata() == false)
			{
				ui->komunikatNieWczytanoGry();
				pomyslnieWczytanoGre = false;
			}
			else {
				pomyslnieWczytanoGre = true;
			}
			break;
		default:
			//wcisnieto nieprawidlowy klawisz - nic wiec nie robimy
			break;
		}
	}

	system("cls");
	nowySwiat->rysujSwiat();
	
	do
	{
		wcisnietyKlawisz = _getch();

		switch (wcisnietyKlawisz)
		{
			case ZAPISZ:
				generator->zapiszStanSwiata();
				break;
			case KOLEJNA_TURA:
				nowySwiat->wykonajTure();
				system("cls");
				nowySwiat->rysujSwiat();
				break;
			case NOWA_GRA:
				system("cls");
				do
				{
					ui->wyborWymiaruPlanszy();
					cin >> szerokosc >> wysokosc;
					system("cls");
				} while (szerokosc * wysokosc < (MINIMALNA_WIELKOSC_PLANSZY));

				nowySwiat = new Swiat(szerokosc, wysokosc);
				generator = new SwiatManager(nowySwiat);
				liczbaZwierzatJednegoGatunku = (szerokosc * wysokosc) / ILE_PROCENT_ZWIERZAT;
				generator->dodajOrganizmyDoNowegoSwiata(liczbaZwierzatJednegoGatunku);
				generator->dodajOrganizmyDoNowegoSwiata(liczbaZwierzatJednegoGatunku);
				system("cls");
				nowySwiat->rysujSwiat();
				break;
			default:
				//wcisnieto nieprawidlowy klawisz - nic wiec nie robimy
				break;
		}
	} while (wcisnietyKlawisz != WYJSCIE);


	//przy zakonczeniu programu przywracamy domyslne kolory konsoli
	cout << "\033[0m";
	return 0;
}