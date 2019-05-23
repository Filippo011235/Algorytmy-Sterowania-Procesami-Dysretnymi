#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <array>

using namespace std;

#define RPQ 3

struct CzasyRPQ{        // Struct zawierająca faktyczny numer zadania z instancji i jej czasy
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


// najwieksze 1≤j≤n takie, ze Cmax(π)=C_π(j)+q_π(j)
int ObliczB(int ZadaneDane[][RPQ], int PiS[], int IleZadan){
    int ZadB; // indeks zadania b
    int GlownyCmax = Cmax(ZadaneDane, IleZadan, PiS); 
    int CmaxDoZadania; // Cmax od 1-go zad do zad na ktorym zachodzi iteracja 
    for (int i=0; i < IleZadan; i++) {              // iteruj po wszystkich zad	
        CmaxDoZadania = Cmax(ZadaneDane, i, PiS);   // oblicz Cmax do iteratora
		if (CmaxDoZadania == GlownyCmax) {          // Cmax(π)=Cπ(j)+qπ(j)
			ZadB = i;                               
		}
	}
    return ZadB;  // zwroc ostatnie z zad spelniajacych warunek if() -> oper. max{}
}

//  najmniejsze 1≤j≤n takie, ze  Cmax(π)=r_π(j)+(Suma p_π(s), dla s = j do b) + q_π(b) 
int ObliczA(int ZadaneDane[][RPQ], int PiS[], int IleZadan, int ZadB){
    int ZadA;  // indeks zadania ZadA
    int GlownyCmax = Cmax(ZadaneDane, IleZadan, PiS);
    int SumaSciezkiKryt;    // prawa strona powyzszego rownania   
    int SumaP;              // Sama suma p_π(s)

    for (int i=0; i < IleZadan; i++) {
        SumaP = 0;
        for (int s = i; s < ZadB; s++) {       // operacja sumy czasow p
            SumaP += ZadaneDane[PiS[s]][1];
        }
        SumaSciezkiKryt = ZadaneDane[i][0] + SumaP + ZadaneDane[ZadB][2];
		if (SumaSciezkiKryt == GlownyCmax) {
			ZadA = i;
            return ZadA;        // zwroc pierwszy indeks zadania ktory spelnia -> operacja min{}
		}
	}
    return -1;      // W razie czego wyswietl bledny indeks zad
}

// najwieksze a≤j≤b takie, ze q_π(j) < q_π(b)
int ObliczC(int ZadaneDane[][RPQ], int PiS[], int IleZadan, int ZadB, int ZadA){
    int ZadC=0;  // indeks zadania ZadC

    for (int i=ZadA; i < ZadB; i++) {	
		if (ZadaneDane[i][2] < ZadaneDane[ZadB][2]) { // zad ktorego q jest < od q zadB
            ZadC = i;
		}
	}
    return ZadC;    // zwroc ostatnie z zad spelniajacych warunek if() -> oper. max{}
}

int MinCzas(int ZadaneDane[][RPQ], int KolejnoscK[], int RozmiarK, int PiNajlepsze[], int KtoryCzas){
    int Bufor = 1000000;

    int GranicaAbsurdu=  KolejnoscK[RozmiarK-1];    // DO SPRAWDZENIA

    for (int i=KolejnoscK[0]; i <= KolejnoscK[RozmiarK-1]; i++) {                   // UWAGA na porownanie <=
        if(ZadaneDane[i][KtoryCzas] < Bufor){     // jak remis to bierze pierwszy z najmniejszym czasem
            Bufor = ZadaneDane[i][KtoryCzas];
        }
    }
    return Bufor;
}

int SumaCzasuP(int ZadaneDane[][RPQ], int KolejnoscK[], int RozmiarK, int PiNajlepsze[]){
    int Suma = 0;
    for (int i=KolejnoscK[0]; i <= KolejnoscK[RozmiarK-1]; i++) {                   // UWAGA na porownanie <=
        Suma += ZadaneDane[i][1];
    }
    return Suma;
}

int Maximum( int a, int b, int c ){
   int max = ( a < b ) ? b : a;
   return ( ( max < c ) ? c : max );
}
void Carlier(int ZadaneDane[][RPQ], int IleZadan, int PiNajlepsze[], int UB = 100000000){
    // U - aktualna wartosc funkcji celu
    // LB – dolne oszacowanie wartoci funkcji ce
    // UB – górne oszacowanie wartoci funkcji celu ( warto funkcji celu dla najlepszego
    // dotychczas najlepszego rozwiazania)
    int U, LB; // wartosc lub oszacowania wartosci funkcji celu
    // Inicjalizacja wartosci funkcji celu, czyli U = Cmax
    int BuforPi[IleZadan]; // Kolejnosc zadan ze Shrage
    Schrage(ZadaneDane, IleZadan, BuforPi);
    U = Cmax(ZadaneDane, IleZadan, BuforPi);
    if(U < UB){     // Wartosc celu ze Schrage, mniejsza niz gorne oszacowanie
        UB = U;         
        for(int i=0; i<IleZadan; i++){  // przepisz najlepsze rozwiazanie
            PiNajlepsze[i] = BuforPi[i];
        }
    }
    
    int ZadB = ObliczB(ZadaneDane, BuforPi, IleZadan);
    int ZadA = ObliczA(ZadaneDane, BuforPi, IleZadan, ZadB);
    int ZadC = ObliczC(ZadaneDane, BuforPi, IleZadan, ZadB, ZadA);
    if(ZadC == 0){
        return; // zwrot wyniku polega na modyfikacji listy zadan PiNajlepsze w argumencie funkcji
    }
    int KolejnoscK[ZadB-ZadC];
    for (int i = ZadC+1; i <= ZadB; i++){  // <= zeby uwzglednic tez ZadB
        KolejnoscK[i-ZadC-1] = i;
    }
    int RozmiarK = sizeof(KolejnoscK)/sizeof(KolejnoscK[0]);
    int RPrim = MinCzas(ZadaneDane, KolejnoscK, RozmiarK, BuforPi, 0);
    int QPrim = MinCzas(ZadaneDane, KolejnoscK, RozmiarK, BuforPi, 2);
    int PPrim = SumaCzasuP(ZadaneDane, KolejnoscK, RozmiarK, BuforPi);

    int RZapasowe = ZadaneDane[BuforPi[ZadC]][0];   // tak na wypadek, moze mozna usunac
    ZadaneDane[BuforPi[ZadC]][0] = (RZapasowe > (RPrim + PPrim)) ? RZapasowe : (RPrim + PPrim);     // Max z tych dwoch czasow
    LB = Schrage_pmtn(ZadaneDane, IleZadan, BuforPi);
    // Max {h(K), h(K ∪ {c}), LB}
    int h_K = RPrim + PPrim + QPrim;
    // Obliczanie h_ModK, czyli h(K ∪ {c})
    /********************************/
        int ModKolejnoscK[ZadB-ZadC+1];             
        for (int i = ZadC; i <= ZadB; i++){  // <= zeby uwzglednic tez ZadB
            ModKolejnoscK[i-ZadC-1] = i;
        }
        int ModRozmiarK = sizeof(ModKolejnoscK)/sizeof(ModKolejnoscK[0]);
        int ModRPrim = MinCzas(ZadaneDane, ModKolejnoscK, ModRozmiarK, BuforPi, 0);
        int ModQPrim = MinCzas(ZadaneDane, ModKolejnoscK, ModRozmiarK, BuforPi, 2);
        int ModPPrim = SumaCzasuP(ZadaneDane, ModKolejnoscK, ModRozmiarK, BuforPi);
        int h_ModK = ModRPrim + ModPPrim + ModQPrim;
    /*********************************/
    LB = Maximum(h_K, h_ModK, LB);
    if(LB < UB){  
        Carlier(ZadaneDane, IleZadan, BuforPi, UB);
    }
    ZadaneDane[BuforPi[ZadC]][0] = RZapasowe;       // odtworzenie r_{pi(c)}
    
    int QZapasowe = ZadaneDane[BuforPi[ZadC]][2];   // tak na wypadek, moze mozna usunac
                                // MOZE RPQ PRIM TRZEBA NA NOWO
    ZadaneDane[BuforPi[ZadC]][2] = (QZapasowe > (QPrim + PPrim)) ? QZapasowe : (QPrim + PPrim);     // Max z tych dwoch czasow
    LB = Schrage_pmtn(ZadaneDane, IleZadan, BuforPi);
    // Max {h(K), h(K ∪ {c}), LB}
    h_K = RPrim + PPrim + QPrim;
    // Obliczanie h_ModK, czyli h(K ∪ {c})
    /********************************/
                 //ModKolejnoscK[ZadB-ZadC+1];             
        for (int i = ZadC; i <= ZadB; i++){  // <= zeby uwzglednic tez ZadB
            ModKolejnoscK[i-ZadC-1] = i;
        }
        ModRozmiarK = sizeof(ModKolejnoscK)/sizeof(ModKolejnoscK[0]);
        ModRPrim = MinCzas(ZadaneDane, ModKolejnoscK, ModRozmiarK, BuforPi, 0);
        ModQPrim = MinCzas(ZadaneDane, ModKolejnoscK, ModRozmiarK, BuforPi, 2);
        ModPPrim = SumaCzasuP(ZadaneDane, ModKolejnoscK, ModRozmiarK, BuforPi);
        h_ModK = ModRPrim + ModPPrim + ModQPrim;
    /*********************************/
    LB = Maximum(h_K, h_ModK, LB);
    if(LB < UB){  
        Carlier(ZadaneDane, IleZadan, BuforPi, UB);
    }
    ZadaneDane[BuforPi[ZadC]][2] = QZapasowe;       // odtworzenie r_{pi(c)}
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

    ofstream Wyniki("Czasy.txt");

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
        Carlier(ZadaneDane, IleZadan, PiS);
        
        cout << "Ostateczna kolejnosc:" << endl;        
        for (int i=0; i < IleZadan; i++) {
            cout << PiS[i] << "   ";
        }

        // Cmax
        cout << endl << "Cmax ____________>  " << Cmax(ZadaneDane, IleZadan, PiS) << endl;        
        } // while czytania z pliku

    //********************************************************
    PlikDane.close();   // zamykanie pliku z danymi
    Wyniki.close();
    cout << endl;
    system("pause");
} // main