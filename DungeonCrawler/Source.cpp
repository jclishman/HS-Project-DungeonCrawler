// Jack Lishman	12-10-2014	P5
// Dungeon Crawler

// All the libraries ever
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Functions
void init();
void viewHighscores();

// Global Vars
ifstream fin;
ofstream fout;

char map[8][15];
char keyPress = 0;

bool gameWin = false;
bool gameLose = false;

char playerChar = 'P';
char monsterChar = 'M';
char exitChar = 'E';

char currentChar;
char destChar;
int hCoord = 0;
int vCoord = 3;
int turn = 0;

bool isMonster = false;
char currentMChar;
char destMChar;
int hMCoord;
int vMCoord;
int Mturn = 0;

string winnerName;
string highscore;

// Main
int main() {
	gameWin = false;
				
	init();
	system("CLS");

	if (keyPress == 'Q' || keyPress == 'q') {
		return 0;
	}

	fin.open("map.txt", ios::in);
	fout.open("highscores.txt", ios::out);

	if (!fin.is_open()) {
		cout << "Unable To Open File..." << endl;
	}

	else {
		
		char keyPress = 0;

		do {
			system("CLS");

			cout << "Press Q to quit" << endl << endl;

			// Draw Map
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 15; j++) {
					cout << " " << map[i][j];
				}
				cout << endl;
			}

			// Keypress Input
			keyPress = 0;
			keyPress = _getch();

			switch (keyPress) {

			case 'W':
			case 'w':

				if (vCoord == 0) {
					break;
				}

				// Magic
				if (turn == 0) currentChar = '.';
				map[vCoord][hCoord] = currentChar;
				destChar = map[vCoord - 1][hCoord];
				map[vCoord - 1][hCoord] = playerChar;
				vCoord--;
				currentChar = destChar;
				if (currentChar == '*' || currentChar == 'M') {
					gameLose = true;
				}
				if (currentChar == 'E') {
					gameWin = true;
				}
				turn++;
				break;

			case 'A':
			case 'a':

				if (hCoord == 0) {
					break;
				}

				// Sorcery
				if (turn == 0) currentChar = '.';
				map[vCoord][hCoord] = currentChar;
				destChar = map[vCoord][hCoord - 1];
				map[vCoord][hCoord - 1] = playerChar;
				hCoord--;
				currentChar = destChar;
				if (currentChar == '*' || currentChar == 'M') {
					gameLose = true;
				}
				if (currentChar == 'E') {
					gameWin = true;
				}
				turn++;
				break;

			case 's':
			case 'S':

				if (vCoord == 7) {
					break;
				}

				// Really, really good luck
				if (turn == 0) currentChar = '.';
				map[vCoord][hCoord] = currentChar;
				destChar = map[vCoord + 1][hCoord];
				map[vCoord + 1][hCoord] = playerChar;
				vCoord++;
				currentChar = destChar;
				if (currentChar == '*' || currentChar == 'M') {
					gameLose = true;
				}
				if (currentChar == 'E') {
					gameWin = true;
				}
				turn++;
				break;


			case 'D':
			case 'd':
				
				if (hCoord == 14) {
					break;
				}

				// This section of the code was outsourced to Harry Potter
				if (turn == 0) currentChar = '.';
				map[vCoord][hCoord] = currentChar;
				destChar = map[vCoord][hCoord + 1];
				map[vCoord][hCoord + 1] = playerChar;
				hCoord++;
				currentChar = destChar;
				if (currentChar == '*' || currentChar == 'M') {
					gameLose = true;
				}
				if (currentChar == 'E') {
					gameWin = true;
				}
				turn++;
				break;

			}

			// Monsters
			if (isMonster == true) {
				int r = rand() % 4;

				switch (r) {

				case 0:
					if (vMCoord == 0) {
						break;
					}
					if (Mturn == 0) currentMChar = '.';
					map[vMCoord][hMCoord] = currentMChar;
					destMChar = map[vMCoord - 1][hMCoord];
					map[vMCoord - 1][hMCoord] = monsterChar;
					vMCoord--;
					currentMChar = destMChar;
					Mturn++;
					break;
				case 1:
					if (hMCoord == 0) {
						break;
					}
					if (Mturn == 0) currentMChar = '.';
					map[vMCoord][hMCoord] = currentMChar;
					destMChar = map[vMCoord][hMCoord - 1];
					map[vMCoord][hMCoord - 1] = monsterChar;
					hMCoord--;
					currentMChar = destMChar;
					Mturn++;
					break;
				case 2:
					if (vMCoord == 7) {
						break;
					}
					if (Mturn == 0) currentMChar = '.';
					map[vMCoord][hMCoord] = currentMChar;
					destMChar = map[vMCoord + 1][hMCoord];
					map[vMCoord + 1][hMCoord] = monsterChar;
					vMCoord++;
					currentMChar = destMChar;
					Mturn++;
					break;
				case 3:
					if (hMCoord == 14) {
						break;
					}
					if (Mturn == 0) currentMChar = '.';
					map[vMCoord][hMCoord] = currentMChar;
					destMChar = map[vMCoord][hMCoord + 1];
					map[vMCoord][hMCoord + 1] = monsterChar;
					hMCoord++;
					currentMChar = destMChar;
					Mturn++;
					break;
				}
			}

		} while (keyPress != 'Q' && keyPress != 'q' && gameWin == false && gameLose == false);

		// Win / Lose Conditions
		if (gameLose == true) {
			system("CLS");
			cout << "...YOU LOSE..." << endl << endl;
			system("PAUSE");
		}

		if (gameWin == true) {
			system("CLS");
			cout << "... YOU WIN!!..." << endl << endl;
			cout << "Score: " << turn << endl;
			cout << "Enter Name: ";
			cin >> winnerName;
			fout << winnerName;
			fout << turn;
			fout.close();

		}
	}
}

// Initializer / Main Menu
void init() {
	srand(time(0));

	system("title Jack's Dungeon Crawler");
	system("cls");

	// Raw Map Generator
	fin.open("map.txt", ios::in);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 15; j++) {
			map[i][j] = '.';
		}
	}

	// Spike Generator
	for (int i = 0; i < 8; i++) {
		
		for (int j = 0; j < 15; j++) {

		int r = rand() % 100;
		//cout << r;
		
		if (r < 20) {
			map[i][j] = '*';
		}
		
		}
	}
	
	// Monster Generator
	for (int i = 0; i < 8; i++) {

		for (int j = 0; j < 10; j++) {

			int r = rand() % 100;
			//cout << r;

			if (r < 1) {
				map[i][j] = 'M';
				isMonster = true;

				vMCoord = i;
				hMCoord = j;
				break;
			}

		}
	}

	// Player + Exit Generator
	map[3][0] = 'P';
	int r = rand() % 7;
	map[r][14] = 'E';

	
	// Main Menu
	cout << endl;
	cout << "	1 - Begin		2 - View Highscores		Q - Quit" << endl;
	cout << endl;

	char keyPress = 0;

	do {

		keyPress = _getch();

		switch (keyPress) {

		case '1':
			break;
		case '2':
			viewHighscores();
			break;
		}
		

	} while (keyPress == '0');
	
}

// View Highscores
void viewHighscores() {

	fin >> highscore;
	system("PAUSE");
}
