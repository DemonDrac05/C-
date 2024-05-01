#include <iostream>
#include <ctype.h>
#include <ctime>
#include <cstdlib>

using namespace std;

#define ROW 100
#define COL 100

void inputMatrix(int mt[][COL], int &m, int &n){

    cout << "Input num of column: "; cin >> m;
    cout << "Input num of row: "; cin >> n;

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cin >> mt[i][j];
        }
    }
}

void outputMatrix(int mt[][COL], int &m, int &n){

    cout << "\nREVERSE\n";

    for(int i = m -1; i >= 0; i--){
        for(int j = 0; j < n; j++){
            cout << mt[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    int mt[ROW][COL];
    int m,n;

    inputMatrix(mt, m, n);
    outputMatrix(mt, m, n);

}
