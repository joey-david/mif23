#include <iostream>

class Employe {
public:
    virtual void affiche() {  // Virtual function
        std::cout << num << std::endl;
    }

private:
    int num;
};

class Cadre : public Employe {
public:
    virtual void affiche() override {  // Override the virtual function
        Employe::affiche();  // Call base class's affiche
        std::cout << echelon << std::endl;
    }

private:
    int echelon;
};

int main() {
    Employe e;          // Base class object
    Cadre d;            // Derived class object
    Employe &re = d;    // Reference to base class, bound to derived object
    Employe *pe = &e;   // Pointer to base class

    e.affiche();        // Call on base class object
    d.affiche();        // Call on derived class object
    re.affiche();       // Call through reference to base
    pe->affiche();      // Call through pointer to base

    e = d;              // Slicing: copy derived object into base object
    e.affiche();        // Call on base object after slicing

    pe = &d;            // Pointer now points to derived object
    pe->affiche();      // Call through pointer to base, pointing to derived

    return 0;
}
