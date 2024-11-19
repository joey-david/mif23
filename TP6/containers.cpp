#include <iostream>
#include <deque>
#include <set>
#include "../TP3/Generator.cpp"

int main() {
    std::deque<int> d(5);
    Generator g(4);
    (d.begin(), d.end(), g);
    return 0;
}