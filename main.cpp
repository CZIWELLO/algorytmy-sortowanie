#include "helpers.h"
#include "introspektywne.h"
#include "quicksort.h"
#include "scalanie.h"
#include <iostream>

void wypiszTablice(int tablica[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << tablica[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    
    unsigned int wielkosci[] = {10000, 50000, 100000, 500000, 1000000};
    size_t liczba_testow = 100;
    float poziom_posortowania[] = {0.0, 0.25, 0.5, 0.75, 0.95, 0.99, 0.997, -1.0};

    for(auto wielkosc : wielkosci){
        int tablica[wielkosc];
        generujLiczby(wielkosc, tablica);
        wypiszTablice(tablica, wielkosc);
    }



    return 0;
}