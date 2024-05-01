#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    int x;
    srand(time(NULL));

    x = rand() % 6 + 1;

    cout << "Rolled dice number: " << x << endl;
    if(x == 1 || x == 3 || x == 5){
        cout << "'The room will be handled by the younger brother'" << endl;
    } else cout << "'The room will be handled by the older brother'" << endl;
}
	