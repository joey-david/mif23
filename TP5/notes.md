## CM 5 - Les limites du polymorphisme en programmation orientée objet

--> le polymorphisme ne s'applique que sur l'argument implicite ```this``` d'une fonction membre, il est donc difficile de créer des opérateurs binaires polymorphes. 
=> Comment faire pour qu'un opérateur s'adapte au type dynamique de ses deux opérandes ?

On peut l'**adapter à l'opérande de gauche** en **surchargant l'opérateur dans la classe dérivée**, ou l'adpater à l'opérande de droite :
- en faisant appel à une fonction membre virtuelle pour chaque spécialisation de l'opérateur. => nécessite de retoucher à la classe de base pour chaque nouvelle dérivation.
- en utilisant ```dynamic_cast<>```.

### Générécité / polymorphisme statique
templates yaaaaaayyyy ^^

Fontions **template** opèrent des opérations similaires sur des types différents. Le corps des fonctions est identique, seul le type diffère. En C++, plutôt que de faire des macros infernales à la C, on peut définir des familles de fonctioins avec **template<>**.

```cpp
template <typename T> //ici, paramétrisation par un nom de type
T myMin(T e1, T e2) {
    return (e1 > e2) ? e2 : e1;
}
```

un patron peut aussi être paramétré par une valeur :
```cpp
template <typename T, unsigned int TAILLE>
```
ici, mettre taille en param du template est clairement discutable.
Définition patron != définition de fonction. La génération des fonctions se fait à la compilation.

Prérequis : faire attention à ce que les classes sur lesquels on crée les templates sont bien munies des outils appropriés.

Depuis C++20, notion de **concept**, pour imposer des contraintes sur les paramètres template. Par exemple :
```cpp
template <typename T>
requires std::totally_ordered<T>
```
Le compilateur refusera d'instancier la fontion avec des classes ne satisfaisant pas requires. Un paquet de concepts dans stdlib.

Attention à la modularité : les templates doivent être dans la même unité de compilation que la def du patron de fonction (puisque statiques).

### Classe Template
On peut appliquer aux classes le même mécanisme de générécité. Une classe est un patron de type : modèle générique utilisable pour générer toute une famille de classes.
=> Les fonctions membres d'une classe template sont des fonctions template. Elles sont définies dans la portée de cette classe template.

Une classe peut être paramétrée par :
- un type
- un type* ou un type &
- des constantes arithmétiques évaluables à la compilation
- des adresses (y compris des pointeurs de fonction)

On peut donner des valeurs par défaut à des paramètres génériques. La spécialisation d'une classe template peut n'être que partielle, si on veut donner des définitions différentes de certaines instantiations. Par exemple :

```cpp
template <typename T1, typename T2>
T1 monTemplate(T1 a, T2 b) {
    return a + b;
}
//puis
template <>
int monTemplate<int, double>(int a, double b) {
    return a - b;
}
```

### Données et fonctions communes à toutes les instances d'une classe

Grâce à ```static```, possibilité de définir des données et fonctions membres existant à un unique exemplaire, indépendante des instances de la classe. Attention : la déclaration d'un membre ```static``` n'entraîne pas sa définition. La définition se fait à l'extérieur de la classe ; excepté pour les constantes de classe de type bool, char et int.

#### Fonction membre statique d'une classe
Invocable à travers une instance ou le nom de la classe. N'a pas d'argument implicite ; ne manipule que les données statiques ou locales de la classe, en gros c'est imperméable.

#### Templates et données membres statiques
une classe template définit les mêmes choses qu'une classe ordinaire. On peut utiliser ```using``` à la place de typedef.
On peut également avoir des fonctions membres **virtuelles** dans des classes templates. Cependant, attention : on ne peut pas avoir des fonctions membres virtuelles template dans des classes, car au moment de la création d'une classe polymorphe, on a besoin de connaître toutes les fonctions membres virtuelles pour pouvoir créer la table des fonctions membres virtuelles.

