#ifndef STANDARD_FUNCTION_H
#define STANDARD_FUNCTION_H

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <Windows.h>
#include <cstdlib>

using namespace std;

void clearScreen() {
#ifdef _WIN32
	system("cls");
#endif
}

void pauseScreen() {
	cout << endl << endl;
	system("pause");
	cout << endl << endl;
};

string ListOfCat[5] = {
	"British Shorthair",
	"Siamese",
	"Maine Coon",
	"Persian",
	"Sphynx"
};

float ListOfCatPrice[5] = { 500, 400, 800, 500, 1500 };

string ListOfDog[5] = {
	"German Shepherd",
	"Bulldog",
	"Golden Retriever",
	"Sieberian Husky",
	"Poodle"
};

float ListOfDogPrice[5] = { 500, 1500, 500, 600, 1000 };

#endif STANDARD_FUNCTION_H
