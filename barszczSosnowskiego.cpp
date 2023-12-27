#include <iostream>

#include "swiat.h"
#include "organizm.h"
#include "roslina.h"
#include "barszczSosnowskiego.h"

BarszczSosnowskiego::BarszczSosnowskiego() : Roslina()
{
	this->sila = 10;
}

BarszczSosnowskiego::BarszczSosnowskiego(int x, int y, Swiat* swiat) : Roslina(10, x, y, swiat)
{

}

char BarszczSosnowskiego::getZnak() const
{
	return znakOrganizmu;
}

string BarszczSosnowskiego::getNazwa() const
{
	return "BarszczSosnowskiego";
}

void BarszczSosnowskiego::akcja()
{
	Organizm* organizm[4];
	int pozycja[4][2] = { {0,-1}, {1,0}, {0,1}, {-1,0} };
	for (int i = 0; i < 4; i++) {
		organizm[i] = swiatObiekt->getPoleMapy(x + pozycja[i][0], y + pozycja[i][1]);
		if (organizm[i] != nullptr && organizm[i]->czyOrganizmToZwierze()) {
			this->komentarzAtak(organizm[i]);
			organizm[i]->smierc();
		}
	}

	int losoweRozprzestrzenienie = rand() % 100;
	if (losoweRozprzestrzenienie < szansaRozsiania)
	{
		Roslina::akcja();
	}
}

void BarszczSosnowskiego::kolizja(Organizm* atakujacy)
{
	atakujacy->komentarzAtak(this);
	atakujacy->smierc();
}

Organizm* BarszczSosnowskiego::urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat)
{
	x--;
	y--;
	return new BarszczSosnowskiego(x, y, swiat);
}

void BarszczSosnowskiego::smierc() {
	getSwiat()->usunOrganizm(this);
}