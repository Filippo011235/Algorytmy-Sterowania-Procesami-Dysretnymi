#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

#define RPQ 3

struct CzasyRPQ{
    int NrZad;
    int Czasy[RPQ];
};

void WyswietlTabRPQ(int Tab[][RPQ], int IleZadan){
    for (int i=0; i < IleZadan; i++) {
        for (int j=0; j < RPQ; j++) {
            cout << Tab[i][j] << "   ";
        }
        cout << endl;
    }
}

int MinR (std::vector<CzasyRPQ> Nniegotowych, int &IndWybranegoZadJ)
{
    int Rbufor = 1000000;
    for (int i=0; i < Nniegotowych.size(); i++) {
        if(Nniegotowych[i].Czasy[0] < Rbufor){     // jak remis to bierze pierwszy z najmniejszym czasem
            Rbufor = Nniegotowych[i].Czasy[0];
            IndWybranegoZadJ = i;
        }
    }
    return Rbufor;
}

void Schrage(int ZadaneDane[][RPQ], int IleZadan, int PiS[]){
    int iter = 0; // numer kolejnosci zadania dodawanego
    int Sigma[IleZadan] = {}; // Czesciowa kolejnosc uszeregowanych zadan // Czy rozmiar dobry?
    // int Ngotowych[IleZadan][RPQ] = {}; // zbior zadan gotowych do uszeregowania
    // int Nniegotowych[IleZadan][RPQ]; // zbior zadan nieuszeregowanych
    int t; // zmienna pomocnicza czas
    int IndWybranegoZadJ;        // j*
    std::vector<CzasyRPQ> Ngotowych;
    std::vector<CzasyRPQ> Nniegotowych;
    CzasyRPQ Kokos;

    for(int i = 0; i < IleZadan; i++) {
        Kokos.NrZad = i;
        for (int j=0; j < RPQ; j++) {
            Kokos.Czasy[j] =  ZadaneDane[i][j];
        }
        Nniegotowych.push_back(Kokos);
    }

    // for (int i=0; i < IleZadan; i++) {
    //     for (int j=0; j < RPQ; j++) {
    //         Nniegotowych[i][j] =  ZadaneDane[i][j];
    //     }
    // }

    // inicjalizowanie poczatkowego czasu t
    t = 1000000000;               // skrajnie duzy czas
    for (int i=0; i < Nniegotowych.size(); i++) {
        if(Nniegotowych[i].Czasy[0] < t){     // jak remis to bierze pierwszy z najmniejszym czasem
            t = Nniegotowych[i].Czasy[0];
        }
    }
    
    while( !Nniegotowych.empty() || !Ngotowych.empty()){
    getchar();
    cout << "Rozmiar Nniegotowych: " << Nniegotowych.size() << endl;
    cout << "Rozmiar Ngotowych: " << Ngotowych.size() << endl;
    
        
                
        while(!Nniegotowych.empty() && MinR(Nniegotowych, IndWybranegoZadJ) <= t){
            cout << "MinR -->    " << MinR(Nniegotowych, IndWybranegoZadJ) << endl;
            cout << "T    -->    " << t << endl;
           

            // IndWybranegoZadJ ma juz indeks zadania z najmniejszym R, patrz wyzej
            Ngotowych.push_back(Nniegotowych[IndWybranegoZadJ]);
            Nniegotowych.erase(Nniegotowych.begin() + IndWybranegoZadJ);
        }
        if(Ngotowych.empty()){
            t = MinR(Nniegotowych, IndWybranegoZadJ);
        } else {
            // szukanie max q
            int Qbufor = 0;
            for (int i=0; i < Ngotowych.size(); i++) {
                if(Ngotowych[i].Czasy[2] > Qbufor){     // jak remis to bierze pierwszy z najwiekszym czasem
                    Qbufor = Ngotowych[i].Czasy[2];
                    IndWybranegoZadJ = i;
                }
            }   
            Sigma[iter] = Ngotowych[IndWybranegoZadJ].NrZad;    // umyslna zamiana; najpierw przepisz, potem usun
            iter++;
            cout << "Usuwanie" << endl;

            t += Ngotowych[IndWybranegoZadJ].Czasy[1];
            Ngotowych.erase(Ngotowych.begin() + IndWybranegoZadJ);
        }
    }   // while oba N nie sa puste
    
    for (int i=0; i < IleZadan; i++) {      // mozna bez Sigma u nas
        PiS[i] = Sigma[i];
    }   
}   // Schrage

// ***********************************************************
int Cmax(int ZadaneDane[][RPQ], int PiS[], int IleZadan) {
    int S[IleZadan];    // Momenty rozpoczecia zadan
    int C[IleZadan];    // Momenty zakończenia wykonania zadan
    vector<int> CzasCmax;
    
    // dla i =0
    S[0] = ZadaneDane[PiS[0]][0];              // czas r z pierwszego zadania z PI
    C[0] = S[0] + ZadaneDane[PiS[0]][1];       // czas r + p z pierwszego zadania z PI
    CzasCmax.push_back(C[0] + ZadaneDane[PiS[0]][2]);
    for (int i=1; i < IleZadan; i++) {  
        S[i] = max(ZadaneDane[PiS[i]][0], S[i-1] + ZadaneDane[PiS[i-1]][1]);
        C[i] = S[i] + ZadaneDane[PiS[i]][1];
        CzasCmax.push_back(C[i] + ZadaneDane[PiS[i]][2]);
    }

    vector<int>::iterator result = max_element(CzasCmax.begin(), CzasCmax.end());
    // cout << "Result ___ " << ( *result) << endl;

    // return CzasCmax[result]; // czyli Cmax
    return *result;
}
// ********************************************************

int main(){
    // ofstream WynikNeh     ("WynikNeh.txt");         // zapis wyników Neh do pliku

    //*****************************************************
    // Pobieranie danych z pliku
    ifstream PlikDane("dane.txt");  // uchwyt do pliku z danymi
    string linia;                   // zmienna potrzebna do odczytu
    int IleZadan = 0;     

    if(PlikDane.is_open() == false) {
        cout << "błąd wczytu pliku";
    }

    while(getline(PlikDane,linia)) {
        cout << endl << "***************************************" << endl;
        PlikDane >> IleZadan;       // popbranie z pliku informacji o ilości zadań 
        cout << "Zad: " << IleZadan << endl; // dla sprawdzenia

        int ZadaneDane[IleZadan][RPQ];   // przechowuje czasy odczytane z pliku
        int PiS[IleZadan] = {};
    
        //Odczyt z pliku
        for (int i=0; i < IleZadan; i++) {
            for (int j=0; j < RPQ; j++) {
                PlikDane >> ZadaneDane[i][j];
            }
        }
        WyswietlTabRPQ(ZadaneDane, IleZadan);
        cout << "Kokos:" << endl;
        Schrage(ZadaneDane, IleZadan, PiS);
        cout << "Ostateczna kolejnosc:" << endl;
        for (int i=0; i < IleZadan; i++) {
            cout << PiS[i] << "   ";
        }

        // Cmax
        cout << endl << "Cmax ____________>  " << Cmax(ZadaneDane, PiS, IleZadan) << endl;

    } // while czytania z pliku

    //********************************************************
    PlikDane.close();   // zamykanie pliku z danymi
    cout << endl;
    // system("pause");
}   // main
