#ifndef IMAGE_INCLUDED
#define IMAGE_INCLUDED

#include <iostream>
#include "pixel.h"

class Image
{
private :
    Pixel * im;
    unsigned int width, height;
public :
    Image() : im(nullptr), width(0), height(0) {}
    Image(int w, int h) : width(w), height(h)
    {
        try{
            if (dynamic_cast<GrayscalePixel*>(im))
                im= new GrayscalePixel(*dynamic_cast<GrayscalePixel*>(im));
            else
                im= new ColoredPixel(*dynamic_cast<ColoredPixel*>(im));}
        catch(std::bad_alloc& ba){std::cout << "bad_alloc caught: " << ba.what() << '\n';}
    }

    Image(const Image& oldIm) : width(oldIm.width), height(oldIm.height) {
        try{
            if (dynamic_cast<GrayscalePixel*>(im))
                im= new GrayscalePixel(*dynamic_cast<GrayscalePixel*>(im));
            else
                im= new ColoredPixel(*dynamic_cast<ColoredPixel*>(im));}
            std::copy(oldIm.im, oldIm.im + width * height, im);
        } catch(std::bad_alloc& ba) {
            im = nullptr;
            width = height = 0;
            throw;
        }
    }

    Image(Image&& oldIm) : im(oldIm.im), width(oldIm.width), height(oldIm.height) {
        oldIm.im = nullptr;
        oldIm.width = oldIm.height = 0;
    }

    Image& operator = (Image&& other) {
        if (&other != this) {
            delete[] im;
            width = other.width;
            height = other.height;
            im = other.im;
            other.im = nullptr;
            other.width = other.height = 0;
        }
        return *this;
    }

    const Pixel & get(unsigned int row, unsigned int col) const {return im[row*width+col];}
    Pixel & get(unsigned int row, unsigned int col){return im[row*width+col];}
    ~Image() {delete im;}
};

class Image2
{
private :
    Pixel ** im;
    unsigned int width, height;
public :
    Image2() : im(nullptr), width(0), height(0) {}
    Image2(unsigned int w,unsigned int h) : width(w), height(h)
    {
        try {im=new Pixel*[w*h];
            for(unsigned int i=0; i<w*h ; i++) {
                if (dynamic_cast<GrayscalePixel*>(im[i]))
                    im[i]= new GrayscalePixel(*dynamic_cast<GrayscalePixel*>(im[i]));
                else
                    im[i]= new ColoredPixel(*dynamic_cast<ColoredPixel*>(im[i]));
            }
        }
        catch(std::bad_alloc& ba){std::cout << "bad_alloc caught: " << ba.what() << '\n';}
    }

    Image2(const Image2& oldIm) : width(oldIm.width), height(oldIm.height) {
        try {
            im = new Pixel*[width*height];
            for (unsigned int i = 0; i < width * height; i++)
                if (dynamic_cast<GrayscalePixel*>(im[i]))
                    im[i]= new GrayscalePixel(*dynamic_cast<GrayscalePixel*>(im[i]));
                else
                    im[i]= new ColoredPixel(*dynamic_cast<ColoredPixel*>(im[i]));
        } catch(std::bad_alloc &ba) {
            im = nullptr;
            width = height = 0;
            throw;
        }
    }

    Image2(Image2&& oldIm) : im(oldIm.im), width(oldIm.width), height(oldIm.height) {
        oldIm.im = nullptr;
        oldIm.width = oldIm.height = 0;
    }

    Image2& operator = (Image2&& other) {
        if (this != &other) {
            if (im) {
                for (unsigned int i = 0; i < width * height; i++)
                    delete im[i];
                delete im;
            }
            im = other.im;
            width = other.width;
            height = other.height;
            other.im = nullptr;
            other.height = other.width = 0;
        }
        return *this;
    }

    const Pixel & get(unsigned int row, unsigned int col) const {return *im[row*width+col];}
    Pixel & get(unsigned int row, unsigned int col){return *im[row*width+col];}
    ~Image2()
    {
        if(im!=nullptr)
        {
            for(unsigned int i=0; i<width*height ; i++) delete im[i];
            delete [] im;
        }
        else{std::cout << "Bip" << std::endl;}
    }
};

#endif // IMAGE_INCLUDED