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