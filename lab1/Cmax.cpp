#include <iostream>

using namespace std;

#include <iostream>
using namespace std;

struct CzasZadaniaNaMaszynie{
   int Obrobka=0; 
   int KoniecObrobki=0;
};

int Cmax = 0;

int main() {

    int IleZadan = 3;
    int IleMaszyn = 3;
    
    CzasZadaniaNaMaszynie Kokos[IleZadan][IleMaszyn];
    
    for(int i=0; i<IleZadan; i++){
        for(int j=0; j<IleZadan; j++){
            Kokos[i][j].Obrobka = i+j; // podawanie czasow obrobki; po kolei zadania
        }
    }
    
    // Pierwsza Maszyna:
    Kokos[0][1].KoniecObrobki = Kokos[0][1].Obrobka;
    for(int i=1; i<IleZadan; i++){
        Kokos[i][1].KoniecObrobki = Kokos[i-1][1].KoniecObrobki + Kokos[i][1].Obrobka; // podawanie czasow obrobki; po kolei zadania
    }
   
	// your code goes here
	std::cout << "KOKO";
	return 0;
}


// tab[i].KoniecObrobkiMasz1=... tab[i-1]+P[i] zaczynaj od 1!!!!
// if tab[i-1].C2 > tab[i].C1 tab[i].C2=tab[i-1].c2+tab[i].p2;
// else tab[i].C2=tab[i].c1+tab[i].p2;
//Cmax=tab[ost i].C2;