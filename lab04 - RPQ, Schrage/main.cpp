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
    void  operator=(const struct CzasyRPQ& B);
};

void CzasyRPQ::operator=(const struct CzasyRPQ& B) {
    for (int i=0; i < RPQ; ++i) {
        this->Czasy[i] = B.Czasy[i]; 
    }
    this->NrZad = B.NrZad;
}

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

struct CzasyRPQ MinR (std::vector<CzasyRPQ> Nniegotowych)
{
    struct CzasyRPQ bufor;
    bufor.Czasy[0] = 1000000;
    for (int i=0; i < Nniegotowych.size(); i++) {
        if(Nniegotowych[i].Czasy[0] < bufor.Czasy[0]){     // jak remis to bierze pierwszy z najmniejszym czasem
            bufor = Nniegotowych[i];
        }
    }
    return bufor;
}


void UsunZwektora(vector<CzasyRPQ>& Kokos, struct CzasyRPQ DoUsuniecia) {
    for (int i=0; i < Kokos.size(); i++) {
        if (Kokos[i].NrZad == DoUsuniecia.NrZad) {
            Kokos.erase(Kokos.begin() + i);
        }
    } 
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
    // getchar();
    
        
                
        while(!Nniegotowych.empty() && MinR(Nniegotowych, IndWybranegoZadJ) <= t){

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

            t += Ngotowych[IndWybranegoZadJ].Czasy[1];
            Ngotowych.erase(Ngotowych.begin() + IndWybranegoZadJ);
        }
    }   // while oba N nie sa puste
    
    for (int i=0; i < IleZadan; i++) {      // mozna bez Sigma u nas
        PiS[i] = Sigma[i];
    }   
}   // Schrage

int Schrage_pmtn(int ZadaneDane[][RPQ], int IleZadan, int PiS[]){
    int CMAX = 0;
    int iter = 0; // numer kolejnosci zadania dodawanego
    int Sigma[IleZadan] = {}; // Czesciowa kolejnosc uszeregowanych zadan // Czy rozmiar dobry?
    // int Ngotowych[IleZadan][RPQ] = {}; // zbior zadan gotowych do uszeregowania
    // int Nniegotowych[IleZadan][RPQ]; // zbior zadan nieuszeregowanych
    int t = 0;  // zmienna pomocnicza czas
    struct CzasyRPQ IndObecnieWykZadL;  // obecnie wykonywane zadanie l
    int q0 = 1000000; // czas dostarczenia
    struct CzasyRPQ IndWybranegoZadJ;        // j*
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
    // t = 1000000000;               // skrajnie duzy czas
    // for (int i=0; i < Nniegotowych.size(); i++) {
    //     if(Nniegotowych[i].Czasy[0] < t){     // jak remis to bierze pierwszy z najmniejszym czasem
    //         t = Nniegotowych[i].Czasy[0];
    //     }
    // }
    
    while( !Nniegotowych.empty() || !Ngotowych.empty()){
    
    
    
                
        while(!Nniegotowych.empty() && MinR(Nniegotowych).Czasy[0] <= t){
            IndWybranegoZadJ = MinR(Nniegotowych);

            // IndWybranegoZadJ ma juz indeks zadania z najmniejszym R, patrz wyzej
            Ngotowych.push_back(IndWybranegoZadJ);
            // Nniegotowych.erase(Nniegotowych.begin() + IndWybranegoZadJ);
            UsunZwektora(Nniegotowych, IndWybranegoZadJ);

            if (IndWybranegoZadJ.Czasy[2] > IndObecnieWykZadL.Czasy[2]) {
                IndObecnieWykZadL.Czasy[1] = t - IndWybranegoZadJ.Czasy[0];
                t = IndWybranegoZadJ.Czasy[0];

                if ( IndObecnieWykZadL.Czasy[1] > 0) {
                    Ngotowych.push_back(IndObecnieWykZadL);
                }
            }
        }
        if(Ngotowych.empty()){
            t = MinR(Nniegotowych).Czasy[0];
        } else {
            // szukanie max q
            IndWybranegoZadJ.Czasy[2] = 0;
            for (int i=0; i < Ngotowych.size(); i++) {
                if(Ngotowych[i].Czasy[2] > IndWybranegoZadJ.Czasy[2]){     // jak remis to bierze pierwszy z najwiekszym czasem
                    IndWybranegoZadJ = Ngotowych[i];
                }
            }  
            UsunZwektora(Ngotowych, IndWybranegoZadJ);  
            // Sigma[iter] = Ngotowych[IndWybranegoZadJ].NrZad;    // umyslna zamiana; najpierw przepisz, potem usun
            IndObecnieWykZadL = IndWybranegoZadJ;   // l = *j
            t += IndWybranegoZadJ.Czasy[1];
            // Ngotowych.erase(Ngotowych.begin() + IndWybranegoZadJ);
           

            CMAX = (CMAX > t + IndWybranegoZadJ.Czasy[2]) ? CMAX : t + IndWybranegoZadJ.Czasy[2];
        }
    }   // while oba N nie sa puste
    
    // for (int i=0; i < IleZadan; i++) {      // mozna bez Sigma u nas
    //     PiS[i] = Sigma[i];
    // }   
    return CMAX;
}   // Schrage pmtn

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
        //WyswietlTabRPQ(ZadaneDane, IleZadan);
        Schrage(ZadaneDane, IleZadan, PiS);
        cout << "Ostateczna kolejnosc:" << endl;
        for (int i=0; i < IleZadan; i++) {
            cout << PiS[i] << "   ";
        }

        // Cmax
        cout << endl << "Cmax ____________>  " << Cmax(ZadaneDane, PiS, IleZadan) << endl;

        cout << endl << "Cmax pmtn _._._._>  " << Schrage_pmtn(ZadaneDane, IleZadan, PiS) << endl;

    } // while czytania z pliku

    //********************************************************
    PlikDane.close();   // zamykanie pliku z danymi
    cout << endl;
    // system("pause");
}   // main
