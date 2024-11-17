#include "image.h"
#include <iostream>
#include <chrono>

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Image im = Image(1000, 1000);
    for (int h = 0; h < 500; h++) {
        for (int i = 0; i < im.getWidth(); i++) {
            for (int j = 0; j < im.getHeight(); j++) {
                Pixel temp = im.getPixel(i, j);
                temp.setR(temp.getR() + 1);
                temp.setG(temp.getG() + 1);
                temp.setB(temp.getB() + 1);
                im.setPixel(i, j, temp);
                //std::cout << temp.getR() << "," << temp.getG() << "," << temp.getB() << " ";
            }
            //std::cout << std::endl;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
    return 0;
}