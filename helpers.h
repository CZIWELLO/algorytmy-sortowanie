#pragma once
#include <fstream>
#include <random>
#include <chrono>

void generujLiczby(int n, int tablica[]) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1000000);

    for (int i = 0; i < n; i++) {
        tablica[i] = dist(gen);
    }
}

class Zegar {
    std::chrono::steady_clock::time_point moment_start;

public:
    void start() {
        moment_start = std::chrono::steady_clock::now();
    }

    std::chrono::nanoseconds::rep stop() {
        auto moment_stop = std::chrono::steady_clock::now();
        auto czas = std::chrono::duration_cast<std::chrono::nanoseconds>(moment_stop - moment_start);
        return czas.count();
    }
};

template <typename Funkcja>
double zmierzCzas(Funkcja operacja) {
    Zegar zegar;
    zegar.start();
    operacja();
    return static_cast<double>(zegar.stop());
}

void zamien(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

template <typename T>
void zamien(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
bool sprawdzCzyPosortowana(T *tab, size_t n) {
    if (n <= 1) return true;
    
    for (size_t i = 0; i < n - 1; i++) {
        if (tab[i] > tab[i + 1]) {
            return false;
        }
    }
    return true;
}