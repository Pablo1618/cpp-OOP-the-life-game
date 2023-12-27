#include <iostream>

#include "swiat.h"
#include "organizm.h"
#include "zwierze.h"
#include "lis.h"

Lis::Lis() : Zwierze()
{
	this->sila = 3;
	this->inicjatywa = 7;
}

Lis::Lis(int x, int y, Swiat* swiat) : Zwierze(3, 7, x, y, swiat)
{

}

void Lis::setPoprzedniRuch(char ruch)
{
	Zwierze::setPoprzedniRuch(ruch);
}

int Lis::getOstatniRuch() const
{
	return Zwierze::getOstatniRuch();
}

char Lis::getZnak() const
{
	return znakOrganizmu;
}

string Lis::getNazwa() const
{
	return "Lis";
}

void Lis::akcja()
{
	Zwierze::ruchZwierzecia(1, true);
}

void Lis::kolizja(Organizm* atakujacy)
{
	Zwierze::kolizja(atakujacy);
}

Organizm* Lis::urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat)
{
	x--;
	y--;
	return new Lis(x, y, swiat);
}

void Lis::smierc() {
	getSwiat()->usunOrganizm(this);
}