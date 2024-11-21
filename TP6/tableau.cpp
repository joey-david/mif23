#include <iostream>
#include <iterator>
#include "tableau.hpp"

int main()
{
    Tableau<int, 6> A(5);
    std::cout << A;
    std::cin >> A;
    TabIterator<int,6> it=A.begin();
    std::cout << *it << std::endl;
    TabIterator<int,6> ite=A.end();
    std::cout << *ite << std::endl;
    for(;it!=ite;++it)
        std::cout << *it << std::endl;
    return 0;
}