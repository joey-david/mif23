#include "image.h"
#include <iostream>

Image::Image() : Image(0, 0) {}
Image::Image(const unsigned int& w, const unsigned int& h) : width(w), height(h) {
    tab = new Pixel*[width];
    for (unsigned int i = 0; i < width; i++) {
        tab[i] = new Pixel[height];
    }

}
Image::~Image() {
    if (tab != nullptr) {
        for (unsigned int i = 0; i < width; i++) {
            delete tab[i];
        }
    delete [] tab;
    }
    else std::cout << "bip" << std::endl;
}

unsigned int Image::getWidth() const {
    return width;
}

unsigned int Image::getHeight() const {
    return height;
}

Pixel Image::getPixel(const int& x, const int& y) const {
    return tab[x][y];
}

void Image::setWidth(const unsigned int& w) {
    width = w;
}

void Image::setHeight(const unsigned int& h) {
    height = h;
}

void Image::setPixel(const int& x, const int& y, const Pixel& p) {
    tab[x][y] = p;
}