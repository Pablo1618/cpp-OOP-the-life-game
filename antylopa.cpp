#include <iostream>

#include "swiat.h"
#include "organizm.h"
#include "zwierze.h"
#include "antylopa.h"

Antylopa::Antylopa() : Zwierze()
{
	this->sila = 4;
	this->inicjatywa = 4;
}

Antylopa::Antylopa(int x, int y, Swiat* swiat) : Zwierze(4, 4, x, y, swiat) { }

void Antylopa::setPoprzedniRuch(char ruch)
{
	Zwierze::setPoprzedniRuch(ruch);
}

int Antylopa::getOstatniRuch() const
{
	return Zwierze::getOstatniRuch();
}

char Antylopa::getZnak() const
{
	return znakOrganizmu;
}

string Antylopa::getNazwa() const
{
	return "Antylopa";
}


void Antylopa::akcja()
{
	swiatObiekt->setPoleMapy(this->x, this->y, nullptr);
	this->ruchZwierzecia(2, false);
}

//----------------------------------------
void Antylopa::kolizja(Organizm* atakujacy)
{

	if (atakujacy->getNazwa() != "Antylopa") {
		int losowanieCzyUcieczka = rand() % 2;
		if (losowanieCzyUcieczka == 1) {
			if (this->ucieczkaPrzedWalka(2) == true) {
				return;
			}
		}
	}

	Zwierze::kolizja(atakujacy);

}

Organizm* Antylopa::urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat)
{
	x--;
	y--;
	return new Antylopa(x, y, swiat);
}

void Antylopa::smierc(){
	getSwiat()->usunOrganizm(this);
}