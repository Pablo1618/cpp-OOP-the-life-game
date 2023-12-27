#include <iostream>

#include "swiat.h"
#include "organizm.h"
#include "zwierze.h"
#include "wilk.h"

Wilk::Wilk() : Zwierze()
{
	this->sila = 9;
	this->inicjatywa = 5;
}

Wilk::Wilk(int x, int y, Swiat* swiat) : Zwierze(9, 5, x, y, swiat)
{

}

void Wilk::setPoprzedniRuch(char ruch)
{
	Zwierze::setPoprzedniRuch(ruch);
}

int Wilk::getOstatniRuch() const
{
	return Zwierze::getOstatniRuch();
}

char Wilk::getZnak() const
{
	return znakOrganizmu;
}

string Wilk::getNazwa() const
{
	return "Wilk";
}

void Wilk::akcja()
{
	Zwierze::akcja();
}

void Wilk::kolizja(Organizm* atakujacy)
{
	Zwierze::kolizja(atakujacy);
}

Organizm* Wilk::urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat)
{
	x--;
	y--;
	return new Wilk(x, y, swiat);
}

void Wilk::smierc() {
	getSwiat()->usunOrganizm(this);
}