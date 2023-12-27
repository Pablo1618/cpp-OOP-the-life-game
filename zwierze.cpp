#include <iostream>
#include <string>

#include "swiat.h"
#include "organizm.h"
#include "zwierze.h"
#include "wilk.h"
#include "owca.h"
#include "zolw.h"
#include "antylopa.h"
#include "lis.h"

#define GORA 1
#define PRAWO 2
#define DOL 3
#define LEWO 4

using namespace std;

Zwierze::Zwierze() : Organizm()
{
	ostatniRuch = NULL;
}

Zwierze::Zwierze(int sila, int inicjatywa, int x, int y, Swiat* swiat) : Organizm(swiat, sila, inicjatywa, x, y)
{
	ostatniRuch = NULL;
}

void Zwierze::akcja()
{
	this->ruchZwierzecia(1, false);
}

string Zwierze::zapiszInfo() const
{
	string result = this->getNazwa() + " " + to_string(sila) + " " + to_string(inicjatywa) + " " + to_string(x) + " " + to_string(y) + " " + to_string(wiek);
	return result;
}

void Zwierze::kolizja(Organizm* atakujacy)
{
	atakujacy->komentarzAtak(this);

	if (this->getNazwa() == atakujacy->getNazwa() && atakujacy->getWiek() > 0)
	{
		this->rozmnazanie(atakujacy, swiatObiekt);
	}
	else if (this->getSila() <= atakujacy->getSila()) //atakujacy wygrywa
	{
		swiatObiekt->setPoleMapy(this->getX(), this->getY(), atakujacy);
		this->smierc();
		atakujacy->ustawOrganizmNaMapie();
	}
	else if (this->getSila() > atakujacy->getSila()) //zaatakowany wygrywa
	{
		atakujacy->smierc();
	}
}

void Zwierze::setPoprzedniRuch(char ruch)
{
	ostatniRuch = ruch;
}

int Zwierze::getOstatniRuch() const
{
	return ostatniRuch;
}

void Zwierze::powrotNaPoprzedniePole()
{
	int X = this->getX() - 1; // -1 bo zamieniamy na indeksowanie od 0
	int Y = this->getY() - 1;
	if (this->getOstatniRuch() == GORA)
	{
		this->setPolozenie(X, Y + 1);
	}
	else if (this->getOstatniRuch() == PRAWO)
	{
		this->setPolozenie(X - 1, Y);
	}
	else if (this->getOstatniRuch() == DOL)
	{
		this->setPolozenie(X, Y - 1);
	}
	else if (this->getOstatniRuch() == LEWO)
	{
		this->setPolozenie(X + 1, Y);
	}
	this->ustawOrganizmNaMapie();
}

bool Zwierze::czyOrganizmToZwierze()
{
	return true;
}

bool Zwierze::ucieczkaPrzedWalka(int odlegloscRuchu) //np. dla antylopy
{
	swiatObiekt->setPoleMapy(x, y, nullptr);
	int staryKoordynatX = x;
	int staryKoordynatY = y;

	if (y - odlegloscRuchu > 0 && swiatObiekt->getPoleMapy(x,y-odlegloscRuchu) == nullptr) { // ucieczka do gory
		ostatniRuch = GORA;
		y--;
	}
	else if (y + odlegloscRuchu < swiatObiekt->getWysokosc() + 1 && swiatObiekt->getPoleMapy(x, y + odlegloscRuchu) == nullptr) { //ucieczka do dolu
		ostatniRuch = DOL;
		y++;
	}
	else if (x - odlegloscRuchu > 0 && swiatObiekt->getPoleMapy(x - odlegloscRuchu, y) == nullptr) { //ucieczka w lewo
		ostatniRuch = LEWO;
		x--;
	}
	else if (x + odlegloscRuchu < swiatObiekt->getSzerokosc() + 1 && swiatObiekt->getPoleMapy(x + odlegloscRuchu, y) == nullptr) { //ucieczka w prawo
		ostatniRuch = PRAWO;
		x++;
	}
	else {
		ostatniRuch = 0;
	}

	if (ostatniRuch != 0) {
		swiatObiekt->nowyKomentarz("[UCIECZKA PRZED WALKA] " + this->getNazwa() + " [" + to_string(staryKoordynatX) + "," + to_string(staryKoordynatY) + "] ----> [" + to_string(x) + "," + to_string(y) + "]");
		return true;
	}
	return false;
}

void Zwierze::ruchZwierzecia(int odlegloscRuchu, bool czyDobryWech)
{
	int staryKoordynatX = this->getX();
	int staryKoordynatY = this->getY();
	int licznikProbRuchu = 0;
	int losowyRuch = rand() % 4;
	string komentarz;

	if (losowyRuch == 0) { //gora
		if (y - odlegloscRuchu > 0) {
			ostatniRuch = GORA;
			y = y - odlegloscRuchu;
		}
		else {
			ostatniRuch = DOL;
			y = y + odlegloscRuchu;
		}
	}
	else if (losowyRuch == 1) { //dol
		if (y + odlegloscRuchu < swiatObiekt->getWysokosc() + 1) {
			ostatniRuch = DOL;
			y = y + odlegloscRuchu;
		}
		else {
			ostatniRuch = GORA;
			y = y - odlegloscRuchu;
		}
	}
	else if (losowyRuch == 2) { //lewo
		if (x - odlegloscRuchu > 0) {
			ostatniRuch = LEWO;
			x = x - odlegloscRuchu;
		}
		else {
			ostatniRuch = PRAWO;
			x = x + odlegloscRuchu;
		}
	}
	else if (losowyRuch == 3) { //prawo
		if (x + odlegloscRuchu < swiatObiekt->getSzerokosc() + 1) {
			ostatniRuch = PRAWO;
			x = x + odlegloscRuchu;
		}
		else {
			ostatniRuch = LEWO;
			x = x - odlegloscRuchu;
		}
	}

	if (czyDobryWech == true) {
		if (swiatObiekt->getPoleMapy(x,y)!=nullptr && swiatObiekt->getPoleMapy(x, y)->getSila() > this->getSila()) {
			x = staryKoordynatX;
			y = staryKoordynatY;
			ostatniRuch = 0;
		}
	}

	if (ostatniRuch != 0) {
		swiatObiekt->setPoleMapy(staryKoordynatX, staryKoordynatY, nullptr);
		komentarz = "[PRZEMIESZCZENIE] " + this->getNazwa() + " [" + to_string(staryKoordynatX) + "," + to_string(staryKoordynatY) + "]" + " ----> " + "[" + to_string(x) + "," + to_string(y) + "]";
		swiatObiekt->nowyKomentarz(komentarz);
	}
}

void Zwierze::rozmnazanie(Organizm* atakujacy, Swiat* swiat)
{
	int pozycjaRodzicaX = atakujacy->getX();
	int pozycjaRodzicaY = atakujacy->getY();
	atakujacy->powrotNaPoprzedniePole();

	if (swiat->getPoleMapy(pozycjaRodzicaX, pozycjaRodzicaY - 1) == nullptr && pozycjaRodzicaY - 1 > 0) { //pole nad
		Organizm* nowyOrganizm = this->urodzenieNowegoOrganizmu(pozycjaRodzicaX, pozycjaRodzicaY - 1, swiat);
		swiat->dodajNowyOrganizm(nowyOrganizm);
		return;
	}
	else if (swiat->getPoleMapy(pozycjaRodzicaX, pozycjaRodzicaY + 1) == nullptr && pozycjaRodzicaY + 1 < swiatObiekt->getWysokosc() + 1) { //pole pod
		Organizm* nowyOrganizm = this->urodzenieNowegoOrganizmu(pozycjaRodzicaX, pozycjaRodzicaY + 1, swiat);
		swiat->dodajNowyOrganizm(nowyOrganizm);
		return;
	}
	else if (swiat->getPoleMapy(pozycjaRodzicaX - 1, pozycjaRodzicaY) == nullptr && pozycjaRodzicaX - 1 > 0) { //pole na lewo
		Organizm* nowyOrganizm = this->urodzenieNowegoOrganizmu(pozycjaRodzicaX - 1, pozycjaRodzicaY, swiat);
		swiat->dodajNowyOrganizm(nowyOrganizm);
		return;
	}
	else if (swiat->getPoleMapy(pozycjaRodzicaX + 1, pozycjaRodzicaY) == nullptr && pozycjaRodzicaX + 1 < swiatObiekt->getSzerokosc() + 1) { //pole na prawo
		Organizm* nowyOrganizm = this->urodzenieNowegoOrganizmu(pozycjaRodzicaX + 1, pozycjaRodzicaY, swiat);
		swiat->dodajNowyOrganizm(nowyOrganizm);
		return;
	}
}

void Zwierze::komentarzAtak(Organizm* atakowany)
{
	string komentarz = "[ATAK] " + this->getNazwa() + " zaatakowal " + atakowany->getNazwa();
	swiatObiekt->nowyKomentarz(komentarz);
}