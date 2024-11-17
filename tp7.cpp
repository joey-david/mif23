#include <iostream>
#include <deque>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include "int_gen.h"

int main () {
    std::deque<int> d(5);
    IntegerGenerator gen(4);

    //fill with multiples of 4
    std::generate(d.begin(), d.end(), gen);

    //build an iterator
    std::cout << "Contenu de d: ";
    std::copy(d.begin(), d.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    //build a set from deque
    std::set<int> s(d.begin(), d.end());

    //empty the deque
    d.clear();

    //create s2
    std::set<int> s2;
    for (int i = 1; i<=10; i++) {
        s2.insert(i*2);
    }
    std::cout<<"Contenu de s2: " << std::endl;
    std::copy(s2.begin(), s2.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "Contenu de d: " << std::endl;
    std::copy(d.begin(), d.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}