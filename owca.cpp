#include <iostream>

#include "swiat.h"
#include "organizm.h"
#include "zwierze.h"
#include "owca.h"

Owca::Owca() : Zwierze()
{
	this->sila = 4;
	this->inicjatywa = 4;
}

Owca::Owca(int x, int y, Swiat* swiat) : Zwierze(4, 4, x, y, swiat)
{

}

void Owca::setPoprzedniRuch(char ruch)
{
	Zwierze::setPoprzedniRuch(ruch);
}

int Owca::getOstatniRuch() const
{
	return Zwierze::getOstatniRuch();
}

char Owca::getZnak() const
{
	return znakOrganizmu;
}

string Owca::getNazwa() const
{
	return "Owca";
}

void Owca::akcja()
{
	Zwierze::akcja();
}

void Owca::kolizja(Organizm* atakujacy)
{
	Zwierze::kolizja(atakujacy);
}

Organizm* Owca::urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat)
{
	x--;
	y--;
	return new Owca(x, y, swiat);
}

void Owca::smierc() {
	getSwiat()->usunOrganizm(this);
}