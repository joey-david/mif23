## CM 7 - Allocation Dynamique Personnalisée, Pointeurs intelligents, Héritage multiple, Exception
### Allocation de mémoire et smart pointers

il faut éviter les appels à `malloc` et `free` à la c, et privilégier `new`, `delete`, `new[]` et `delete[]`. Ménage à la charge du programmeur.

--> Redéfinition de **new** et **delete** pour changer la stratégie d'allocation. Surcharge globale ou locale.
En soit, simple surcharge d'opérateur :
```cpp
void* operator new(size_t size);
void* operator new[](size_t size);
void operator delete(void* ptr);
void operator delete[](void* ptr);
```

On peut aussi paramétrer ces opérateurs durant la surcharge. Pour surcharger pour une classe, on utilise des fonctions membres statiques. On redéfinit donc indépendamment du conteneur pour lequel on alloue des objets.
```cpp
static void* Complexe::operator new(size_t size);
static void Complexe::operator delete(void* ptr);
static void* Complexe::operator new[ ](size_t size);
static void Complexe::operator delete[ ](void* ptr);
```

Pendant la redéfinition, attention à ne pas faire un double appel à new (déjà appelé par défaut à la fin). Remplacer par un appel à malloc.

### allocateurs
Objets gérant l'allocation mémoire des conteneurs standards. Comporte `allocate`, `construct`, `destroy`, `deallocate`. A realiser avec un ordre bien précis !

Pour ne pas imposer l'allocation et désallocation à l'utilisateur du langage, on crée des **smart pointers**.
Implémentation précédente : `auto_ptr`, très moyennement intelligent. Remplacé par `unique_ptr` depuis C++ 11. Il garantit la propriété unique d'un objet, avec transmission explicite de propriété obligatoire. **Utiliser `std::make_unique`**.

On peut aussi mettre en place un comptage de références avec des `smart_pointers`, qui compte le nombre de pointeurs pointant vers chaque objet alloué, et détruit et libère l'objet alloué si le nombre de pointeurs tombe à 0. Il est possible de forcer l'implémentation du compter dans les objets tracés, avec un compteur statique.

Sinon, à l'extérieur des objets, le compteur nécessite une indirection supplémentaire, les pointeurs pointant sur le compteur qui pointe sur l'objet. On peut par exemple définir une `struct`.

Il y a cependant une limite claire aux pointeurs intelligents : si un objet contient un pointeur intelligent, il est très facile de créer des dépendances circulaires, ce qui entraine une fuite de mémoire. Il faudrait que dans le cycle, un des pointeurs intelligents soit non-copropriétaire : `weak_ptr`. Poitne sur un objet géré par un ou plusieurs shared_ptr, modélise la notion d'accès temporaire.

Désormais, plus besoin de recourir directement à delete
– Utilisation de pointeurs intelligents pour prendre la valeur de retour d’un new
– Faire attention à la formation éventuelle de cycles….