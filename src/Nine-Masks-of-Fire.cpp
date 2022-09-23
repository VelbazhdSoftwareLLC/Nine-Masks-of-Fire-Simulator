//============================================================================
// Name        : Nine-Masks-of-Fire.cpp
// Author      : Todor Balabanov
// Version     : 1.0
// Copyright   : Velbazhd Software LLC, 2022 (c)
// Description : Slot Game Monte Carlo Simulator
//============================================================================

#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <iostream>

using namespace std;

int paytable[10][11] = {
	{     0,  0,    0,   0,   0,   0,  0,  0,  0,  0,  0, },
	{     0,  0,    0,   0,   0,   0,  0,  0,  0,  0,  0, },
	{     0,  0,    0,   0,   0,   0,  0,  0,  0,  0,  0, },
	{    20, 20,  125,  50,  25,  20, 10, 10,  5,  5,  5, },
	{   100,  0,  500, 325, 125,  75, 20, 20, 15,  8,  8, },
	{   300,  0, 2500, 750, 400, 150, 65, 65, 40, 20, 20, },
	{   800,  0,    0,   0,   0,   0,  0,  0,  0,  0,  0, },
	{  2000,  0,    0,   0,   0,   0,  0,  0,  0,  0,  0, },
	{ 10000,  0,    0,   0,   0,   0,  0,  0,  0,  0,  0, },
	{ 40000,  0,    0,   0,   0,   0,  0,  0,  0,  0,  0, },
};

int lines[20][5] = {
	{1,1,1,1,1},
	{0,0,0,0,0},
	{2,2,2,2,2},
	{0,1,2,1,0},
	{2,1,0,1,2},
	{0,0,1,0,0},
	{2,2,1,2,2},
	{1,2,2,2,1},
	{1,0,0,0,1},
	{1,0,1,0,1},
	{1,2,1,2,1},
	{0,1,0,1,0},
	{2,1,2,1,2},
	{1,1,0,1,1},
	{1,1,2,1,1},
	{0,1,1,1,0},
	{2,1,1,1,2},
	{2,0,0,0,2},
	{0,2,2,2,0},
	{0,2,0,2,0},
};

int baseGameReels[5][113] = {
	{0,1,2,3,4,5,6,7,8,9,10},
	{0,1,2,3,4,5,6,7,8,9,10},
	{0,1,2,3,4,5,6,7,8,9,10},
	{0,1,2,3,4,5,6,7,8,9,10},
	{0,1,2,3,4,5,6,7,8,9,10},
};

int freeSpinsReels[5][113] = {
	{0,1,2,3,4,5,6,7,8,9,10},
	{0,1,2,3,4,5,6,7,8,9,10},
	{0,1,2,3,4,5,6,7,8,9,10},
	{0,1,2,3,4,5,6,7,8,9,10},
	{0,1,2,3,4,5,6,7,8,9,10},
};

int freeSpinsWheel[2][614] = { { 30, 30, 30, 30, 30, 30, 30,
		30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 25, 25, 25, 25, 25,
		25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
		25, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
		20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
		20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
		20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
		20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
		20, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
		15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
		15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
		15, 15, 15, 15, 15, 15, 15, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
		12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
		12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
		12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
		12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
		12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
		12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
		12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
		12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, }, { 3, 3, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, }, };

int singleBet = 1;

int totalBet = 20;

long wonMoney = 0L;

long lostMoney = 0L;

long totalNumberOfGames = 0L;

long totalNumberOfFreeSpins = 0L;

long totalNumberOfFreeSpinsStarts = 0L;

long totalNumberOfFreeSpinsRestarts = 0L;

long baseGameMoney = 0L;

long freeSpinsMoney = 0L;

long baseGameMaxWin = 0L;

long freeSpinsMaxWin = 0L;

long baseGameHitFrequency = 0L;

long freeSpinsHitFrequency = 0L;

int freeSpinsAmount = 0;

int freeSpinsMultiplier = 0;

int view[5][3] = {
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
};

long baseGameSymbolsMoney[10][11] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
};

long baseGameSymbolsHitFrequency[10][11] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
};

long freeSpinsSymbolsMoney[10][11] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
};

long freeSpinsSymbolsHitFrequency[10][11] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
};

void print(int view[5][3]) {
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 5; i++) {
			cout << setw(4) << view[i][j];
		}

		cout << endl;
	}
}

int *const freeSpins(int *const parameters) {
	int index = rand() % 614;

	parameters[0] = freeSpinsWheel[0][index];
	parameters[1] = freeSpinsWheel[1][index];

	return parameters;
}

void spin(int reels[5][113], int length) {
	for (int i = 0, u, m, d; i < 5; i++) {
		u = rand() % length;
		m = u + 1;
		d = u + 2;

		m = m % length;
		d = d % length;

		view[i][0] = reels[i][u];
		view[i][1] = reels[i][m];
		view[i][2] = reels[i][d];
	}
}

int scatterWin() {
	int numberOfScatters = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			if (view[i][j] == 0) {
				numberOfScatters++;
			}
		}
	}

	return paytable[numberOfScatters][0];
}

int freeSpinsWin() {
	int numberOfScatters = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			if (view[i][j] == 1) {
				numberOfScatters++;
			}
		}
	}

	return paytable[numberOfScatters][1];
}

int differentSevensLineWin(int &symbol, int line[5], int multiplier) {
	if (line[0] != 3 && line[0] != 4 && line[0] != 5) {
		return 0;
	}

	int number = 0;
	bool different = false;
	for (int i = 0; i < 5; i++) {
		if (line[i] != 3 && line[i] != 4 && line[i] != 5) {
			break;
		}

		if (line[i] != line[0]) {
			different = true;
		}

		number++;
	}

	if (different == false) {
		symbol = -1;
		return 0;
	}

	symbol = 6;
	return paytable[number][6];
}

int wildLineWin(int &symbol, int line[5], int multiplier) {
	if (line[0] != 2) {
		return 0;
	}

	int number = 0;
	for (int i = 0; i < 5; i++) {
		if (line[i] != 2) {
			break;
		}

		number++;
	}

	symbol = 2;
	return paytable[number][2];
}

int lineWin(int &symbol, int line[5], int multiplier) {
	int symbol1 = -1;
	int symbol2 = -1;
	int win1 = differentSevensLineWin(symbol1, line, multiplier);
	int win2 = wildLineWin(symbol2, line, multiplier);

	int symbol3 = line[0];
	for (int i = 0; i < 5; i++) {
		if (line[i] != 2) {
			symbol3 = line[i];
			break;
		}
	}

	for (int i = 0; i < 5; i++) {
		if (line[i] == 2) {
			line[i] = symbol3;
		} else {
			break;
		}
	}

	int number = 0;
	for (int i = 0; i < 5; i++) {
		if (line[i] == symbol3) {
			number++;
		} else {
			break;
		}
	}

	int win3 = paytable[number][symbol3] * multiplier;

	if (win1 > win2) {
		if (win1 > win3) {
			symbol = symbol1;
			return win1;
		} else if (win1 < win3) {
			symbol = symbol3;
			return win3;
		} else {
			symbol = symbol3;
			return win3;
		}
	} else if (win1 < win2) {
		if (win2 > win3) {
			symbol = symbol2;
			return win2;
		} else if (win2 < win3) {
			symbol = symbol3;
			return win3;
		} else {
			symbol = symbol3;
			return win3;
		}
	} else {
		if (win1 > win3 && win2 > win3) {
			symbol = symbol1;
			return win1;
		} else if (win1 < win3 && win2 < win3) {
			symbol = symbol3;
			return win3;
		} else {
			symbol = symbol3;
			return win3;
		}
	}

	return 0;
}

int main() {
	srand (time(NULL) );

	int wheel[2];
	freeSpins(wheel);
	cout << wheel[0] << endl;
	cout << wheel[1] << endl;

	spin(baseGameReels, 11);
	print( view );

	return 0;
}
