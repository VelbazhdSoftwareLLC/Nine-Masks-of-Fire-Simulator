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
	{ 1, 1, 1, 1, 1 },
	{ 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 2, 2 },
	{ 0, 1, 2, 1, 0 },
	{ 2, 1, 0, 1, 2 },
	{ 0, 0, 1, 0, 0 },
	{ 2, 2, 1, 2, 2 },
	{ 1, 2, 2, 2, 1 },
	{ 1, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 1 },
	{ 1, 2, 1, 2, 1 },
	{ 0, 1, 0, 1, 0 },
	{ 2, 1, 2, 1, 2 },
	{ 1, 1, 0, 1, 1 },
	{ 1, 1, 2, 1, 1 },
	{ 0, 1, 1, 1, 0 },
	{ 2, 1, 1, 1, 2 },
	{ 2, 0, 0, 0, 2 },
	{ 0, 2, 2, 2, 0 },
	{ 0, 2, 0, 2, 0 },
};

int baseGameReels[5][113] = {
	{	8,	2,	6,	9,	6,	2,	6,	0,	9,	2,	7,	9,	10,	9,	7,	6,	10,	4,	10,	4,	8,	6,	10,	2,	9,	7,	9,	5,	8,	6,	8,	9,	4,	2,	5,	0,	2,	0,	5,	0,	5,	0,	7,	0,	10,	8,	9,	3,	6,	5,	9,	6,	3,	8,	2,	5,	2,	4,	10,	2,	9,	10,	0,	10,	0,	9,	10,	2,	8,	10,	2,	7,	8,	10,	8,	4,	10,	8,	2,	3,	10,	8,	10,	7,	10,	7,	10,	6,	9,	2,	8,	7,	6,	10,	5,	9,	10,	9,	0,	9,	0,	7,	10,	9,	6,	9,	7,	9,	8,	9,	10,	7,	9,	},
	{	9,	10,	9,	4,	5,	6,	8,	6,	7,	2,	6,	9,	10,	9,	6,	0,	1,	0,	10,	3,	10,	5,	9,	10,	1,	10,	1,	10,	9,	8,	9,	3,	8,	6,	7,	10,	2,	1,	9,	7,	6,	10,	9,	6,	8,	1,	10,	2,	8,	2,	8,	10,	9,	8,	2,	7,	8,	6,	0,	8,	0,	10,	6,	10,	7,	3,	2,	8,	1,	10,	7,	5,	9,	4,	5,	2,	0,	10,	0,	8,	7,	9,	7,	5,	9,	7,	9,	1,	8,	5,	10,	9,	1,	10,	5,	4,	9,	4,	9,	10,	9,	4,	10,	2,	10,	2,	6,	8,	6,	9,	7,	9,	7,	},
	{	10,	5,	9,	10,	4,	10,	3,	0,	1,	10,	0,	7,	10,	8,	4,	2,	5,	9,	8,	9,	6,	9,	5,	10,	0,	1,	6,	2,	4,	7,	9,	1,	9,	8,	3,	9,	10,	9,	10,	8,	1,	10,	5,	10,	3,	10,	9,	7,	10,	1,	8,	2,	7,	9,	6,	2,	6,	1,	9,	2,	9,	7,	10,	9,	1,	9,	8,	2,	8,	9,	10,	2,	8,	0,	6,	7,	5,	6,	8,	6,	9,	7,	6,	8,	7,	10,	4,	9,	8,	9,	5,	6,	1,	8,	10,	2,	10,	8,	1,	7,	6,	2,	9,	4,	7,	9,	10,	0,	6,	10,	5,	10,	7,	},
	{	5,	9,	1,	9,	2,	9,	10,	6,	5,	8,	5,	2,	9,	10,	4,	6,	5,	10,	9,	2,	8,	6,	10,	6,	10,	6,	9,	10,	3,	2,	9,	8,	10,	4,	10,	8,	1,	10,	9,	7,	10,	8,	6,	2,	7,	6,	7,	8,	1,	10,	7,	1,	8,	7,	4,	10,	1,	0,	8,	0,	10,	0,	9,	4,	7,	2,	8,	1,	8,	7,	8,	5,	4,	8,	3,	6,	9,	8,	9,	5,	2,	9,	3,	10,	9,	10,	9,	0,	2,	0,	10,	0,	9,	7,	10,	1,	5,	9,	6,	10,	7,	10,	9,	2,	9,	6,	1,	7,	9,	6,	10,	7,	9,	},
	{	8,	9,	10,	2,	10,	2,	9,	5,	2,	10,	8,	7,	0,	10,	0,	2,	9,	5,	8,	10,	8,	5,	9,	4,	9,	7,	9,	8,	7,	9,	8,	10,	7,	9,	7,	10,	9,	10,	0,	9,	0,	10,	2,	0,	10,	0,	10,	8,	2,	10,	8,	2,	5,	4,	7,	6,	10,	7,	6,	7,	6,	10,	6,	2,	8,	6,	8,	10,	5,	10,	7,	8,	9,	7,	9,	2,	9,	0,	9,	0,	3,	0,	8,	6,	9,	0,	2,	10,	4,	10,	7,	10,	9,	10,	6,	4,	5,	2,	9,	4,	6,	9,	6,	2,	6,	5,	3,	9,	3,	8,	9,	2,	6,	},
};

int freeSpinsReels[5][113] = {
	{	2,	7,	8,	6,	3,	6,	2,	6,	7,	6,	3,	5,	9,	5,	10,	7,	9,	2,	8,	5,	6,	7,	10,	7,	9,	10,	2,	10,	6,	9,	8,	10,	2,	10,	8,	10,	8,	10,	9,	5,	9,	10,	8,	6,	8,	4,	8,	0,	9,	0,	3,	8,	9,	6,	9,	7,	2,	9,	0,	5,	0,	9,	2,	9,	10,	9,	10,	2,	2,	10,	4,	9,	0,	5,	0,	4,	8,	4,	2,	7,	10,	0,	10,	7,	8,	7,	8,	9,	10,	9,	5,	0,	8,	4,	10,	6,	8,	9,	10,	7,	10,	9,	7,	0,	6,	0,	9,	6,	10,	9,	10,	9,	10,	},
	{	9,	2,	8,	2,	8,	9,	1,	10,	5,	9,	5,	9,	1,	6,	1,	7,	9,	7,	8,	10,	7,	10,	7,	10,	2,	6,	8,	6,	10,	6,	9,	10,	8,	1,	9,	7,	6,	7,	10,	6,	7,	10,	9,	10,	6,	9,	2,	10,	5,	4,	10,	8,	4,	10,	3,	10,	9,	10,	2,	1,	7,	4,	8,	10,	1,	10,	9,	1,	9,	7,	9,	8,	9,	1,	9,	8,	0,	3,	0,	5,	0,	8,	5,	7,	9,	8,	9,	8,	10,	2,	9,	4,	6,	7,	6,	4,	10,	6,	8,	0,	9,	0,	10,	0,	9,	5,	9,	8,	10,	3,	10,	5,	6,	},
	{	5,	9,	1,	3,	8,	9,	0,	10,	7,	9,	4,	9,	6,	10,	6,	10,	7,	2,	10,	1,	10,	4,	10,	6,	1,	8,	7,	5,	7,	9,	0,	10,	9,	10,	2,	10,	6,	9,	7,	6,	10,	8,	2,	10,	9,	7,	9,	8,	6,	0,	5,	9,	5,	6,	7,	9,	8,	10,	1,	6,	7,	10,	8,	9,	8,	1,	2,	9,	6,	7,	9,	8,	10,	2,	9,	1,	5,	10,	9,	10,	9,	5,	9,	0,	6,	3,	10,	0,	8,	9,	8,	4,	7,	10,	3,	4,	7,	10,	8,	2,	4,	8,	6,	8,	10,	1,	9,	8,	1,	9,	5,	1,	10,	},
	{	7,	2,	7,	10,	2,	7,	10,	7,	8,	7,	10,	1,	0,	10,	0,	9,	7,	9,	6,	9,	2,	9,	4,	8,	9,	8,	0,	8,	0,	10,	9,	10,	7,	10,	1,	10,	5,	7,	6,	4,	9,	6,	8,	6,	9,	8,	10,	5,	7,	1,	6,	2,	9,	1,	6,	9,	1,	9,	5,	9,	3,	9,	6,	9,	10,	1,	9,	5,	10,	8,	10,	1,	6,	8,	7,	6,	3,	6,	4,	10,	0,	10,	0,	9,	10,	1,	10,	8,	10,	9,	8,	10,	4,	9,	2,	9,	10,	8,	9,	5,	10,	8,	3,	7,	2,	4,	5,	8,	10,	5,	9,	6,	8,	},
	{	7,	10,	9,	10,	8,	10,	6,	8,	9,	6,	7,	6,	7,	0,	10,	2,	0,	2,	6,	8,	2,	7,	9,	2,	9,	5,	10,	9,	2,	10,	2,	4,	9,	10,	9,	10,	9,	10,	5,	3,	7,	9,	0,	5,	0,	5,	7,	6,	7,	10,	4,	10,	8,	6,	9,	3,	10,	9,	8,	9,	10,	9,	2,	9,	0,	4,	0,	8,	7,	10,	10,	9,	10,	9,	3,	9,	2,	9,	10,	0,	7,	0,	8,	10,	8,	9,	6,	8,	9,	8,	7,	8,	6,	8,	0,	5,	9,	8,	4,	6,	2,	7,	10,	6,	10,	4,	0,	6,	5,	8,	2,	10,	5,	},
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

int freeSpinsRestartAmount = 0;

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

	int win = paytable[numberOfScatters][0];

	if (win > 0 && freeSpinsAmount == 0) {
		baseGameSymbolsMoney[numberOfScatters][0] += win;
		baseGameSymbolsHitFrequency[numberOfScatters][0]++;
	} else if (win > 0 && freeSpinsAmount > 0) {
		freeSpinsSymbolsMoney[numberOfScatters][0] += win;
		freeSpinsSymbolsHitFrequency[numberOfScatters][0]++;
	}

	return win;
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

	int win = paytable[numberOfScatters][1];

	if (win > 0 && freeSpinsAmount == 0) {
		baseGameSymbolsMoney[numberOfScatters][1] += win;
		baseGameSymbolsHitFrequency[numberOfScatters][1]++;
	} else if (win > 0 && freeSpinsAmount > 0) {
		freeSpinsSymbolsMoney[numberOfScatters][1] += win;
		freeSpinsSymbolsHitFrequency[numberOfScatters][1]++;
	}

	return win;
}

int differentSevensLineWin(int &number, int &symbol, int line[5],
		int multiplier) {
	if (line[0] != 3 && line[0] != 4 && line[0] != 5) {
		symbol = -1;
		return 0;
	}

	number = 0;
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

int wildLineWin(int &number, int &symbol, int line[5], int multiplier) {
	if (line[0] != 2) {
		symbol = -1;
		return 0;
	}

	number = 0;
	for (int i = 0; i < 5; i++) {
		if (line[i] != 2) {
			break;
		}

		number++;
	}

	symbol = 2;
	return paytable[number][2];
}

int lineWin(int &number, int &symbol, int line[5], int multiplier) {
	int number1 = 0;
	int number2 = 0;
	int symbol1 = -1;
	int symbol2 = -1;
	int win1 = differentSevensLineWin(number1, symbol1, line, multiplier);
	int win2 = wildLineWin(number2, symbol2, line, multiplier);

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

	int number3 = 0;
	for (int i = 0; i < 5; i++) {
		if (line[i] == symbol3) {
			number3++;
		} else {
			break;
		}
	}

	int win3 = paytable[number3][symbol3] * multiplier;

	if (win1 > win2) {
		if (win1 > win3) {
			number = number1;
			symbol = symbol1;
			return win1;
		} else if (win1 < win3) {
			number = number3;
			symbol = symbol3;
			return win3;
		} else {
			number = number3;
			symbol = symbol3;
			return win3;
		}
	} else if (win1 < win2) {
		if (win2 > win3) {
			number = number2;
			symbol = symbol2;
			return win2;
		} else if (win2 < win3) {
			number = number3;
			symbol = symbol3;
			return win3;
		} else {
			number = number3;
			symbol = symbol3;
			return win3;
		}
	} else {
		if (win1 > win3 && win2 > win3) {
			number = number1;
			symbol = symbol1;
			return win1;
		} else if (win1 < win3 && win2 < win3) {
			number = number3;
			symbol = symbol3;
			return win3;
		} else {
			number = number3;
			symbol = symbol3;
			return win3;
		}
	}

	number = 0;
	symbol = -1;
	return 0;
}

int linesWin(int multiplier) {
	int win = 0;

	for (int l = 0; l < 20; l++) {
		int line[5] = { -1, -1, -1, -1, -1 };
		for (int i = 0; i < 5; i++) {
			int index = lines[l][i];
			line[i] = view[i][index];
		}

		int number = 0;
		int symbol = -1;
		int result = lineWin(number, symbol, line, multiplier);

		if (result > 0 && freeSpinsAmount == 0) {
			baseGameSymbolsMoney[number][symbol] += result;
			baseGameSymbolsHitFrequency[number][symbol]++;
		} else if (win > 0 && freeSpinsAmount > 0) {
			freeSpinsSymbolsMoney[number][symbol] += result;
			freeSpinsSymbolsHitFrequency[number][symbol]++;
		}

		win += result;
	}

	return (win);
}

void freeSpins(int &amount, int &multiplier) {
	int index = rand() % 614;

	amount = freeSpinsWheel[0][index];
	multiplier = freeSpinsWheel[1][index];
}

void freeSpinsSetup() {
	int numberOfScatters = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			if (view[i][j] == 1) {
				numberOfScatters++;
			}
		}
	}

	if (numberOfScatters == 3 && freeSpinsAmount == 0) {
		freeSpins(freeSpinsAmount, freeSpinsMultiplier);
		freeSpinsRestartAmount = freeSpinsAmount;
		totalNumberOfFreeSpinsStarts++;
	} else if (numberOfScatters == 3 && freeSpinsAmount > 0) {
		freeSpinsAmount += freeSpinsRestartAmount;
		totalNumberOfFreeSpinsRestarts++;
	}
}

void singleFreeSpin() {
	spin(freeSpinsReels, 113);

	int win = linesWin(freeSpinsMultiplier) + scatterWin() + freeSpinsWin();

	wonMoney += win;
	freeSpinsMoney += win;

	if (win > 0) {
		freeSpinsHitFrequency++;
	}

	if (freeSpinsMaxWin < win) {
		freeSpinsMaxWin = win;
	}

	freeSpinsSetup();
}

void singleBaseGame() {
	spin(baseGameReels, 113);

	int win = linesWin(1) + scatterWin() + freeSpinsWin();

	wonMoney += win;
	baseGameMoney += win;

	if (win > 0) {
		baseGameHitFrequency++;
	}

	if (baseGameMaxWin < win) {
		baseGameMaxWin = win;
	}

	freeSpinsAmount = 0;
	freeSpinsMultiplier = 1;
	freeSpinsRestartAmount = 0;
	freeSpinsSetup();

	while (freeSpinsAmount > 0) {
		totalNumberOfFreeSpins++;
		singleFreeSpin();
		freeSpinsAmount--;
	}
}

void monteCarloSimulation() {
	for (long g = 0L; g < 1000000/*00L*/; g++) {
		totalNumberOfGames++;
		lostMoney += totalBet;
		singleBaseGame();

		if (totalNumberOfGames % 10000 == 0) {
			cerr << (double) wonMoney / (double) lostMoney << endl;
		}
	}
}

void printDataStructures() {
	cout << "Paytable:" << endl;
	for (int i = 0; i < 10; i++) {
		cout << "\t" << i << " of";
	}
	cout << endl;
	for (int j = 0; j < 11; j++) {
		cout << j << "\t";
		for (int i = 0; i < 10; i++) {
			cout << paytable[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Lines:" << endl;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 5; j++) {
			cout << lines[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Base Game Reels:" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 113; j++) {
			cout << setw(3) << baseGameReels[i][j];
		}
		cout << endl;
	}
	cout << endl;

	cout << "Free Spins Reels:" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 113; j++) {
			cout << setw(3) << freeSpinsReels[i][j];
		}
		cout << endl;
	}
	cout << endl;

	cout << "Base Game Reels:" << endl;
	{
		int counters[5][11] = {
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		};
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 113; j++) {
				counters[i][baseGameReels[i][j]]++;
			}
		}
		for (int i = 0; i < 5; i++) {
			cout << "\tReel " << (i + 1);
		}
		cout << endl;
		for (int j = 0; j < 11; j++) {
			cout << j << "\t";
			for (int i = 0; i < 5; i++) {
				cout << counters[i][j] << "\t";
			}
			cout << endl;
		}
		cout << "---------------------------------------------" << endl;
		cout << "Total:\t";
		long combinations = 1L;
		for (int i = 0; i < 5; i++) {
			int sum = 0;
			for (int j = 0; j < 11; j++) {
				sum += counters[i][j];
			}
			cout << sum << "\t";
			if (sum != 0) {
				combinations *= sum;
			}
		}
		cout << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Combinations:\t" << combinations;
	}
	cout << endl;

	cout << "Free Spins Reels:" << endl;
	{
		int counters[5][11] = {
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		};
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 113; j++) {
				counters[i][freeSpinsReels[i][j]]++;
			}
		}
		for (int i = 0; i < 5; i++) {
			cout << "\tReel " << (i + 1);
		}
		cout << endl;
		for (int j = 0; j < 11; j++) {
			cout << j << "\t";
			for (int i = 0; i < 5; i++) {
				cout << counters[i][j] << "\t";
			}
			cout << endl;
		}
		cout << "---------------------------------------------" << endl;
		cout << "Total:\t";
		long combinations = 1L;
		for (int i = 0; i < 5; i++) {
			int sum = 0;
			for (int j = 0; j < 11; j++) {
				sum += counters[i][j];
			}
			cout << sum << "\t";
			if (sum != 0) {
				combinations *= sum;
			}
		}
		cout << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Combinations:\t" << combinations;
	}
	cout << endl;
	cout << endl;

	cout << "Free Spins Wheel:" << endl;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 614; j++) {
			cout << setw(3) << freeSpinsWheel[i][j];
		}
		cout << endl;
	}
}

void printStatistics() {
	cout << "Won money:\t" << wonMoney << endl;
	cout << "Lost money:\t" << lostMoney << endl;
	cout << "Total Number of Games:\t" << totalNumberOfGames << endl;
	cout << endl;
	cout << "Total RTP:\t" << ((double) wonMoney / (double) lostMoney) << "\t\t"
			<< (100.0 * (double) wonMoney / (double) lostMoney) << "%" << endl;
	cout << "Base Game RTP:\t" << ((double) baseGameMoney / (double) lostMoney)
			<< "\t\t" << (100.0 * (double) baseGameMoney / (double) lostMoney)
			<< "%" << endl;
	cout << "Free Spins RTP:\t" << ((double) freeSpinsMoney / (double) lostMoney)
			<< "\t\t" << (100.0 * (double) freeSpinsMoney / (double) lostMoney)
			<< "%" << endl;
	cout << endl;
	cout << "Hit Rate in Base Game:\t"
			<< ((double) baseGameHitFrequency / (double) totalNumberOfGames)
			<< "\t\t"
			<< (100.0 * (double) baseGameHitFrequency
					/ (double) totalNumberOfGames) << "%" << endl;
	cout << "Hit Rate in Free Spins:\t"
			<< ((double) freeSpinsHitFrequency / (double) totalNumberOfFreeSpins)
			<< "\t\t"
			<< (100.0 * (double) freeSpinsHitFrequency
					/ (double) totalNumberOfFreeSpins) << "%" << endl;
	cout << "Hit Rate Base Game into Free Spins:\t"
			<< ((double) totalNumberOfFreeSpinsStarts
					/ (double) totalNumberOfGames) << "\t\t"
			<< (100.0 * (double) (totalNumberOfFreeSpinsStarts)
					/ (double) totalNumberOfGames) << "%" << endl;
	cout << "Hit Rate Free Spins into Free Spins:\t"
			<< ((double) totalNumberOfFreeSpinsRestarts
					/ (double) totalNumberOfFreeSpinsStarts) << "\t\t"
			<< (100.0 * (double) (totalNumberOfFreeSpinsRestarts)
					/ (double) totalNumberOfFreeSpinsStarts) << "%" << endl;
	cout << endl;
	cout << "Max Win in Base Game:\t" << baseGameMaxWin << endl;
	cout << "Max Win in Free Spins:\t" << freeSpinsMaxWin << endl;

	cout << endl;
	cout << endl;
	cout << "Base Game Symbols RTP:" << endl;
	cout << "\t";
	for (int i = 0; i < 10; i++) {
		cout << i << "of\t";
	}
	cout << endl;
	for (int j = 0; j < 11; j++) {
		cout << j << "\t";
		for (int i = 0; i < 10; i++) {
			cout << (double) baseGameSymbolsMoney[i][j] / (double) lostMoney
					<< "\t";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Base Game Symbols Hit Frequency:" << endl;
	cout << "\t";
	for (int i = 0; i < 10; i++) {
		cout << i << "of\t";
	}
	cout << endl;
	for (int j = 0; j < 11; j++) {
		cout << j << "\t";
		for (int i = 0; i < 10; i++) {
			cout << (double) baseGameSymbolsHitFrequency[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Base Game Symbols Hit Rate:" << endl;
	cout << "\t";
	for (int i = 0; i < 10; i++) {
		cout << i << "of\t";
	}
	cout << endl;
	for (int j = 0; j < 11; j++) {
		cout << j << "\t";
		for (int i = 0; i < 10; i++) {
			cout
					<< (double) baseGameSymbolsHitFrequency[i][j]
							/ (double) totalNumberOfGames << "\t";
		}
		cout << endl;
	}

	cout << endl;
	cout << "Free Spins Symbols RTP:" << endl;
	cout << "\t";
	for (int i = 0; i < 10; i++) {
		cout << i << "of\t";
	}
	cout << endl;
	for (int j = 0; j < 11; j++) {
		cout << j << "\t";
		for (int i = 0; i < 10; i++) {
			cout << (double) freeSpinsSymbolsMoney[i][j] / (double) lostMoney
					<< "\t";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Free Spins Symbols Hit Frequency:" << endl;
	cout << "\t";
	for (int i = 0; i < 10; i++) {
		cout << i << "of\t";
	}
	cout << endl;
	for (int j = 0; j < 11; j++) {
		cout << j << "\t";
		for (int i = 0; i < 10; i++) {
			cout << (double) freeSpinsSymbolsHitFrequency[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Free Spins Symbols Hit Rate:" << endl;
	cout << "\t";
	for (int i = 0; i < 10; i++) {
		cout << i << "of\t";
	}
	cout << endl;
	for (int j = 0; j < 11; j++) {
		cout << j << "\t";
		for (int i = 0; i < 10; i++) {
			cout
					<< (double) freeSpinsSymbolsHitFrequency[i][j]
							/ (double) totalNumberOfGames << "\t";
		}
		cout << endl;
	}
}

int main() {
	srand(time(NULL));

	monteCarloSimulation();

	printDataStructures();
	cout << endl;

	printStatistics();
	cout << endl;

	return 0;
}
