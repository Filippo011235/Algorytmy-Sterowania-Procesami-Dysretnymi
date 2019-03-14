#include <iostream>
using namespace std;

struct CzasZadaniaNaMaszynie{
   int Obrobka=0; 
   int KoniecObrobki=0;
};

int main() {
//*****************************************************
// Uzytkownik podaje:
    int IleZadan = 4;
    int IleMaszyn = 3;
    
    int ZadaneDane[IleZadan][IleMaszyn] =
    // Zadania \ Maszyny 
                {
                {4,4,5},  // 6 zamiast 5, blad graf <. tabela, w pdf!
                {3,5,7},
                {5,5,3},
                {4,5,2}
                };
    /*
                {
                {4,6},  // 6 zamiast 5, blad graf <. tabela, w pdf!
                {4,1},
                {10,4},
                {6,10},
                {2,3},
                };
    */
    /*
                {
                {6,4},  // 6 zamiast 5, blad graf <-> tabela, w pdf!
                {2,4},
                {8,4}
                };
    */
//*****************************************************
    int IterZad = IleZadan+1;
    int IterMasz = IleMaszyn+1;   
    int IterujOd = 1;

    struct CzasZadaniaNaMaszynie TabZadMasz[IterZad][IterMasz] = {0};

    // Przypisanie zadanych czasow Zadan Maszynom
    for(int i=IterujOd; i<IterZad; i++){
      for(int j=IterujOd; j<IterMasz; j++){
        TabZadMasz[i][j].Obrobka = ZadaneDane[i-1][j-1]; 
      }
    }
    
    cout << "Zapisano takie Dane" << endl;
    for(int i=IterujOd; i<IterZad; i++){
        for(int j=IterujOd; j<IterMasz; j++){
            cout << TabZadMasz[i][j].Obrobka << "    "; // podawanie czasow obrobki; tabulatory . kolejne Masz
        }
        cout << endl; // kolejne Zad w nowej linii
    }
    
    // Obliczanie Cmax
    for(int i=IterujOd; i<IterMasz; i++){   // UWAGA odwrotne przypisane "j" i "i" niz zazwyczaj
        for(int j=IterujOd; j<IterZad; j++){
            if(TabZadMasz[j-1][i].KoniecObrobki > TabZadMasz[j][i-1].KoniecObrobki){
                // Aktualna Masz musi skonczyc poprzednie Zad
                TabZadMasz[j][i].KoniecObrobki = TabZadMasz[j-1][i].KoniecObrobki + TabZadMasz[j][i].Obrobka;
            } else {    
                // Poprzednia Masz musi skonczyc aktualne Zad
                TabZadMasz[j][i].KoniecObrobki = TabZadMasz[j][i-1].KoniecObrobki + TabZadMasz[j][i].Obrobka;
            }
        }
    }

    // Wyswietlanie koncowych czasow obrobki
    /* cout << "Koniec czasow obrobki: " << endl;
    for(int i=IterujOd; i<IterZad; i++){
        for(int j=IterujOd; j<IterMasz; j++){
            cout << TabZadMasz[i][j].KoniecObrobki << "    "; // tabulatory . kolejne Masz
        }
        cout << endl; // kolejne Zad w nowej linii
    } */

    cout << endl << "CZAS WYKONANIA C_MAX: " << TabZadMasz[IleZadan][IleMaszyn].KoniecObrobki << endl <<endl;
	system("pause");
	return 0;
}