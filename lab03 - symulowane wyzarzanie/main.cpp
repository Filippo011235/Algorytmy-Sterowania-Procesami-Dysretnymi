#include <iostream>
#include <cstdlib>
#include <algorithm>    // std::min_element
#include <fstream>
#include <ctime>
#include <cmath> // dla exp w prawdopodobienstwie

using namespace std;

#define SREDNIA 4
// #define TEMPERATURA 4
// #define MIKRO 4

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
    // srand(time(NULL));
    int i = rand() % IleZadan;
    int j = rand() % IleZadan;
    while(i==j) {
        j = rand() % IleZadan;
    }
    int bufor = tab[i];
    tab[i] = tab[j];
    tab[j] = bufor;
    // cout << "Swapuje: " << j << " z " << i << endl;
}
// Funkcja liczaca prawdopodobienstwo przejsca do sasiada w sym. wyzarz.
float Prawdopodobienstwo(int CmaxPi,int CmaxPiPrim, float Temp){
    float p = 0; // zmienna pomocnicza

    // cout << "Cmax Pi: " << CmaxPi << endl;
    // cout << "Cmax Pi prim: " << CmaxPiPrim << endl;

    if(CmaxPiPrim >= CmaxPi){ // Sasiad z lepszym Cmax
        p = exp((CmaxPi - CmaxPiPrim)/Temp);
    } else {
        p = 1;
    }
    // cout << "wartosc prawdop.: " << p << endl;  
    return p;
}
// Zmniejszanie temperatury
void FunkcjaChlodzenia(float &Temp){
    float mikro = 0.99;
    Temp *= mikro;
}
// Srednia z tablicy
int SredniaTablicy(int Tab[SREDNIA]){
    int Wynik = 0;
    for(int i=0; i < SREDNIA; i++){
        Wynik += Tab[i];
    }
    return Wynik/SREDNIA;
}


// ********************************************************

int main(){
    srand(time(NULL));
    ofstream WynikNeh     ("WynikNeh.txt");         // zapis wyników Neh do pliku
    ofstream WynikSW      ("WynikSW.txt");          // plkik do za
    ofstream WynikRoznica ("WynikRoznica.txt");     // plkik do za
    int lMaszynPlik = 0, lZadPlik = 0;
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
        int PiStartoweZNEH[IleZadan]; 
        int NEH_Cmax = 10000000; 
    //**************************************************************
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

                if(WynikiCmax[NrPermutacji] < NajmniejszyCmax){ // Nadpisanie najmniejszego Cmax
                    NajmniejszyCmax = WynikiCmax[NrPermutacji];
                    OptymalnyNrPermutacji = NrPermutacji;    
                }
            } // koniec sprawdzania wszystkich permutacji
    //*************************************
            // PRZEZENTACJA WYNIKOW
            if(RozwazaneZad == IleZadan){       // Pokazuj tylko dla ostatniej iteracji
                cout << "***************************************" << endl;
                if (IleMaszyn > lMaszynPlik) {
                    WynikNeh        << endl << "MASZYNY " << IleMaszyn << endl;
                    WynikSW         << endl << "MASZYNY " << IleMaszyn << endl;
                    WynikRoznica    << endl << "MASZYNY " << IleMaszyn << endl;
                    lMaszynPlik = IleMaszyn;
                } 
                if (IleZadan > lZadPlik) {
                    WynikNeh        << endl << "ZADANIA " << IleZadan << endl;
                    WynikSW         << endl << "ZADANIA " << IleZadan << endl;
                    WynikRoznica    << endl << "ZADANIA " << IleZadan << endl;
                    lZadPlik = IleZadan;
                } 
                WynikNeh << NajmniejszyCmax << endl; // Zapis wyników do plku

                cout << "NEH: \t" << NajmniejszyCmax << endl;
                NEH_Cmax = NajmniejszyCmax; // Do porownania z SW
                // " osiagnieto dla permutacji: " << endl;
                // for (int j=0; j < RozwazaneZad; j++) {
                //     cout << TabKombinacji[OptymalnyNrPermutacji][j] << " ";
                // }
                // cout << endl;
                // Deklaracja Pi0 i jego Cmax
                // for (int j=0; j < IleZadan; j++) {
                //     PiStartoweZNEH[j] = TabKombinacji[OptymalnyNrPermutacji][j];
                // } 
                for (int j=0; j < IleZadan; j++) {
                    PiStartoweZNEH[j] = TabKombinacji[OptymalnyNrPermutacji][j];
                    
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
        int WynikiSW[3];
        int SredniCmax = 1000000;
        // Porównanie początkowych kombinacji startowych
        // for (int n=0; n<IleMaszyn; n++) {
        //     LosowySwap(PiStartoweZNEH, IleZadan);
        // }
        for(int k = 0; k < SREDNIA; k++){    // wykonaj kilka razy, w celu obliczenia sredniej
            float Temp = 50;     // deklaracja temp. początkowej
            int Pi[IleZadan], PiBufor[IleZadan];
            int CmaxPi, CmaxPiPrim;
            for(int i = 0; i < IleZadan; i++){
                Pi[i] = PiStartoweZNEH[i];
            }
            
            do{
                for (int j=0; j < IleZadan; j++) {      // zauktualizowanie Bufora
                    PiBufor[j] = Pi[j];
                }            
                // Wygenerowanie ruchu (sasiada)
                LosowySwap(PiBufor, IleZadan);

                // PI prim - utworzenie tablicy potrzebnej do obliczenia Cmax
                int** TabPiPrim = new int*[IleZadan];
                for (int i = 0; i < IleZadan; i++){
                    TabPiPrim[i] = new int[IleMaszyn];
                }
                for(int i = 0; i<IleZadan; i++){    // Przypisanie czasów do pi prim
                    for(int j = 0; j<IleMaszyn; j++){
                        TabPiPrim[i][j] =  ZadaneDane2[PiBufor[i]-1][j];
                    }
                }
                CmaxPiPrim = Cmax(TabPiPrim, IleZadan-1, IleMaszyn);
                
                // PI  - utworzenie tablicy potrzebnej do obliczenia Cmax
                int** TabPi = new int*[IleZadan];
                for (int i = 0; i < IleZadan; i++){
                    TabPi[i] = new int[IleMaszyn];
                }
                for(int i = 0; i<IleZadan; i++){    // Przypisanie czasów do pi
                    for(int j = 0; j<IleMaszyn; j++){
                        TabPi[i][j] =  ZadaneDane2[Pi[i]-1][j];
                    }
                }
                CmaxPi = Cmax(TabPi, IleZadan-1, IleMaszyn);

                // Sprawdzenie
                // cout << "Przypisanie Pi Prim: " << endl;
                // for(int i = 0; i<IleZadan; i++){
                //     cout << PiBufor[i] << " : ";
                //     for(int j = 0; j<IleMaszyn; j++){
                //         cout << TabPiPrim[i][j] << " ";
                //     }
                //     cout << endl;
                // }

                // Wyznaczenie prawdopodobienstwa przejscia do Pi'            
                // wygenerowanie losowej liczby(od 0.0 do 1.0):
                float LosowaLiczba = ((double) rand() / (RAND_MAX));
                // cout << "Rand: " << LosowaLiczba << endl;
                if(Prawdopodobienstwo(CmaxPi, CmaxPiPrim, Temp) >= LosowaLiczba){
                    for (int j=0; j < IleZadan; j++) {
                        Pi[j] = PiBufor[j];
                    }   
                }
                FunkcjaChlodzenia(Temp);
            } while(Temp > 0.25);  // warunek petli na podstawie temperatury
            WynikiSW[k] = CmaxPi;
            cout << "SW" << k << ": \t" << WynikiSW[k] << endl;
        }   // koniec liczenia srednich SW 
        SredniCmax = SredniaTablicy(WynikiSW);
        cout << "Sred. Cmax:\t" << SredniCmax << endl;
        WynikSW << SredniCmax << endl;     // Zapis wyników do plku
        cout << "Roznica:" << NEH_Cmax - SredniCmax << " (+ na korzysc SW)" << endl;
        WynikRoznica << (NEH_Cmax - SredniCmax) << endl;    // Zapis wyników do plku
    } // koniec pętli while czytajacej z pliku
    //****************************
    // Zamykanie
    cout << endl;
    PlikDane.close();   // zamykanie pliku z danymi
    system("pause");
    return 0;
}