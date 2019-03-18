#include <iostream>
using namespace std;

struct CzasZadaniaNaMaszynie{
   int Obrobka=0; 
   int KoniecObrobki=0;
};

class ZadaneDane{
    int const IloscZadan;
    int const IloscMaszyn;
    int** TabZadaneDane;

    public:
    ZadaneDane(int Zadania, int Maszyny): IloscZadan(Zadania), IloscMaszyn(Maszyny){
        TabZadaneDane = new int *[IloscZadan];
        for(int i = 0; i < IloscZadan; i++){
            TabZadaneDane[i] = new int[IloscMaszyn];
        }
    } // konstruktor
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
    
// ALGORYTM NEH
void SumaCzasowNaMaszynach(ZadaneDane const TabDanych){
    int LiczbaZadan = TabDanych.IleZadan();
    int TabSum[LiczbaZadan] = {};
    
    for (int i = 0; i < LiczbaZadan; i++){
        for(int j = 0; j < TabDanych.IleMaszyn(); j++){
            TabSum[i] += TabDanych.Pokaz(i, j);
        }
    }
} 




int main(){
//*****************************************************
// Uzytkownik podaje:
    int IleZadan = 4;       // zmienna utworzona na poczatku
    int IleMaszyn = 3;

    int ZadaneDane2[IleZadan][IleMaszyn] =
    // Zadania \ Maszyny 
                /* {
                {4,4,5},  // 6 zamiast 5, blad graf <. tabela, w pdf!
                {3,5,7},
                {5,5,3},
                {4,5,2}
                }; */
                /*
                {
                {10,8},  // 6 zamiast 5, blad graf <. tabela, w pdf!
                {9,7},
                {8,9},
                {8,12},
                };*/
                {
                {4,1,4},
                {4,3,3},
                {1,2,3},
                {5,1,3}
                };

    ZadaneDane TabZadMasz(IleZadan, IleMaszyn);

    // Uzupełnianie tablicy
    for(int i = 0; i<IleZadan; i++){
        for(int j = 0; j<IleMaszyn; j++){
            TabZadMasz.Ustaw(i,j,ZadaneDane2[i][j]);
        }
    }


    SumaCzasowNaMaszynach(TabZadMasz);


//*****************************************************








//****************
system("pause");
} // main