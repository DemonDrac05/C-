#include <iostream>

using namespace std;

int main()
{
    //DECLARATION
    unsigned int i = 1, num;
    cout << "Enter number: "; cin >> num;
    cout << "\n\tMULTIPLACATION TABLE OF " << num << "\n" << endl;
    //CONDITION
    while(i <= 10){
        cout << "\t\t" << num << " x " << i;
        cout << " = " << num * i << endl;
        i++;}

    return 0;
}
