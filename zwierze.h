#pragma once

#include "organizm.h"

using namespace std;


class Zwierze : public Organizm
{
private:
	void rozmnazanie(Organizm* atakowany, Swiat* swiat);
protected:
	int ostatniRuch;
	bool ucieczkaPrzedWalka(int odlegloscRuchu);
	void ruchZwierzecia(int odlegloscRuchu, bool czyDobryWech);
public:
	Zwierze();
	Zwierze(int sila, int inicjatywa, int x, int y, Swiat* swiat);
	void setPoprzedniRuch(char ruch) override;
	int getOstatniRuch() const override;
	virtual char getZnak() const = 0;
	virtual string getNazwa() const = 0;
	string zapiszInfo() const override;
	void akcja() override;
	void kolizja(Organizm* atakujacy) override;	
	void powrotNaPoprzedniePole() override;
	bool czyOrganizmToZwierze() override;
	void komentarzAtak(Organizm* atakowany) override;
};