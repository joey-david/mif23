#include <iostream>

class Generator {
private:
    int iteration;
    int seed;
public:
    Generator(int seed) : iteration(1), seed(seed) {}
    int operator () () {
        return seed * iteration++;
    }
};