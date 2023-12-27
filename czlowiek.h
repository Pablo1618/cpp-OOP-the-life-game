#pragma once

#include "zwierze.h"

using namespace std;

class Czlowiek : public Zwierze
{
private:
	const char znakOrganizmu = 'X';
	bool umiejetnoscJestAktywowana;
	int turyUmiejetnosc;
public:
	Czlowiek(int x, int y, Swiat* swiat);
	void setPoprzedniRuch(char ruch) override;
	void SetCzyUmiejetnoscAktywowana(bool umiejetnoscAktywowana);
	void setIleTurMineloUmiejetnosc(int tury);
	int getOstatniRuch() const override;
	bool umiejetnoscWlaczona() const;
	int ileTurMineloUmiejetnosc() const;
	char getZnak() const override;
	string getNazwa() const override;
	string zapiszInfo() const override;
	void akcja() override;
	void kolizja(Organizm* atakujacy) override;
	void uzyjUmiejetnosci(bool rekurencja);
	void aktywujUmiejetnosc();
	void dezaktywujUmiejetnosc();
	void smierc() override;
	Organizm* urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat) override;
};