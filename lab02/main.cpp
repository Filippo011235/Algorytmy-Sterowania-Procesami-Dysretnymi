#include <iostream>
#include <fstream>
#include <string>
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

void Zamien(struct NrCzasSumyZadania *xp, struct NrCzasSumyZadania *yp) { 
    struct NrCzasSumyZadania temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

/* class AlgorytmNEH{
    int const IloscZadan;
    struct NrCzasSumyZadania SumaCzasowZadania[];

    public:
    AlgorytmNEH(class ZadaneDane Dane): IloscZadan(Dane.IleZadan()){
        for (int i = 0; i < IloscZadan; i++){
            SumaCzasowZadania[i].Numer = i; // ZWIEKSZANIE O JEDEN POWINNO BYC ALE PSUJE DESTRUKTOR ZadaneDane
            cout << "SCZ NR " << SumaCzasowZadania[i].Numer << endl;
            SumaCzasowZadania[i].SumaCzasu = 0;
        }
    }; // konstruktor
    ~AlgorytmNEH(){}; // destruktor
    void SumaCzasowNaMaszynach(ZadaneDane const TabDanych){
        for (int i = 0; i < IloscZadan; i++){
            cout << "Przechodze do dodawania" << endl;
            for(int j = 0; j < TabDanych.IleMaszyn(); j++){
                SumaCzasowZadania[i].SumaCzasu += TabDanych.Pokaz(i, j);
                cout << "Aktualna suma: " << SumaCzasowZadania[i].SumaCzasu << "    ";
            }
            cout << endl << "Numer: " << SumaCzasowZadania[i].Numer << "  Suma: " << SumaCzasowZadania[i].SumaCzasu << endl;
        }
    } 
}; // klasa
 */

int main(){
//*****************************************************
// Uzytkownik podaje:
    // int IleZadan = 5;       // zmienna utworzona na poczatku
    // int IleMaszyn = 4;

    // int ZadaneDane2[IleZadan][IleMaszyn] =
    // // Zadania \ Maszyny 
    //             /* {
    //             {4,4,5},  // 6 zamiast 5, blad graf <. tabela, w pdf!
    //             {3,5,7},
    //             {5,5,3},
    //             {4,5,2}
    //             }; */
    //             /*
    //             {
    //             {10,8},  // 6 zamiast 5, blad graf <. tabela, w pdf!
    //             {9,7},
    //             {8,9},
    //             {8,12},
    //             };*/
    //             {
    //             {4,1,4,2},
    //             {4,3,3,5},
    //             {1,2,3,1},
    //             {5,1,3,2},
    //             {6,1,1,4}
    //             };

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

    ZadaneDane TabZadMasz(IleZadan, IleMaszyn);

    // Uzupełnianie roboczej tablicy
    for(int i = 0; i<IleZadan; i++){
        for(int j = 0; j<IleMaszyn; j++){
            TabZadMasz.Ustaw(i,j,ZadaneDane2[i][j]); 
        }
    }
//*****************************************************

    struct NrCzasSumyZadania SumaCzasowZadania[IleZadan];
    // Liczenie sumy czasow
    for (int i = 0; i < IleZadan; i++){
        // cout << "Przechodze do dodawania" << endl;
        SumaCzasowZadania[i].Numer = i;
        for(int j = 0; j < IleMaszyn; j++){
            SumaCzasowZadania[i].SumaCzasu += TabZadMasz.Pokaz(i, j);
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
              Zamien(&SumaCzasowZadania[j], &SumaCzasowZadania[j+1]);
           }
       }
    } // Koniec Bąbelka

    // cout sprawdzenia
    cout << "Po bubble sortcie: " << endl;
    for (int i = 0; i < IleZadan; i++){
        cout << endl << "Numer: " << SumaCzasowZadania[i].Numer << "  Suma: " << SumaCzasowZadania[i].SumaCzasu << endl;
    }
//*********************************************************
// Obliczanie Cmax
    }



//*****************************
    cout << endl;
    PlikDane.close();   // zamykanie pliku z danymi
    //system("pause");

    return 0;
} // main
