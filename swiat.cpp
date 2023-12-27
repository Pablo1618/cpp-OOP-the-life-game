#include <conio.h>
#include <string>

#include "organizm.h"
#include "czlowiek.h"
#include "swiat.h"
#include "zolw.h"
#include "antylopa.h"
#include "trawa.h"
#include "mlecz.h"
#include "guarana.h"
#include "wilczeJagody.h"
#include "barszczSosnowskiego.h"
#include "wilk.h"
#include "owca.h"
#include "lis.h"
#include "ui.h"

#define GORA 1
#define PRAWO 2
#define DOL 3
#define LEWO 4
#define STRZALKA_GORA 72
#define STRZALKA_DOL 80
#define STRZALKA_PRAWO 77
#define STRZALKA_LEWO 75

using namespace std;

Swiat::Swiat() : Swiat(100, 100)
{
	ui = NULL;
}

Swiat::Swiat(int szerokosc, int wysokosc)
{
	ui = NULL;
	this->szerokosc = szerokosc;
	this->wysokosc = wysokosc;
	this->liczbaOrganizmowDoroslych = 0;
	this->czyCzlowiekZyje = false;
	this->czlowiek = nullptr;
	this->komentarze = new string[ 4 * szerokosc * wysokosc];
	this->liczbaKomentarzy = 0;
	this->organizmy = new Organizm * [szerokosc * wysokosc];
	this->liczbaOrganizmow = 0;
	this->tura = 0;

	mapa = new Organizm** [wysokosc + 2];
	for (int y = 0; y < wysokosc + 2; y++)
	{
		mapa[y] = new Organizm * [szerokosc + 2] {nullptr};
	}

}

void Swiat::setTura(int tura)
{
	this->tura = tura;
}

void Swiat::setPoleMapy(int x, int y, Organizm* organizm)
{
	mapa[y][x] = organizm;
}

void Swiat::setRozmiarPlanszy(int szerokosc, int wysokosc)
{
	this->szerokosc = szerokosc;
	this->wysokosc = wysokosc;
}
void Swiat::setCzyCzlowiekZyje(bool opcja) {

	this->czyCzlowiekZyje = false;
}

void Swiat::nowyKomentarz(string komentarz)
{
	this->komentarze[liczbaKomentarzy] = komentarz;
	liczbaKomentarzy++;
}

int Swiat::getSzerokosc() const
{
	return szerokosc;
}

int Swiat::getWysokosc() const
{
	return wysokosc;
}

int Swiat::getLiczbaOrganizmow() const
{
	return liczbaOrganizmow;
}

int Swiat::getTura() const
{
	return tura;
}

Organizm* Swiat::getPoleMapy(int x, int y) const
{
	if ((x > 0) && (x < (szerokosc + 2)) && (y > 0) && (y < (wysokosc + 2)))
	{
		return mapa[y][x];
	}
	else {
		return nullptr;
	}
}

Organizm* Swiat::getOrganizm(int i) const
{
	return organizmy[i];
}

Czlowiek* Swiat::getCzlowiek() const
{
	return czlowiek;
}

void Swiat::dodajNowyOrganizm(Organizm* nowyOrganizm)
{
	if (mapa[nowyOrganizm->getY()][nowyOrganizm->getX()] == nullptr && liczbaOrganizmow < szerokosc*wysokosc)
	{
		int i = 0;
		Organizm* doPrzesuniecia;
		organizmy[liczbaOrganizmow] = nowyOrganizm;
		liczbaOrganizmow++;

		//szukamy pierwszego organizmu o mniejszej inicjatywie

		while (i < liczbaOrganizmow && organizmy[i]->getInicjatywa() >= nowyOrganizm->getInicjatywa())	{	i++;	}

		//przesuwamy elementy w tablicy tak aby nowyOrganizm byl w odpowiednim miejscu
		int g = liczbaOrganizmow - 2;
		while (g >= i)
		{
			doPrzesuniecia = organizmy[g];
			organizmy[g] = organizmy[g + 1];
			organizmy[g + 1] = doPrzesuniecia;
			g--;
		}

		nowyOrganizm->ustawOrganizmNaMapie();
		if(nowyOrganizm->getNazwa() == "Czlowiek")
		{
			czyCzlowiekZyje = true;
			czlowiek = dynamic_cast<Czlowiek*>(nowyOrganizm);
		}
		
		this->nowyKomentarz("[NOWY ORGANIZM] " + nowyOrganizm->getNazwa() + " [" + to_string(nowyOrganizm->getX()) + "," += to_string(nowyOrganizm->getY()) + "]");
	}
	else if (liczbaOrganizmow >= szerokosc * wysokosc)
	{
		this->nowyKomentarz("Osiagnieto limit liczby organizmow.");
	}
}

void Swiat::usunOrganizm(Organizm* organizmUsuwany)
{

	if (mapa[organizmUsuwany->getY()][organizmUsuwany->getX()] == organizmUsuwany)
	{
		mapa[organizmUsuwany->getY()][organizmUsuwany->getX()] = nullptr;
	}

	Organizm* doPrzesuniecia;
	for (int i = 0; i < liczbaOrganizmow; i++)
	{
		if (organizmy[i] == organizmUsuwany)
		{
			organizmy[i] = nullptr;
			int j = i;
			//ponizej przesuwamy elementy w tablicy, tak aby nie bylo w niej pustych miejsc
			while (j < liczbaOrganizmow - 1)
			{
				doPrzesuniecia = organizmy[j];
				organizmy[j] = organizmy[j + 1];
				organizmy[j + 1] = doPrzesuniecia;
				j++;
			}
			i = liczbaOrganizmow;
		}
	}
	liczbaOrganizmow--;
	liczbaOrganizmowDoroslych--;

	this->nowyKomentarz("[SMIERC] " + organizmUsuwany->getNazwa() + "[" + to_string(organizmUsuwany->getX()) + "," + to_string(organizmUsuwany->getY()) + "]");
	delete organizmUsuwany;
}

void Swiat::wykonajTure()
{

	bool graczRuszylCzlowiekiem = false;
	liczbaOrganizmowDoroslych = liczbaOrganizmow;
	if (czyCzlowiekZyje)
	{
		if (czlowiek->umiejetnoscWlaczona() == false && czlowiek->ileTurMineloUmiejetnosc() >= 5)
		{
			cout << "Umiejetnosc czlowieka dostepna - wcisnij 'U' aby aktywowac." << endl;
		}
		else if (czlowiek->umiejetnoscWlaczona() == true && czlowiek->ileTurMineloUmiejetnosc() >= 5)
		{
			cout << "Umiejetnosc czlowieka zostala dezaktywowana (minelo 5 tur)." << endl;
			czlowiek->dezaktywujUmiejetnosc();
		}
		cout << "Oczekiwanie na ruch postaci... (strzalki)";
	}

	if (czyCzlowiekZyje)
	{
		unsigned char znak = _getch();
		unsigned char setPoprzedniRuch = NULL;

		if (znak == 'u') {
			if (czlowiek->umiejetnoscWlaczona() == false && czlowiek->ileTurMineloUmiejetnosc() >= 5)
			{
				czlowiek->aktywujUmiejetnosc();
				setPoprzedniRuch = 0;
				graczRuszylCzlowiekiem = true;
			}
		}
		else {
			znak = _getch();
			if (znak == STRZALKA_GORA || znak == STRZALKA_DOL || znak == STRZALKA_PRAWO || znak == STRZALKA_LEWO) {
				graczRuszylCzlowiekiem = true;
				czlowiek->setPoprzedniRuch(znak);
			}
		}
	}
	if (graczRuszylCzlowiekiem || czyCzlowiekZyje == false)
	{
		symulacjaAkcjiOrganizmow();
	}
}

void Swiat::symulacjaAkcjiOrganizmow()
{
	Organizm* biezacyOrganizm;
	Organizm* atakowanyOrganizm;

	for (int i = 0; i < liczbaOrganizmowDoroslych; i++)
	{
		biezacyOrganizm = organizmy[i];
		biezacyOrganizm->akcja();
		atakowanyOrganizm = mapa[biezacyOrganizm->getY()][biezacyOrganizm->getX()];
		if (atakowanyOrganizm == nullptr || biezacyOrganizm->getOstatniRuch() == 0)
		{
			biezacyOrganizm->ustawOrganizmNaMapie();
		}
		else
		{
			atakowanyOrganizm->kolizja(biezacyOrganizm);
		}
	}

	if (czyCzlowiekZyje)
	{
		czlowiek->setIleTurMineloUmiejetnosc(czlowiek->ileTurMineloUmiejetnosc() + 1);
		if (czlowiek->umiejetnoscWlaczona() && czlowiek->ileTurMineloUmiejetnosc() < 5)
		{
			nowyKomentarz("[UMIEJETNOSC] Niesmiertelnosc gracza jest aktywna! Pozostalo: " + to_string(5 - czlowiek->ileTurMineloUmiejetnosc()) + " tur.");
		}
	}

	//zwiekszanie wieku kazdego organizmu
	for (int i = 0; i < liczbaOrganizmowDoroslych; i++)
	{
		biezacyOrganizm = organizmy[i];
		biezacyOrganizm->setWiek(biezacyOrganizm->getWiek() + 1);
	}

	tura++;
}

void Swiat::rysujSwiat()
{
	for (int i = 0; i < liczbaKomentarzy; i++)
	{
		cout << komentarze[i] << endl;
	}
	liczbaKomentarzy = 0;

	ui->narysujInfoTura(tura);

	for (int i = 0; i < liczbaOrganizmow; i++)
	{
		organizmy[i]->ustawOrganizmNaMapie();
	}

	for (int y = 0; y < (wysokosc + 2); y++) // +2 wynika z obramowania mapy (woda dookola wyspy)
	{
		for (int x = 0; x < (szerokosc + 2); x++)
		{
			if (getPoleMapy(x, y) == nullptr)
			{
				if ((x == 0) || (y == 0) || (x == szerokosc + 1) || (y == wysokosc + 1)) // po kolei: lewa, gorna, dolna, prawa
				{
					cout << "\033[46m";
					cout << ' ';
					cout << "\033[40m";
				}
				else {
					cout << "\033[43m";
					cout << ' ';
				}
			}
			else // na polu znajduje sie jakis organizm/roslina
			{
				char symbol = getPoleMapy(x, y)->getZnak();
				if (symbol == 'X') {
					cout << "\033[41m"; //pole na ktorym znajduje sie czlowiek jest wyswietlane w innym kolorze
					cout << symbol;
				}
				else {
					cout << "\033[43m";
					cout << symbol;
				}
			}
		}
		cout << endl;
	}
	cout << endl;
}

Swiat::~Swiat()
{
	delete[] organizmy;
	delete czlowiek;

	for (int y = 0; y < wysokosc; y++)
	{
		for (int x = 0; x < szerokosc; x++)
		{
			delete mapa[y];
		}
	}

	delete[] komentarze;

}