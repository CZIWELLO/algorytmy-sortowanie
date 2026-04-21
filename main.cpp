#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "helpers.h"
#include "introspektywne.h"
#include "quicksort.h"
#include "scalanie.h"

// Funkcja zamieniająca kropkę na przecinek dla CSV
std::string formatujDoCSV(double wartosc, int precyzja = 2) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precyzja) << wartosc;
    std::string str = oss.str();
    size_t pos = str.find('.');
    if (pos != std::string::npos) {
        str[pos] = ',';
    }
    return str;
}

int main() {
    unsigned int wielkosci[] = {10000, 50000, 100000, 500000, 1000000};
    float poziom_posortowania[] = {-1, 0.0, 0.25, 0.5, 0.75, 0.95, 0.99, 0.997};
    int liczba_powtorzen = 100;
    
    // Mapy do przechowywania wyników: [wielkość] -> wektor czasów dla każdego poziomu
    std::map<unsigned int, std::vector<double>> wyniki_qs, wyniki_hs, wyniki_ms;

    for(auto wielkosc : wielkosci){
        // Alokacja na stercie zamiast stosu
        int* tablica = new int[wielkosc];
        generujLiczby(wielkosc, tablica);
        
        for(auto poziom : poziom_posortowania){
            double suma_qs = 0, suma_hs = 0, suma_ms = 0;
            
            for(int run = 0; run < liczba_powtorzen; run++) {
                // Przygotowanie tablicy startowej
                int* tablica_start = new int[wielkosc];
                std::copy(tablica, tablica + wielkosc, tablica_start);

                // Przygotowanie danych testowych
                if (poziom < 0) {
                    // Tablica posortowana w odwrotnej kolejności
                    quick_sort(tablica_start, 0, wielkosc - 1);
                    std::reverse(tablica_start, tablica_start + wielkosc);
                } else {
                    // Sortowanie częściowo posortowanej części
                    size_t posortowane_elementy = static_cast<size_t>(wielkosc * poziom);
                    if (posortowane_elementy > 0) {
                        quick_sort(tablica_start, 0, posortowane_elementy - 1);
                    }
                }

                // Test QuickSort
                int* tablica_qs = new int[wielkosc];
                std::copy(tablica_start, tablica_start + wielkosc, tablica_qs);
                suma_qs += zmierzCzas([&]() {
                    quick_sort(tablica_qs, 0, wielkosc - 1);
                });

                // Test HeapSort
                int* tablica_hs = new int[wielkosc];
                std::copy(tablica_start, tablica_start + wielkosc, tablica_hs);
                suma_hs += zmierzCzas([&]() {
                    heap_sort_zakres(tablica_hs, 0, wielkosc - 1);
                });

                // Test MergeSort
                int* tablica_ms = new int[wielkosc];
                std::copy(tablica_start, tablica_start + wielkosc, tablica_ms);
                suma_ms += zmierzCzas([&]() {
                    merge_sort(tablica_ms, wielkosc);
                });

                // Czyszczenie pamięci
                delete[] tablica_start;
                delete[] tablica_qs;
                delete[] tablica_hs;
                delete[] tablica_ms;
            }
            
            // Zapis średniej
            wyniki_qs[wielkosc].push_back(suma_qs / liczba_powtorzen);
            wyniki_hs[wielkosc].push_back(suma_hs / liczba_powtorzen);
            wyniki_ms[wielkosc].push_back(suma_ms / liczba_powtorzen);

            std::cout << "✓ Wielkość: " << wielkosc << ", Poziom: ";
            if (poziom < 0) {
                std::cout << "Odwrotnie";
            } else {
                std::cout << std::fixed << std::setprecision(1) << poziom * 100 << "%";
            }
            std::cout << std::endl;
        }
        
        delete[] tablica;
    }
    
    // Zapis wyników do 3 plików CSV
    // QuickSort
    std::ofstream plik_qs("quicksort.csv");
    plik_qs << "Wielkość";
    for(auto poz : poziom_posortowania) {
        plik_qs << ";";
        if (poz < 0) {
            plik_qs << "Odwrotnie";
        } else {
            plik_qs << formatujDoCSV(poz * 100) << "%";
        }
    }
    plik_qs << std::endl;
    for(auto wielkosc : wielkosci) {
        plik_qs << wielkosc;
        for(auto czas : wyniki_qs[wielkosc]) {
            plik_qs << ";" << formatujDoCSV(czas);
        }
        plik_qs << std::endl;
    }
    plik_qs.close();
    
    // HeapSort
    std::ofstream plik_hs("heapsort.csv");
    plik_hs << "Wielkość";
    for(auto poz : poziom_posortowania) {
        plik_hs << ";";
        if (poz < 0) {
            plik_hs << "Odwrotnie";
        } else {
            plik_hs << formatujDoCSV(poz * 100) << "%";
        }
    }
    plik_hs << std::endl;
    for(auto wielkosc : wielkosci) {
        plik_hs << wielkosc;
        for(auto czas : wyniki_hs[wielkosc]) {
            plik_hs << ";" << formatujDoCSV(czas);
        }
        plik_hs << std::endl;
    }
    plik_hs.close();
    
    // MergeSort
    std::ofstream plik_ms("mergesort.csv");
    plik_ms << "Wielkość";
    for(auto poz : poziom_posortowania) {
        plik_ms << ";";
        if (poz < 0) {
            plik_ms << "Odwrotnie";
        } else {
            plik_ms << formatujDoCSV(poz * 100) << "%";
        }
    }
    plik_ms << std::endl;
    for(auto wielkosc : wielkosci) {
        plik_ms << wielkosc;
        for(auto czas : wyniki_ms[wielkosc]) {
            plik_ms << ";" << formatujDoCSV(czas);
        }
        plik_ms << std::endl;
    }
    plik_ms.close();
    
    std::cout << "\nWyniki zapisane do: quicksort.csv, heapsort.csv, mergesort.csv" << std::endl;

    return 0;
}