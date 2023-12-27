#pragma once

#include "organizm.h"

using namespace std;

class Roslina : public Organizm
{
public:
	Roslina();
	Roslina(int sila, int x, int y, Swiat* swiat);
	int getOstatniRuch() const override;
	virtual char getZnak() const = 0;
	virtual string getNazwa() const = 0;
	string zapiszInfo() const override;
	void akcja() override;
	void kolizja(Organizm* atakujacy) override;
	bool czyOrganizmToZwierze() override;
	void komentarzAtak(Organizm* atakowany) override;
	void setPoprzedniRuch(char ruch) override;
	void powrotNaPoprzedniePole() override;
};