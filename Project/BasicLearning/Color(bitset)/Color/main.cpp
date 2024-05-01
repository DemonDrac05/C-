#include <iostream>
#include <windows.h>
#include <bitset>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

int main(){
for(int color = 0; color <=0b11111111; color++){
        SetConsoleTextAttribute(console, 0b00001111);
        bitset<8> colorCode(color);

        cout << colorCode;
        SetConsoleTextAttribute(console, color);
        cout << "X\t";
    }

    SetConsoleTextAttribute(console, 0b00001111);
    cout << endl << endl << endl;
return 0;
}
