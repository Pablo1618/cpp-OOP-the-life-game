#include <iostream>

#include "swiat.h"
#include "organizm.h"
#include "roslina.h"
#include "mlecz.h"

Mlecz::Mlecz() : Roslina()
{
	this->sila = 0;
}

Mlecz::Mlecz(int x, int y, Swiat* swiat) : Roslina(0, x, y, swiat)
{

}

char Mlecz::getZnak() const
{
	return znakOrganizmu;
}

string Mlecz::getNazwa() const
{
	return "Mlecz";
}

void Mlecz::akcja()
{
	for (int i = 0; i < 3; i++) //trzy proby rozprzestrzenienia
	{
		int losoweRozprzestrzenienie = rand() % 100;
		if (losoweRozprzestrzenienie < szansaRozsiania)
		{
			Roslina::akcja();
		}
	}
}

void Mlecz::kolizja(Organizm* atakujacy)
{
	Roslina::kolizja(atakujacy);
}

Organizm* Mlecz::urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat)
{
	x--;
	y--;
	return new Mlecz(x, y, swiat);
}

void Mlecz::smierc() {
	getSwiat()->usunOrganizm(this);
}