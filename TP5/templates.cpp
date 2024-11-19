#include "templates.h"
#include <iostream>

int main(){
    std::cout << myMin(5,6) <<std::endl;
    std::cout << myMin(6,5) <<std::endl;
    std::cout << myMin("lili","lala") <<std::endl;
    std::cout << myMin("li","lala") <<std::endl; // 2 arguments de types différents
    const char * cc="mumu";
    const char * dd="ma";
    std::cout << myMin(cc,dd) <<std::endl;
    char ee[5]="toto";
    char ff[5]="ta"; //tableau de même taille que le précédent
    std::cout << myMin(ee,ff) <<std::endl;
    std::cout << myMin("zut",ff) <<std::endl;
    return 0;
}