#include <iostream>
#include <fstream>

using namespace std;

#define RPQ 3

void WyswietlTabRPQ(int Tab[][RPQ], int IleZadan){
    for (int i=0; i < IleZadan; i++) {
        for (int j=0; j < RPQ; j++) {
            cout << Tab[i][j] << "   ";
        }
        cout << endl;
    }
}

void Schrage(int ZadaneDane[][RPQ], int IleZadan, int PiS[]){


    // zmienic wektor


    int i = 1; // numer kolejnosci zadania dodawanego
    int Sigma[IleZadan] = {}; // Czesciowa kolejnosc uszeregowanych zadan // Czy rozmiar dobry?
    int Ngotowych[IleZadan][RPQ] = {}; // zbior zadan gotowych do uszeregowania
    int Nniegotowych[IleZadan][RPQ]; // zbior zadan nieuszeregowanych
    int t; // zmienna pomocnicza czas

    for (int i=0; i < IleZadan; i++) {
        for (int j=0; j < RPQ; j++) {
            Nniegotowych[i][j] =  ZadaneDane[i][j];
        }
    }

    // inicjalizowanie poczatkowego czasu t
    t = 1000000000;               // skrajnie duzy czas
    for (int i=0; i < IleZadan; i++) {
        if(Nniegotowych[i][0] < t){     // jak remis to bierze pierwszy z najmniejszym czasem
            t = Nniegotowych[i][0];
        }
    }

    while( ||)


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
    
        //Odczyt z pliku
        for (int i=0; i < IleZadan; i++) {
            for (int j=0; j < RPQ; j++) {
                PlikDane >> ZadaneDane[i][j];
            }
        }
        WyswietlTabRPQ(ZadaneDane, IleZadan);
    } // while czytania z pliku

    //********************************************************
    PlikDane.close();   // zamykanie pliku z danymi
    system("pause");
}   // main
