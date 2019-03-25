#include <iostream>
using namespace std;

void zamien(int *tab, int i){
    int bufor = tab[i];
    tab[i] = tab[i - 1];
    tab[i - 1] = bufor;
}

int main(){

    int tab[4] = {};
    int TabPosortowane[] = {2, 1, 4, 3};
    int TabKombinacji[sizeof(TabPosortowane) / 4][sizeof(TabPosortowane) / 4] = {};

    int krok = 1;
    while (krok <= 4 )
    {
        tab[krok-1] = TabPosortowane[krok-1];
        for (int i = 0; i < krok; i++)
        {
            if (i != 0)
                zamien(tab, krok - i);
            for (int j = 0; j < krok; j++)
            {
                cout << tab[j] << ' ';
                TabKombinacji[i][j] = tab[j];
            }
            cout << endl;
        }
        krok++;
    }

    return 0;
}