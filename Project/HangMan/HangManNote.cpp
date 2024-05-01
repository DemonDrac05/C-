#include <iostream>
#include <windows.h>
#include <algorithm>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cctype>
#include <bitset>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

#define MAX 100

const short MAX_ANIMAL = 100;

short numOfAnimals = 0;

char faultSymbol[6] = {NULL,NULL,' ',NULL,NULL,NULL};

short numOfFault = 0;
short countLetter = 0;
short countFault = 0;

short randomValue;
string quest;
short lengthQ;
char* letter;
char boardLayer[MAX];
char inputLetter;




bool startingGame = true;

/*****==========GLOBAL FUNCTION==========*****/
void clearScreen();
void gotoxy(short,short);

struct animalHints{
    string nameOfAnimals[MAX_ANIMAL];
}; animalHints animal;

void transferTextIntoMain();
void randomGenerator();

void drawing();
void gameOn(); void varSetUp();
void boardDisplay(); void quizDisplay(); void inputDisplay();
void checkWin();
/*****===================================*****/

// Clear screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#endif
}

// Check coordinates
void gotoxy(short x, short y){
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursor = {x,y};
    SetConsoleCursorPosition(screen,cursor);
}

/*****==========MAIN==========*****/
int main()
{
    randomGenerator();

    gameOn();

    return 0;
}

/*****==========SET UP==========*****/
/****==========.TXT -> .CPP==========****/
void transferTextIntoMain(){
    // Specify the input file name
    string filename = "listOfAnimal.txt";

    // Open the file for reading
    ifstream inputFile(filename);

    // Read each line from the file
    string line;
    short index = 0;
    while(getline(inputFile, line)) {
        istringstream iss(line);

        // Split the line into cells using tab as a delimiter
        string cell;
        while (getline(iss, cell, '\t')) {
            if (index < MAX_ANIMAL) {
                // Store both headers and data cells in the same array
                animal.nameOfAnimals[index++] = cell;
            }
        }
    }

    // Close the file
    inputFile.close();

    // Uppercase elements in text
    for (short i = 0; i < index; ++i){
        for(short j = 0; j < animal.nameOfAnimals[i].length(); j++){
            animal.nameOfAnimals[i][j] = toupper(animal.nameOfAnimals[i][j]);
        } numOfAnimals++;
    }
}

/****==========RANDOM GENERATOR==========****/
void randomGenerator(){
    transferTextIntoMain();

    srand(time(NULL));
    randomValue = rand() % numOfAnimals;
    quest = animal.nameOfAnimals[randomValue];
}

/****==========VARIABLES==========****/
void varSetUp(){
    // Convert string into char
    lengthQ = quest.length();

    letter = new char[lengthQ + 1];

    // Create an array to store and display words
    for(unsigned short i = 0; i < lengthQ; i++)
        boardLayer[i] = '_';
}

void drawing(){
    switch(numOfFault){
    case 1:{ faultSymbol[0] = 'O'     ; break; }
    case 2:{ faultSymbol[1] = '|'     ; break; }
    case 3:{ faultSymbol[2] = '/'     ; break; }
    case 4:{ faultSymbol[3] = char(92); break; }
    case 5:{ faultSymbol[4] = '/'     ; break; }
    case 6:{ faultSymbol[5] = char(92); break; }
    }

    cout << " ========| \n"
            " ||      "<< faultSymbol[0] <<" \n"
            " ||     "<< faultSymbol[2] << faultSymbol[1] << faultSymbol[3] <<"  \n"
            " ||     "<< faultSymbol[4]<< " " << faultSymbol[5] <<"   \n"
            " ||        \n"
            "/  " << char(92);

}

/*****==========GAME ON==========*****/
void gameOn(){
    varSetUp();
    while(startingGame){
        boardDisplay();
        for(unsigned short i = 0; i < lengthQ; i++){
            while(boardLayer[i] == inputLetter){
                boardDisplay();
            }
        }
        checkWin();
    }
}

/****==========ORDER DISPLAY==========****/
void boardDisplay(){ quizDisplay(); inputDisplay(); }

void quizDisplay(){
    clearScreen(); drawing();
    gotoxy(5,7);
    for(unsigned short i = 0; i < lengthQ; i++)
        cout << boardLayer[i] << " ";
}

void inputDisplay(){
    gotoxy (10,10);
    cout << "Input your letter: "; cin >> inputLetter;
    inputLetter = toupper(inputLetter);
}

/****==========CHECK WIN==========****/
void checkWin(){
    strcpy(letter, quest.c_str());
    for(unsigned short i = 0; i < lengthQ; i++){
        if(letter[i] == inputLetter && boardLayer[i] != inputLetter){
            boardLayer[i] = letter[i];
            countLetter++; countFault++;
        } else continue; }

    if(countFault == 0){ numOfFault++; }
    else countFault = 0;

    if(countLetter == lengthQ){
        quizDisplay();
        gotoxy(25,14);
        cout << "Splendid";
        startingGame = false;
    }

    if(numOfFault == 6){
        quizDisplay();
        gotoxy(25,14);
        cout << "Sorry, it's " << quest;
        startingGame = false;
    }
}


