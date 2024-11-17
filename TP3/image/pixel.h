#ifndef PIXEL_INCLUDED
#define PIXEL_INCLUDED

class Pixel
{
protected :
    //unsigned chars are always contained in [0,255]
    unsigned char _r,_g,_b;
public :
    virtual ~Pixel() = default;
    unsigned char r() const {return _r;}
    unsigned char g() const {return _g;}
    unsigned char b() const {return _b;}
    virtual void setR(unsigned char value) = 0;
    virtual void setG(unsigned char value) = 0;
    virtual void setB(unsigned char value) = 0;
};

class ColoredPixel : public Pixel {
public:
    void setR(unsigned char value) override{
        _r = value;
    }
    void setG(unsigned char value) override{
        _g = value;
    }
    void setB(unsigned char value) override{
        _b = value;
    }
};

class GrayscalePixel : public Pixel {
    public:
    void setR(unsigned char value) override{
        _r = value;
        _g = value;
        _b = value;
    }
    void setG(unsigned char value) override{
        _r = value;
        _g = value;
        _b = value;
    }
    void setB(unsigned char value) override{
        _r = value;
        _g = value;
        _b = value;
    }
    void setValue(unsigned char value){
        _r = value;
        _g = value;
        _b = value;
    }
    unsigned char getValue() const {return _r;}
};

#endif // PIXEL_INCLUDED