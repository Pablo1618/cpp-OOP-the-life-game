#pragma once
#include "ui.h"

using namespace std;

class Organizm;
class Czlowiek;

class Swiat
{
private:
	int liczbaOrganizmow, szerokosc, wysokosc, tura, liczbaKomentarzy;
	int liczbaOrganizmowDoroslych;
	UI* ui;
	Organizm*** mapa; //tablica dwuwymiarowa wskaznikow na organizmy
	Organizm** organizmy;
	Czlowiek* czlowiek;
	bool czyCzlowiekZyje;
	string* komentarze;
	void symulacjaAkcjiOrganizmow();
public:
	Swiat();
	Swiat(int szerokosc, int wysokosc);
	void setRozmiarPlanszy(int szerokosc, int wysokosc);
	void setPoleMapy(int x, int y, Organizm* organizm);
	int getTura() const;
	Organizm* getPoleMapy(int x, int y) const;
	Organizm* getOrganizm(int i) const;
	Czlowiek* getCzlowiek() const;
	void setTura(int tura);
	void setCzyCzlowiekZyje(bool opcja);
	void nowyKomentarz(string komentarz);
	int getSzerokosc() const;
	int getWysokosc() const;
	int getLiczbaOrganizmow() const;
	void dodajNowyOrganizm(Organizm* org);
	void usunOrganizm(Organizm* org);
	void wykonajTure();
	void rysujSwiat();
	~Swiat();
};