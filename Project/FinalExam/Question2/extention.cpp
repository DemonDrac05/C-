#include <iostream>
#include <windows.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <bitset>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

/**==========VARIABLES==========**/
int lineNumber = 0, newIndex = -1;

short winIndex = 0, numOfRound = 0;

char answer; short randomNumber;

bool startingGame = true, question = false;

short playerChoice = -1;

string listOfChoice[3] = {"Rock","Paper","Scissors"};

/**==========GLOBAL FUNCTION==========**/
void ruleSetUp();
void setUpFile();
void outputToFile();
void menuScreen();
void displayInfo();
void gameOn();
void questionAfterGameplay();

/**==========CORDINATES==========**/
void gotoxy(short x, short y){
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Cursor = {x,y};
    SetConsoleCursorPosition(screen, Cursor);
}

/**==========CORDINATES==========**/
void clearScreen(){
#ifdef _WIN32
    system("cls");
#endif
}

/**==========PLAYER INFO==========**/
struct Player{
    string name;
    int winScore = 0;
    int lostScore = 0;
    int totalScore = 0;
    float percentWin;
}; Player player[100];

/**==========BACK UP==========**/
struct BackupData{
    string name;
    int winScore = 0;
    int lostScore = 0;
    int totalScore = 0;
    float percentWin;
}; BackupData bk[100];

/**==========MAIN==========**/
int main() {
    setUpFile();

    menuScreen();

    outputToFile();
}

/**==========MENU==========**/
void menuScreen(){
    while(answer != 'Y' && answer != 'y'
              && answer != 'N' && answer != 'n'){
        clearScreen();
        cout << "\n\n\t\tWelcome to RPS Game, " << player[newIndex].name;

        cout << "\n\n\t\tDo you want to start now? (Y/y -> Yes ### N/n -> No)";

        cout << "\n\n\t\tYour answer: "; cin >> answer;
    }

    if(answer == 'y' || answer == 'Y'){
        clearScreen();
        ruleSetUp(); system("pause"); gameOn();
    }

    else switch(answer){
    case 'N': case 'n':
        clearScreen();
        cout << "\n\n\t\tHope to see you soon, " << player[newIndex].name; break;
    default:
        clearScreen();
        cout << "\n\n\t\tError!"; break;
    }
}
/**==========IFSTREAM==========**/
void setUpFile(){
    //Access to the file
    ifstream input("playerList.txt");

    string line; int lineNumber = 0;
    //Read line by line
    while(getline(input,line)){
        lineNumber++; //Count the row orders and total of rows (after the first row in .txt)

        /**Store values by order**/
        input >> player[lineNumber-1].name;
        //Erase all of spaces after name
        player[lineNumber-1].name.erase(remove_if(player[lineNumber-1].name.begin(),
                                        player[lineNumber-1].name.end(),::isspace),
                              player[lineNumber-1].name.end());

        input >> player[lineNumber-1].winScore;
        input >> player[lineNumber-1].lostScore;
        input >> player[lineNumber-1].totalScore;
        input >> player[lineNumber-1].percentWin;
        /**Backup when needed**/
        bk[lineNumber-1].name = player[lineNumber-1].name;
        bk[lineNumber-1].winScore = player[lineNumber-1].winScore;
        bk[lineNumber-1].lostScore = player[lineNumber-1].lostScore;
        bk[lineNumber-1].totalScore = player[lineNumber-1].totalScore;
        bk[lineNumber-1].percentWin = player[lineNumber-1].percentWin;
    }
    //Close the accessibility
    input.close();

    string answerString;
    cout << "\n\n\t\tMay I have your name please? ^.^ ";
    cout << "\n\n### INTRODUCTION: "
    << "\n***If you want to choose existing account, please input 'L' or 'l' to see list of registered players."
    << "\n***If not, please input your new name in the same answer box below.";

    cout << "\n\n\t\tYOUR ANSWER: "; cin >> answerString;

    if(answerString == "L" || answerString == "l"){
        clearScreen();
        cout << "\n\n\t\tList of registered player(s): " << endl;
        for(unsigned int i = 0; i < lineNumber - 1; i++)
            cout << "\t\t" <<i + 1 << ". " << player[i].name << endl;
        cout << "Your answer: "; cin >> answerString;
    }

    //Check if the answer is same with data registered
    for(unsigned short i = 0; i < lineNumber - 1; i++)
        if(answerString == to_string(i+1) || answerString == player[i].name)
            newIndex = i;
    //If not the data will add new one (through structure)
    if(newIndex == -1){
        newIndex = lineNumber - 1;
        player[newIndex].name = answerString;
        player[newIndex].winScore = 0;
        player[newIndex].lostScore = 0;
        lineNumber++;
    }
}
/**==========OFSTREAM==========**/
void outputToFile(){
    //Access to export contents to file
    ofstream output("playerList.txt");
    //First row of the content (where lineNumber will ignore the value)
    output << "Name		Win	  Lost	    Total     %Win\n";

    /**Output contents by order and decorate for the space after each element**/
    for(unsigned short i = 0; i < lineNumber - 1; i++){
        //Name
        output << player[i].name;
        for(unsigned short space = 0; space < 10 - player[i].name.length(); space++)
            output << " ";
        //winScore
        output << "\t" << player[i].winScore;

        int countDigit = 0, checkScore = player[i].winScore;
        while(checkScore != 0){ checkScore = checkScore / 10; countDigit++; }
        if(checkScore == 0) countDigit = 1;

        for(unsigned short space = 0; space < 10 - countDigit; space++)
            output << " ";
        //lostScore
        output << player[i].lostScore;

        checkScore = player[i].lostScore; countDigit = 0;
        while(checkScore != 0){ checkScore = checkScore / 10; countDigit++; }
        if(checkScore == 0) countDigit = 1;

        for(unsigned short space = 0; space < 10 - countDigit; space++)
            output << " ";
        //totalScore
        player[i].totalScore = player[i].winScore - player[i].lostScore;
        output << player[i].totalScore;

        checkScore = player[i].totalScore; countDigit = 0;
        while(checkScore != 0){ checkScore = checkScore / 10; countDigit++; }
        if(checkScore == 0) countDigit = 1;

        for(unsigned short space = 0; space < 10 - countDigit; space++)
            output << " ";
        //percentWin
        output << player[i].percentWin << endl;
    }

    output.close();
}
/**==========RULE==========**/
void ruleSetUp(){
        SetConsoleTextAttribute(console,FOREGROUND_RED);
        cout << "\n\t\tREAD CAREFULLY";
        SetConsoleTextAttribute(console,0b00001111);
        cout << "\n\t - You should not enter any undefined choice";
        cout << "\n\t - This is a virtual game so loss and win ";
        cout << "can always be happened";

        SetConsoleTextAttribute(console,FOREGROUND_RED);
        cout << "\n\n\t\tRULE BEFORE GAME STARTS: ";
        SetConsoleTextAttribute(console,0b00001111);
        cout << "\n\t = Rock will defeat Scissors";
        cout << "\n\t = Scissors will defeat Paper";
        cout << "\n\t = Paper will defeat ";
        cout << "\n\n\t # Win will earn you 200 points";
        cout << "\n\t # Draw will earn you 100 points";
        cout << "\n\t # Loss will take from you 50 points\n\n\t\t";
}
/**==========DISPLAY PLAYER INFO==========**/
void displayInfo(){
    gotoxy(50,2); cout << player[newIndex].name << "'s Information:";
    gotoxy(50,3); cout << "***Total score: " << player[newIndex].totalScore;
    gotoxy(50,4); cout << "***(%)Win: " << player[newIndex].percentWin;
    gotoxy(0,0);
}
/**==========GAME START==========**/
void gameOn(){
    while(startingGame){
        playerChoice = -1;
        //Check if there is no wrong number inputed
        while(playerChoice < 0 || playerChoice > 2){
            clearScreen(); displayInfo();
            cout << "\n\n\t\t" << player[newIndex].name << " VS Computer";
            cout << "\n\n{ Rock -> 0 }";
            cout << "{ Paper -> 1 }";
            cout << "{ Scissors -> 2 }";

            SetConsoleTextAttribute(console,0b00001111);

            cout << "\n\n\t\tInput your choice: "; cin >> playerChoice;
        }

        clearScreen(); displayInfo(); cout << "\n\n\t\t ";
        switch(playerChoice){
        case 0:
            playerChoice = 0;
            cout << "You've chosen " << listOfChoice[playerChoice]; break;
        case 1:
            playerChoice = 1;
            cout << "You've chosen " << listOfChoice[playerChoice]; break;
        case 2:
            playerChoice = 2;
            cout << "You've chosen " << listOfChoice[playerChoice]; break;
        }

        srand(time(NULL));
        randomNumber = rand() % 2;
        cout << "\n\n\t\t Computer's chosen " << listOfChoice[randomNumber];

        cout << "\n\n\t\t ";
        if(playerChoice == randomNumber){
            player[newIndex].winScore += 50;

            SetConsoleTextAttribute(console,FOREGROUND_GREEN);
            cout << "DRAW! You're lucky this time >:)";
        } else switch(playerChoice){
        case 0: //Rock
            switch(randomNumber){
            case 1:
                player[newIndex].lostScore += 100;

                SetConsoleTextAttribute(console,FOREGROUND_RED);
                cout << "You lost! Sorry, better next time...";
                break;
            case 2:
                player[newIndex].winScore += 200; winIndex++;

                SetConsoleTextAttribute(console,FOREGROUND_BLUE);
                cout << "You win! Nice Game 0:)";
                break;
            } break;
        case 1: //Paper
            switch(randomNumber){
            case 2:
                player[newIndex].lostScore += 100;

                SetConsoleTextAttribute(console,FOREGROUND_RED);
                cout << "You lost! Sorry, better next time...";
                break;
            case 0:
                player[newIndex].winScore += 200; winIndex++;

                SetConsoleTextAttribute(console,FOREGROUND_BLUE);
                cout << "You win! Splendid 0:)";
                break;
            } break;
        case 2: //Scissors
            switch(randomNumber){
            case 0:
                player[newIndex].lostScore += 100;

                SetConsoleTextAttribute(console,FOREGROUND_RED);
                cout << "You lost! Sorry, better next time...";
                break;
            case 1:
                player[newIndex].winScore += 200; winIndex++;

                SetConsoleTextAttribute(console,FOREGROUND_BLUE);
                cout << "You win! GG 0:)";
                break;
            } break;
        }

        numOfRound++;

        startingGame = false; question = true;

        player[newIndex].totalScore = player[newIndex].winScore - player[newIndex].lostScore;
        player[newIndex].percentWin = double(winIndex)/double(numOfRound);
    }
    questionAfterGameplay();
}
/**==========QUESTION AFTER GAMEPLAY==========**/
void questionAfterGameplay(){
    Sleep(3000); clearScreen(); answer = NULL;
    SetConsoleTextAttribute(console, 0b00001111);
    while(answer != 'Y' && answer != 'y'
              && answer != 'N' && answer != 'n'
              && question == true){
        clearScreen();
        cout << "\n\n\t\tDo you want to continue? ";
        cout << " (Y/y -> Yes ### N/n -> No)";
        cout << "\n\n\t\tYour answer: "; cin >> answer;
    } clearScreen();
    if(answer == 'y' || answer == 'Y'){ question = false; startingGame = true; gameOn(); }

    if(answer == 'n' || answer == 'N') answer = NULL;


    while(answer != 'Y' && answer != 'y'
              && answer != 'N' && answer != 'n'
              && question == true){
        clearScreen();
        cout << "\n\n\t\tBefore you leave, do you want to save your process? ";
        cout << " (Y/y -> Yes ### N/n -> No)";
        cout << "\n\n\t\tYour answer: "; cin >> answer;
    } clearScreen();
    if(answer == 'y' || answer == 'Y'){
        question = false;
        cout << "\n\n\t\tHope to see you soon, " << player[newIndex].name;
        Sleep(2000);
    }

    if(answer == 'n' || answer == 'N') answer = NULL;

    while(answer != 'Y' && answer != 'y'
              && answer != 'N' && answer != 'n'
              && question == true){
        clearScreen();
        cout << "\n\n\t\tMaybe you want to save your last process before deleting this one?";
        cout << " (Y/y -> Yes ### N/n -> No)";
        cout << "\n\n\t\tYour answer: "; cin >> answer;
    } clearScreen();
    if((answer == 'y' || answer == 'Y') && question == true){
        question = false;

        player[newIndex].name = bk[newIndex].name;
        player[newIndex].winScore = bk[newIndex].winScore;
        player[newIndex].lostScore = bk[newIndex].lostScore;
        player[newIndex].totalScore = bk[newIndex].totalScore;
        player[newIndex].totalScore = bk[newIndex].totalScore;

        cout << "\n\n\t\tSweet, thanks for playing my game. See you soon " << player[newIndex].name;
    }

    if((answer == 'n' || answer == 'N') && question == true){
        question = false;
        cout << "\n\n\t\tAlright, I have deleted all your process. Hope you love my game "
        << player[newIndex].name;

        player[newIndex].winScore = 0;
        player[newIndex].lostScore = 0;
        player[newIndex].totalScore = 0;
        player[newIndex].totalScore = 0;
    }
}

