#include <iostream>
using namespace std;

int iloscZadan = 0;

// Liczenie silni
int silnia(int n) {
    if (n <=0 ) return 0;
    if (n == 1) return n;
    n = n * silnia(n-1);
    return n;
}

bool czy_byla_wczesniej(int* c, int i) {         // sprawdza czy dana wartość nie pojawiła się wcześniej
    for (int j=0; j < iloscZadan; j++) 
            if (i == c[j]) return true;
    return false;
}

// Wyświetla wszystkie możliwe kombinacje zawartości tablicy nrZadan
void permutacja(int*nrZadan, int poziomRekurencji = 0, int* c = NULL) {
    int cont[iloscZadan];                    // przechowuje wartości które zostały już użyte
    for (int i=0; i < iloscZadan; i++){
        if ((poziomRekurencji > 0) && (i < poziomRekurencji))   // wartosć z wyższej rekurencji
            cont[i] = c[i];
        else    
            cont[i] = -1;
    }
    if (poziomRekurencji == 2) cout << endl;
    for (int i=0; i < iloscZadan; i++) {
        if (czy_byla_wczesniej(cont, i)) continue;     // Każda wartość zostanie rozpatrzona tylko raz
        cont[poziomRekurencji] = i;
        
        if (poziomRekurencji == iloscZadan - 1) {
            for (int i=0; i < iloscZadan; i++) 
                cout << nrZadan[cont[i]];
            cout << ' ';
            return;
        }
        permutacja(nrZadan, poziomRekurencji+1, cont);
    }
    
    return;
}

void wyswietl(int* nrZadan) {
    permutacja(nrZadan, 0);
}

int main() {
    cout << "Podaj ilość zadań: ";
    cin >> iloscZadan;

    int nrZadan[iloscZadan];
    for (int i=0; i <iloscZadan; i++) {
        nrZadan[i] = i + 1;
    }

    wyswietl(nrZadan);  
    cout << endl; 

    return 0;
}