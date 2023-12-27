#pragma once

using namespace std;

class Swiat;

class Organizm
{
protected:	
	int x, y, sila, inicjatywa, wiek;
	Swiat* swiatObiekt;
public:
	virtual Organizm* urodzenieNowegoOrganizmu(int x, int y, Swiat* swiat) = 0;
	Organizm();
	Organizm(Swiat* swiat, int sila, int inicjatywa, int x, int y);
	void setSila(int sila);
	void setInicjatywa(int ini);
	void setPolozenie(int x, int y);
	void setWiek(int wiek);
	void setSwiat(Swiat* swiat);
	virtual void setPoprzedniRuch(char ruch) = 0;
	virtual void smierc() = 0;
	int getSila() const;
	int getInicjatywa() const;
	int getX() const;
	int getY() const;
	int getWiek() const;
	Swiat* getSwiat() const;
	virtual int getOstatniRuch() const = 0;
	virtual char getZnak() const = 0;
	virtual string getNazwa() const = 0;
	virtual string zapiszInfo() const = 0;
	virtual void akcja() = 0;
	virtual void kolizja(Organizm* atakujacy) = 0;
	void ustawOrganizmNaMapie();
	virtual void powrotNaPoprzedniePole() = 0;
	virtual bool czyOrganizmToZwierze() = 0;
	virtual void komentarzAtak(Organizm* atakowany) = 0;
};