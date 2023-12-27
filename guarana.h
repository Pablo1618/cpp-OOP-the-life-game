#pragma once

#include "roslina.h"

using namespace std;


class Guarana : public Roslina
{
private:
	const char znakOrganizmu = 'G';
	const int szansaRozsiania = 30;
public:
	Guarana();
	Guarana(int x, int y, Swiat* swiat);
	char getZnak() const override;
	string getNazwa() const override;
	void akcja() override;
	void smierc() override;
	void kolizja(Organizm* atakujacy) override;
	Organizm* urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat) override;
};