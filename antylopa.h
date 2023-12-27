#pragma once
#include "zwierze.h"

using namespace std;

class Antylopa : public Zwierze
{
private:
	const char znakOrganizmu = 'A';
public:
	Antylopa();
	Antylopa(int x, int y, Swiat* swiat);
	void setPoprzedniRuch(char ruch) override;
	string getNazwa() const override;
	void akcja() override;
	void kolizja(Organizm* atakujacy) override;
	void smierc() override;
	int getOstatniRuch() const override;
	char getZnak() const override;
	Organizm* urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat) override;
};
