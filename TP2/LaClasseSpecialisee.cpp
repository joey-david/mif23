#include <iostream>
#include "../TP1/LaClasse.cpp"

class LaClasseSpecialisee : public LaClasse {
public:
    LaClasseSpecialisee() : LaClasse(), m('a') {
        std::cout<< "LaClasseSpecialisee::LaClasseSpecialise avec l= "
            << l << " et m= " << m << std::endl;
    }
    LaClasseSpecialisee(const LaClasseSpecialisee & lcs) : LaClasse(lcs), m(lcs.m) {
        std::cout<< "LaClasseSpecialisee::LaClasseSpecialisee(const LaClasseSpecialisee &) avec l= "
            << l << " et m= " << m << std::endl;
    }
    LaClasseSpecialisee(const LaClasseSpecialisee && lcs) : LaClasse(lcs), m(lcs.m) {
        std::cout<< "LaClasseSpecialisee::LaClasseSpecialisee(const LaClasseSpecialisee &&) avec l= "
            << l << " et m= " << m << std::endl;
    }
    LaClasseSpecialisee(int i, char c) : LaClasse(i), m(c) {
        std::cout<< "LaClasseSpecialisee::LaClasseSpecialisee(int, char) avec l= "
            << l << " et m= " << m << std::endl;
    }
    LaClasseSpecialisee(int i) : LaClasse(i) {
        std::cout<< "LaClasseSpecialisee::LaClasseSpecialisee(int, char) avec l= "
            << l << " et m= " << m << std::endl;
    }
    operator bool() const {
        std::cout<< "LaClasseSpecialisee::operator bool() const avec l= "
            << l << " et m= " << m << std::endl;
        return true;
    }
    LaClasseSpecialisee & operator=(const LaClasseSpecialisee & c) {
        l = c.l;
        m = c.m;
        std::cout<< "LaClasseSpecialisee::operator=(const LaClasseSpecialisee &) avec l= "
            << l << " et m= " << m << std::endl;
        return *this;
    }
    LaClasseSpecialisee Fspe(LaClasseSpecialisee);
    // Déclaration fonction extérieure amie
    friend std::ostream & operator << (std::ostream & os, const LaClasseSpecialisee & lcs);
private:
    char m;
};

LaClasseSpecialisee Fspe(LaClasseSpecialisee vv)
{
    std::cout << " in Fspe \n";
    return vv;
}

LaClasseSpecialisee LaClasseSpecialisee::Fspe(LaClasseSpecialisee v) {
    std::cout << " in LaClasseSpecialisee::Fspe avec v.l=" << v.l++ << " et v.m=" << v.m++ << "\n";
    return ::Fspe(v);  // Call the global Fspe function instead
}

std::ostream & operator << (std::ostream & os, const LaClasseSpecialisee & lcs)
{
    os << " in ostream << LaClasseSpecialisee "<< lcs.l << " et " << lcs.m << std::endl;
    return os;
}

int main () {
    LaClasseSpecialisee c1;
    std::cout<< std::endl;
    LaClasseSpecialisee c2=LaClasseSpecialisee();
    std::cout<< std::endl;
    LaClasseSpecialisee cc1(c1);
    std::cout<< std::endl;
    LaClasseSpecialisee cc2=c1;
    std::cout<< std::endl;
    LaClasseSpecialisee cc3=LaClasseSpecialisee(c1);
    std::cout<< std::endl;
    LaClasseSpecialisee cv1(5, 'b');
    std::cout<< std::endl;
    LaClasseSpecialisee cv2=5;
    std::cout<< std::endl;
    LaClasseSpecialisee cv3=LaClasseSpecialisee(5, 'c');
    std::cout<< std::endl;
    LaClasseSpecialisee cv4=LaClasseSpecialisee(5, 'd');
    std::cout<< std::endl;
    c1=cc1;
    std::cout<< std::endl;
    c2=8;
    std::cout<< std::endl;
    c1=LaClasseSpecialisee(5, 'e');
    std::cout<< std::endl;
    c1=LaClasseSpecialisee(5, 'f');
    std::cout<< std::endl;
    if(cv1)
    {
        std::cout<< "cv1 est vrai\n";
    }
    std::cout<< std::endl;
    c1.Fspe(cv1);
    std::cout<< std::endl;
    c1.Fspe(5);
    std::cout<< std::endl;
    return 0;
}