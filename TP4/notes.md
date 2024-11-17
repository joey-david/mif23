## CM4 - Généricité dynamique, RTTI, Sémantique des casts en C++
### Constructeurs et classes polymorphes

Les constructeurs ne peuvent pas être virtuels (initialisation des vtables, ordre d'initialisation si runtime, but des controleurs). On initialise donc le pointeur vers la table des fonctions virtuelles seulement après la création et l'initialisation de cet objet.

Le destructeur d'une classe polymorphe amenée à être dérivée doit être virtuel.
On peut créer un objet par copie de type imprécis à la compilation. Pour celà, on utilise la fonction **clone**.

#### Fonctions membres **static** de classes polymorphes

pas de liaison dynamique pour les fonctions membres ```static```. En Java, pas de liaison dynamique (late binding) sur les méthodes de classe.

#### Fonction virtuelle pure
Une fonction virtuelle déclarée mais non définie au niveau général d'une hiérarchie est dite **abstraite**. On utilise le mot clef **abstract** en Java devant les classes abstraites. Elle demeure virtuelle au fil des dérivations, aussi longtemps qu'elle ne fait pas l'objet d'une def.
=> obligation définir une implantation dans la classe dérivée, sinon elle devient à son tour abstraite.

Dans la déclaration d'une fonction purement virtuelle, on utilise = 0 après sa signature pour le signaler. 

### Intérêt de l'abstraction et patrons de méthodes

Intérêt des classes abstraites C++
– Définition d’une interface commune à travers laquelle accéder aux fonctionnalités des sous-classes : classe d’interface
– Mais aussi possibilité de factoriser des algos incomplets mais communs aux classes dérivées :
Design pattern du ```modèle de conception```.

```cpp
class Magnitude {
public :
virtual bool operator <(const Magnitude & mag) const =0;
virtual bool operator ==(const Magnitude & mag) const=0;

bool operator >=(const Magnitude & mag) const {
    return !(*this < mag);
    }
};

//puis

class Entier : public Magnitude {
private :
    int val;
public :
    virtual bool operator <(const Magnitude & mag) const
    { return val < (( const Entier &) mag).val; }
    virtual bool operator ==(const Magnitude & mag) const
    { return val == (( const Entier &) mag).val; }
    //Pas de redéfinition de operator >=
};
```

### Identification dynamique du type (RTTI)

Encombrement mémoire supplémentaire des classes polymorphes : solution => possible de connaître le type dynamique d'un objet pointé à l'éxécution.
Il existe deux opérateurs pour gérer les types dynamiques : ```typeid``` et ```dynamic_cast<>```.

#### ```typeid```

nécessite ```#include <typeinfo>```, et renvoie une value de type ```const type_info &```.

```cpp
class type_info
{
public :
    const char * name() const;
    int operator == (const type_info &) const;
    int operator != (const type_info &) const;
    int before (const type_info &) const;
};

Cadre c; Employe *ademp = &c;
std::cout << typeid(c).name()
<< typeid(*ademp).name();
```

Pour obtenir des informations sur le type de l'objet pointé, déréférencer les pointeurs, sinon on retourne le type statique du pointeur.

#### ```dynamic_cast<>```

Conversion de pointeurs au sein d'une hiérarchie de classes polymorphes.
```cpp
Employe * ademp = …;
Cadre* adcad=dynamic_cast<Cadre*>(ademp);
```
- rend l’adresse de l’objet Cadre effectivement pointé par ademp si c’est possible
- 0 sinon

Peut aussi s'appliquer aux références.

Bilan sur les 2 opérateurs cast : 
- ```static_cast``` pour une conversion plausible de valeurs, avec analyse statique à la compilation.
- ```dynamic_cast``` pour downcast avec vérification statique puis dynamique à l'exécution.

