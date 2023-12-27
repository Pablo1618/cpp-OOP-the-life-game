#pragma once

#include "zwierze.h"

using namespace std;

class Zolw : public Zwierze
{
private:
	const char znakOrganizmu = 'Z';
public:
	Zolw();
	Zolw(int x, int y, Swiat* swiat);
	void setPoprzedniRuch(char ruch) override;
	int getOstatniRuch() const override;
	char getZnak() const override;
	string getNazwa() const override;
	void akcja() override;
	void smierc() override;
	void kolizja(Organizm* atakujacy) override;
	Organizm* urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat) override;
};
