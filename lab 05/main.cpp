#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <array>

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

int MinR (std::vector<CzasyRPQ> Nniegotowych, int &IndWybranegoZadJ){
    int Rbufor = 1000000;
    for (unsigned i=0; i < Nniegotowych.size(); i++) {
        if(Nniegotowych[i].Czasy[0] < Rbufor){     // jak remis to bierze pierwszy z najmniejszym czasem
            Rbufor = Nniegotowych[i].Czasy[0];
            IndWybranegoZadJ = i;
        }
    }
    return Rbufor;
}

struct CzasyRPQ MinR (std::vector<CzasyRPQ> Nniegotowych){
    struct CzasyRPQ bufor;
    bufor.Czasy[0] = 1000000;
    for (unsigned i=0; i < Nniegotowych.size(); i++) {
        if(Nniegotowych[i].Czasy[0] < bufor.Czasy[0]){     // jak remis to bierze pierwszy z najmniejszym czasem
            bufor = Nniegotowych[i];
        }
    }
    return bufor;
}


void UsunZwektora(vector<CzasyRPQ>& Kokos, struct CzasyRPQ DoUsuniecia) {
    for (unsigned i=0; i < Kokos.size(); i++) {
        if (Kokos[i].NrZad == DoUsuniecia.NrZad) {
            Kokos.erase(Kokos.begin() + i);
        }
    } 
}

void Schrage(int ZadaneDane[][RPQ], int IleZadan, int PiS[]){
    int iter = 0; // numer kolejnosci zadania dodawanego
    int Sigma[IleZadan] = {}; // Czesciowa kolejnosc uszeregowanych zadan // Czy rozmiar dobry?
    int t; // zmienna pomocnicza czas
    int IndWybranegoZadJ;        // j*
    std::vector<CzasyRPQ> Ngotowych;
    std::vector<CzasyRPQ> Nniegotowych;
    CzasyRPQ Kokos;     // bufor na struktury - do przepisywania na liste Nniegotowych

    for(int i = 0; i < IleZadan; i++) {
        Kokos.NrZad = i;
        for (int j=0; j < RPQ; j++) {
            Kokos.Czasy[j] =  ZadaneDane[i][j];
        }
        Nniegotowych.push_back(Kokos);
    }

    // inicjalizowanie poczatkowego czasu t
    t = 1000000000;               // skrajnie duzy czas
    for (unsigned i=0; i < Nniegotowych.size(); i++) {
        if(Nniegotowych[i].Czasy[0] < t){     // jak remis to bierze pierwszy z najmniejszym czasem
            t = Nniegotowych[i].Czasy[0];
        }
    }
    
    while( !Nniegotowych.empty() || !Ngotowych.empty()){
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
            for (unsigned i=0; i < Ngotowych.size(); i++) {
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
    int t = 0;  // zmienna pomocnicza czas
    struct CzasyRPQ IndObecnieWykZadL;  // obecnie wykonywane zadanie l
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

    while( !Nniegotowych.empty() || !Ngotowych.empty()){
        while(!Nniegotowych.empty() && MinR(Nniegotowych).Czasy[0] <= t){
            IndWybranegoZadJ = MinR(Nniegotowych);
            Ngotowych.push_back(IndWybranegoZadJ);
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
            for (unsigned i=0; i < Ngotowych.size(); i++) {
                if(Ngotowych[i].Czasy[2] > IndWybranegoZadJ.Czasy[2]){     // jak remis to bierze pierwszy z najwiekszym czasem
                    IndWybranegoZadJ = Ngotowych[i];
                }
            }  
            UsunZwektora(Ngotowych, IndWybranegoZadJ);  
            IndObecnieWykZadL = IndWybranegoZadJ;   // l = *j
            t += IndWybranegoZadJ.Czasy[1];

            CMAX = (CMAX > t + IndWybranegoZadJ.Czasy[2]) ? CMAX : t + IndWybranegoZadJ.Czasy[2];
        }
    }   // while oba N nie sa puste
    
    return CMAX;
}   // Schrage pmtn

// ***********************************************************
int Cmax(int ZadaneDane[][RPQ],  int IleZadan, int PiS[]) {
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
    return *result;
}
// ********************************************************

int ObliczB(int ZadaneDane[][RPQ], int PiS[], int IleZadan){
    int b; // indeks zadania b
    int TymczasowyCMax = 0, CzasZadania;
    for (int i=0; i < IleZadan; i++) {	
        CzasZadania = ZadaneDane[PiS[i]][0]+ZadaneDane[PiS[i]][1]+ZadaneDane[PiS[i]][2];        // NIE R TYLKO S_j
		if (CzasZadania > TymczasowyCMax) {
			b = i;
			TymczasowyCMax = CzasZadania;
		}
	}
    return b;
}

void Carlier(int ZadaneDane[][RPQ], int IleZadan, int PiOptymalnne[]){
    int U, LB, UB = 10000000; // wartosc lub oszacowania wartosci funkcji celu
    int a,b,c;
    // Inicjalizacja wartosci funkcji celu, czyli U = Cmax
    int BuforPi[IleZadan]; // Kolejnosc zadan ze Shrage
    Schrage(ZadaneDane, IleZadan, BuforPi);
    U = Cmax(ZadaneDane, IleZadan, BuforPi);
    if(U < UB){     // Wartosc celu ze Schrage, mniejsza niz gorne oszacowanie
        UB = U;         
        for(int i=0; i<IleZadan; i++){
            PiOptymalnne[i] = BuforPi[i];
        }
    }




}   // Carlier

int main(){
    //*****************************************************
    // Pobieranie danych z pliku
    ifstream PlikDane("dane.txt");  // uchwyt do pliku z danymi
    string linia;                   // zmienna potrzebna do odczytu
    int IleZadan = 0;     

    if(PlikDane.is_open() == false) {
        cout << "błąd wczytu pliku";
    }

    ofstream Kokos("Czasy.txt");

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
        Schrage(ZadaneDane, IleZadan, PiS);
        // cout << "Ostateczna kolejnosc:" << endl;
        // for (int i=0; i < IleZadan; i++) {
        //     cout << PiS[i] << "   ";
        // }

        // Cmax
        cout << endl << "Cmax ____________>  " << Cmax(ZadaneDane, IleZadan, PiS) << endl;        

        cout << endl << "Cmax pmtn _._._._>  " << Schrage_pmtn(ZadaneDane, IleZadan, PiS) << endl;
        } // while czytania z pliku

    //********************************************************
    PlikDane.close();   // zamykanie pliku z danymi
    Kokos.close();
    cout << endl;
    system("pause");
}   // main
