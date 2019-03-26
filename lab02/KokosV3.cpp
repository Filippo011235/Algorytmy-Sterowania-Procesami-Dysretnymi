#include <iostream>
#include <algorithm>    // std::min_element
#include <fstream>
using namespace std;


struct CzasZadaniaNaMaszynie{
   int Obrobka=0; 
   int KoniecObrobki=0;
};

struct NrCzasSumyZadania{
    int Numer = 0;
    int SumaCzasu = 0;
};

class ZadaneDane{
    int const IloscZadan;
    int const IloscMaszyn;
    int** TabZadaneDane;

    public:
                                    //ZadaneDane();
    ZadaneDane(int Zadania, int Maszyny): IloscZadan(Zadania), IloscMaszyn(Maszyny){
        TabZadaneDane = new int *[IloscZadan];
        for(int i = 0; i < IloscZadan; i++){
            TabZadaneDane[i] = new int[IloscMaszyn];
        }
    } // konstruktor
                                    //ZadaneDane(const ZadaneDane&);
    ~ZadaneDane(){
        for(int i = 0; i < IloscZadan; ++i) {
            delete [] TabZadaneDane[i];
        }
        delete [] TabZadaneDane;
    } // destruktor
    void Ustaw(int const Z, int const M, int const WartoscCzasu){
        TabZadaneDane[Z][M] = WartoscCzasu;
    }
    int Pokaz(int const Z, int const M) const{
        return TabZadaneDane[Z][M];
    }
    int IleZadan() const{
        return IloscZadan;
    }
    int IleMaszyn() const{
        return IloscMaszyn;
    }
}; // klasa

void ZamienStruktue(struct NrCzasSumyZadania *xp, struct NrCzasSumyZadania *yp) { 
    struct NrCzasSumyZadania temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void zamien(int *tab, int i){
    int bufor = tab[i];
    tab[i] = tab[i - 1];
    tab[i - 1] = bufor;
}

int main(){
//*****************************************************
/* // Uzytkownik podaje:
    int IleZadan = 4;       // zmienna utworzona na poczatku
    int IleMaszyn = 3;

    int ZadaneDane2[IleZadan][IleMaszyn] =
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
                // {
                // {4,1,4},
                // {4,3,3},
                // {1,2,3},
                // // {3,5,7},
                // // {5,5,3},
                // {5,1,3},
                // // {4,5,2},
                // }; */

        

    // Pobieranie danych z pliku
    ifstream PlikDane("dane.txt");  // uchwyt do pliku z danymi
    string linia;                   // zmienna potrzebna do odczytu
    string NazwaZbioru = " ";
    int IleZadan = 0;       // zmienna utworzona na poczatku
    int IleMaszyn = 0;

    if(PlikDane.is_open() == false) {
        cout << "błąd";
    }

    while(getline(PlikDane,linia)) {
        cout << endl << "Nazwa zbioru " << NazwaZbioru << linia << endl;  // wyswietla naze aktualnego zbioru
        PlikDane >> IleZadan;       // popbranie z pliku informacji o ilości zadań 
        PlikDane >> IleMaszyn;      // pobranie informacji o ilości maszyn

        int ZadaneDane2[IleZadan][IleMaszyn];   // przechowuje czasy odczytane z pliku
    
        // Odczyt z pliku
        for (int i=0; i < IleZadan; i++) {
            for (int j=0; j < IleMaszyn; j++) {
            PlikDane >> ZadaneDane2[i][j];
            }
        }
        PlikDane >> linia;
        NazwaZbioru = linia;

// ***********************SPRAWDZENIE******************************
        cout << "Sprawdzenie: " << endl;
        cout << "Zadania: " << IleZadan << "   Maszyny: " << IleMaszyn << endl;

        for (int i=0; i < IleZadan; i++) {
            for (int j=0; j < IleMaszyn; j++) {
                cout << ZadaneDane2[i][j] << ' ';
            }
            cout << endl;
        }
    
//**************************************************************
// Zmienne do iteracji po tablicy TabZadMasz(dalej w kodzie)
        int IterZad = IleZadan+1;
        int IterMasz = IleMaszyn+1;   
        int IterujOd = 1;
//*****************************************************
    ZadaneDane TabZadMaszKlasa(IleZadan, IleMaszyn);

    // Uzupełnianie roboczej tablicy
    for(int i = 0; i<IleZadan; i++){
        for(int j = 0; j<IleMaszyn; j++){
            TabZadMaszKlasa.Ustaw(i,j,ZadaneDane2[i][j]); 
        }
    }

    cout << "IleZadan: " << IleZadan << endl;
    int tab[IleZadan] = {};
 
    int TabKombinacji[IleZadan][IleZadan] = {};

//*******************************************************
    struct NrCzasSumyZadania SumaCzasowZadania[IleZadan];
    // Liczenie sumy czasow
    for (int i = 0; i < IleZadan; i++){
        // cout << "Przechodze do dodawania" << endl;
        SumaCzasowZadania[i].Numer = i;
        for(int j = 0; j < IleMaszyn; j++){
            SumaCzasowZadania[i].SumaCzasu += ZadaneDane2[i][j];
            // cout << "Aktualna suma: " << SumaCzasowZadania[i].SumaCzasu << "    ";
        }
        // cout << endl << "Numer: " << SumaCzasowZadania[i].Numer << "  Suma: " << SumaCzasowZadania[i].SumaCzasu << endl;
    } // Liczenie sumy czasow
    
    // cout do  sprawdzenia
    cout << "Przed bubble sortem: " << endl;
    for (int i = 0; i < IleZadan; i++){
        cout << endl << "Numer: " << SumaCzasowZadania[i].Numer << "  Suma: " << SumaCzasowZadania[i].SumaCzasu << endl;
    }

    // BUBBLE SORT
    int i, j; 
    for (i = 0; i < IleZadan-1; i++){       
       // Ostatnie i elementow jest juz w miejscu
       for (j = 0; j < IleZadan-i-1; j++){  
           if (SumaCzasowZadania[j].SumaCzasu < SumaCzasowZadania[j+1].SumaCzasu){ 
              ZamienStruktue(&SumaCzasowZadania[j], &SumaCzasowZadania[j+1]);
           }
       }
    } // Koniec Bąbelka

    // cout sprawdzenia
    cout << "Po bubble sortcie: " << endl;
    for (int i = 0; i < IleZadan; i++){
        cout << endl << "Numer: " << SumaCzasowZadania[i].Numer << "  Suma: " << SumaCzasowZadania[i].SumaCzasu << endl;
    }

    int TabPosortowane[IleZadan] ;
    cout << "kolejnosc zadan: ";
    for (int i = 0; i < IleZadan; i++){
        TabPosortowane[i] = SumaCzasowZadania[i].Numer + 1;
        cout << TabPosortowane[i] << ' ';
    }
    cout << endl;
    //*****************************************************************


    int krok = 1;
    while (krok <= IleZadan){
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
        for (int i=0; i < IleZadan; i++) {
            for (int j=0; j < IleZadan; j++) {
                cout << TabKombinacji[i][j] << " ";
            }
        cout << endl;
        }
        // koniec wyswiwetlanie TK
        // Liczenie Cmax
        //************************************************
        // Liczenie C_max dla permutacji
        //int krok = krok;                                // TUATJ PROBLEM Z KROK + ILEZADAN
        IterZad = krok+1;
        int WynikiCmax[krok] = {0};
        int OptymalnyNrPermutacji = 0;
        int NajmniejszyCmax = 1000000; // dla pewności

        // Petla liczaca Cmax dla permutacji o numerze NrPermutacji
        for(int NrPermutacji = 0; NrPermutacji < krok; NrPermutacji++){
            int TabDoWyliczenia[krok][IleMaszyn]; // Tab gdzie bedzie przechowywana aktualnie badana permutacja ZadaneDane
            for(int i = 0; i<krok; i++){
                for(int j = 0; j<IleMaszyn; j++){
                    int NrZadaniaZPermutacji = TabKombinacji[NrPermutacji][i];
                    TabDoWyliczenia[i][j] =  ZadaneDane2[NrZadaniaZPermutacji - 1][j];
                }
            }

            struct CzasZadaniaNaMaszynie TabZadMasz[IterZad][IterMasz] ;

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

            WynikiCmax[NrPermutacji] = TabZadMasz[krok][IleMaszyn].KoniecObrobki; // czyli Cmax

            cout << "Permutacja: ";
            for (int j=0; j < krok; j++) {
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
        for (int j=0; j < krok; j++) {
            cout << TabKombinacji[OptymalnyNrPermutacji][j] << " ";
        }
        for (int i=0; i < krok; i++) {
            tab[i] = TabKombinacji[OptymalnyNrPermutacji][i];
        }
/*         cout << endl << "Wyswietlam aktualny tab: ";
        for (int i=0; i < krok; i++){
            cout << tab[i] << " ";
        } */
        cout << endl << "KROK " << krok << endl;
        krok++;
    }
    } // koniec pętli while, czytania plików
    cout << endl;
    PlikDane.close();   // zamykanie pliku z danymi
    return 0;
}