#include <iostream>
using namespace std;

#define ZADANIA 6
#define MASZYNY 2

int sumaWszystkichCzasow(int tablica_czasow[][ZADANIA], int nrMaszyny, int nrZadania)
{
    int suma = 0;
    for (int i = 0; i < nrMaszyny; i++)
    {
        for (int j = 0; j < nrZadania; j++)
        {
            suma += tablica_czasow[i][j];
        }
    }
    return suma;
}

bool sprawdzZadanie(int kolejnoscZadan[ZADANIA], int zadanie) {
    for (int i=0; i < ZADANIA; i++) {
        if (kolejnoscZadan[i] == zadanie)
            return true;
    }
    return false;
}

int main()
{
    // Algorytm Johnson'a dla dwuch maszyn

    // Tablice do przechowywania zadań
    const int nrMaszyny = 2, nrZadania = 6;
    int tablica_czasow[2][6];
    int kolejnosc_zadan[ZADANIA];
    int lista_1[ZADANIA];
    int lista_2[ZADANIA];

    for (int i = 0; i < nrZadania; i++) // wypełnienie pustych list
        kolejnosc_zadan[i] = i + 1;
    for (int i = 0; i < nrZadania; i++) // wypełnienie pustych list
        lista_1[i] = lista_2[i] = -1;

    // Uzupełnienie lisy czasami
    tablica_czasow[0][0] = 6;
    tablica_czasow[0][1] = 10;
    tablica_czasow[0][2] = 4;
    tablica_czasow[0][3] = 7;
    tablica_czasow[0][4] = 6;
    tablica_czasow[0][5] = 5;

    tablica_czasow[1][0] = 4;
    tablica_czasow[1][1] = 8;
    tablica_czasow[1][2] = 9;
    tablica_czasow[1][3] = 2;
    tablica_czasow[1][4] = 3;
    tablica_czasow[1][5] = 6;

    for (int i=0; i < nrMaszyny; i++) {
        cout << "Maszyna " << i << ": ";
        for (int j=0; j < nrZadania; j++)
            cout << tablica_czasow[i][j] << " ";
        cout << endl;
    }

    int suma = sumaWszystkichCzasow(tablica_czasow, nrMaszyny, nrZadania);

    // szukanie najmniejszej wartosci
    int zadanieOstatecznie=0, maszynaOstatecznie=0;
    int powtorzenieZadania=0, powtorzenieMaszyny=0;
    int granica = 0;
    int k = 0;
    while (k != nrZadania)
    {
        int najkrotszyCzas = suma;
        bool remis = false;

        for (int i=0; i < nrMaszyny; i++) {
            for (int j=0; j < nrZadania; j++) {
                if ((tablica_czasow[i][j] == granica) && !((powtorzenieZadania == j) || (powtorzenieMaszyny == i))) {
                    cout << "Wykryto remis " << tablica_czasow[i][j] << " <- na m " << i + 1 << " | z: " << j+1<< endl;
                    remis = true;
                    najkrotszyCzas = tablica_czasow[i][j];
                    zadanieOstatecznie = j;
                    maszynaOstatecznie = i;
                }

                if ((tablica_czasow[i][j] <= najkrotszyCzas) && (tablica_czasow[i][j] > granica) && sprawdzZadanie(kolejnosc_zadan, j) && !remis) {
                    najkrotszyCzas = tablica_czasow[i][j];
                    zadanieOstatecznie = j;
                    maszynaOstatecznie = i;
                }
            }
        }
        powtorzenieZadania = zadanieOstatecznie;
        powtorzenieMaszyny = maszynaOstatecznie;
        granica = najkrotszyCzas;
        if (remis) granica++;   // znaleźć lepsze rozwiązanie !!!
        cout << k << " - Najkrótszy czas: -> " << najkrotszyCzas << " <- na maszyniie " << maszynaOstatecznie + 1 << " | zadanie: " << zadanieOstatecznie+1 << endl;

        if (maszynaOstatecznie == 0) {
            for (int i=0; i < nrZadania; i++) {
                if (lista_1[i] == -1) {
                    lista_1[i] = zadanieOstatecznie;
                    break;
                }
            }
        }

        if (maszynaOstatecznie == 1) {
            for (int i=nrZadania-2; i >= 0; i--) {
                lista_2[i+1] = lista_2[i];
            }
            lista_2[0] = zadanieOstatecznie;
        }

        // znajduje i usuwa zadanie 
        for (int i=0; i < ZADANIA; i++) {
            if (kolejnosc_zadan[i] == zadanieOstatecznie) {
                kolejnosc_zadan[i] = -1;
            }
        }

        k++;
    }

    cout << "L1: ";
    for (int i=0; i < nrZadania; i++) {
        cout << lista_1[i]+1 << " ";
    }
    cout << endl << "L2: ";
    for (int i=0; i < nrZadania; i++) {
        cout << lista_2[i]+1 << " ";
    }



    return 0;
}

// 1. szuka najmniejszej
// 2. szuka remisu
// 2.1 czy na róznych maszynach
// 2.2 czy na tej samej maszynie