#include <iostream>
#include <time.h>
#include <limits>  // it's for limiting of user to write only numbers

using namespace std;

short i, j, userRow, userCol;

char userMove, PCmove;

const int rowEx = 3, colEx = 3, rowGm = 3, colGm = 3, rows = 3, cols = 3;

short PCrow, PCcol;

const int winCombination[][3] = { /* the empty brackets [] without anything inside are used to
    indicate that the size of the first dimension of the array is unspecified and will be
    determined by the compiler based on the provided initializer list*/
    {0, 1, 2}, // Row 1
    {3, 4, 5}, // Row 2
    {6, 7, 8}, // Row 3
    {0, 3, 6}, // Column 1
    {1, 4, 7}, // Column 2
    {2, 5, 8}, // Column 3
    {0, 4, 8}, // Diagonal from top-left to bottom-right
    {2, 4, 6}  // Diagonal from top-right to bottom-left
};

bool checkResult(char gameField[3][3]) {

    for (short i = 0; i < 8; ++i) {// Iteration through each winning combination
        short pos1 = winCombination[i][0];
        short pos2 = winCombination[i][1];
        short pos3 = winCombination[i][2];

        // Check if the same symbols
        if (gameField[pos1 / 3][pos1 % 3] == gameField[pos2 / 3][pos2 % 3] &&
            gameField[pos2 / 3][pos2 % 3] == gameField[pos3 / 3][pos3 % 3] &&
            gameField[pos1 / 3][pos1 % 3] != ' ') {


            cout << gameField[pos1 / 3][pos1 % 3] << " - Winner!" << endl;
            return true;
        }
    }
    return false;}

void displayExampleField(char exampleField [rowEx][colEx]) {
cout << "This is the model of the game: " << endl;
    for (short i = 0; i < rowEx; i++) {
        for (short j = 0; j < colEx; j++) {
            cout << " ---";
        }
        cout << endl;
        for (short j = 0; j < colEx; j++) {
            cout << "| " << exampleField[i][j] << " ";
        }
        cout << "|" << endl;
    }
    for (short j = 0; j < colEx; j++) {
        cout << " ---";
    }
    cout << endl;
    cout << "To occupy any space you need to enter its number!" << endl << endl;}

void displayGameField(char gameField[rowGm][colGm]) {

    for (short i = 0; i < rowGm; i++) {
        for (short j = 0; j < colGm; j++) {
            cout << " ---";
        }
        cout << endl;

        for (short j = 0; j < colGm; j++) {
            cout << "| " << gameField[i][j] << " ";
        }
        cout << "|" << endl;
    }

    for (short j = 0; j < colGm; j++) {
        cout << " ---";
    }
    cout << endl;
}

void restartGame(char gameField[3][3]) {

    for (short i = 0; i < 3; ++i) {
        for (short j = 0; j < 3; ++j) {

            gameField[i][j] = ' ';// empty each cell to a space (' ')
        }
    }
}

void gameConditions(char gameField[3][3], short gameSign, short signOposite, short process){
    /**==========================PC movements ATTACK============================================*/

    /**final PC movements to win (at first PC always must check possibility to win faster)*/

/**  OO[O]  */
if (gameField[0][0] == gameSign && gameField[0][1] == gameSign && gameField[0][2] == ' '){

gameField[0][2] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

else if (gameField[1][0] == gameSign && gameField[1][1] == gameSign && gameField[1][2] == ' '){

gameField[1][2] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}
else if (gameField[2][0] == gameSign && gameField[2][1] == gameSign && gameField[2][2] == ' '){

gameField[2][2] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

/**  [O]OO  */

else if (gameField[0][0] == ' ' && gameField[0][1] == gameSign && gameField[0][2] == gameSign){

gameField[0][0] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

else if (gameField[1][0] == ' ' && gameField[1][1] == gameSign && gameField[1][2] == gameSign){

gameField[1][0] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}
else if (gameField[2][0] == ' ' && gameField[2][1] == gameSign && gameField[2][2] == gameSign){

gameField[2][0] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

/**
     O
     O
    [O]  */
else if (gameField[0][0] == gameSign && gameField[1][0] == gameSign && gameField[2][0] == ' '){

gameField[2][0] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

else if (gameField[0][1] == gameSign && gameField[1][1] == gameSign && gameField[2][1] == ' '){

gameField[2][1] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}
else if (gameField[0][2] == gameSign && gameField[1][2] == gameSign && gameField[2][2] == ' '){

gameField[2][2] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

   /**
    [O]
     O
     O  */

else if (gameField[0][0] == ' ' && gameField[1][0] == gameSign && gameField[2][0] == gameSign){

gameField[0][0] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

else if (gameField[0][1] == ' ' && gameField[1][1] == gameSign && gameField[2][1] == gameSign){

gameField[0][1] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}
else if (gameField[0][2] == ' ' && gameField[1][2] == gameSign && gameField[2][2] == gameSign){

gameField[0][2] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

/** diagonals
  [O] [O]
     O
  [O] [O]  */

else if (gameField[0][0] == gameSign && gameField[1][1] == gameSign && gameField[2][2] == ' '){

gameField[2][2] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

else if (gameField[0][2] == gameSign && gameField[1][1] == gameSign && gameField[2][0] == ' '){

gameField[2][0] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}
else if (gameField[0][0] == ' ' && gameField[1][1] == gameSign && gameField[2][2] == gameSign){

gameField[0][0] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

else if (gameField[0][2] == ' ' && gameField[1][1] == gameSign && gameField[2][0] == gameSign){

gameField[0][2] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

/**  O[O]O  */

else if (gameField[0][0] == gameSign && gameField[0][1] == ' ' && gameField[0][2] == gameSign){

gameField[0][1] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

else if (gameField[1][0] == gameSign && gameField[1][1] == ' ' && gameField[1][2] == gameSign){

gameField[1][1] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}
else if (gameField[2][0] == gameSign && gameField[2][1] == ' ' && gameField[2][2] == gameSign){

gameField[2][1] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

   /**
     O
    [O]
     O  */

else if (gameField[0][0] == gameSign && gameField[1][0] == ' ' && gameField[2][0] == gameSign){

gameField[1][0] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

else if (gameField[0][1] == gameSign && gameField[1][1] == ' ' && gameField[2][1] == gameSign){

gameField[1][1] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}
else if (gameField[0][2] == gameSign && gameField[1][2] == ' ' && gameField[2][2] == gameSign){

gameField[1][2] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}



/**If it's no ability to win then PC must check conditions to defend itself if need to*/

/**=====================PC movements DEFENCE=======================================*/


   /**For XX_ conditions*/
else if (gameField[0][0] == signOposite && gameField[0][1] == signOposite && gameField[0][2] == ' '){

gameField[0][2] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}
else if (gameField[1][0] == signOposite && gameField[1][1] == signOposite && gameField[1][2] == ' '){

gameField[1][2] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

else if (gameField[2][0] == signOposite && gameField[2][1] == signOposite && gameField[2][2] == ' '){

gameField[2][2] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}




/**for conditions '_XX'*/
                    else if
                        (gameField[0][1] == signOposite && gameField[0][2] == signOposite && gameField[0][0] == ' ') {

                                gameField[0][0] = gameSign;
                            cout << "Computer's move:" << endl;

                            displayGameField(gameField);
                            }

                    else if
                        (gameField[1][1] == signOposite && gameField[1][2] == signOposite && gameField[1][0] == ' ') {

                                gameField[1][0] = gameSign;
                            cout << "Computer's move:" << endl;

                            displayGameField(gameField);
                            }

                     else if
                        (gameField[2][1] == signOposite && gameField[2][2] == signOposite && gameField[2][0] == ' ') {

                                gameField[2][0] = gameSign;
                            cout << "Computer's move:" << endl;

                            displayGameField(gameField);
                            }

/**Conditions for columns (XX_ from top to bottom)*/
else if
(gameField[0][0] == signOposite && gameField[1][0] == signOposite && gameField[2][0] == ' ') {

gameField[2][0] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

else if
(gameField[0][1] == signOposite && gameField[1][1] == signOposite && gameField[2][1] == ' ') {

gameField[2][1] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

else if
(gameField[0][2] == signOposite && gameField[1][2] == signOposite && gameField[2][2] == ' ') {

gameField[2][2] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

/**For columns _XX (from bottom to top)*/
                        else if  (gameField[1][0] == signOposite && gameField[2][0] == signOposite && gameField[0][0] == ' ')
                             {
                                    gameField[0][0] = gameSign;
                                    cout << "Computer's move:" << endl;


                                    displayGameField(gameField);
                            }

                            else if (gameField[1][1] == signOposite && gameField[2][1] == signOposite && gameField[0][1] == ' ')
                             {
                                    gameField[0][1] = gameSign;
                                    cout << "Computer's move:" << endl;

                                    displayGameField(gameField);
                                }

                            else if (gameField[1][2] == signOposite && gameField[2][2] == signOposite && gameField[0][2] == ' ')
                             {
                                    gameField[0][2] = gameSign;
                                    cout << "Computer's move:" << endl;

                                    displayGameField(gameField);
                                }


/** condition x_x */
else if (gameField[0][0] == signOposite && gameField[0][2] == signOposite && gameField[0][1] == ' ')
 {
gameField[0][1] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

//for x_x condition in the second row
else if (gameField[1][0] == signOposite && gameField[1][2] == signOposite && gameField[1][1] == ' ')
 {
gameField[1][1] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

//x_x for the third row
else if(gameField[2][0] == signOposite && gameField[2][2] == signOposite && gameField[2][1] == ' ')
 {
gameField[2][1] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}
/**for diagonals */

                        else if ((gameField[0][0] == signOposite && gameField[2][2] == signOposite && gameField[1][1] == ' ') ||
                                 (gameField[0][2] == signOposite && gameField[2][0] == signOposite && gameField[1][1] == ' ')){

                                gameField[1][1] = gameSign;
                                cout << "Computer's move:" << endl;

                                displayGameField(gameField);
                            }

                            else if (gameField[0][0] == signOposite && gameField[2][2] == ' ' && gameField[1][1] == signOposite){

                                gameField[2][2] = gameSign;
                                cout << "Computer's move:" << endl;

                                displayGameField(gameField);
                            }

                            else if (gameField[0][0] == ' ' && gameField[2][2] == signOposite && gameField[1][1] == signOposite){

                                gameField[0][0] = gameSign;
                                cout << "Computer's move:" << endl;

                                displayGameField(gameField);
                            }

                            else if(gameField[0][2] == signOposite && gameField[2][0] == ' ' && gameField[1][1] == signOposite)
                         {
                                gameField[2][0] = gameSign;
                                cout << "Computer's move:" << endl;

                                displayGameField(gameField);
                            }

                            else if(gameField[0][2] == ' ' && gameField[2][0] == signOposite && gameField[1][1] == signOposite)
                         {
                                gameField[0][2] = gameSign;
                                cout << "Computer's move:" << endl;

                                displayGameField(gameField);
                            }


/**And then if no conditions of winning or defence are used, so PC can make

========================SECOND MOVE TO WIN IN FUTURE=================================*/


/**  O[O]_  */

else if (gameField[0][0] == gameSign && gameField[0][1] == ' ' && gameField[0][2] == ' '){

gameField[0][1] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

else if (gameField[1][0] == gameSign && gameField[1][1] == ' ' && gameField[1][2] == ' '){

gameField[1][1] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

else if (gameField[2][0] == gameSign && gameField[2][1] == ' ' && gameField[2][2] == ' '){

gameField[2][1] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

/**  _[O]O  */

else if (gameField[0][0] == ' ' && gameField[0][1] == ' ' && gameField[0][2] == gameSign){

gameField[0][1] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

else if (gameField[1][0] == ' ' && gameField[1][1] == ' ' && gameField[1][2] == gameSign){

gameField[1][1] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

else if (gameField[2][0] == ' ' && gameField[2][1] == ' ' && gameField[2][2] == gameSign){

gameField[2][1] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

/**  [O]O_  */

else if (gameField[0][0] == ' ' && gameField[0][1] == gameSign && gameField[0][2] == ' '){

gameField[0][0] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

else if (gameField[1][0] == ' ' && gameField[1][1] == gameSign && gameField[1][2] == ' '){

gameField[1][0] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

else if (gameField[2][0] == ' ' && gameField[2][1] == gameSign && gameField[2][2] == ' '){

gameField[2][0] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}

/** diagonals
 O   O
  [O]
 O   O  */

else if ((gameField[0][0] == gameSign && gameField[1][1] == ' ' && gameField[2][2] == ' ') ||
         (gameField[2][0] == ' ' && gameField[1][1] == ' ' && gameField[0][2] == gameSign) ||
         (gameField[2][0] == gameSign && gameField[1][1] == ' ' && gameField[0][2] == ' ') ||
         (gameField[0][0] == ' ' && gameField[1][1] == ' ' && gameField[2][2] == gameSign)
         ){

gameField[1][1] = gameSign;
cout << "Computer's move:" << endl;

displayGameField(gameField);
}


//if PC is making the first move
 else if (process == 1 && gameField[1][1] == ' ') {
        gameField[1][1] = gameSign;
        cout << "Computer's move:" << endl;
        displayGameField(gameField);
    }

    // If still no move, make a random move
    else {
        int PCmove;
        int PCrow, PCcol;

        do {
            PCmove = rand() % 9 + 1;
            PCrow = (PCmove - 1) / 3;
            PCcol = (PCmove - 1) % 3;
        } while (gameField[PCrow][PCcol] != ' '); //IT'S VERY IMPORTANT PART (do-while)!!! Because sometimes in some
                                                  //cases PC makes a move sometimes - no! But counts process in both cases.
        gameField[PCrow][PCcol] = gameSign;
        cout << "Computer's move:" << endl;
        displayGameField(gameField);
    }}

int main() {
    char exampleField[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    char gameField[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };


        cout << "Hello in Tic Tac Toe game!!!" << endl;
        cout << endl;

    bool playAgain = true; //implementation of restarting of the program
    while (playAgain){


    short gameCode;

    do {
        cout << "Choose the game mode (1 - PvP or 2 - PvPC): ";

        // Check if the input is an integer
        while (!(cin >> gameCode)) {
            cout << "Invalid input! Please enter a numeric value(1 or 2): ";

            cin.clear(); // to clear the input space

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any remaining characters in the input space
        }

        if (gameCode != 1 && gameCode != 2) {
            cout << "Invalid mode of the game!" << endl;
            system("CLS");
        }
    } while (gameCode != 1 && gameCode != 2);

    cout << endl;

    switch(gameCode){

    case 1:{

displayExampleField(exampleField);

cout << "'x' moves first!" << endl << endl;
/**Player against player================================================================*/


    for (short process = 0; process < 9; process++) {

        cout << "Enter space to occupy: ";
        cin >> userMove;

        short userMoveInt = userMove - '0';  // Convert the character to integer

        if (userMoveInt >= 1 && userMoveInt <= 9) {
    userMoveInt--; // Adjust to 0-based indexing
    userRow = userMoveInt / colGm; //previously here was ".../3" and "...%3", but because of it...
    userCol = userMoveInt % colGm; //... I had the status code -1073741510 - a segmentation fault - error in memory of the code

            if (gameField[userRow][userCol] == ' ') {

                if (process % 2 == 0) {
                    gameField[userRow][userCol] = 'x';
                } else {
                    gameField[userRow][userCol] = 'o';
                } system("CLS"); /**system("CLS") - command to remove previous displaying moves*/

    displayExampleField(exampleField); //I put it again to keep exampleField constantly

    displayGameField(gameField);
    if (checkResult(gameField)) {
                    // If a winner is found, break out of the loop
                    cout << "Game over!" << endl;
                    break;
                }
                else if(process > 7){
                    cout << "The game is a draw! \n Game over!" << endl;
                }
            } else {
                cout << "This space is already occupied! Choose another space." << endl;
                process--;
            }
        } else {
            cout << "Invalid userStep value!" << endl;
            process--;
        }
    }
    }
    break;



 case 2:{

    /**Player against computer=============================================================*/
    short sign;

    do {
        cout << "Choose your sign (1 - x, 2 - o): ";

        while (!(cin >> sign)) {
            cout << "Invalid input! Please enter a numeric value(1 or 2): ";

            cin.clear();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (sign != 1 && sign != 2) {
            cout << "Invalid value! Please enter 1 for - x or 2 for - o." << endl;
            system("CLS");
        }
    } while (sign != 1 && sign != 2);

    cout << endl;


/**XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx*/
char gameField[3][3] = { //this declaration for 'playAgain' of the 'while' loop
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

        if (sign == 1) {
                char exampleField[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    char gameField[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

displayExampleField(exampleField);

/**Process*/

srand(time(NULL));


for (short process = 0; process < 9; process++) {
    if (process % 2 == 0) {
        cout << "Enter space to occupy: ";
        cin >> userMove;


        short userMoveInt = userMove - '0';

        if (userMoveInt >= 1 && userMoveInt <= 9) {

            userRow = (userMoveInt - 1) / 3;
            userCol = (userMoveInt - 1) % 3;



            //"User's Move"



            if (gameField[userRow][userCol] == ' ') {
                gameField[userRow][userCol] = 'x';
             cout << "Next move: ";



            } else {
                cout << "This space is already occupied! Choose another space." << endl;
                process--;  // Retry the user's move in the next iteration
            }
        } else {
            cout << "Invalid userStep value!" << endl;
            process--;  // Retry the user's move in the next iteration
        }
    }

  /**Conditions for PC====================================*/

    else{
            gameConditions(gameField, 'o', 'x', process);
    }

    system("CLS"); /**system("CLS") - command to remove previous displaying moves*/

    displayExampleField(exampleField); //I put it again to keep exampleField constantly

    displayGameField(gameField);

    if (checkResult(gameField)) {
                    // If a winner is found, break out of the loop
                    cout << "Game over!" << endl;
                    break;
                }
                else if(process > 7){
                    cout << "The game is a draw! \n Game over!" << endl;
                }
    }

        }




/**OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO*/

        else if (sign == 2) {
            char exampleField[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    char gameField[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };


/**Process*/

srand(time(NULL));


        short difcl;

    do {
        cout << "Choose difficulty of the game (1 or 2): ";

        while (!(cin >> difcl)) {
            cout << "Invalid input! Please enter a numeric value (1 or 2): ";

            cin.clear();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (difcl != 1 && difcl != 2) {
            cout << "Invalid value! Please enter 1 or 2." << endl;
            system("CLS");
        }
    } while (difcl != 1 && difcl != 2);

    cout << endl;

        switch (difcl){

    case 1:{ //the first difficulty

    displayExampleField(exampleField);

for (short process = 0; process < 9; process++) {

    if (process % 2 == 0) {

            gameConditions(gameField, 'x', 'o', process);

    }


        else{
        cout << "Enter space to occupy: ";
        cin >> userMove;


        short userMoveInt = userMove - '0';

        if (userMoveInt >= 1 && userMoveInt <= 9) {

            userRow = (userMoveInt - 1) / 3;
            userCol = (userMoveInt - 1) % 3;


            if (gameField[userRow][userCol] == ' ') {
                gameField[userRow][userCol] = 'o';
             cout << "Your move: ";




    system("CLS"); /**system("CLS") - command to remove previous displaying moves*/

    displayExampleField(exampleField);
    }
             else {
                cout << "This space is already occupied! Choose another space." << endl;
                process--;
            }
        } else {
            cout << "Invalid userStep value!" << endl;
            process--;
        }


    }if (checkResult(gameField)) {

                    cout << "Game over!" << endl;
                    break;
                }
                else if(process > 7){
                    cout << "The game is a draw! \n Game over!" << endl;
                }
        }

}break;

case 2:{//the second difficulty

    displayExampleField(exampleField);

    if (gameField[1][1] == ' '){

            gameField[1][1] = 'x';

            cout << "Computer's move: " << endl;
            displayGameField(gameField);
        }

       cout << "Enter space to occupy: ";
        cin >> userMove;


        short userMoveInt = userMove - '0';

        if (userMoveInt >= 1 && userMoveInt <= 9) {

            userRow = (userMoveInt - 1) / 3;
            userCol = (userMoveInt - 1) % 3;


            if (gameField[userRow][userCol] == ' ') {
                gameField[userRow][userCol] = 'o';
             cout << "Your move: ";
            }}
            system("CLS");

            displayExampleField(exampleField);
//first scenario
if (gameField[0][1] == 'o' || gameField[1][0] == 'o' || gameField[1][2] == 'o' || gameField[2][1] == 'o'){

    for (short process = 2; process < 9; process++){

    /**EASY-WIN combinations*/
        if (process == 2){
            gameField[0][0] = 'x';
            cout << "Computer's move: " << endl;
            displayGameField(gameField);
        }

        else if (process == 4 && gameField[2][2] == ' '){

            gameField[2][2] = 'x';

            cout << "Computer's move: " << endl;
            displayGameField(gameField);
        }

        else if (process == 4 && (gameField[0][1] == 'o' || gameField[2][1] == 'o')) {
            gameField[2][0] = 'x';
            cout << "Computer's move: " << endl;
            displayGameField(gameField);
        }

        else if (process == 4 && (gameField[1][0] == 'o' || gameField[1][2] == 'o')) {
            gameField[0][2] = 'x';
            cout << "Computer's move: " << endl;
            displayGameField(gameField);
        }
        else if (process == 6){
            gameConditions(gameField, 'x', 'o', process);
        }


        else{
        cout << "Enter space to occupy: ";
        cin >> userMove;


        short userMoveInt = userMove - '0';

        if (userMoveInt >= 1 && userMoveInt <= 9) {

            userRow = (userMoveInt - 1) / 3;
            userCol = (userMoveInt - 1) % 3;


            if (gameField[userRow][userCol] == ' ') {
                gameField[userRow][userCol] = 'o';
             cout << "Your move: ";




    system("CLS"); /**system("CLS") - command to remove previous displaying moves*/

    displayExampleField(exampleField);
    }
             else {
                cout << "This space is already occupied! Choose another space." << endl;
                process--;
            }
        } else {
            cout << "Invalid userStep value!" << endl;
            process--;
        }
        }



      if (checkResult(gameField)) {

                    cout << "Game over!" << endl;
                    break;
                }
                else if(process > 7){
                    cout << "The game is a draw! \n Game over!" << endl;
                }  }



    }
    else{ //second scenario
        for (short process = 2; process < 9; process++){

        if (process % 2 == 0){
                gameConditions(gameField, 'x', 'o', process);
            }

        else{
        cout << "Enter space to occupy: ";
        cin >> userMove;


        short userMoveInt = userMove - '0';

        if (userMoveInt >= 1 && userMoveInt <= 9) {

            userRow = (userMoveInt - 1) / 3;
            userCol = (userMoveInt - 1) % 3;


            if (gameField[userRow][userCol] == ' ') {
                gameField[userRow][userCol] = 'o';
             cout << "Your move: ";




    system("CLS"); /**system("CLS") - command to remove previous displaying moves*/

    displayExampleField(exampleField);
    }
             else {
                cout << "This space is already occupied! Choose another space." << endl;
                process--;
            }
        } else {
            cout << "Invalid userStep value!" << endl;
            process--;
        }
        }

        if (checkResult(gameField)) {

                    cout << "Game over!" << endl;
                    break;
                }
                else if(process > 7){
                    cout << "The game is a draw! \n Game over!" << endl;
                }}
    }
    }break;}
        }
}
    break;}
    /**Implementation of restart the game============*/
        short choice;

    do {
        cout << endl;
        cout << "Do you want to play again? (1 - yes / 2 - no): ";


        while (!(cin >> choice)) {
            cout << "Invalid input! Please enter a numeric value (1 or 2): ";

            cin.clear();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (choice != 1 && choice != 2) {
            cout << "Invalid value! Please enter 1 for - yes or 2 for - no." << endl;
            system("CLS");
        }

    } while (choice != 1 && choice != 2);

    if (choice == 1) {
        restartGame(gameField);
    } else if (choice == 2) {
        cout << "Goodbye! Thanks for playing." << endl;
        break;
    }

    system("CLS");}

    }
