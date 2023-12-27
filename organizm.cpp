#include <iostream>

#include "swiat.h"
#include "organizm.h"

using namespace std;

Organizm::Organizm()
{
	this->sila = 0;
	this->inicjatywa = 0;
	this->x = 0;
	this->y = 0;
	this->swiatObiekt = nullptr;
	this->wiek = 0;
}

Organizm::Organizm(Swiat* swiat, int sila, int inicjatywa, int x, int y)
{
	this->sila = sila;
	this->inicjatywa = inicjatywa;
	this->x = x + 1;
	this->y = y + 1;
	this->swiatObiekt = swiat;
	this->wiek = 0;
}

void Organizm::setWiek(int wiek)
{
	this->wiek = wiek;
}

void Organizm::setSila(int sila)
{
	this->sila = sila;
}

void Organizm::setInicjatywa(int ini)
{
	this->inicjatywa = ini;
}

void Organizm::setPolozenie(int x, int y)
{
	this->x = x + 1;
	this->y = y + 1;
}

void Organizm::setSwiat(Swiat* swiat)
{
	swiatObiekt = swiat;
}

int Organizm::getX() const
{
	return this->x;
}

int Organizm::getY() const
{
	return this->y;
}

int Organizm::getSila() const
{
	return this->sila;
}

int Organizm::getInicjatywa() const
{
	return this->inicjatywa;
}

int Organizm::getWiek() const
{
	return this->wiek;
}

Swiat* Organizm::getSwiat() const
{
	return swiatObiekt;
}

void Organizm::ustawOrganizmNaMapie()
{
	swiatObiekt->setPoleMapy(this->x, this->y, this);
}