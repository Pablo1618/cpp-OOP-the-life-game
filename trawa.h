#pragma once

#include <iostream>
#include <string.h>

#include "roslina.h"

using namespace std;

class Trawa : public Roslina
{
private:
	const char znakOrganizmu = 'T';
	const int szansaRozsiania = 20;
public:
	Trawa();
	Trawa(int x, int y, Swiat* swiat);
	char getZnak() const override;
	string getNazwa() const override;
	void smierc() override;
	void akcja() override;
	void kolizja(Organizm* atakujacy) override;
	Organizm* urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat) override;
};