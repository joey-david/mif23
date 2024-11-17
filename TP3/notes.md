## CM3 - Elements de contrôle pour les classes
### Fonctions spéciales

**friend** permet à une fonction amie d'accéder à tous les membres d'une classe dont elle est amie.
On peut aussi déclarer une classe comme amie (à condition de la déclarer comme telle dans la classe à exporter).

**explicit** permet d'éviter les constructions implicites induites par constructeurs à un seul arg.

### Surcharge de l'opérateur **()**
--> foncteur. 

```cpp
double operator () (double sum) const {
    return sum*10;
}

// leads to

class Convertisseur {
public :
    Convertisseur(double d=1.0) : taux(d) {}
    double operator () (double sum) const {
        return sum*taux;
    }
private :
    double taux;
};

Convertisseur euro2francs(6.56);
std::cout << euro2francs(1000) << std::endl;
std::cout << Convertisseur(2.0)(1000) << std::endl;
std::cout << Convertisseur()(1000) << std::endl
```

les objets fonctions peuvent être transmis en argument d'une autre fonction, sémantique plus précise qu'un pointeur de fonction.

### Redéfinitions de fonctions membres et polymorphismes

**Polymorphisme** pour programmer des classes avec des fonctionnalités générales sans rentrer dans les détails. On programme le détail dans des classes dérivées. Utiliser les fonctionnalités spécialisées d'un objet sans savoir de quelle spécialisation il s'agit.

en java, se fait avec **super**. Par exemple
```java
class Cadre extends Employe
{
    public void affiche() {
        super.affiche(); //affiche de la classe Employe
        system.out.println(‘’ Cadre ’’);
    }
} // Mot clé super pour accéder à la méthode de
//la classe mère
Employe gege = new Cadre;
gege.affiche();
```

les redéfinitions de fonctions membres n'en sont que si elles partagent le même prototype. On ne peut modifier que le type de retour (covariance limitée). Si les fonctions partagent juste le même nom, il ne s'agit plus d'une redéfinition.

Lors d’un appel, c’est le type statique de l’instance appelante qui détermine la version utilisée (résolution statique à la compilation).

#### Type statique / Type dynamique
 Si on considère un pointeur ou une référence sur un objet de type A,
– le type statique de l’objet pointé ou référencé est A (type connu à la compilation)
– mais l'objet pointé ou référencé est-il réellement du type A ou d'un type dérivé ? On ne peut savoir qu'à l'exécution.

Par défaut, la résolution de l'appel à une fonction membre accédée à travers un pointeur ou une référence se fait à la compilation, d'après le type statique. Cependant, on peut utiliser **virtual** pour la faire basculer sur le type dynamique, ce qui permet une éventuelle redéfinition de la fonction membre.

Une classe avec une fonction membre virtuelle est dite **polymorphe**. Une fonction membre virtuelle est appellée **méthode**.

#### Masquage

La définition d'une classe dérivée D de B correspond à l'introduction d'une nouvelle portée qui prévaut localement sur celle de B.

```cpp
class B {
public:
    int f(int);
};

class D : public B {
public:
    int f(int, int); // Overloading in D
};

D d;
d.f(3); // ???
```

when the compiler calls f, it finds only f(int, int) since its block has hidden B's, which means that it runs into an error. **Identifiers** are function names, and the scope hiding is done based on identifiers, not on types. To solve such an issue, use **using**. For instance, here, you would've needed to use the following in D.
```cpp
using B::f;
```

Le choix de la **signature** de la fonction, c'est à dire la fonction de la forme
```cpp
returnType functionName(parameterType1 param1, parameterType2 param2)
```
est fait à la compilation, sur la base du type statique du pointeur ou de la référence **même quand il s'agit d'une fonction virtuelle.**

Pour s'assurer qu'on a bien fait une redéfinition, et pas simplement une surcharge venant masquer l'existant : **override**. Le compilateur rale si ce n'est pas une vraie définition.

Le masquage (hiding) en Java se fait sur la base du nom mais aussi des paramètres d’une méthode (**@Override).

Les polymorphismes entrainent la création de table de fonctions pour les classes polymorphiques, ce qui impose l'existence d'un pointeur pointant vers ces tables. On définit unne fonction comme virtuelle si redéfinition à prévoir il y a dans les classes dérivées. Pour empêcher la dérivation d'une classe, utilisation de **final** depuis C++11. Existait déjà en Java.

