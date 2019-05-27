#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <array>
#include <string>
using namespace std;

#define RPQ 4

static int OstatecznePi1[50];
static int OstatecznePi2[100];
static int OstatecznePi3[200];
static bool Koniec = false;

struct CzasyRPQ{        // Struct zawierająca faktyczny numer zadania z instancji i jej czasy
    int NrZad;
    int Czasy[RPQ];
    void  operator=(const struct CzasyRPQ& B);
};

void CzasyRPQ::operator=(const struct CzasyRPQ& B) {
    for (int i=0; i < RPQ - 1; ++i) {
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
        for (int j=0; j < RPQ - 1; j++) {
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

int Schrage_pmtn(int ZadaneDane[][RPQ], int IleZadan){
    int CMAX = 0;
    int t = 0;  // zmienna pomocnicza czas
    struct CzasyRPQ IndObecnieWykZadL;  // obecnie wykonywane zadanie l
    struct CzasyRPQ IndWybranegoZadJ;        // j*
    std::vector<CzasyRPQ> Ngotowych;
    std::vector<CzasyRPQ> Nniegotowych;
    CzasyRPQ Kokos;

    for(int i = 0; i < IleZadan; i++) {
        Kokos.NrZad = i;
        for (int j=0; j < RPQ - 1; j++) {
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
        ZadaneDane[PiS[i]][3] = S[i];           // Potrzebne do liczenia ZadB w Carlierze
        CzasCmax.push_back(C[i] + ZadaneDane[PiS[i]][2]);
    }

    vector<int>::iterator result = max_element(CzasCmax.begin(), CzasCmax.end());
    return *result;
}
// ********************************************************


// najwieksze 1≤j≤n takie, ze Cmax(π)=C_π(j)+q_π(j)
int ObliczB(int ZadaneDane[][RPQ], int PiS[], int IleZadan){

        // cout << "Ostateczna kolejnosc:" << endl;        
        // for (int i=0; i < IleZadan; i++) {
        //     cout << PiS[i] << "   ";
        // }

    int ZadB = -1000; // indeks zadania b
    int GlownyCmax = Cmax(ZadaneDane, IleZadan, PiS); 
    int CzasCPi; // zmienna pomocnicza przechowująca czasy danego zadania
    for (int i=0; i < IleZadan; i++) {              // iteruj po wszystkich zad	
        CzasCPi = ZadaneDane[PiS[i]][3] + ZadaneDane[PiS[i]][1] + ZadaneDane[PiS[i]][2];
		if (CzasCPi == GlownyCmax) { // Cmax(π)=Cπ(j)+qπ(j)
			ZadB = i;         // ZadB to indeks zadania w kolejnosci PiS
		}
	}
    return ZadB;  // zwroc ostatnie z zad spelniajacych warunek if() -> oper. max{}
}

//  najmniejsze 1≤j≤n takie, ze  Cmax(π)=r_π(j)+(Suma p_π(s), dla s = j do b) + q_π(b) 
int ObliczA(int ZadaneDane[][RPQ], int PiS[], int IleZadan, int const ZadB){
    int ZadA = -1000;  // indeks zadania ZadA
    int GlownyCmax = Cmax(ZadaneDane, IleZadan, PiS);
    int SumaSciezkiKryt = 0;    // prawa strona powyzszego rownania   
    int SumaP;              // Sama suma p_π(s)

    for (int i=0; i < IleZadan; i++) {
        SumaP = 0;
        for (int s = i; s <= ZadB; s++) {       // operacja sumy czasow p
            SumaP += ZadaneDane[PiS[s]][1];
        }
        SumaSciezkiKryt = ZadaneDane[PiS[i]][0] + SumaP + ZadaneDane[PiS[ZadB]][2];
		if (SumaSciezkiKryt == GlownyCmax) {
			ZadA = i;       // indeks zadania "a" w kolejnossci PiS
            return ZadA;        // zwroc pierwszy indeks zadania ktory spelnia -> operacja min{}
		}
	}
    return ZadA;      // W razie czego wyswietl bledny indeks zad
}

// najwieksze a≤j≤b takie, ze q_π(j) < q_π(b)
int ObliczC(int ZadaneDane[][RPQ], int PiS[], int IleZadan, int const ZadB, int const ZadA){
    int ZadC = -1000;  // indeks zadania ZadC

    for (int i=ZadA; i < ZadB; i++) {
		if (ZadaneDane[PiS[i]][2] < ZadaneDane[PiS[ZadB]][2]) { // zad ktorego q jest < od q zadB
            ZadC = i;   // indeks zadania "c" w kolejnossci PiS
		}
	}
    return ZadC;    // zwroc ostatnie z zad spelniajacych warunek if() -> oper. max{}
}

// r/q'(K) ← min r/q π(j), dla j∈K
// KtoryCzas wybiera który z czasow RPQ
                                        // Może nie działać dla q, "bo tak"?
int MinCzas(int ZadaneDane[][RPQ], int KolejnoscK[], int RozmiarK, int PiNajlepsze[], int KtoryCzas){
    int Bufor = 1000000;

    for (int i=KolejnoscK[0]; i <= KolejnoscK[RozmiarK-1]; i++) {       // UWAGA na porownanie <=
        if(ZadaneDane[PiNajlepsze[i]][KtoryCzas] < Bufor){     // jak remis to bierze pierwszy z najmniejszym czasem
            Bufor = ZadaneDane[PiNajlepsze[i]][KtoryCzas];
        }
    }
    return Bufor;
}

// p(K) ← suma pπ(j), dla j∈K
int SumaCzasuP(int ZadaneDane[][RPQ], int KolejnoscK[], int RozmiarK, int PiNajlepsze[]){
    int Suma = 0;
    for (int i=KolejnoscK[0]; i <= KolejnoscK[RozmiarK-1]; i++) {                   // UWAGA na porownanie <=
        Suma += ZadaneDane[PiNajlepsze[i]][1];
    }
    return Suma;
}

int Maximum( int a, int b, int c ){
   return max(max(a, b), c);
}

void Carlier(int ZadaneDane[][RPQ], int IleZadan, int KopiaPi[], int UB = 100000000){
    if(Koniec == true){     // Potrzebne żeby uniknąć zbyt wielu rekurencji
        return;
    }
    // U - aktualna wartosc funkcji celu
    // LB – dolne oszacowanie wartoci funkcji ce
    // UB – górne oszacowanie wartoci funkcji celu ( warto funkcji celu dla najlepszego
    // dotychczas najlepszego rozwiazania)
    int U, LB; // wartosc lub oszacowania wartosci funkcji celu
    // Inicjalizacja wartosci funkcji celu, czyli U = Cmax
    
    int BuforPi[IleZadan];
    for (int i=0; i < IleZadan; i++) {
        BuforPi[i] = KopiaPi[i];
    }
    Schrage(ZadaneDane, IleZadan, BuforPi);
    U = Cmax(ZadaneDane, IleZadan, BuforPi);
    if(U < UB){     // Wartosc celu ze Schrage, mniejsza niz gorne oszacowanie
        UB = U;         
        if(IleZadan == 50){
            for(int i=0; i<IleZadan; i++){  // przepisz najlepsze rozwiazanie
            OstatecznePi1[i] = BuforPi[i];
            // cout << OstatecznePi[i] << "   ";
            }
        }
        if(IleZadan == 100){
            for(int i=0; i<IleZadan; i++){  // przepisz najlepsze rozwiazanie
            OstatecznePi2[i] = BuforPi[i];
            // cout << OstatecznePi[i] << "   ";
            }
        }
        if(IleZadan == 200){
            for(int i=0; i<IleZadan; i++){  // przepisz najlepsze rozwiazanie
            OstatecznePi3[i] = BuforPi[i];
            // cout << OstatecznePi[i] << "   ";
            }
        }
    }
    
    int ZadB = ObliczB(ZadaneDane, BuforPi, IleZadan);
    int ZadA = ObliczA(ZadaneDane, BuforPi, IleZadan, ZadB);
    int ZadC = ObliczC(ZadaneDane, BuforPi, IleZadan, ZadB, ZadA);

    // cout << endl << "A, B, C >>>\t" << ZadA << "\t" << ZadB << "\t" << ZadC << endl;

    if(ZadC == -1000){  // Nie ma takiego zadania/blad
        Koniec = true;  // sprawia ze juz zaden Carlier sie nie wywola(faktyczne wyjscie z funkcji)
        return; // zakoncz ten wezel
    }

    int KolejnoscK[ZadB-ZadC];
    for (int i = ZadC+1; i <= ZadB; i++){  // "<=" zeby uwzglednic tez ZadB
        KolejnoscK[i-ZadC-1] = i;
    }
    int RozmiarK = sizeof(KolejnoscK)/sizeof(KolejnoscK[0]);

    // r'(K) ← min rπ(j), dla j∈K
    int RPrim = MinCzas(ZadaneDane, KolejnoscK, RozmiarK, BuforPi, 0);
    // q(K) ← min qπ(j), dla j∈K
                                        // QPrim może nie działać, "bo tak"? Albo zaobserwowano jakąś anomalię
    int QPrim = MinCzas(ZadaneDane, KolejnoscK, RozmiarK, BuforPi, 2);
    // p(K) ← suma pπ(j), dla j∈K
    int PPrim = SumaCzasuP(ZadaneDane, KolejnoscK, RozmiarK, BuforPi);

    // przygotowanie do Max{h(K), h(K ∪ {c}), LB}
    int h_K = RPrim + PPrim + QPrim;  // 1342 dla 50 
    // Obliczanie h_ModK, czyli h(K ∪ {c})
    /********************************/
        int ModKolejnoscK[ZadB-ZadC+1];             
        for (int i = ZadC; i <= ZadB; i++){  // "<=" zeby uwzglednic tez ZadB
            ModKolejnoscK[i-ZadC] = i;
        }
        int ModRozmiarK = sizeof(ModKolejnoscK)/sizeof(ModKolejnoscK[0]);
        int ModRPrim = MinCzas(ZadaneDane, ModKolejnoscK, ModRozmiarK, BuforPi, 0);
        int ModQPrim = MinCzas(ZadaneDane, ModKolejnoscK, ModRozmiarK, BuforPi, 2);
        int ModPPrim = SumaCzasuP(ZadaneDane, ModKolejnoscK, ModRozmiarK, BuforPi);
        int h_ModK = ModRPrim + ModPPrim + ModQPrim;
    /*********************************/

    int RZapasowe = ZadaneDane[BuforPi[ZadC]][0];   // bufor na r_{pi(c)}
    ZadaneDane[BuforPi[ZadC]][0] = max(RZapasowe, (RPrim + PPrim));     // Max z tych dwoch czasow
    LB = Schrage_pmtn(ZadaneDane, IleZadan);       // nie liczy dla instancji z czasami = 0
    LB = Maximum(h_K, h_ModK, LB);
    if(LB < UB){  
        Carlier(ZadaneDane, IleZadan, BuforPi, UB);
    }
    ZadaneDane[BuforPi[ZadC]][0] = RZapasowe;     // odtworzenie r_{pi(c)}

    int QZapasowe = ZadaneDane[BuforPi[ZadC]][2];   
    ZadaneDane[BuforPi[ZadC]][2] = max(QZapasowe, (QPrim + PPrim));     // Max z tych dwoch czasow
    LB = Schrage_pmtn(ZadaneDane, IleZadan);
    LB = Maximum(h_K, h_ModK, LB);

    if(LB < UB){ 
        Carlier(ZadaneDane, IleZadan, BuforPi, UB);
    }
    ZadaneDane[BuforPi[ZadC]][2] = QZapasowe;       // odtworzenie q_{pi(c)}

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

    while(getline(PlikDane,linia)) {
        cout << endl << "***************************************" << endl;
        PlikDane >> IleZadan;       // popbranie z pliku informacji o ilości zadań 
        cout << "Zad: " << IleZadan << endl; // dla sprawdzenia

        int ZadaneDane[IleZadan][RPQ];   // przechowuje czasy odczytane z pliku
        int PiS[IleZadan] = {};
    
        //Odczyt z pliku
        for (int i=0; i < IleZadan; i++) {
            for (int j=0; j < RPQ - 1; j++) {
                PlikDane >> ZadaneDane[i][j];
            }
        }
        Carlier(ZadaneDane, IleZadan, PiS);
        Koniec = false; // pozwala na uruchomienie Carliera dla nast. instancji
        
        cout << "Ostateczna kolejnosc:" << endl;        
  
        if(IleZadan == 50){

            cout << endl << "Cmax ===>  " << Cmax(ZadaneDane, IleZadan, OstatecznePi1) << endl;        

        }

        if(IleZadan == 100){
        cout << endl << "Cmax ===>  " << Cmax(ZadaneDane, IleZadan, OstatecznePi2) << endl;        

        }
        if(IleZadan == 200){
            cout << endl << "Cmax ===>  " << Cmax(ZadaneDane, IleZadan, OstatecznePi3) << endl;        
        }    
    } // while czytania z pliku

    //********************************************************
    PlikDane.close();   // zamykanie pliku z danymi
    cout << endl;
    system("pause");
} // main