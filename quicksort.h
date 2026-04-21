#pragma once

#include <cstddef>
#include "helpers.h"

template <typename T>
T mediana_trzech(const T& a, const T& b, const T& c) {  // zwaraca medianę z trzech elementów - pozawala wybrać optymalniejszy pivot
    if((a <= b && b <= c) || (a >= b && b >= c)) {return b;}
    if((b <= a && a <= c) || (b >= a && a >= c)) {return a;}
    return c;
}

template <typename T>
size_t partycja(T *tab, size_t poczatek, size_t koniec) {
    T wskaznik = mediana_trzech(tab[poczatek], tab[(poczatek + koniec) / 2], tab[koniec]); // wybieramy pivot jako medianę z trzech elementów - początku, środka i końca

    std::ptrdiff_t i = static_cast<std::ptrdiff_t>(poczatek) - 1;
    std::ptrdiff_t j = static_cast<std::ptrdiff_t>(koniec) + 1;
    while(true) {
        do {i++;} while(tab[i] < wskaznik); // szukamy większego elementu niż pivot po lewej stronie
        do {j--;} while(tab[j] > wskaznik); // szukamy mniejszego elementu niż pivot po prawej stronie 

        if(i >= j) {return j;} // jeśli wskaźniki się spotkają zwracamy indeks j jako punkt podziału

        zamien(tab[i], tab[j]); // zamieniamy te elementy miejscami
    }
}

template <typename T>
void quick_sort(T *tab, size_t poczatek, size_t koniec) {
    while(poczatek < koniec) {
        size_t w = partycja(tab, poczatek, koniec); // wybieramy pivot i dzielimy tablicę na dwie części - mniejszą i większą od pivota
        
        size_t lewa = w - poczatek + 1;
        size_t prawa = koniec - w;

        if(lewa < prawa) { // jeśli lewa część jest mniejsza niż prawa
            quick_sort(tab, poczatek, w); // sortujemy lewą część
            poczatek = w + 1; // przesuwamy lewy wskaźnik
        } else { // jeśli prawa część jest mniejsza niż lewa
            quick_sort(tab, w + 1, koniec); // sortujemy prawą część
            koniec = w; // przesuwamy prawy wskaźnik
        }
    }
}



