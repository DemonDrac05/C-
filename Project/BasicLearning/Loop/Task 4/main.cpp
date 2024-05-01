#include <iostream>
#include <string>

using namespace std;

int main()
{
    //VILNIUS FOUNDATION YEAR
    unsigned short limitAnswer = 3;
    string answer;

    cout << "Which year was Vilnius founded?" << endl;
    while(limitAnswer > 0){
        cout << "\tEnter your answer: "; cin >> answer;
        if(answer == "1323"){
            cout <<"\nCorrect answer. Good job!"<< endl;
            break;} else limitAnswer--;
        if(limitAnswer == 0){cout <<"\nIncorrect. Vilnius was founded in 1323"<<endl;}}

    //ELLA GARDEN
    short flower, flowerCount = 1;
    short day, dayCount = 0;
    //How many flowers will bloom in Ella's garden after n days?
    cout << "\n==How many flowers will bloom in Ella's garden after n days?" << endl;
    cout << "Enter number of day(s): "; cin >> day;
    //CONDITION
    if(day == 0){cout << "There is no flower blooming in the garden." << endl;}
    else for(short dayNum = 0; dayNum < day; dayNum++){flowerCount += 3;}
            cout << "There are " << flowerCount << " will blow in Ellla's garden after "
                    << day << " days." << endl;

    //How many days will it take Ella to have m flowers blooming in the garden?
    cout << "\n==How many days will it take Ella to have m flowers blooming in the garden?" << endl;
    cout << "Enter number of flower(s): "; cin >> flower;
    //CONDITION
    if(flower <= 0){cout << "Invalid Input!!!" << endl;}
    else for(short flowerNum = flower; flowerNum > 1; flowerNum -= 3){dayCount += 1;}
        if(flower <= 4){
            switch(flower){
            case 1:{cout << "There is no flower blooming in the garden." << endl; break;}
            case 2: case 3: case 4:{
                cout << "There is one day will take Ella to have "
                    << flower << " flowers blooming in the garden." << endl; break;}}}
        else cout << "There are " << dayCount << " days will take Ella to have "
                    << flower << " flowers blooming in the garden." << endl;

}
