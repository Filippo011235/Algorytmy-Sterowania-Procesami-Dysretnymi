#include <iostream>
#include <fstream>
#include <vector>

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

void Schrage(int ZadaneDane[][RPQ], int IleZadan, int PiS[]){
    int i = 0; // numer kolejnosci zadania dodawanego
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
    
    cout << "Pierwszy while, ktory sie zapetla:" << endl;
    
        int Rbufor = 1000000;
        for (int i=0; i < Nniegotowych.size(); i++) {
            if(Nniegotowych[i].Czasy[0] < Rbufor){     // jak remis to bierze pierwszy z najmniejszym czasem
                Rbufor = Nniegotowych[i].Czasy[0];
                IndWybranegoZadJ = i;
            }
        }        
        while(!Nniegotowych.empty() && Rbufor <= t){
            // IndWybranegoZadJ ma juz indeks zadania z najmniejszym R, patrz wyzej
            Ngotowych.push_back(Nniegotowych[IndWybranegoZadJ]);
            Nniegotowych.erase(Nniegotowych.begin() + IndWybranegoZadJ);
        }
        if(Nniegotowych.empty()){
            t = Rbufor;
        } else {
            // szukanie max q
            int Qbufor = 0;
            for (int i=0; i < Ngotowych.size(); i++) {
                if(Ngotowych[i].Czasy[2] > Qbufor){     // jak remis to bierze pierwszy z najwiekszym czasem
                    Qbufor = Ngotowych[i].Czasy[2];
                    IndWybranegoZadJ = i;
                }
            }   
            Sigma[i] = Ngotowych[IndWybranegoZadJ].NrZad;    // umyslna zamiana; najpierw przepisz, potem usun
            i++;
            t += Ngotowych[IndWybranegoZadJ].Czasy[1];
            Ngotowych.erase(Ngotowych.begin() + IndWybranegoZadJ);
        }
    }   // while oba N nie sa puste
    
    for (int i=0; i < IleZadan; i++) {      // mozna bez Sigma u nas
        PiS[i] = Sigma[i];
    }   
}   // Schrage


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
        cout << "***************************************" << endl;
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
    } // while czytania z pliku

    //********************************************************
    PlikDane.close();   // zamykanie pliku z danymi
    system("pause");
}   // main
