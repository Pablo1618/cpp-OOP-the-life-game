#pragma once

#include "zwierze.h"

using namespace std;

class Owca : public Zwierze
{
private:
	const char znakOrganizmu = 'O';
public:
	Owca();
	Owca(int x, int y, Swiat* swiat);
	void setPoprzedniRuch(char ruch) override;
	int getOstatniRuch() const override;
	char getZnak() const override;
	string getNazwa() const override;
	void smierc() override;
	void akcja() override;
	void kolizja(Organizm* atakujacy) override;
	Organizm* urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat) override;
};