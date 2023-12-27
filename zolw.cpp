#include <iostream>

#include "swiat.h"
#include "organizm.h"
#include "zwierze.h"
#include "zolw.h"

Zolw::Zolw() : Zwierze()
{
	this->sila = 2;
	this->inicjatywa = 1;
}

Zolw::Zolw(int x, int y, Swiat* swiat) : Zwierze(2, 1, x, y, swiat)
{

}

void Zolw::setPoprzedniRuch(char ruch)
{
	Zwierze::setPoprzedniRuch(ruch);
}

int Zolw::getOstatniRuch() const
{
	return Zwierze::getOstatniRuch();
}

char Zolw::getZnak() const
{
	return znakOrganizmu;
}

string Zolw::getNazwa() const
{
	return "Zolw";
}

void Zolw::akcja()
{
	int losowyRuch = rand() % 4;
	if (losowyRuch < 2) // 25% szansy na ruch
	{
		Zwierze::akcja();
	}
	else
	{
		ostatniRuch = 0;
	}
}

void Zolw::kolizja(Organizm* atakujacy)
{
	if (atakujacy->getSila() < 5 && atakujacy->getNazwa()!= "Zolw")
	{
		atakujacy->powrotNaPoprzedniePole();
	}
	else
	{
		Zwierze::kolizja(atakujacy);
	}	
}

Organizm* Zolw::urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat)
{
	x--;
	y--;
	return new Zolw(x, y, swiat);
}

void Zolw::smierc() {
	getSwiat()->usunOrganizm(this);
}