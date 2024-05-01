#include <iostream>
#include <cmath>
#include <windows.h>
#include <bitset>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void setMultiplicationBoard(int row, int layerCount, int maxColRange, int digitCount){
    for(unsigned int rowSet = 1; rowSet <= row; rowSet++){
            //Set up Columns (Each 10 units, automatically jump into the next loop)
            for(unsigned int colSet = layerCount; colSet <= maxColRange; colSet++){
                //Check space between different digits number
                for(unsigned int numGet = rowSet * colSet; numGet < pow(10,digitCount); numGet*=10){cout << " ";}
                cout << "\t" << rowSet * colSet;
            } cout << endl;
        } cout << endl;
}

void setLayer(int col, int row, int layerCount, int maxColRange, int digitCount){
    for(unsigned int layerSet = 1; layerSet < col + 1; layerSet+=10){
        //Check 10 units in a row
        if(col % 10 >= 0 && col > 10){
            layerCount = (layerSet/10) * 10 + 1;
            maxColRange = layerCount + 9;
            if(maxColRange > col){maxColRange = col;}
        } else {maxColRange = col; layerCount = 1;}
        setMultiplicationBoard(row, layerCount, maxColRange, digitCount);}
}

int main()
{
    system("Color 04");
    //Variables & Input (Row & Column)
    unsigned int row, col, maxColRange, digitCount = 0, layerCount = 0;
    cout << "Enter number of row: "; cin >> row;
    cout << "Enter number of col: "; cin >> col;

    cout << "\n\t\t\t\tMULTIPLICATION BOARD OF " << row << " X " << col;
    cout << endl << endl;
    //Count the digits number (1 -> 1; 10 -> 2; 100 -> 3)
    for(unsigned int numSet = 1; numSet <= row * col; numSet*=10){digitCount++;}
    //Function call
    setLayer(col, row, layerCount, maxColRange, digitCount);
}


