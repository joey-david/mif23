#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <string>
#include <cstring>

template <typename T>
void mySwap(T& a, T& b) {
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}

template <typename T>
T myMin(const T& a, const T& b) {
    return (a < b) ? a : b;
}

//spécialisation pour les tableaux statiques de même taille
template <size_t size>
const char* myMin(const char(&a)[size], const char(&b)[size]) {
    return std::strcmp(a, b) < 0 ? a : b;
}

//spécialisation pour les tableaux statiques de tailles différentes
template <size_t I, size_t J>
const char* myMin(const char(&a)[I], const char(&b)[J]) {
    return std::strcmp(a, b) < 0 ? a : b;
}

#endif