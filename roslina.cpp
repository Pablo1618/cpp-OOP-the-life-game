#include <iostream>
#include <string>
#include "swiat.h"
#include "organizm.h"
#include "guarana.h"
#include "wilczeJagody.h"
#include "barszczSosnowskiego.h"
#include "roslina.h"
#include "trawa.h"
#include "mlecz.h"

using namespace std;

Roslina::Roslina() : Organizm() { }

Roslina::Roslina(int sila, int x, int y, Swiat* swiat) : Organizm(swiat, sila, 0, x, y) { }

int Roslina::getOstatniRuch() const
{
	return 0;
}

string Roslina::zapiszInfo() const
{
	string result = this->getNazwa() + " " + to_string(this->getSila()) + " " + to_string(this->getInicjatywa()) + " " + to_string(this->getX()) + " " + to_string(this->getY()) + " " + to_string(this->getWiek());
	return result;
}

//------------------
void Roslina::akcja()
{
	bool czyRozsiano = false;
	int losowyRuch = rand() % 4;

	if (losowyRuch == 0 && swiatObiekt->getPoleMapy(x, y - 1) == nullptr) { //gora
		if (y - 1 > 0) {
			Organizm* org = this->urodzenieNowegoOrganizmu(x, y-1, swiatObiekt);
			swiatObiekt->dodajNowyOrganizm(org);
			czyRozsiano = true;
		}
	}
	else if (losowyRuch == 1 && swiatObiekt->getPoleMapy(x, y + 1) == nullptr) { //dol
		if (y + 1 < swiatObiekt->getWysokosc() + 1) {
			Organizm* org = this->urodzenieNowegoOrganizmu(x, y+1, swiatObiekt);
			swiatObiekt->dodajNowyOrganizm(org);
			czyRozsiano = true;
		}
	}
	else if (losowyRuch == 2 && swiatObiekt->getPoleMapy(x-1, y) == nullptr) { //lewo
		if (x - 1 > 0) {
			Organizm* org = this->urodzenieNowegoOrganizmu(x-1, y, swiatObiekt);
			swiatObiekt->dodajNowyOrganizm(org);
			czyRozsiano = true;
		}
	}
	else if (losowyRuch == 3 && swiatObiekt->getPoleMapy(x+1, y) == nullptr) { //prawo
		if (x + 1 < swiatObiekt->getSzerokosc() + 1) {
			Organizm* org = this->urodzenieNowegoOrganizmu(x+1, y, swiatObiekt);
			swiatObiekt->dodajNowyOrganizm(org);
			czyRozsiano = true;
		}
	}

	if (czyRozsiano == true) {
		swiatObiekt->nowyKomentarz("[ROZPRZESTRZENIENIE] " + this->getNazwa() + " ===> " + "[" + to_string(x) + "," + to_string(y) + "]");
	}
}

void Roslina::kolizja(Organizm* atakujacy)
{
	atakujacy->komentarzAtak(this);

	if (this->getSila() > atakujacy->getSila())
	{
		//swiatObiekt->usunOrganizm(atakujacy);
		atakujacy->smierc();
	}
	else
	{
		swiatObiekt->setPoleMapy(this->getX(), this->getY(), atakujacy);
		//swiatObiekt->usunOrganizm(this);
		this->smierc();
		atakujacy->ustawOrganizmNaMapie();
	}
}

bool Roslina::czyOrganizmToZwierze()
{
	return false;
}

void Roslina::komentarzAtak(Organizm* atakowany)
{
	string komentarz;
	swiatObiekt->nowyKomentarz("[SMIERTELNA ROSLINA] " + this->getNazwa() + " zabija " + atakowany->getNazwa());
}

void Roslina::setPoprzedniRuch(char ruch)
{
	//
}

void Roslina::powrotNaPoprzedniePole()
{
	//
}
