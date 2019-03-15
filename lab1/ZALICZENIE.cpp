#include <iostream>
#include <algorithm>    // std::min_element
using namespace std;


struct CzasZadaniaNaMaszynie{
   int Obrobka=0; 
   int KoniecObrobki=0;
};

int IleZadan = 0;

// Liczenie silni
int silnia(int n) {
    if (n <=0 ) return 0;
    if (n == 1) return n;
    n = n * silnia(n-1);
    return n;
}

bool czy_byla_wczesniej(int* c, int i) {         // sprawdza czy dana wartość nie pojawiła się wcześniej
    for (int j=0; j < IleZadan; j++) 
            if (i == c[j]) return true;
    return false;
}

// Wyświetla wszystkie możliwe kombinacje zawartości tablicy nrZadan
void permutacja(int** tablicaKombinacji, int& licznik, int*nrZadan, int poziomRekurencji = 0, int* c = NULL) {
    int cont[IleZadan];                    // przechowuje wartości które zostały już użyte
    for (int i=0; i < IleZadan; i++){
        if ((poziomRekurencji > 0) && (i < poziomRekurencji))   // wartosć z wyższej rekurencji
            cont[i] = c[i];     // kopiuje dane z tablicy z poprzedniej rekurencji
        else    
            cont[i] = -1;       // wypełniam pustą tablicę
    }

    for (int i=0; i < IleZadan; i++) {
        if (czy_byla_wczesniej(cont, i)) continue;     // Każda wartość zostanie rozpatrzona tylko raz
        cont[poziomRekurencji] = i;
        
        if (poziomRekurencji == IleZadan - 1) {   // wyświetla watości na ostatnim poziomie rekurencji
            for (int i=0; i < IleZadan; i++){
                tablicaKombinacji[licznik][i] = nrZadan[cont[i]];
            }
            licznik++;
            return;
        }
        permutacja(tablicaKombinacji, licznik, nrZadan, poziomRekurencji+1, cont);
    }
    return;
}

void wyswietl(int** tablicaKombinacji, int licznik, int IleZadan) {
    for (int i=0; i < licznik; i++) {
        for (int j=0; j < IleZadan; j++) {
            cout << tablicaKombinacji[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
//*****************************************************
// Uzytkownik podaje:
    IleZadan = 3;       // zmienna utworzona na poczatku
    int IleMaszyn = 3;

    int ZadaneDane[IleZadan][IleMaszyn] =
    // Zadania \ Maszyny 
                /*{
                {4,4,5},  // 6 zamiast 5, blad graf <. tabela, w pdf!
                {3,5,7},
                {5,5,3},
                {4,5,2}
                };*/ 
                /*
                {
                {10,8},  // 6 zamiast 5, blad graf <. tabela, w pdf!
                {9,7},
                {8,9},
                {8,12},
                };*/
    
                {
                {6,5,2},
                {3,2,5},
                {6,5,8}
                };

        // Zmienne do iteracji po tablicy TabZadMasz(dalej w kodzie)
        int IterZad = IleZadan+1;
        int IterMasz = IleMaszyn+1;   
        int IterujOd = 1;
//*****************************************************
//              OBLICZANIE PERMUTACJI
    int licznik=0;
    int kombinacje = silnia(IleZadan);
    int** tablicaKombinacji = new int*[kombinacje];
    for (int i = 0; i < kombinacje; i++){
        tablicaKombinacji[i] = new int[IleZadan];
    }
    int nrZadan[IleZadan];
    for (int i=0; i < IleZadan; i++) {
        nrZadan[i] = i + 1;
    }

    permutacja(tablicaKombinacji, licznik, nrZadan, 0);
    // wyswiatla wszystkie permutacje
    //wyswietl(tablicaKombinacji, licznik, IleZadan);

//************************************************
// Liczenie C_max dla permutacji
    int WynikiCmax[kombinacje] = {0};
    int NrNajoptymalniejszejPermutacji = 0;
    int NajmniejszyCmax = 1000000; //dla pewności

    // Petla liczaca Cmax dla permutacji o numerze NrPermutacji
    for(int NrPermutacji = 0; NrPermutacji < kombinacje; NrPermutacji++){
        int TabDoWyliczenia[IleZadan][IleMaszyn]; // Tab gdzie bedzie przechowywana aktualnie badana permutacja ZadaneDane
        for(int i = 0; i<IleZadan; i++){
            for(int j = 0; j<IleMaszyn; j++){
                int NrZadaniaZPermutacji = tablicaKombinacji[NrPermutacji][i];
                TabDoWyliczenia[i][j] =  ZadaneDane[NrZadaniaZPermutacji - 1][j];
            }
        }

        struct CzasZadaniaNaMaszynie TabZadMasz[IterZad][IterMasz] = {0};

        // Przypisanie zadanych czasow Zadan Maszynom
        for(int i=IterujOd; i<IterZad; i++){
            for(int j=IterujOd; j<IterMasz; j++){
                TabZadMasz[i][j].Obrobka = TabDoWyliczenia[i-1][j-1]; // i-1, j-1, poniewaz TadZadMasz jest wieksza
            }
        }
        
        /* // Wyswietlanie czasow w TabZadMasz, w celu sprawdzania
         cout << "Zapisano takie Dane" << endl;
        for(int i=IterujOd; i<IterZad; i++){
            for(int j=IterujOd; j<IterMasz; j++){
                cout << TabZadMasz[i][j].Obrobka << "    "; // podawanie czasow obrobki; tabulatory . kolejne Masz
            }
            cout << endl; // kolejne Zad w nowej linii
        } */
        
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

        // Wyswietlanie koncowych czasow obrobki danych zadan, w celu sprawdzania poprawnosci
        /* cout << "Koniec czasow obrobki: " << endl;
        for(int i=IterujOd; i<IterZad; i++){
            for(int j=IterujOd; j<IterMasz; j++){
                cout << TabZadMasz[i][j].KoniecObrobki << "    "; // tabulatory . kolejne Masz
            }
            cout << endl; // kolejne Zad w nowej linii
        } */ 

        WynikiCmax[NrPermutacji] = TabZadMasz[IleZadan][IleMaszyn].KoniecObrobki; // czyli Cmax

    
        cout << "Permutacja: ";
        for (int j=0; j < IleZadan; j++) {
            cout << tablicaKombinacji[NrPermutacji][j] << " ";
        }
        cout << endl << "C_max: " << WynikiCmax[NrPermutacji] << endl << endl;
        
        if(WynikiCmax[NrPermutacji] < NajmniejszyCmax){ // Nadpisanie najmniejszego Cmax
            NajmniejszyCmax = WynikiCmax[NrPermutacji];
            NrNajoptymalniejszejPermutacji = NrPermutacji;    
        }
    }

    cout << "***************************************" << endl;
    cout << "Najmniejszy C_max: " << NajmniejszyCmax << " osiagnieto dla permutacji: " << endl;
    for (int j=0; j < IleZadan; j++) {
        cout << tablicaKombinacji[NrNajoptymalniejszejPermutacji][j] << " ";
    }
    cout << endl << endl;

    system("pause");

    return 0;
}