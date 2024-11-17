#ifndef IMAGE_H
#define IMAGE_H

#include "pixel.h"

class Image {
private:
    unsigned int width, height;
    Pixel ** tab;
public:
    Image();
    Image(const unsigned int& w, const unsigned int& h);
    ~Image();
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    Pixel getPixel(const int& x, const int& y) const;
    void setWidth(const unsigned int& w);
    void setHeight(const unsigned int& h);
    void setPixel(const int& x, const int& y, const Pixel& p);
};

#endif