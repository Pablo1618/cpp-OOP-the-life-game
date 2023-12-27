#include <iostream>
#include <string>

#include "swiat.h"
#include "organizm.h"
#include "zwierze.h"
#include "czlowiek.h"

#define STRZALKA_GORA 72
#define STRZALKA_DOL 80
#define STRZALKA_LEWO 75
#define STRZALKA_PRAWO 77
#define GORA 1
#define PRAWO 2
#define DOL 3
#define LEWO 4

using namespace std;

Czlowiek::Czlowiek(int x, int y, Swiat* swiat) : Zwierze(5, 4, x, y, swiat)
{
	turyUmiejetnosc = 5;
	umiejetnoscJestAktywowana = false;
}

void Czlowiek::setPoprzedniRuch(char ruch)
{
	if (ruch == STRZALKA_GORA)
	{
		ostatniRuch = GORA;
	}		
	else if (ruch == STRZALKA_PRAWO)
	{
		ostatniRuch = PRAWO;
	}
	else if (ruch == STRZALKA_DOL)
	{
		ostatniRuch = DOL;
	}
	else if (ruch == STRZALKA_LEWO)
	{
		ostatniRuch = LEWO;
	}
}

void Czlowiek::SetCzyUmiejetnoscAktywowana(bool umiejetnoscAktywowana)
{
	umiejetnoscJestAktywowana = umiejetnoscAktywowana;
}

void Czlowiek::setIleTurMineloUmiejetnosc(int tury)
{
	turyUmiejetnosc = tury;
}

int Czlowiek::getOstatniRuch() const
{
	return Zwierze::getOstatniRuch();
}

void Czlowiek::uzyjUmiejetnosci(bool rekurencja){

	if (rekurencja == false) {
		swiatObiekt->setPoleMapy(x, y, nullptr);
	}
	int staryKoordynatX = x;
	int staryKoordynatY = y;
	int losowyRuch = rand() % 4;

	if (losowyRuch == 0) { //gora
		if (y - 1 > 0) {
			ostatniRuch = GORA;
			y--;
		}
		else {
			ostatniRuch = DOL;
			y++;
		}
	}
	else if (losowyRuch == 1) { //dol
		if (y + 1 < swiatObiekt->getWysokosc() + 1) {
			ostatniRuch = DOL;
			y++;
		}
		else {
			ostatniRuch = GORA;
			y--;
		}
	}
	else if (losowyRuch == 2) { //lewo
		if (x - 1 > 0) {
			ostatniRuch = LEWO;
			x--;
		}
		else {
			ostatniRuch = PRAWO;
			x++;
		}
	}
	else if (losowyRuch == 3) { //prawo
		if (x + 1 < swiatObiekt->getSzerokosc() + 1) {
			ostatniRuch = PRAWO;
			x++;
		}
		else {
			ostatniRuch = LEWO;
			x--;
		}
	}

	if ((swiatObiekt->getPoleMapy(x + 1, y) != nullptr && swiatObiekt->getPoleMapy(x + 1, y)->getZnak() == 'B') ||
		(swiatObiekt->getPoleMapy(x - 1, y) != nullptr && swiatObiekt->getPoleMapy(x - 1, y)->getZnak() == 'B') ||
		(swiatObiekt->getPoleMapy(x, y + 1) != nullptr && swiatObiekt->getPoleMapy(x, y + 1)->getZnak() == 'B') ||
		(swiatObiekt->getPoleMapy(x, y - 1) != nullptr && swiatObiekt->getPoleMapy(x, y - 1)->getZnak() == 'B')) {

		uzyjUmiejetnosci(true);
		return;
	}
	if (swiatObiekt->getPoleMapy(x, y) != nullptr && swiatObiekt->getPoleMapy(x, y)->getZnak() == 'J') {
		uzyjUmiejetnosci(true);
		return;
	}
	if (swiatObiekt->getPoleMapy(x, y) != nullptr) {
		kolizja(swiatObiekt->getPoleMapy(x, y));
	}

	swiatObiekt->setPoleMapy(x, y, this);

	if (ostatniRuch != 0) {
		swiatObiekt->nowyKomentarz("[NIESMIERTELNOSC] " + this->getNazwa() + " [" + to_string(staryKoordynatX) + "," + to_string(staryKoordynatY) + "] ----> [" + to_string(x) + "," + to_string(y) + "]");
	}
}

bool Czlowiek::umiejetnoscWlaczona() const
{
	return umiejetnoscJestAktywowana;
}

int Czlowiek::ileTurMineloUmiejetnosc() const
{
	return turyUmiejetnosc;
}

char Czlowiek::getZnak() const
{
	return znakOrganizmu;
}

string Czlowiek::getNazwa() const
{
	return "Czlowiek";
}

string Czlowiek::zapiszInfo() const //do zapisu stanu gry
{
	string result = this->getNazwa() + " " + to_string(sila) + " " + to_string(inicjatywa) + " " + to_string(x) + " " + to_string(y) + " " + to_string(wiek) + " " + to_string(umiejetnoscJestAktywowana) + " " + to_string(turyUmiejetnosc);
	return result;
}

void Czlowiek::akcja()
{
	string komentarz;
	int staryKoordynatX = x;
	int staryKoordynatY = y;

	swiatObiekt->setPoleMapy(x, y, nullptr);
	if (ostatniRuch == GORA && y - 1 > 0)
	{
		y -= 1;
	}
	else if (ostatniRuch == DOL && y != swiatObiekt->getWysokosc())
	{
		y += 1;
	}
	else if (ostatniRuch == LEWO && x - 1 > 0)
	{
		x -= 1;
	}
	else if (ostatniRuch == PRAWO && x != swiatObiekt->getSzerokosc())
	{
		x += 1;
	}
	else
	{
		ostatniRuch = 0;
		this->ustawOrganizmNaMapie();
	}

	komentarz = "[RUCH CZLOWIEKA] [" + to_string(x) + "," + to_string(y) + "] ----> [" += to_string(x) + ", " + to_string(y) + "]";
	swiatObiekt->nowyKomentarz(komentarz);
}

void Czlowiek::kolizja(Organizm* atakujacy)
{
	Zwierze::kolizja(atakujacy);
}

void Czlowiek::aktywujUmiejetnosc()
{
	umiejetnoscJestAktywowana = true;
	turyUmiejetnosc = 0;
	cout << endl << "[UMIEJETNOSC] Niesmiertelnosc na 5 tur zostala aktywowana!" << endl;
}

void Czlowiek::dezaktywujUmiejetnosc()
{
	this->umiejetnoscJestAktywowana = false;
	this->turyUmiejetnosc = 0;
}

Organizm* Czlowiek::urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat)
{
	x--;
	y--;
	return new Czlowiek(x, y, swiat);
}

void Czlowiek::smierc() {

	if (umiejetnoscWlaczona() == true) {
		uzyjUmiejetnosci(false);
	}
	else {
		swiatObiekt->setCzyCzlowiekZyje(false);
		getSwiat()->usunOrganizm(this);
	}
}