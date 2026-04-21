#pragma once

#include <cstddef>

template <typename T>
void scal(T* tab, T* pomocnicza, size_t poczatek, size_t srodek, size_t koniec) {
    size_t i = poczatek;
    size_t j = srodek + 1;
    size_t k = poczatek;

    // scalanie do tablicy pomocniczej
    while (i <= srodek && j <= koniec) {
        if (tab[i] <= tab[j]) {
            pomocnicza[k++] = tab[i++];
        } else {
            pomocnicza[k++] = tab[j++];
        }
    }

    while (i <= srodek) {
        pomocnicza[k++] = tab[i++];
    }

    while (j <= koniec) {
        pomocnicza[k++] = tab[j++];
    }

    // kopiujemy z powrotem do oryginalnej tablicy
    for (size_t idx = poczatek; idx <= koniec; idx++) {
        tab[idx] = pomocnicza[idx];
    }
}

template <typename T>
void merge_sort_impl(T* tab, T* pomocnicza, size_t poczatek, size_t koniec) {
    if (poczatek >= koniec) return;

    size_t srodek = poczatek + (koniec - poczatek) / 2;

    merge_sort_impl(tab, pomocnicza, poczatek, srodek);
    merge_sort_impl(tab, pomocnicza, srodek + 1, koniec);

    scal(tab, pomocnicza, poczatek, srodek, koniec);
}

template <typename T>
void merge_sort(T* tab, size_t n) {
    if (n == 0) return;

    T* pomocnicza = new T[n];

    merge_sort_impl(tab, pomocnicza, 0, n - 1);

    delete[] pomocnicza;
}