#include "tableau.h"
#include <iostream>

int main() {
    Tableau<int> t;
    for (unsigned int i = 0; i < 26; i++) {
        t.add(int('a' + i));
        std::cout << t[i] << std::endl;
    }
    return 0;
}