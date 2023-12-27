#pragma once

#include "roslina.h"

using namespace std;

class WilczeJagody : public Roslina
{
private:
	const char znakOrganizmu = 'J';
	const int szansaRozsiania = 10;
public:
	WilczeJagody();
	WilczeJagody(int x, int y, Swiat* swiat);
	char getZnak() const override;
	string getNazwa() const override;
	void akcja() override;
	void smierc() override;
	void kolizja(Organizm* atakujacy) override;
	Organizm* urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat) override;
};
