#include <iostream>

using namespace std;

void yourAge(int);

int main(){
    yourAge(10);
}

void yourAge(int& age){
    cout << age;
}
