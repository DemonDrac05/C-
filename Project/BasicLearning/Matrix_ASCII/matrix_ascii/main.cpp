#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;

const int SKAICIUS=65;  // krentančių "linijų" skaičius ekrane (default 65)
const int MAXX=120;      // Ekrano dydis X (default 80)
const int MAXY=29;      // Ekrano dydis Y (default 24)
const int pause=50;     // Uždelsimo trukmė ms
const int MAX_GREITIS=10;//
const int MIN_GREITIS=5; //
const int MIN_UODEGA=8;  // Mažiausias uodegos ilgis (default 8)
const int MAX_UODEGA=20; // Maksimalus uodegos ilgis (default 20)

struct Linija {
  int x, y, ilgis, greitis, ciklas;
} sn[SKAICIUS];

void Piesk (Linija);

HANDLE ekr=GetStdHandle(STD_OUTPUT_HANDLE); // Rodyklė į STD išvedimo objektą

int main() {
  srand(time(NULL));
  for (int i=0; i<SKAICIUS; i++) { // Užpildome masyvą prdiniais duomenimis
    sn[i].x= rand() % (MAXX-1);
    sn[i].y=rand() % (MAXY-1);
    sn[i].ilgis= MIN_UODEGA + rand() % (MAX_UODEGA - MIN_UODEGA);
    sn[i].greitis= MIN_GREITIS + rand() % (MAX_GREITIS-MIN_GREITIS);
    sn[i].ciklas=0;
  }
  while(true) {
    for (int i=0; i<SKAICIUS; i++) {
      Piesk(sn[i]);
      if (sn[i].y - sn[i].ilgis >=MAXY) {
        sn[i].x=rand()%MAXX-1;
        sn[i].y=0;
        sn[i].ilgis=rand()%(MAX_UODEGA-MIN_UODEGA)+MAXY/5;
        sn[i].greitis=rand()%MAX_GREITIS;
        sn[i].ciklas=0;
      } else if (sn[i].greitis<=sn[i].ciklas) {
        sn[i].ciklas=0;
        sn[i].y++;
      } else sn[i].ciklas++;
    }
    Sleep(pause);
  }
}

void Piesk(Linija lin) {
  COORD xy;// Koordinačių struktūra iš windows.h
  xy.X=lin.x;
  xy.Y=lin.y;
  if (lin.y<MAXY) {
    /*** Spalva koduojama bitais, tad kas yra kas, suprasite pabandę keisti parametrą bitas po bito ;) ***/
    if (lin.greitis<=1) SetConsoleTextAttribute(ekr, 15); // Nustatome spalvą
    else SetConsoleTextAttribute(ekr, 10); // Nustatome spalvą
    SetConsoleCursorPosition(ekr, xy); // Nustatome kursorių į poziciją xy
    cout << char(34+rand()%222);
  }
  if (lin.y > 0 && lin.y-1 < MAXY) {
    xy.Y--;
    SetConsoleTextAttribute(ekr, 2);
    SetConsoleCursorPosition(ekr, xy);
    cout << char(34+rand()%222);
  }
  if (lin.y >= lin.ilgis && lin.y <= MAXY+lin.ilgis) {
    xy.Y=lin.y - lin.ilgis;
    SetConsoleCursorPosition(ekr, xy);
    cout << ' ';
  }
}
