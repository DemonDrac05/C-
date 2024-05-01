#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

#define ROW 3
#define COL 3

int main() {




    int mXValue[] = {2, 7, 12};
    int mYValue[] = {2, 5, 8};

    int posM3x3[3][3];
    int posM9[9];
    int indexM9 = 0;

    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            posM3x3[i][j] = mXValue[i] + mYValue[j];
            posM9[indexM9++] = posM3x3[i][j];
        }
    }

    random_shuffle(begin(posM9), end(posM9));

    int* posM9_begin = posM9;
    int* posM9_end = posM9 + sizeof(posM9)/sizeof(int);

    posM9_end = remove(posM9_begin, posM9_end, 12);
    posM9_end = remove(posM9_begin, posM9_end, 20);

    for (int* p= posM9_begin; p!= posM9_end; ++p)
        std::cout << ' ' << *p << sizeof(p);
    std::cout << '\n' ;

    cout << sizeof(posM9);

    return 0;








/****/
    // Sample array
    int myints[] = {11,22,33,44,55};            // 1 2 3 4 5 6 7 8 9

    // bounds of range:
    int* pbegin = myints;                          // ^
    int* pend = myints+sizeof(myints)/sizeof(int); // ^                 ^

    pend = std::remove_if (pbegin, pend, [](int i) { return ((i%2)==1); });   // 2 4 6 8 ? ? ? ? ?
                                                 // ^       ^
    std::cout << "the range contains:";
    for (int* p=pbegin; p!=pend; ++p)
    std::cout << ' ' << *p;
    std::cout << '\n';

/****/

    // Create two arrays of integersz
    int array1[] = {1, 2, 3, 4, 5};
    int array2[] = {10, 20, 30, 40, 50};

    int array_combination[5][5];
    int arr[25];
    int index =0;

    // Seed the random number generator using srand and time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Shuffle both arrays using rand
    std::random_shuffle(std::begin(array1), std::end(array1));
    std::random_shuffle(std::begin(array2), std::end(array2));

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            array_combination[i][j] = array1[i] + array2[j];
            arr[index++] = array_combination[i][j];
        }
    }

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cout << array_combination[i][j] << " ";
        } cout << "\n";
    }

    std::random_shuffle(std::begin(arr), std::end(arr));

    cout << "\n\n";
    index = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            array_combination[i][j] = arr[index++];
        }
    }

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cout << array_combination[i][j] << " ";
        } cout << "\n";
    }

/****/
    int sampleInts[] = {11,22,33,44,55};
    int* arrBegin = arr;
    int* arrEnd = arr+sizeof(arr)/sizeof(int); // ^                 ^

    for(int i = 0; i < 5; i++){
        arrEnd = remove(arrBegin, arrEnd, sampleInts[i]);
    }

    std::cout << "\n\nrange contains:";
    for (int* p=arrBegin; p!=arrEnd; ++p)
        std::cout << ' ' << *p;
    std::cout << '\n';

//
//    int array_1[5][5];
//
//    for(int i = 0; i < 5; i++){
//        for(int j = 0; j < 5; j++){
//            array_1[i][j] = array_combination[i][j];
//            cout << array_1[i][j] << " ";
//        }
//    }
//
//    cout << "\n\n";
//    std::random_shuffle(std::begin(array_combination), std::end(array_combination));
//    for(int i = 0; i < 5; i++){
//        for(int j = 0; j < 5; j++){
//            cout << array_combination[i][j] << " ";
//        }
//    }
//
//
//    return 0;



}
