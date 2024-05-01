#include <iostream>

using namespace std;

int main()
{
    int x;
    cout << "Number of rolled dice: "; cin >> x;

    //SOLUTION I
    switch(x){
    case 1: case 3: case 5:
        cout << "'The room will be handled by the younger brother'" << endl;
        break;
    case 2: case 4: case 6:
        cout << "'The room will be handled by the older brother'" << endl;
        break;}

    //SOLUTION II
    if(x == 1 || x == 3 || x == 5){
        cout << "'The room will be handled by the younger brother'" << endl;
    } else if (x == 2 || x == 4 || x == 6){
        cout << "'The room will be handled by the older brother'" << endl;
    } else cout << "Undefined number! ERROR!!!" << endl;

    return 0;
}
