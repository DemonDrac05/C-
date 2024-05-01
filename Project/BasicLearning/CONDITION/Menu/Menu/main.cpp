#include <iostream>
#include <math.h>
#include <iomanip>
#include <windows.h>
#include <bitset>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{

    int numMenu;
    system("Color 0A");
    cout << "\n\t\t==========!!!WELCOME TO OUR MENU!!!==========" << endl;
    cout << "\n\tINSERT YOUR ASSIGNMENT NUMBER: "; cin >> numMenu;

    //MENU CONDITION
    switch(numMenu){
    case 1:
        int n;
        cout << "\n\t\tEnter number: "; cin >> n;

        cout <<"\n\tRESULT: ";
        if(n > 0){
            cout << "Positive" << endl;
        } else if(n < 0){
            cout << "Negative" << endl;
        } else cout << "Undefined" << endl;
        break;

    case 2:
        int age;
        cout << "\n\t\tEnter age: "; cin >> age;

        cout <<"\n\tRESULT: ";
        if(age >= 0 && age <= 10){
            cout << "Child group" << endl;
        } else if(age >= 11 && age <= 17){
            cout << "Teenager group" << endl;
        } else if(age >= 18 && age <= 25){
            cout << "Young person group" << endl;
        } else if(age >= 26 && age <= 120){
            cout << "Adult group" << endl;
        } else cout << "Undefined age group" << endl;
        break;

    case 3:
        float a, b, c;
        cout << "\n\t\tInput first number: "; cin >> a;
        cout << "\n\t\tInput second number: "; cin >> b;
        cout << "\n\t\tInput third number: "; cin >> c;

        cout <<"\n\tRESULT: ";
        if(a + b > c && b + c > a && c + a > b){
            if(a == b && b == c){
                cout << "This is an equilateral triangle with " << fixed << setprecision(2)
                << (sqrt(3)/4) * pow(a,2) << " square meters." << endl;
            } else{
                float p = (a + b + c)/2;
                cout << "This is a polygonal triangle with " << fixed << setprecision(2)
                << sqrt(p * (p - a) * (p - b) * (p -c)) << " square meters." << endl;
            }
        } else cout << "This is not a triangle." << endl;
        break;

    case 4:
        char area;
        cout << "\n\t\tWhich shape you would like to calculate? (Rectangle:r|R OR Triangle:t|T): ";
        cin >> area;

        switch(area){
        case 'r': case 'R':
            int width, height;
            cout << "\n\tWidth: "; cin >> width;
            cout << "\n\tHeight: "; cin >> height;

            cout <<"\n\tRESULT: ";
            if(width > 0 and height > 0){
                cout << "Rectangle's area: " << width * height << " square meters." << endl;
            } else cout << "Invalid input data!!!" << endl;
            break;

        case 't': case 'T':
            float a, b, c;
            cout << "\n\t\tInput first edge: "; cin >> a;
            cout << "\n\t\tInput second edge: "; cin >> b;
            cout << "\n\t\tInput third edge: "; cin >> c;

            cout <<"\n\tRESULT: ";
            if(a + b > c && b + c > a && c + a > b){
                if(a == b && b == c){
                    cout << "This is an equilateral triangle with " << fixed << setprecision(2)
                    << (sqrt(3)/4) * pow(a,2) << " square meters." << endl;
                } else{
                    float p = (a + b + c)/2;
                    cout << "This is a polygonal triangle with " << fixed << setprecision(2)
                    << sqrt(p * (p - a) * (p - b) * (p -c)) << " square meters." << endl;
                }
            } else cout << "Invalid input data!!!" << endl;
            break;}
        break;

    case 5:
        int x,y;
        cout << "\n\t\tEnter x-axis: "; cin >> x;
        cout << "\n\t\tEnter y-axis: "; cin >> y;

        cout <<"\n\tRESULT: ";
        if(x > 0 && y > 0){
            cout << "(" << x << "," << y << ") is located in QUARTER I" << endl;
        } else if(x < 0 && y > 0){
            cout << "(" << x << "," << y << ") is located in QUARTER II" << endl;
        } else if(x < 0 && y < 0){
            cout << "(" << x << "," << y << ") is located in QUARTER III" << endl;
        } else if(x > 0 && y < 0){
            cout << "(" << x << "," << y << ") is located in QUARTER IV" << endl;
        } else cout << "(" << x << "," << y << ") is not located in any QUARTERS" << endl;
        break;}
    return 0;
}
