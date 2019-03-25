#include <iostream>
#include <algorithm>    // std::min_element
using namespace std;


struct CzasZadaniaNaMaszynie{
   int Obrobka=0; 
   int KoniecObrobki=0;
};

void zamien(int *tab, int i){
    int bufor = tab[i];
    tab[i] = tab[i - 1];
    tab[i - 1] = bufor;
}

int main(){
//*****************************************************
// Uzytkownik podaje:
    int IleZadan = 4;       // zmienna utworzona na poczatku
    int IleMaszyn = 3;

    int ZadaneDane[IleZadan][IleMaszyn] =
    // Zadania \ Maszyny 
                /* {
                {4,4,5},  // 6 zamiast 5, blad graf <. tabela, w pdf!
                {3,5,7},
                {5,5,3},
                {4,5,2}
                }; */
                /*
                {
                {10,8},  // 6 zamiast 5, blad graf <. tabela, w pdf!
                {9,7},
                {8,9},
                {8,12},
                };*/
                {
                {4,1,4},
                {4,3,3},
                {1,2,3},
                {5,1,3},
                };

        // Zmienne do iteracji po tablicy TabZadMasz(dalej w kodzie)
        int IterZad = IleZadan+1;
        int IterMasz = IleMaszyn+1;   
        int IterujOd = 1;
//*****************************************************
    cout << "IleZadan: " << IleZadan << endl;
    int tab[IleZadan] = {};
    int TabPosortowane[] = {2, 1, 4, 3};
    int ZmiennaZagadka = sizeof(TabPosortowane) / 4;
    cout << "Zagadka: " << ZmiennaZagadka << endl;
    int TabKombinacji[ZmiennaZagadka][ZmiennaZagadka] = {};

    int krok = 1;
    while (krok <= 4){
        tab[krok-1] = TabPosortowane[krok-1];
        for (int i = 0; i < krok; i++)
        {
            if (i != 0)
                zamien(tab, krok - i);
            for (int j = 0; j < krok; j++)
            {
                TabKombinacji[i][j] = tab[j];
                // cout << TabKombinacji[i][j] << ' ';
            }
            cout << endl;

        }
        // wyswiwetlanie TK
        for (int i=0; i < 4; i++) {
            for (int j=0; j < 4; j++) {
                cout << TabKombinacji[i][j] << " ";
            }
        cout << endl;
        }
        // koniec wyswiwetlanie TK
        // Liczenie Cmax
        //************************************************
        // Liczenie C_max dla permutacji
        IleZadan = krok;                                // TUATJ PROBLEM Z KROK + ILEZADAN
        IterZad = krok+1;
        int WynikiCmax[krok] = {0};
        int OptymalnyNrPermutacji = 0;
        int NajmniejszyCmax = 1000000; // dla pewności

        // Petla liczaca Cmax dla permutacji o numerze NrPermutacji
        for(int NrPermutacji = 0; NrPermutacji < krok; NrPermutacji++){
            int TabDoWyliczenia[IleZadan][IleMaszyn]; // Tab gdzie bedzie przechowywana aktualnie badana permutacja ZadaneDane
            for(int i = 0; i<IleZadan; i++){
                for(int j = 0; j<IleMaszyn; j++){
                    int NrZadaniaZPermutacji = TabKombinacji[NrPermutacji][i];
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

            WynikiCmax[NrPermutacji] = TabZadMasz[IleZadan][IleMaszyn].KoniecObrobki; // czyli Cmax

            cout << "Permutacja: ";
            for (int j=0; j < IleZadan; j++) {
                cout << TabKombinacji[NrPermutacji][j] << " ";
            }
            cout << endl << "C_max: " << WynikiCmax[NrPermutacji] << endl << endl;
            
            if(WynikiCmax[NrPermutacji] < NajmniejszyCmax){ // Nadpisanie najmniejszego Cmax
                NajmniejszyCmax = WynikiCmax[NrPermutacji];
                OptymalnyNrPermutacji = NrPermutacji;    
            }
        } // koniec sprawdzania wszystkich permutacji

        cout << "***************************************" << endl;
        cout << "Najmniejszy C_max: " << NajmniejszyCmax << " osiagnieto dla permutacji: " << endl;
        for (int j=0; j < IleZadan; j++) {
            cout << TabKombinacji[OptymalnyNrPermutacji][j] << " ";
        }
        for (int i=0; i < krok; i++) {
            tab[i] = TabKombinacji[OptymalnyNrPermutacji][i];
        }
/*         cout << endl << "Wyswietlam aktualny tab: ";
        for (int i=0; i < krok; i++){
            cout << tab[i] << " ";
        } */
        cout << endl;
        krok++;
    }

    return 0;
}