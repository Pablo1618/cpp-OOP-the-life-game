#include <iostream>
#include <string>

#include "swiat.h"
#include "organizm.h"
#include "roslina.h"
#include "guarana.h"

Guarana::Guarana() : Roslina()
{
	this->sila = 0;
}

Guarana::Guarana(int x, int y, Swiat* swiat) : Roslina(0, x, y, swiat) { }

char Guarana::getZnak() const
{
	return znakOrganizmu;
}

string Guarana::getNazwa() const
{
	return "Guarana";
}

void Guarana::akcja()
{
	int los = rand() % 100;
	if (los < szansaRozsiania)
	{
		Roslina::akcja();
	}
}

void Guarana::kolizja(Organizm* atakujacy)
{
	atakujacy->komentarzAtak(this);
	atakujacy->setSila(atakujacy->getSila() + 3);
	swiatObiekt->nowyKomentarz("[GUARANA] Dodano 3 punkty sily dla organizmu ====> " + atakujacy->getNazwa() + " [" + to_string(atakujacy->getX()) + "," + to_string(atakujacy->getY()) + "]");
	swiatObiekt->setPoleMapy(this->getX(), this->getY(), atakujacy);
	this->smierc();
	atakujacy->ustawOrganizmNaMapie();
}

Organizm* Guarana::urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat)
{
	x--;
	y--;
	return new Guarana(x, y, swiat);
}

void Guarana::smierc() {
	getSwiat()->usunOrganizm(this);
}