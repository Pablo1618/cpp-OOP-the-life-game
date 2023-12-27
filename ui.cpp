#pragma once
#include "ui.h"

#include <iostream>
#include <string>

#define USTAW_KOLOR_CZCIONKI "\033[1;33m"
#define USTAW_KOLOR_TLA "\033[42m"

using namespace std;

	void UI::wypiszMenuGlowne() {
		cout << USTAW_KOLOR_CZCIONKI;
		cout << USTAW_KOLOR_TLA;
		cout << "\033[3m";
		cout << "O---------------------------------O" << endl;
		cout << "|         Pawel Wawrzynski        |" << endl;
		cout << "|             193270              |" << endl;
		cout << "O---------------------------------O" << endl;
		cout << "|         Wirtualny swiat         |" << endl;
		cout << "|                                 |" << endl;
		cout << "|    Rozpocznij nowa gre - N      |" << endl;
		cout << "|        Wczytaj gre - L          |" << endl;
		cout << "O---------------------------------O" << endl;
		cout << "\033[0m";
	}

	void UI::narysujDrzewo() {
		cout << endl;
		cout << "\033[40m" << "	     " << "\033[42m" << "         " << endl;
		cout << "\033[40m" << "	    " << "\033[42m" << "           " << endl;
		cout << "\033[40m" << "	    " << "\033[42m" << "           " << endl;
		cout << "\033[40m" << "	    " << "\033[42m" << "           " << endl;
		cout << "\033[40m" << "	     " << "\033[42m" << "         " << endl;
		cout << "\033[43m";
		cout << "		   " << endl;
		cout << "		   " << endl;
		cout << "		   " << endl << endl;
		cout << "\033[0m";
	}

	void UI::wyborWymiaruPlanszy() {
		cout << USTAW_KOLOR_CZCIONKI;
		cout << USTAW_KOLOR_TLA;
		cout << "O---------------------------------O" << endl;
		cout << "|                                 |" << endl;
		cout << "|    Wybierz wymiary planszy:     |" << endl;
		cout << "|                                 |" << endl;
		cout << "O---------------------------------O" << endl;
		cout << "\033[0m" << endl;
		cout << "\033[33m";
		cout << "\033[6m";
		cout << "          X  Y" << endl;
		cout << "   --->   ";
		cout << "\033[0m";
	}

	void UI::narysujInfoTura(int tura) {
		cout << USTAW_KOLOR_CZCIONKI;
		cout << "O---------------------------------------O" << endl;
		cout << "|           Wirtualny swiat             |" << endl;
		cout << "|                                       |" << endl;
		cout << "|   S - zapisz stan wirtualnego swiata  |" << endl;
		cout << "|       N - rozpocznij nowa gre         |" << endl;
		cout << "|           Q - wyjdz z gry             |" << endl;
		cout << "O---------------------------------------O" << endl;
		cout << " Obecna tura --> | " << tura << " | <--" << endl << endl;
		cout << "\033[0m";
	}

	void UI::komunikatZaMalaPlansza(int minimalnaWielkosc) {
		cout << endl << "Wybrana plansza jest za mala do gry!" << endl;
		cout << "Minimalny rozmiar mapy do prawidlowej rozgrywki to: " << minimalnaWielkosc << endl;
		cout << "Wybierz wymiary planszy jeszcz raz." << endl << endl;
	}

	void UI::komunikatNieWczytanoGry() {
		cout << "Nie wczytano gry! Prawdopodobnie zapis gry nie istnieje." << endl;
	}