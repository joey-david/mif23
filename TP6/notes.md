## CM6 - Standard Template Library

Tout simplement un ensemble de bibliothèques ISO regroupées sous le **namespace std**. C, iostream, C++...
template => un ensemble de patrons génériques de classes et de fonctions :
- conteneurs
- itérateurs
- algorithmes

### Conteneurs

Modèles génériques représentant les structures de données les plus répandues.

--> pour stocker des **séquences** : `vector`, `deque`, `list`.

--> pour stocker des collections de clefs : `set`, `multiset`, et avec des clefs associées : `map`, `multimap`.

Plein de fonctions spécifiques, etc, mais chacun a accès à `size_t size` et `bool empty`.

#### vector
- accès direct aux élements (O(1))
- insertion / suppression à la fin en O(1) (O(n) sinon)
- nombre dynamique d'elts avec gestion auto d'extension de mem.

Exemple:
```cpp
std::vector<int> v;
v.push_back(5); // 5
v.push_back(1); // 5 1
v.insert(v.begin() + 1, 9); // 5 9 1
v.pop_back(); // 5 9
v.insert(v.begin(), 2, 7); // 7 7 5 9
std::cout << v[1] << " " << v.at(2) << std::endl;
v[0] = v.at(1) = v.back() = 1; // 1 1 5 1
v.erase(v.begin() + 2); // 1 1 1
v.insert(v.end(), 3); // 1 1 1 3
std::cout << v.size() << std::endl;
v.resize(6, 0); // 1 1 1 3 0 0
v.resize(2); // 1 1
```

#### list (liste doublement chainée)
- insertion/suppression en O(1) à une position donnée `insert`, `erase`, `push_front(elt)`, `pop_front()`, `push_back(elt)`, `pop_back()`.
- pas d'accès direct à tous les éléments, fonctions membres `front` et `back`.
- possibilité de parcours séquentiel dans les deux sens.
- gestion auto
- fonctions spécifiques : `remove(elt)`, `unique`, `splice`, `sort` (is that really specific?), `merge`...

Exemple:
```cpp
std::list<double> l(4, 1.5); // 1.5 1.5 1.5 1.5
l.push_front(5.9); // 5.9 1.5 1.5 1.5 1.5
l.pop_back(); // 5.9 1.5 1.5 1.5
l.insert(l.begin(), 7.7); // 7.7 5.9 1.5 1.5 1.5
l.reverse(); // 1.5 1.5 1.5 5.9 7.7
l.sort(); // 1.5 1.5 1.5 5.9 7.7
l.remove(1.5); // 5.9 7.7
l.push_back(7.7); // 5.9 7.7 7.7
l.unique(); // 5.9 7.7
l.erase(l.begin()); // 7.7
```

#### deque (file à double entrée)
- accès direct aux élements en temps constant avec `[]`, `at()`, `back()`, `front()`.
- insertion/suppression à la fin en temps constant avec `push_back(elt)`, `pop_back()`, `push_front(elt)`, `pop_front()`.
- insertion/suppression en temps linéaire sinon.
- gestion auto taille etc.

#### array (tableau de taille fixe fournie en template)
principales opérations : `[]`, `at()`, `back()`, `front()`.

### Adaptateurs de séquences

Fournis en association avec les séquences. Définition d'une nouvelle interface pour un conteneur, afin de lui donner le comportement d'un type abstrait. `stack`, `queue` ou `priority_queue`.

Exemples de déclarations :
```cpp
#include <stack>
std::stack<int, std::vector<int>> pi;
#include <queue>
std::queue<int, std::deque<int>> fi;
std::priority_queue<int, std::deque<int>> fip;
std::priority_queue<int, std::deque<int>, std::greater<int>> fip2;
```

#### stack
```cpp
template <class T, class Container = deque<T>>
class stack;
```

le conteneur utilisé à l'instanciation doit supporter `back`, `push_back` et `pop_back`.

Principales opérations sur les `std::stack` : `push(elt)`, `pop()`, `top()`, `empty()`, `size()`.

#### queue
```cpp
template <class T, class Container=deque<T>>
class queue;
```

le conteneur utilisé à l'instanciation doit supporter `back`, `front`, `push_back`, `pop_front`.

#### priority_queue
```cpp
template <class T, class Container=vector<T>, class Compare=std::less<typename Container::value_type>
class priority_queue;
```

type abstrait de queue de priorité offrant l'extraction de l'élément de plus grande priorité (au sens de la classe `Compare`, qui teste l'infériorité).
Le conteneur utilisé à l'instanciation doit supporter l'indexation ainsi que les opérations `front`, `push_back` et `pop_back`.
Les principales opérations sur les priority_queue sont `push(elt)`, `pop()`, `top()`, `empty()` et `size()`.

Exemple d'utilisation :
```cpp
std::priority_queue < int, std::vector<int> > p1;
std::priority_queue < int, std::deque<int>, std::greater<int> > p2;
p1.push(9); p2.push(9);
p1.push(7); p2.push(7);
p1.push(30); p2.push(30);
while(!p1.empty())
{ std::cout << p1.top() << std::endl;
p1.pop();
} // 30 9 7
while(!p2.empty())
{ std::cout << p2.top() << std::endl;
p2.pop();
} // 7 9 30
```

##### Fabrication d'une classe d'objets "fonctions de comparaison"
Classe disposant d’une surcharge de l’opérateur () correspondant à une fonction de comparaison : fonction de 2 arguments renvoyant 1 booléen.
On découvrira bientôt les **lambda fonctions** :
```cpp
auto compare = [](int i, int j) {return (i>>1) < (j>>1);}
std::priority_queue<int, std::vector<int>, decltype(compare)>p(compare);
```

#### set et multiset
```cpp
template<class Key>, class Compare=less<Key>>
class set;
```
principales opérations : `insert(key)`, `erase(key)`, `find(key)`, `size(key)`, `empty()`.

Les sets et les multisets ne sont pas des séquences, un multiset peut conserver les elts équivalents.

#### map
```cpp
template<class Key, class T, class Compare=less<Key>>
class map;
```

table associative de keys/values. Principale opération va l'opérateur `[]`. Insertion si la clef n'est pas déjà présente. Utiliser `find()` pour chercher la clef.

#### multimap

équivalent, mais peut conserver plusieurs valeurs dont la clef est la même.

### Itérateurs

Un **iterator** désigne toute classe munie des opérateurs membres `*` (et si nécessaire de `->`).
C'est une abstraction de la notion de pointeur, qui est donc un cas particulier d'itérateur.
- un **input iterator** accède en lecture à l'elt pointé, par retour de `operator *()`
- un **output iterator** accède en écriture à l'elt pointé, et fait le retour d'une référence par `operator *()`.
- un **forward iterator** est un input ET un output iterator.

^ tous ceux-ci sont munis de l'opérateur `++`.
- un **bidirectional operator** est aussi muni de `--`.
- un **random access operator** est muni d'une arithmétique similaire, à celle des pointeurs, de l'opérateur `[]`, et supporte des opérations de comparaison.

#### Opérateurs de déréférencement
L'opérateur surchargé (`*` ou `->`) s'applique à un itérateur, et non à un pointeur. Surcharge de l'opérateur unaire `*`.
```cpp
template <typename T> class Iterator {
    T& operator *() {return blabla;} // Retour d’une référence
    //sur l’objet « pointé »
    // par l’itérateur
    T* operator ->() {return blibli;} // Cas où l’objet « pointé »
    // a des membres
};
```

#### surcharge de l'opérateur ++ (préfixé)
Possibilité de donner un sens à ++z : soit en surchargeant ++ en opérateur membre sans argument, soit en fonction amie ayant pour unique argument un Itérateur.

#### surcharge de l'opérateur ++ (postfixé)
Possibilité de donner un sens à ++z : soit en surchargeant ++ en opérateur membre avec un arg entier, soit en fonction amie ayant pour unique argument un Itérateur et un entier.

Chaque conteneur de la stl fournit un type local d'itérateur permettant d'accéder à ses éléments, et d'en faire un parcours exhaustif, une fonction membre `begin()`, et une fonction membre `end()`, deux fonctions membres renvoyant des valeurs d'itérateurs correspondant au type local du conteneur.

#### itérateurs d'insertion
- *output iterator* permettant d'étendre le contenu d'un conteneur, par insertion de nouveaux elts à l'endroit pointé. Par exemple, ici, à la fin :
```cpp
std::list<int> l;
std::back_insert_iterator<std::list<int> >
it=std::back_inserter(l);
for(int i=0;i<10;i++)
*++it= i; //equivaut l.pushback(i);
```

insert-iterator peuvent aussi permettre l'insertion en une position donnée de la séquence. `back_insert_iterator` utilise un travail déclenché par l'opérateur d'affectaion, et le déréférecement et l'incrémentation sont sans effet.
```cpp
*it++ = i
//est équivalent à
it.operator++(0).operator*().operator=(i);
```

#### itérateurs de flux

On peut associer un itérateur à un flux de sortie (**ostream**) de manière à pouvoir écrire dessus. Dans ce cas:
```cpp
std::ostream_iterator<int> os(std::cout,“ puis ”);
//pour écrire des entiers séparés par “ puis”
*os=8;
++os;
*os=9;
++os;
```
travail réalisé par l'opérateur `=`.

Resp **istream**, pour lire des données. Dans ce cas,
```cpp
std::istream_iterator<int> is(std::cin);
//pour lire des entiers sur l’entrée standard
int a,b;
a=*is;
++is;
b=*is;
++is;
```
travail effectué par surcharge de l'opérateur `*`.

### Algorithmes

Applicables à différents conteneurs. Comment ? Accès aux elts des conteneurs uniquement via des itérateurs. On a donc accès à de nombreux algorithmes.

Notables : `copy`, `find`, `for_each`, `sort`, `transform`.