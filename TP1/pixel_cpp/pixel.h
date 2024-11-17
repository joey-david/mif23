#ifndef PIXEL_H
#define PIXEL_H

#include <string>

class Pixel {
private:
    int r, g, b;
public:
    Pixel();
    int getR() const;
    int getG() const;
    int getB() const;
    void setR(const int& newR);
    void setG(const int& newG);
    void setB(const int& newB);
};

#endif