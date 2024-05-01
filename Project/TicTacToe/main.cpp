#include <iostream>
#include <windows.h>
#include <algorithm>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cctype>
#include <bitset>

using namespace std;

HANDLE console=GetStdHandle(STD_OUTPUT_HANDLE);

#define ROW 3
#define COL 3

/**==========PUBLIC VARIABLES==========**/
//playerName
string playerName;

//Button
char keypress, button, menuButton;
const char left_key='a', right_key='d', up_key='w', down_key='s';
const char xKey = 'x', oKey = 'o';
const char quit_key = 'q', activate_key = ' ', retryKey = 'r', menuKey = 'm';

//Menu Button (position)
short menuChoice = 0;
short menuBPX = 10;
short menuBPY = 14;
const short orgPX = menuBPX, orgPY = menuBPY;

//Pieces (position)
short piecePX = 28;
short piecePY = 6;
const short PPX = piecePX;
const short PPY = piecePY;

//Game On
char playerSymbol;
short countSlot = 0;
short turnChoice, playerChoice, random_seed;
const short horizontalMove = 7, verticalMove = 4;
const short numHButton = 3, numVButton = 3;

//Bool Variables
bool menuActive = true;
bool emptySlot = true;
bool changeTurn = true;
bool activeMode = true;
bool startGame = true;

//Board Layer
char boardLayer[ROW][COL];

//Positions in array
short posX = 0, posY = 0;
short posXValue = 0, posYValue = 0;

//Machine Generator
short mXValue[3]; short mYValue[3];
short posM9[9]; short indexM9 = 0;

/**==========PUBLIC FUNCTION==========**/
void clearScreen();
void gotoxy(short, short);

void introText();
void introTextAnimation();
void introScreen();
void loadingScreen(string,short,short,short);

void menuText();
void menuAnimation(short,char&,short&,short&,short&,short,short);
void mainMenu();

void printBoard();

void Button(char&,short&,short&,short&,short&);
void horizontalMovement(short,char&,short&,short&);
void verticalMovement(short,char&,short&,short&);

void playMechanism(char&,short&,short&,short&,short&);
void playerTurn(char&,char,short&,short&,short&,short&);
void machineTurn(char,short&,short&,short&,short&);

void machineData(short&,short&);
void machineLearning(short,short,short&);
void checkEmpty(unsigned short,unsigned short);
void arrPos(short&,short&,short&,short&);

void modeScreen();
void gameScreenSetup();
void gameOn();
void checkWin();

void otherMechanism(char&);
void gameSetting();
void endScreen();

/**==========CLS==========**/
void clearScreen() {
#ifdef _WIN32
    system("cls");
#endif
}

/**==========CORDINATES==========**/
void gotoxy(short x, short y){
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Cursor = {x,y};
    SetConsoleCursorPosition(screen, Cursor);
}

/**==========MAIN===========**/
int main(){
    clearScreen();

    introScreen();

    while(menuActive){ mainMenu(); }
}

/**===========INTRO===========**/
//Loading animation
void loadingScreen(string loading, short numLoop, short x, short y){
    for(unsigned short loadingLoop =0; loadingLoop < numLoop; loadingLoop++){
        for (unsigned short i = 0; i < 10; ++i) {
            gotoxy(x,y);
            cout << loading;
            for (unsigned short j = 0; j <= i; ++j){ cout << "."; }
            for (unsigned short j = i + 1; j < 10; ++j){cout << " "; }
            cout << flush;

            Sleep(100);
            cout << "\r";
        }
    }
}

//Symbol text of Tic Tac Toe
void introText(){
    SetConsoleTextAttribute(console,0b00001111);
    cout << "\t\t   ____________   ____________   ____________  \n"
            "\t\t  /__________ /| /__________ /| /__________ /| \n"
            "\t\t |           | ||           | ||           | | \n"
            "\t\t |____ T  ___|/ |____ T  ___|/ |____ T  ___|/  \n"
            "\t\t     | I | |        | A | |        | O | |     \n"
            "\t\t     | C | |        | C | |        | E | |     \n"
            "\t\t     |___|/         |___|/         |___|/     \n";
}

//Intro text animation
void introTextAnimation(){
    clearScreen();
    const unsigned short introDuration = 200;
    for (int i = 0; i <= 5; ++i) {
        clearScreen();
        for (int j = 0; j < i; ++j) { cout << "\n"; }
        introText();
        Sleep(introDuration);
    }

    menuBPX = orgPX; menuBPY = orgPY; menuChoice = 0;
}

//Intro (main screen)
void introScreen(){
    SetConsoleTextAttribute(console,0b00001111);
    //Input player name & check error whether input without name
    do{
        clearScreen();
        gotoxy(20,10); cout << "YOUR NAME: "; cin >> playerName;
    }while(playerName == "\n");

    clearScreen(); loadingScreen("Processing",2,20,10); clearScreen();

    //Uppercase first letter of playerName
    if(!playerName.empty()){ playerName[0] = toupper(playerName[0]); }
    gotoxy(20,10); cout << "HI, WELCOME " << playerName << " :)";

    Sleep(5000); introTextAnimation();

    menuText(); //Transfer to MAIN MENU

}

/**==========MAIN MENU==========**/
//MENU TEXT
void menuText(){
    SetConsoleTextAttribute(console, 0b00000110);
    gotoxy(orgPX,menuBPY); cout << "[";
    gotoxy(orgPX + 17, menuBPY); cout << "]";
    SetConsoleTextAttribute(console, 0b00001111);
    gotoxy(orgPX + 6 , menuBPY); cout << "START \t\tOPTIONS\t\t   EXIT";
    gotoxy(orgPX + 12, menuBPY + 3); cout << "> Press SPACE to select <";
}

//MOVE LEFT & RIGHT (with a box text)
void menuAnimation
(short orgX, char& menuButton, short& menuChoice,
 short& mx, short& my, short numButton, short HMove){
    SetConsoleTextAttribute(console, 0b00000110);
    for(unsigned short i = 0; i < numButton; i++){
        if(mx == orgX + HMove * i){
            menuChoice = i + 1;
        }
    }

    if(menuButton == 'a' || menuButton == 'A'){
        gotoxy(mx,my); cout << " ";
        gotoxy(mx + HMove, my); cout << " ";

        mx = mx - HMove;
        if(mx < orgX){ mx = orgX; }
        gotoxy(mx,my);

        cout << "["; gotoxy(mx + HMove, my);
        cout << "]"; gotoxy(mx,my);
    }

    if(menuButton == 'd' || menuButton == 'D'){
        gotoxy(mx,my); cout << " ";
        gotoxy(mx + HMove, my); cout << " ";

        mx = mx + HMove;
        if(mx > (HMove * (numButton - 1)) + orgX)
            { mx = HMove * (numButton - 1) + orgX; }
        gotoxy(mx, my);

        cout << "["; gotoxy(mx + HMove, my);
        cout << "]"; gotoxy(mx,my);
    }
}

//MAIN MENU (main screen)
void mainMenu(){
    gotoxy(menuBPX,menuBPY);
    if(kbhit()){
        keypress = getch();
        if(keypress == right_key  || keypress == 'A'
           ||keypress == left_key || keypress == 'D'
           ||keypress == activate_key)
                { menuButton = keypress; }

        menuAnimation(orgPX,menuButton,menuChoice,menuBPX,menuBPY,3,17);

        if(menuButton == ' '){
            switch(menuChoice){
                case 1: modeScreen(); break;
                case 2: gameSetting(); break;
                case 3: endScreen(); break;
            }
        }
    }
}

/**==========GAME SETTING==========**/
void gameSetting(){
    clearScreen();

    gotoxy(10,10); cout << "Sorry :( We will update this feature in the future";

    Sleep(3000);

    introTextAnimation(); menuText();
    while(menuActive){ mainMenu(); }
}

/**==========END SCREEN==========**/
void endScreen(){
    clearScreen();

    gotoxy(10,10); cout << "Thanks for playing, " << playerName << " :) See you soon";

    Sleep(3000);

    HWND consoleWindow = GetConsoleWindow();
    if (consoleWindow != NULL){ ShowWindow(consoleWindow, SW_HIDE); }

    main();
}

/**==========CONSOLE============**/
//A,D Keys to move left and right
void horizontalMovement
(short orgX, char& moveButton, short& mx, short& my){
    if(moveButton == 'a' || moveButton == 'A'){
        mx = mx - horizontalMove;
        if(mx < orgX){ mx = orgX; }
        gotoxy(mx,my);
    }

    if(moveButton == 'd' || moveButton == 'D'){
        mx = mx + horizontalMove;
        if(mx > (horizontalMove * (numHButton - 1)) + orgX)
            { mx = horizontalMove * (numHButton - 1) + orgX; }
        gotoxy(mx, my);
    }
}

//W,S Keys to move up and down
void verticalMovement
(short orgY, char& moveButton, short& mx, short& my){
    if(moveButton == 'w' || moveButton == 'W'){
        my = my - verticalMove;
        if(my < orgY){ my = orgY; }
        gotoxy(mx, my);
    }

    if(moveButton == 's' || moveButton == 'S'){
        my = my + verticalMove;
        if(my > (verticalMove * (numVButton - 1)) + orgY)
            { my = (verticalMove * (numVButton - 1)) + orgY; }
        gotoxy(mx,my);
    }
}

//Button (console)
void Button(char& button, short& mx, short& my, short& posX, short& posY){
    gotoxy(mx,my);
    if(kbhit()){
        keypress = getch();
        if(keypress == right_key  || keypress == 'A'
           ||keypress == left_key || keypress == 'D'
           || keypress == up_key  || keypress == 'W'
           || keypress == down_key|| keypress == 'S'
           || keypress == xKey    || keypress == 'X'
           || keypress == oKey    || keypress == 'O'
           || keypress == quit_key|| keypress == 'Q'
           || keypress == retryKey|| keypress == 'R'
           || keypress == menuKey || keypress == 'M')
                { button = keypress; }

        horizontalMovement(PPX,button,mx,my);

        verticalMovement(PPY,button,mx,my);

        playMechanism(button,mx,my,posX,posY);

        otherMechanism(button);
    }
}

//Other mechanism in button functions
void otherMechanism(char& button){
    SetConsoleTextAttribute(console,0b00001111);
    //Restart the game (mode screen)
    if(button == retryKey || button == 'R'){
        startGame = false; clearScreen(); loadingScreen("Restarting",2,20,10);

        clearScreen(); modeScreen();
    }

    //Quit to menu (menu screen)
    if(button == quit_key || button == 'Q'){
        startGame = false; clearScreen(); loadingScreen("Returning to menu",2,20,10);

        clearScreen(); introTextAnimation(); menuText();

        while(menuActive){ mainMenu(); }
    }
}

/**==========GAMEPLAY MECHANISM==========**/
//Mechanism in Gameplay
void playMechanism(char& button, short& mx, short& my, short& posX, short& posY){
    //Check empty slot with specific pieces
    if(boardLayer[posX][posY] == 'x' || boardLayer[posX][posY] == 'X'||
       boardLayer[posX][posY] == 'o' || boardLayer[posX][posY] == 'O'){
        emptySlot = false;
    } else emptySlot = true;

    //Check empty slot before input pieces
    if(emptySlot){
        switch(playerChoice){
        case 1: playerSymbol = xKey;
            { if(button == 'X'){ button = xKey; }
            playerTurn(button,xKey,mx,my,posX,posY); break; }
        case 2: playerSymbol = oKey;
            { if(button == 'O'){ button = oKey; }
            playerTurn(button,oKey,mx,my,posX,posY); break; }}
        checkWin();

        while(!changeTurn){
        switch(playerChoice){
        case 1:
            { machineTurn(oKey,mx,my,posX,posY); break; }
        case 2:
            { machineTurn(xKey,mx,my,posX,posY); break; }}}}

    arrPos(mx,my,posX,posY); checkWin();
}

//Player Turn
void playerTurn
(char& playButton, char keySet, short& mx, short& my, short& posX, short& posY){
    if(playButton == keySet){
    while(changeTurn){
        //Print playerTurn from flexible variables
        boardLayer[posX][posY] = keySet;
        SetConsoleTextAttribute(console, FOREGROUND_RED);
        cout << boardLayer[posX][posY];

        //Restore printed value into 1D array(with ASCII character)
        indexM9 = 0;
        for(unsigned short i = 0; i < ROW; i++){
            for(unsigned short j = 0; j < COL; j++){
                posM9[indexM9++] = boardLayer[i][j];
            }
        } countSlot++; //Count slots whether they're full

        changeTurn = false;}} //Change turn to machine
}

/**==========MACHINE LEARNING==========**/
void machineData(short& mx, short& my){
    //Store value of positions of pieces with moves
    for(unsigned short i = 0; i < 3; i++){
        mXValue[i] = mx + horizontalMove*i;
        mYValue[i] = my + verticalMove*i;
    }

    //Store value into matrix 3x3 (ASCII character) and array 1D (check when random a seed)
    indexM9 = 0;
    for(unsigned short i = 0; i < ROW; i++){
        for(unsigned short j = 0; j < COL; j++){
            boardLayer[i][j] = mXValue[i] + mYValue[j];
            posM9[indexM9++] = boardLayer[i][j];
        }
    }
}

//Machine Turn
void machineTurn(char keySet, short& mx, short& my, short& posX, short& posY){
        //Random generator for moves not include in ML
        srand(time(NULL));
        do{
            random_seed = posM9[rand() % 9];
        }while(random_seed >= 111);

        //Machine learning (block && attack)
        machineLearning(PPX,PPY,random_seed);


        //Store positions in fixed array (with random seed value)
        for(unsigned short i = 0; i < ROW; i++){
            for(unsigned short j = 0; j < COL; j++){
                if(random_seed == boardLayer[i][j]){
                    posX = i; posY = j;
                }
            }
        }

        //Store positions in 2D plane (with random seed value)
        for(unsigned short i = PPX;
            i <= PPX + horizontalMove*(numHButton - 1); i+=horizontalMove){
            for(unsigned short j = PPY;
                j <= PPY + verticalMove*(numVButton - 1); j+=verticalMove){
                    if(random_seed == i + j){ mx = i; my = j; }
            }
        }

        //Print machineTurn from stored variables
        gotoxy(mx,my);
        boardLayer[posX][posY] = keySet;
        SetConsoleTextAttribute(console, FOREGROUND_BLUE);
        cout << boardLayer[posX][posY];

        //Restore printed value into 1D array(with ASCII character)
        indexM9 = 0;
        for(unsigned short i = 0; i < ROW; i++){
            for(unsigned short j = 0; j < COL; j++){
                posM9[indexM9++] = boardLayer[i][j];
            }
        } countSlot++; //Count slots whether they're full

        changeTurn = true; //Change turn to player
}

//Machine Learning
void machineLearning(short orgX, short orgY, short& random_seed){
    for(unsigned short i = 0; i < ROW; i++){
        for(unsigned short j = 0; j < COL; j++){
            if(emptySlot && boardLayer[i][j]){
                //Check if there are same pieces in a diagonal line (135*)
                if(boardLayer[0][0] == boardLayer[1][1]){
                    random_seed = (orgX + horizontalMove * 2)
                                    + (orgY + verticalMove * 2);
                    checkEmpty(2,2);
                }
                if(boardLayer[0][0] == boardLayer[2][2]){
                    random_seed = (orgX + horizontalMove * 1)
                                    + (orgY + verticalMove * 1);
                    checkEmpty(1,1);
                }
                if(boardLayer[1][1] == boardLayer[2][2]){
                    random_seed = (orgX + horizontalMove * 0)
                                    + (orgY + verticalMove * 0);
                    checkEmpty(0,0);
                }

                //Check if there are same pieces in a diagonal line (45*)
                if(boardLayer[0][2] == boardLayer[1][1]){
                    random_seed = (orgX + horizontalMove * 2)
                                    + (orgY + verticalMove * 0);
                    checkEmpty(2,0);
                }
                if(boardLayer[0][2] == boardLayer[2][0]){
                    random_seed = (orgX + horizontalMove * 1)
                                    + (orgY + verticalMove * 1);
                    checkEmpty(1,1);
                }
                if(boardLayer[1][1] == boardLayer[2][0]){
                    random_seed = (orgX + horizontalMove * 0)
                                    + (orgY + verticalMove * 2);
                    checkEmpty(0,2);
                }

                //Check if there are same pieces in a row
                else if(i < 1){
                    if(boardLayer[i][j] == boardLayer[i+1][j]){
                        random_seed = (orgX + horizontalMove * 2)
                                        + (orgY + verticalMove * j);
                        checkEmpty(i+2,j);
                    }
                    if(boardLayer[i][j] == boardLayer[i+2][j]){
                        random_seed = (orgX + horizontalMove * 1)
                                        + (orgY + verticalMove * j);
                        checkEmpty(i+1,j);
                    }
                    if(boardLayer[i+1][j] == boardLayer[i+2][j]){
                        random_seed = (orgX + horizontalMove * 0)
                                        + (orgY + verticalMove * j);
                        checkEmpty(i+0,j);
                    }
                }

                //Check if there are same pieces in a column
                else if(j < 1){
                    if(boardLayer[i][j] == boardLayer[i][j+1]){
                        random_seed = (orgX + horizontalMove * i)
                                        + (orgY + verticalMove * 2);
                        checkEmpty(i,j+2);
                    }
                    if(boardLayer[i][j] == boardLayer[i][j+2]){
                        random_seed = (orgX + horizontalMove * i)
                                        + (orgY + verticalMove * 1);
                        checkEmpty(i,j+1);
                    }
                    if(boardLayer[i][j+1] == boardLayer[i][j+2]){
                        random_seed = (orgX + horizontalMove * i)
                                        + (orgY + verticalMove * 0);
                        checkEmpty(i,j+0);
                    }
                }
            }
        }
    }
}

//Check empty during learning process (Machine Learning)
void checkEmpty(unsigned short i, unsigned short j){
    if(boardLayer[i][j] == 'x' || boardLayer[i][j] == 'o'){
        srand(time(NULL));
        do{
            random_seed = posM9[rand() % 9];
        }while(random_seed >= 111);
    }
}

//Store array positions when pos & move values changes
void arrPos(short& mx, short& my, short& posX, short& posY){
    for(short i = 0; i < 3; i++){
        if(mx == PPX + horizontalMove * i){ posX = i; }
        if(my == PPY + verticalMove * i) { posY = i; }
    }
}

/**==========BOARD TEMPLATE==========**/
void printBoard(){
    SetConsoleTextAttribute(console, 0b00001111);
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            boardLayer[i][j] = '-';
        }
    } cout << "\n";

    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            gotoxy((PPX - 3) + i * horizontalMove, (PPY - 1) + j * verticalMove);
            cout << " ===== ";
        } cout << "\n";
        for(int j = 0; j < COL; j++){
            gotoxy((PPX - 3) + i * horizontalMove, (PPY + 0) + j * verticalMove);
            cout << " | " << boardLayer[i][j] << " | ";
        } cout << "\n";
        for(int j = 0; j < COL; j++){
            gotoxy((PPX - 3) + i * horizontalMove, (PPY + 1) + j * verticalMove);
            cout << " ===== ";
        } cout << "\n";
    }
}

/**==========MODE SCREEN==========**/
//Setup text and box text
void msSetup(){
    SetConsoleTextAttribute(console,0b00001111);
    menuBPX = 36, menuBPY = 13;
    gotoxy(28,10); cout << "OXOXOX--PLAY MODE--XOXOXO";

    gotoxy(15,menuBPY); cout << "Choose your turn: ";
    gotoxy(40,menuBPY); cout << "GO  FIRST";
    gotoxy(55,menuBPY); cout << "SECOND TURN";

    gotoxy(15,menuBPY+3); cout << "Choose your sign: ";
    gotoxy(40,menuBPY+3); cout << "x: X Sign";
    gotoxy(55,menuBPY+3); cout << "o: O Sign";

    SetConsoleTextAttribute(console, 0b00000110);
    gotoxy(menuBPX,menuBPY); cout << "[";
    gotoxy(menuBPX+16,menuBPY); cout << "]";

    SetConsoleTextAttribute(console, 0b00001100);
    gotoxy(16,20); cout << "< SPACE: to Select > ";
    gotoxy(39,20); cout << "< Q:  Quit to Main Menu >";
}

//Mode screen (before gameOn)
void modeScreen(){
    clearScreen(); activeMode = true; msSetup();
    SetConsoleTextAttribute(console, 0b00000110);

    const short orgMSPX = menuBPX, orgMSPY = menuBPY;
    while(activeMode){
        gotoxy(menuBPX,menuBPY);
        if(kbhit()){
            keypress = getch();
            if(keypress == right_key  || keypress == 'A'
               ||keypress == left_key || keypress == 'D'
               ||keypress == quit_key || keypress == 'Q'
               ||keypress == retryKey || keypress == 'R'
               ||keypress == activate_key)
                    { menuButton = keypress; }

            otherMechanism(menuButton);

            menuAnimation(orgMSPX,menuButton,menuChoice,menuBPX,menuBPY,2,16);

            if(menuButton == ' '){
                if(menuBPY == 13){ turnChoice = menuChoice; menuChoice = 0; }
                menuBPX = orgMSPX, menuBPY = orgMSPY + 3;
                gotoxy(menuBPX,menuBPY); cout << "[";
                gotoxy(menuBPX+16,menuBPY); cout << "]";
            }

            if(menuBPY == 16 && menuButton == ' ')
                { playerChoice = menuChoice;
                if(playerChoice == 1 || playerChoice == 2)
                    { activeMode = false; startGame = true; gameOn(); } }
        }
    }
}

/**==========GAME ON==========**/
void gameScreenSetup(){
    clearScreen(); loadingScreen("Creating a battle",2,20,10); clearScreen();

    startGame = true; printBoard();

    //Introduction Setup
    SetConsoleTextAttribute(console,FOREGROUND_GREEN);

    for(unsigned short i = 60; i <= 85; i++){ gotoxy(i,5); cout << "="; gotoxy(i,15); cout << "="; }
    for(unsigned short i = 6; i <= 14; i++){ gotoxy(60,i); cout << "|"; gotoxy(85,i); cout << "|"; }

    gotoxy(66,6);  cout << "INTRODUCTION";
    gotoxy(62,8);  cout << "W,S: Move up & down";
    gotoxy(62,9);  cout << "A,D: Move left & right";
    gotoxy(62,11); cout << "R: Restart the game";
    gotoxy(62,13); cout << "Q: Quit to menu";
}

void gameOn(){
    gameScreenSetup();

    piecePX = PPX; piecePY = PPY;
    machineData(piecePX,piecePY);

    //If machine goes first
    if(turnChoice == 2){
    switch(playerChoice){
    case 1:
        { machineTurn(oKey,piecePX,piecePY,posX,posY); changeTurn = true; break; }
    case 2:
        { machineTurn(xKey,piecePX,piecePY,posX,posY); changeTurn = true; break; }}
    countSlot = 1;
    if(countSlot == 9){ checkWin(); }}

    //Game start
    while(startGame){ Button(button,piecePX,piecePY,posX,posY); }
}

/**==========CHECK WIN==========**/
void checkWin(){
    for(unsigned short i = 0; i < ROW; i++){
        for(unsigned short j = 0; j < COL; j++){
            /**DIAGONAL LINE CASE**/
            if(//DIAGONAL LINE (ANGLE 135)
               (boardLayer[0][0] == boardLayer[1][1] &&
                boardLayer[0][0] == boardLayer[2][2])||
               //DIAGONAL LINE (ANGLE 45)
               (boardLayer[0][2] == boardLayer[1][1] &&
                boardLayer[0][2] == boardLayer[2][0]))
                //Check if player won
                { if(boardLayer[1][1] == playerSymbol)
                    { gotoxy(PPX,17);
                    cout << "YOU WON, " << playerName << "!"; startGame = false;
                } else{ gotoxy(32,17); cout << "AI WON!"; startGame = false;}
                countSlot--; }

            /**NORMAL CASE**/
            //Match in a row
            else if(i < 1){
                if(boardLayer[i][j] == boardLayer[i+1][j] &&
                   boardLayer[i+1][j] == boardLayer[i+2][j])
                   //Check if player won
                    { if(boardLayer[i+1][j] == playerSymbol)
                        { gotoxy(PPX,17);
                        cout << "YOU WON, " << playerName << "!"; startGame = false;
                    } else{ gotoxy(32,17); cout << "AI WON!"; startGame = false; }
                    countSlot--; }}

            //Match in a column
            else if(j < 1){
                if(boardLayer[i][j] == boardLayer[i][j+1] &&
                   boardLayer[i][j+1] == boardLayer[i][j+2])
                   //Check if player won
                    { if(boardLayer[i][j+1] == playerSymbol)
                        { gotoxy(PPX,17);
                        cout << "YOU WON, " << playerName << "!"; startGame = false;
                    } else{ gotoxy(32,17); cout << "AI WON!"; startGame = false; }
                    countSlot--; }}

            /**DRAW MATCH**/
            else if(countSlot == 9){
                gotoxy(PPX,17); cout << "DRAW MATCH!"; startGame = false;
            }
        }
    }

    if(!startGame){
        countSlot = 0; startGame = false; activeMode = false; menuChoice = 0;

        Sleep(3000); loadingScreen("Returning to menu...",2,PPX,17);

        clearScreen();

        SetConsoleTextAttribute(console,0b00001111);

        introTextAnimation(); menuText();

        while(menuActive){ mainMenu(); }
    }
}
