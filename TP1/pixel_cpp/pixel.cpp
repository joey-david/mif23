#include "pixel.h"
#include <iostream>

Pixel::Pixel() : r(0), g(0), b(0) {}

int Pixel::getR() const {
    return r;
}

int Pixel::getG() const {
    return g;
}

int Pixel::getB() const {
    return b;
}

void Pixel::setR(const int& newR) {
    r = newR;
}

void Pixel::setG(const int& newG) {
    g = newG;
}

void Pixel::setB(const int& newB) {
    b = newB;
}