
#include <fstream> //do obslugi zapisu/wczytywania

#include "swiat.h"
#include "swiatManager.h"
#include "wilk.h"
#include "owca.h"
#include "lis.h"
#include "organizm.h"
#include "czlowiek.h"
#include "zolw.h"
#include "antylopa.h"
#include "trawa.h"
#include "wilczeJagody.h"
#include "mlecz.h"
#include "guarana.h"
#include "barszczSosnowskiego.h"

#define LICZBA_GATUNKOW 10

using namespace std;

SwiatManager::SwiatManager(Swiat* swiat)
{
	this->swiat = swiat;
}

void SwiatManager::losowanieWspolrzednych(bool** zajetePola, int szerokosc, int wysokosc, int* losowyX, int* losowyY) {
	do {
		*losowyX = rand() % szerokosc;
		*losowyY = rand() % wysokosc;
	} while (zajetePola[*losowyY][*losowyX] == true); //losujemy az znajdziemy pole puste

	zajetePola[*losowyY][*losowyX] = true;
}

void SwiatManager::dodajOrganizmyDoNowegoSwiata(int ileZwierzatJednegoGatunku)
{
	int losowyX, losowyY;
	int szerokosc = swiat->getSzerokosc();
	int wysokosc = swiat->getWysokosc();

	//tworzymy dwuwymiarowa tablice na zapisanie ktore pola zostaly juz zajete
	bool** zajetePola = new bool* [wysokosc];
	for (int i = 0; i < wysokosc; i++) {
		zajetePola[i] = new bool[szerokosc];
	}

	//spawnujemy zwierzeta i rosliny
	for (int i = 0; i < ileZwierzatJednegoGatunku; i++)
	{
		losowanieWspolrzednych(zajetePola, szerokosc, wysokosc, &losowyX, &losowyY);
		Organizm* wilk = new Wilk(losowyX, losowyY, swiat);
		swiat->dodajNowyOrganizm(wilk);

		losowanieWspolrzednych(zajetePola, szerokosc, wysokosc, &losowyX, &losowyY);
		Organizm* owca = new Owca(losowyX, losowyY, swiat);
		swiat->dodajNowyOrganizm(owca);

		losowanieWspolrzednych(zajetePola, szerokosc, wysokosc, &losowyX, &losowyY);
		Organizm* lis = new Lis(losowyX, losowyY, swiat);
		swiat->dodajNowyOrganizm(lis);

		losowanieWspolrzednych(zajetePola, szerokosc, wysokosc, &losowyX, &losowyY);
		Organizm* zolw = new Zolw(losowyX, losowyY, swiat);
		swiat->dodajNowyOrganizm(zolw);

		losowanieWspolrzednych(zajetePola, szerokosc, wysokosc, &losowyX, &losowyY);
		Organizm* antylopa = new Antylopa(losowyX, losowyY, swiat);
		swiat->dodajNowyOrganizm(antylopa);

		losowanieWspolrzednych(zajetePola, szerokosc, wysokosc, &losowyX, &losowyY);
		Organizm* trawa = new Trawa(losowyX, losowyY, swiat);
		swiat->dodajNowyOrganizm(trawa);

		losowanieWspolrzednych(zajetePola, szerokosc, wysokosc, &losowyX, &losowyY);
		Organizm* mlecz = new Mlecz(losowyX, losowyY, swiat);
		swiat->dodajNowyOrganizm(mlecz);

		losowanieWspolrzednych(zajetePola, szerokosc, wysokosc, &losowyX, &losowyY);
		Organizm* guarana = new Guarana(losowyX, losowyY, swiat);
		swiat->dodajNowyOrganizm(guarana);

		losowanieWspolrzednych(zajetePola, szerokosc, wysokosc, &losowyX, &losowyY);
		Organizm* jagoda = new WilczeJagody(losowyX, losowyY, swiat);
		swiat->dodajNowyOrganizm(jagoda);

		losowanieWspolrzednych(zajetePola, szerokosc, wysokosc, &losowyX, &losowyY);
		Organizm* barszcz = new BarszczSosnowskiego(losowyX, losowyY, swiat);
		swiat->dodajNowyOrganizm(barszcz);
	}

	//spawnujemy czlowieka
	losowanieWspolrzednych(zajetePola, szerokosc, wysokosc, &losowyX, &losowyY);
	Organizm* gracz = new Czlowiek(losowyX, losowyY, swiat);
	swiat->dodajNowyOrganizm(gracz);
}

bool SwiatManager::wczytajStanSwiata()
{
	string nazwa;
	ifstream odczytPliku("stan_wirtualnego_swiata.txt");
	if (odczytPliku.good() == true)
	{
		int szerokosc, wysokosc, liczbaOrganizmow, ktoraTura;
		odczytPliku >> ktoraTura >> szerokosc >> wysokosc >> liczbaOrganizmow;
		swiat->setRozmiarPlanszy(szerokosc, wysokosc);
		swiat->setTura(ktoraTura);
		int sila, inicjatywa, x, y, wiek, umiejetnoscAktywowana, turyZUmiejetnoscia;
		bool umiejetnoscZeWczytywania;

		for (int i = 0; i < liczbaOrganizmow; i++)
		{
			odczytPliku >> nazwa;

			odczytPliku >> sila >> inicjatywa >> x >> y >> wiek;
			if (nazwa == "Czlowiek")
			{
				odczytPliku >> umiejetnoscAktywowana >> turyZUmiejetnoscia;
				Organizm* wczytywanyOrganizm = new Czlowiek(x - 1, y - 1, swiat);
				wczytywanyOrganizm->setInicjatywa(inicjatywa);
				wczytywanyOrganizm->setWiek(wiek);
				wczytywanyOrganizm->setSila(sila);
				if (umiejetnoscAktywowana == false) {
					umiejetnoscZeWczytywania = false;
				}
				else if(umiejetnoscAktywowana == true){
					umiejetnoscZeWczytywania = true;
				}
				swiat->dodajNowyOrganizm(wczytywanyOrganizm);
				swiat->getCzlowiek()->setIleTurMineloUmiejetnosc(turyZUmiejetnoscia);
				swiat->getCzlowiek()->SetCzyUmiejetnoscAktywowana(umiejetnoscZeWczytywania);
			}
			else
			{
				wczytywanieDanychOrganizmu(nazwa, sila, inicjatywa, x - 1, y - 1, wiek);
			}
		}

		odczytPliku.close();
	}
	else
	{
		//nie istnieje zapis gry - zwracamy wiec false
		return false;
	}

	return true;
}

void SwiatManager::zapiszStanSwiata()
{
	ofstream zapisStanuSwiata("stan_wirtualnego_swiata.txt");

	zapisStanuSwiata << swiat->getTura() << " " << swiat->getSzerokosc() << " " << swiat->getWysokosc() << " " << swiat->getLiczbaOrganizmow() << endl;
	Organizm* organizm = nullptr;
	for (int g = 0; g < swiat->getLiczbaOrganizmow(); g++)
	{
		organizm = swiat->getOrganizm(g);
		zapisStanuSwiata << organizm->zapiszInfo() << endl;
	}

	zapisStanuSwiata.close();
	cout << "Pomyslnie zapisano stan wirtualnego swiata do pliku 'stan_wirtualnego_swiata.txt'." << endl;
}

void SwiatManager::wczytywanieDanychOrganizmu(string nazwa, int sila, int ini, int x, int y, int wiek)
{
	Organizm* wczytywanyOrganizm = nullptr;
	if (nazwa == "Lis")	{ wczytywanyOrganizm = new Lis(x, y, swiat);}
	else if (nazwa == "Zolw") { wczytywanyOrganizm = new Zolw(x, y, swiat);}
	else if (nazwa == "Wilk") { wczytywanyOrganizm = new Wilk(x, y, swiat);}
	else if (nazwa == "Owca") { wczytywanyOrganizm = new Owca(x, y, swiat);}
	else if (nazwa == "Antylopa") { wczytywanyOrganizm = new Antylopa(x, y, swiat);}
	else if (nazwa == "Trawa") { wczytywanyOrganizm = new Trawa(x, y, swiat);}
	else if (nazwa == "WilczeJagody") { wczytywanyOrganizm = new WilczeJagody(x, y, swiat);}
	else if (nazwa == "Mlecz") { wczytywanyOrganizm = new Mlecz(x, y, swiat);}
	else if (nazwa == "Guarana") { wczytywanyOrganizm = new Guarana(x, y, swiat);}
	else if (nazwa == "BarszczSosnowskiego") { wczytywanyOrganizm = new BarszczSosnowskiego(x, y, swiat);}

	wczytywanyOrganizm->setInicjatywa(ini);
	wczytywanyOrganizm->setWiek(wiek);
	wczytywanyOrganizm->setSila(sila);
	swiat->dodajNowyOrganizm(wczytywanyOrganizm);
}

SwiatManager::~SwiatManager()
{
	delete swiat;
}