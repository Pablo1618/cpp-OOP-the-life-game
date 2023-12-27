#include <iostream>

#include "swiat.h"
#include "organizm.h"
#include "roslina.h"
#include "trawa.h"

Trawa::Trawa() : Roslina()
{
	this->sila = 0;
}

Trawa::Trawa(int x, int y, Swiat* swiat) : Roslina(0, x, y, swiat) { }

char Trawa::getZnak() const
{
	return znakOrganizmu;
}

string Trawa::getNazwa() const
{
	return "Trawa";
}

void Trawa::akcja()
{
	int los = rand() % 100;
	if (los < szansaRozsiania)
	{
		Roslina::akcja();
	}
}

void Trawa::kolizja(Organizm* atakujacy)
{
	Roslina::kolizja(atakujacy);
}

Organizm* Trawa::urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat)
{
	x--;
	y--;
	return new Trawa(x, y, swiat);
}

void Trawa::smierc() {
	getSwiat()->usunOrganizm(this);
}