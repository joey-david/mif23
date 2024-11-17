## CM2 - Anatomie d'une classe

### Dérivation et constructeurs

Si une classe D hérite de plusieurs classes B1, ..., Bn.
```cpp
class D : public B1, private B2, protected B3, public B4 {
    //constructors etc
}
```
Lors de la construction, on initialise d'abord les bases directes (B1, B2, B3) --> puis les membres spécifiques à la classe dérivée --> puis on exécute les instructions du corps du constructeur.

La def du constructeur doit préciser chacun des arguments utilisés pour les constructeurs des classes de base.

Absence de constructeur : génération par C++ d'un constructeur par défaut ou par copie.
**upcast**: conversion d'une classe dérivée en sa dérivante. On peut passer un objet dérivé en param de constr d'une classe dérivante, et c++ réalise la conversion.

absence d'opération d'affectation de la classe dérivée => génération par C++ d'une surcharge de = qui utilise les règles d'affectations propres aux membres et parties héritées et spécifiques. Possibilité d'upcast géré intelligemment par C++.

The constructor by default takes no argument, and can be compiler generated but needs to be written explicitly if another constructor than it is defined. The compiler can generate a constructor by copy if need be.

Destructeur => si pas de destructeur clairement défini, génération par C++. Destruction dans l'ordre inverse de création, en appelant les destructeurs des données membres puis des classes de base. On peut forcer ou forcer la suppression de l'implémentation dans le compilateur via =default et =delete.

C++11 apporte des constructeurs plus souples. On peut utiliser un constructeur dans la définition d'un autre :
```cpp
LaClasse() : LaClasse(55, 2) {};
//ou
struct AutreClasse: public LaClasse {
    using LaClasse::LaClasse;
    //...
}
```
capsules RAII : Ressource Acquisition is Initialization => gestion de données supplémentaires via des données-membres. Nécessité de copies profondes.
Rule of 3 : triplet constructeur par copie / affectation /destructeur => Lorsqu’on ne prend pas ceux générés par le langage, il faut redéfinir les 3.
Depuis C++11, Rule of 3 => Rule of 5. constructeur par copie, constructeur par déplacement, opérateur d'affectation par copie, opérateur d'affectation par déplacement, destructeur.

Depuis C++11, possibilité d'utiliser && => référence temporaire à une xvalue. On peut donc utiliser la construction par déplacement. Constructeur par déplacement choisi à la place du constructeur de recopie en cas de copie d'un objet temporaire (sur le point d'être supprimé). Introduction du semantic move(), qui retourne une référence sur une xvalue. Pas de copie profonde.


## TP2

#### 1. Retour sur TP1

Copy Constructor:

A copy constructor is called when a new object is created from an existing object, as in the case of LaClasse cc2 = c1;.
This involves initializing cc2 with the values from c1.
Assignment Operator:
The assignment operator is used when an already existing object is assigned the values of another existing object, as in cc2 = c1; (assuming cc2 was already declared).

#### 2. Capsules RAII, construction et affectation par déplacement.

#### 3. Constructuers, destructeurs et affectations des classes dérivées.

omission des constructeurs : 

Les créations plus alambiquées ne peuventg pas se faire (no instance of constructor "LaClasseSpecialisee::LaClasseSpecialisee" matches the argument listC/C++(289))
Mais pour les versions plus simples, le constructeur automatique créé par c++ fait l'affaire.

omission du constructeur par copie :

problème pour les copies... wow...

omission des listes d'initialisation : valeurs par défaut, int = 0, char = misc.

#### 4. Un module String fait main