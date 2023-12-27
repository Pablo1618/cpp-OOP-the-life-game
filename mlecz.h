#pragma once

#include "roslina.h"

using namespace std;

class Mlecz : public Roslina
{
private:
	const char znakOrganizmu = 'M';
	const int szansaRozsiania = 20;
public:
	Mlecz();
	Mlecz(int x, int y, Swiat* swiat);
	char getZnak() const override;
	string getNazwa() const override;
	void akcja() override;
	void smierc() override;
	void kolizja(Organizm* atakujacy) override;
	Organizm* urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat) override;

};