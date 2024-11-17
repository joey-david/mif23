#include <iostream>
class LaClasse {
public :
    // fonctions membres publiques
    // Constructeurs
    LaClasse() {
        i=1;
        std::cout << "LaClasse::LaClasse() " << i << " (constructeur par défaut) "
        << std::endl;
    }
    // Destructeur
    ~LaClasse() {}
private :
    // donnees membres
    unsigned int i;
};

int main(int argc, const char * argv[]) {
    LaClasse * lolo; // Variable de type pointeur cree sur la pile
    // (32 ou 64 bits suivant l’architecture)
    lolo=new LaClasse(); //Allocation d’un LaClasse dans le tas,
    //initialise par defaut,
    // et dont l’adresse est retournee dans lolo
    {
        LaClasse lili; //Instance creee sur la pile
        //et initialisee par appel automatique au constructeur par defaut
    } //Appel automatique au destructeur de lili
    delete lolo; // Appel au destructeur de l’instance pointee par lolo
    // et restitution de l’espace alloue
    return 0;
}