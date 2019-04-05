
#include <iostream>
#include <cstdlib>
#include <algorithm>    // std::min_element
#include <fstream>
#include <ctime>
using namespace std;


struct CzasZadaniaNaMaszynie{
   int Obrobka=0; 
   int KoniecObrobki=0;
};

struct NrCzasSumyZadania{
    int Numer = 0;
    int SumaCzasu = 0;
};

void ZamienElemStruct(struct NrCzasSumyZadania *xp, struct NrCzasSumyZadania *yp) { 
    struct NrCzasSumyZadania temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void ZamienElemTab(int *tab, int i){
    int bufor = tab[i];
    tab[i] = tab[i - 1];
    tab[i - 1] = bufor;
}

// ***********************************************************
int Cmax(int **TabDoWyliczenia, int RozwazaneZad, int IleMaszyn) {
    int IterujOd = 1;
    int IterMasz = IleMaszyn+1;
    int IterZad = RozwazaneZad+1;
    struct CzasZadaniaNaMaszynie TabZadMasz[IterZad][IterMasz];

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

    return TabZadMasz[RozwazaneZad][IleMaszyn].KoniecObrobki; // czyli Cmax
}
// ********************************************************

void LosowySwap(int *tab, int IleZadan) {
    srand(time(NULL));
    int i = rand() % IleZadan;
    int j = rand() % IleZadan;
    while(i==j) {
        j = rand() % IleZadan;
    }
    int bufor = tab[i];
    tab[i] = tab[j];
    tab[j] = bufor;
}

int main(){
    //*****************************************************
    // Pobieranie danych z pliku
    ifstream PlikDane("dane.txt");  // uchwyt do pliku z danymi
    string linia;                   // zmienna potrzebna do odczytu
    string NazwaZbioru = " ";
    int IleZadan = 0;       // zmienna utworzona na poczatku
    int IleMaszyn = 0;

    if(PlikDane.is_open() == false) {
        cout << "błąd wczytu pliku";
    }

    while(getline(PlikDane,linia)) {
        cout << "***************************************" << endl;
        cout << endl << "Nazwa: " << NazwaZbioru << linia << endl;  // wyswietla nazwe aktualnego zbioru
        PlikDane >> IleZadan;       // popbranie z pliku informacji o ilości zadań 
        PlikDane >> IleMaszyn;      // pobranie informacji o ilości maszyn
        cout << "Zad: " << IleZadan << "   Masz: " << IleMaszyn << endl;

        int ZadaneDane2[IleZadan][IleMaszyn];   // przechowuje czasy odczytane z pliku
    
        // Odczyt z pliku
        for (int i=0; i < IleZadan; i++) {
            for (int j=0; j < IleMaszyn; j++) {
                PlikDane >> ZadaneDane2[i][j];
            }
        }
        PlikDane >> linia;
        NazwaZbioru = linia;

        // Zminenne do wyżarzania
        int Pi[IleZadan];  
    //**************************************************************
    // Zmienne do iteracji po tablicy TabZadMasz(dalej w kodzie)
        int IterZad = IleZadan+1;
        // int IterMasz = IleMaszyn+1;   
        // int IterujOd = 1;
    //*****************************************************
        int tab[IleZadan] = {}; // Pomocnicza tab przechowujaca aktualnie rozwazane zadania
    
        int TabKombinacji[IleZadan][IleZadan] = {};

    //*******************************************************
    //                      SORTOWANIE
        struct NrCzasSumyZadania SumaCzasowZadania[IleZadan];
        // Liczenie sumy czasow
        for (int i = 0; i < IleZadan; i++){
            // cout << "Przechodze do dodawania" << endl;
            SumaCzasowZadania[i].Numer = i;
            for(int j = 0; j < IleMaszyn; j++){
                SumaCzasowZadania[i].SumaCzasu += ZadaneDane2[i][j];
            }
        } // Liczenie sumy czasow

        // BUBBLE SORT
        int i, j; 
        for (i = 0; i < IleZadan-1; i++){       
            // Ostatnie i elementow jest juz w miejscu
            for (j = 0; j < IleZadan-i-1; j++){  
                if (SumaCzasowZadania[j].SumaCzasu < SumaCzasowZadania[j+1].SumaCzasu){ 
                    ZamienElemStruct(&SumaCzasowZadania[j], &SumaCzasowZadania[j+1]);
                }
            }
        } // Koniec Bąbelka

        int TabPosortowane[IleZadan];
        for (int i = 0; i < IleZadan; i++){
            TabPosortowane[i] = SumaCzasowZadania[i].Numer + 1; 
        }
        //*****************************************************************

        int RozwazaneZad = 1;   // Zmienna pomocnicza, indeks zadan
        while (RozwazaneZad <= IleZadan){       // wykonuj od pierwszego do ostatniego posortowanego zadania
            tab[RozwazaneZad-1] = TabPosortowane[RozwazaneZad-1];   // wybierz kolejne Zad o najwiekszym Cmax
            
            // wstaw zadanie "i" na "i" pozycjach
            for (int i = 0; i < RozwazaneZad; i++){
                if (i != 0){    // nie robic przy jednym elemencie
                    ZamienElemTab(tab, RozwazaneZad - i);
                }
                for (int j = 0; j < RozwazaneZad; j++){
                    TabKombinacji[i][j] = tab[j];
                }
            }

            //************************************************
            // Liczenie C_max 
            // IterZad = RozwazaneZad+1;
            int WynikiCmax[RozwazaneZad] = {0};
            int OptymalnyNrPermutacji = 0;
            int NajmniejszyCmax = 1000000; // dla pewności

            // Petla liczaca Cmax dla permutacji o numerze NrPermutacji
            for(int NrPermutacji = 0; NrPermutacji < RozwazaneZad; NrPermutacji++){
                //int TabDoWyliczenia[RozwazaneZad][IleMaszyn]; // Tab gdzie bedzie przechowywana aktualnie badana permutacja ZadaneDane
                int** TabDoWyliczenia = new int*[RozwazaneZad];
                for (int i = 0; i < RozwazaneZad; i++)
                    TabDoWyliczenia[i] = new int[IleMaszyn];

                for(int i = 0; i<RozwazaneZad; i++){
                    for(int j = 0; j<IleMaszyn; j++){
                        int NrZadaniaZPermutacji = TabKombinacji[NrPermutacji][i];
                        TabDoWyliczenia[i][j] =  ZadaneDane2[NrZadaniaZPermutacji - 1][j];
                    }
                }
                WynikiCmax[NrPermutacji] = Cmax(TabDoWyliczenia, RozwazaneZad, IleMaszyn);


                /* struct CzasZadaniaNaMaszynie TabZadMasz[IterZad][IterMasz];

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

                WynikiCmax[NrPermutacji] = TabZadMasz[RozwazaneZad][IleMaszyn].KoniecObrobki; // czyli Cmax */

                if(WynikiCmax[NrPermutacji] < NajmniejszyCmax){ // Nadpisanie najmniejszego Cmax
                    NajmniejszyCmax = WynikiCmax[NrPermutacji];
                    OptymalnyNrPermutacji = NrPermutacji;    
                }
            } // koniec sprawdzania wszystkich permutacji
    //*************************************
            // PRZEZENTACJA WYNIKOW
            if(RozwazaneZad == IleZadan){       // Pokazuj tylko dla ostatniej iteracji
                cout << "Najmniejszy C_max: " << NajmniejszyCmax << " osiagnieto dla permutacji: " << endl;
                for (int j=0; j < RozwazaneZad; j++) {
                    cout << TabKombinacji[OptymalnyNrPermutacji][j] << " ";
                }
                cout << endl;
                // Deklaracja Pi0
                for (int j=0; j < IleZadan; j++) {
                    Pi[j] = TabKombinacji[OptymalnyNrPermutacji][j];
                } 
            }
            
            // Przepisz aktualne zadania z optymalnej TabKombi jako kolejne do rozwazenia
            for (int i=0; i < RozwazaneZad; i++) {
                tab[i] = TabKombinacji[OptymalnyNrPermutacji][i];
            }

            RozwazaneZad++;
        } // while RozwazanychZadan
        //************************************************************
        // Symulowane wyżarzanie
              

        int T = 50;     // temperatura początkowa
        for (int j=0; j < IleZadan; j++) {
            cout << Pi[j] << " ";
        }
        cout << endl;
        LosowySwap(Pi, IleZadan);
        cout << "Po losowaniu" << endl;
        for (int j=0; j < IleZadan; j++) {
            cout << Pi[j] << " ";
        }
        cout << endl;

        


    } // koniec pętli while czytajacej z pliku
    //****************************
    // Zamykanie
    cout << endl;
    PlikDane.close();   // zamykanie pliku z danymi
    system("pause");
    return 0;
}