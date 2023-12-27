#pragma once

#include "zwierze.h"

using namespace std;

class Lis : public Zwierze
{
private:
	const char znakOrganizmu = 'L';
public:
	Lis();
	Lis(int x, int y, Swiat* swiat);
	void setPoprzedniRuch(char ruch) override;
	int getOstatniRuch() const override;
	char getZnak() const override;
	string getNazwa() const override;
	void akcja() override;
	void smierc() override;
	void kolizja(Organizm* atakujacy) override;
	Organizm* urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat) override;
};
