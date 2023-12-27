#pragma once
#include <iostream>

using namespace std;

class SwiatManager
{
private:
	Swiat* swiat;
	void losowanieWspolrzednych(bool** zajetePola, int szerokosc, int wysokosc, int* losowyX, int* losowyY);
	void wczytywanieDanychOrganizmu(string nazwa, int sila, int ini, int x, int y, int wiek);
public:
	SwiatManager(Swiat* swiat);
	bool wczytajStanSwiata();
	void zapiszStanSwiata();
	void dodajOrganizmyDoNowegoSwiata(int ileZwierzatJednegoGatunku);
	~SwiatManager();
};
