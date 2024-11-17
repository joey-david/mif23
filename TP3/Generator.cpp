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

int main() {
    Generator a(5);
    for (int i = 0; i < 10; i++) {
        std::cout << a() << std::endl;
    }
    return 0;
}