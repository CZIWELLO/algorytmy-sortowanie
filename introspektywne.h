#pragma once

#include <cstddef>
#include <cmath>
#include "quicksort.h"

template <typename T>
void heapify(T* tab, size_t poczatek, size_t rozmiar, size_t i) {
    while(true) {
        size_t najwiekszy = i;
        size_t l = 2*i + 1;
        size_t r = 2*i + 2;

        if(l < rozmiar && tab[poczatek + l] > tab[poczatek + najwiekszy])
            najwiekszy = l;

        if(r < rozmiar && tab[poczatek + r] > tab[poczatek + najwiekszy])
            najwiekszy = r;

        if(najwiekszy == i) return;

        zamien(tab[poczatek + i], tab[poczatek + najwiekszy]);
        i = najwiekszy;
    }
}

template <typename T>
void heap_sort_zakres(T* tab, size_t poczatek, size_t koniec) {
    size_t n = koniec - poczatek + 1;

    for(std::ptrdiff_t i = static_cast<std::ptrdiff_t>(n/2) - 1; i >= 0; i--) {
        heapify(tab, poczatek, n, static_cast<size_t>(i));
    }

    for(size_t i = n - 1; i > 0; i--) {
        zamien(tab[poczatek], tab[poczatek + i]);
        heapify(tab, poczatek, i, 0);
    }
}

template <typename T>
void introsort_impl(T* tab, size_t poczatek, size_t koniec, size_t limit) {
    while(poczatek < koniec) {

        if(limit == 0) {
            heap_sort_zakres(tab, poczatek, koniec);
            return;
        }

        limit--;

        size_t w = partycja(tab, poczatek, koniec);

        size_t lewa = w - poczatek + 1;
        size_t prawa = koniec - w;

        if(lewa < prawa) {
            introsort_impl(tab, poczatek, w, limit);
            poczatek = w + 1;
        } else {
            introsort_impl(tab, w + 1, koniec, limit);
            koniec = w;
        }
    }
}

template <typename T>
void intro_sort(T* tab, size_t n) {
    if(n < 2) return;

    size_t limit = 2 * static_cast<size_t>(std::log2(n));
    introsort_impl(tab, 0, n - 1, limit);
}