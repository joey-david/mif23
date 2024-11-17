## CM 1 - Introduction, références et pointeurs, héritage

But de l'UE : introduire générécité et méta-programmation.
Langages à maitriser, en général : Python, Java, Javascript, C++

C++ proche de la prog système => utilisation massive de la pile, pointeurs, résolution statique maximale, personnalisation possible de l'allocation dynamique, pas de garbage collection.

#### Java vs C++
(Java) variable : allouée dynamiquement sur le tas, désalloué par le garbage collector.
(C++) variable : allouée sur la pile, libéré à la fin du bloc de définition par appel automatique du destructeur. new doit être utilisé pour utiliser une ref vers le tas.

Pointer	: A variable that stores the memory address of another variable.
Reference : An alias for another variable.

Example in C++

```cpp
int a = 10;
int b = 20;

int *p = &a;  // p is a pointer to a
p = &b;       // p can be reassigned to point to b

int &r = a;   // r is a reference to a
// r = &b;    // Error: a reference cannot be reassigned to a different variable
```

classes : in C++ --> MyClass* ptrMC = new MyClass creates a pointer on the stack which keeps the memory address of the instance of MyClass in the stack.

the pointer (in the stack) will be freed automatically, but you need an explicit call to delete plc to free the instance allocation in the heap.

this est une **réference** (=alias) sur l'instance courante en Java, et un **pointeur** vers l'instance courante en C++.

#### valueness:
lvalue : variaale or space on the heap **with an address**
rvalue : values which can be stored in lvalues (ex 7). Can be returned by functions. **without an address**
xvalue (x for expiring): temporary containers stored on the stack

==> lvalues et xvalues = glvalues (generalized left values)
==> rvalue = prvalue since c++11

types de programmation en c++ :
- programmation structurée procédurale : typage fort, conversions, références, templates
- programmation modulaire : compilation séparée, namespaces, modules correspondant à plusieurs classes formant un tout cohérent.
- types abstraits de données
- programmation orientée objet : hiérarchies, polymorphismes.

**généricité** implémentée par les method templates, comme dans le **design pattern patron de méthode**. (resp non méthode, généricité statique)

héritage en Java :
```Java
class Cadre extends Employe {
    //blabla
}

Employe john = new Cadre;
```

en C++, plus complexe:
```cpp
class Cadre : public Employe {
public:
    void affiche_echelon();
private:
    int echelon;
};
```

les méthodes et membres définies ainsi sont supplémentaires et ne remplacent pas ceux de la classe de base. Cadre est aussi muni des méthodes et membres d'employé. Evidemment, pas d'accès à private.
protected existe...

--> se servir de **using** pour des héritages partiellement publics.

upcast : conversion d'une partie de la classe héritante à la classe héritée. Toute la classe continue d'exister, mais seulement une partie est accessible via la classe parent.

Downcasts impossibles pour des instances, mais possibles pour des pointeurs : utiliser <static_cast> de préférence au cast classique.

## TP1

1. Trace :
51, constructeur par défaut ligne 7
52, affectation à lvalue non initialisée du constructeur par défaut ligne 7
53, constructeur par copie ligne 9
54, constructeur par copie ligne 9
55, constructeur par copie ligne 9
56, constructeur(int)
57, constructeur(int) + temp lvalue
58, constructeur(int) + temp lvalue
59, constructeur(int) + temp lvalue
60, surchage op égal
63, constructeur(int), opérateur égal, destructeur de la classe temporaire.
65, opérateur bool pour check la valeur de cv1
67, constructeur(int) créé temporairement pour être appelé via F, affecté par opérateur = puis détruit, comme F, puis constructeur int détruit aussi.
68, idem mais pas de premier constructeur int. 
69, idem, mais appels récursifs multiples.

Si on modifie
```cpp
LaClasse F(LaClasse vv)
```
en
```cpp
LaClasse F(const LaClasse& vv)
```
on passe à un passage de paramètre en référence, pas en copie, ce qui nécessite une création et une suppression de moins par appel à F.


2. Au fur et à mesure que le nombre de boucles augmente, Java gagne de plus en plus de temps sur l'exécution par rapport à C++. Peut-être que le garbage collection est plus efficace que notre implémentation manuelle sur C++ ? Ou peut-être que les constructeurs par copie sont utilisés à excès dans C++, et sont plus lents que ceux par référence de Java.