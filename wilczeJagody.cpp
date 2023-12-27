#include <iostream>

#include "swiat.h"
#include "organizm.h"
#include "roslina.h"
#include "wilczeJagody.h"

WilczeJagody::WilczeJagody() : Roslina()
{
	this->sila = 99;
}

WilczeJagody::WilczeJagody(int x, int y, Swiat* swiat) : Roslina(99, x, y, swiat)
{

}

char WilczeJagody::getZnak() const
{
	return znakOrganizmu;
}

string WilczeJagody::getNazwa() const
{
	return "WilczeJagody";
}

void WilczeJagody::akcja()
{
	int los = rand() % 100;
	if (los < szansaRozsiania)
	{
		Roslina::akcja();
	}
}

void WilczeJagody::kolizja(Organizm* atakujacy)
{
	atakujacy->komentarzAtak(this);
	atakujacy->smierc();
}

Organizm* WilczeJagody::urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat)
{
	x--;
	y--;
	return new WilczeJagody(x, y, swiat);
}

void WilczeJagody::smierc() {
	getSwiat()->usunOrganizm(this);
}