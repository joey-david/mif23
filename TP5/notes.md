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