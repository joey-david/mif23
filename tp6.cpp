#include <iostream>
#include <deque>
#include <set>
#include <iterator>
#include <algorithm>
#include <list>
#include "int_gen.h"
#include "tp5.cpp"

int main() {
    std::cout << "=== Début des tests de la classe Tableau ===" << std::endl;
    
    // Test 1: Construction et insertion basique
    std::cout << "\n--- Test 1: Construction et insertion ---" << std::endl;
    Tableau<int, 6> t1;
    t1.push_back(1);
    t1.push_back(2);
    t1.push_back(3);
    t1.push_back(4);
    t1.push_back(5);
    t1.push_back(6);
    std::cout << "Tableau t1: " << t1 << std::endl;

    // Test 2: Itérateur standard
    std::cout << "\n--- Test 2: Itérateur standard ---" << std::endl;
    std::cout << "Parcours avec itérateur: ";
    for (Tableau<int, 6>::iterator it = t1.begin(); it != t1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Test 3: Itérateur pair
    std::cout << "\n--- Test 3: Itérateur pair ---" << std::endl;
    std::cout << "Parcours des indices pairs: ";
    for (Tableau<int, 6>::evenIterator it = t1.evenBegin(); it != t1.evenEnd(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Test 4: Modification via itérateur
    std::cout << "\n--- Test 4: Modification via itérateur ---" << std::endl;
    for (Tableau<int, 6>::iterator it = t1.begin(); it != t1.end(); ++it) {
        *it *= 2;
    }
    std::cout << "Tableau après multiplication par 2: " << t1 << std::endl;

    // Test 5: Test avec différents types
    std::cout << "\n--- Test 5: Test avec type string ---" << std::endl;
    Tableau<std::string, 4> t2;
    t2.push_back("Hello");
    t2.push_back("World");
    t2.push_back("!");
    t2.push_back("C++");
    std::cout << "Tableau de strings: " << t2 << std::endl;

    // Test 6: Test des accès par index négatif
    std::cout << "\n--- Test 6: Test des index négatifs ---" << std::endl;
    std::cout << "Dernier élément (index -1): " << t1[-1] << std::endl;
    std::cout << "Avant-dernier élément (index -2): " << t1[-2] << std::endl;

    // Test 7: Test de l'opérateur post-incrémentation de l'itérateur
    std::cout << "\n--- Test 7: Test post-incrémentation ---" << std::endl;
    Tableau<int, 6>::iterator it = t1.begin();
    std::cout << "Valeur actuelle: " << *it << std::endl;
    Tableau<int, 6>::iterator old_it = it++;
    std::cout << "Ancienne valeur: " << *old_it << std::endl;
    std::cout << "Nouvelle valeur: " << *it << std::endl;

    // Test 8: Test de copie de Tableau
    std::cout << "\n--- Test 8: Test de copie ---" << std::endl;
    Tableau<int, 6> t3 = t1;
    std::cout << "Tableau original: " << t1 << std::endl;
    std::cout << "Tableau copié: " << t3 << std::endl;

    // Test 9: Test des itérateurs avec for-range (C++11)
    std::cout << "\n--- Test 9: Test for-range ---" << std::endl;
    std::cout << "Parcours avec for-range: ";
    for (const auto& val : t1) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Test 10: Test des limites
    std::cout << "\n--- Test 10: Test des limites ---" << std::endl;
    try {
        std::cout << "Tentative d'accès hors limites: " << t1[10] << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Exception attrapée comme prévu: " << e.what() << std::endl;
    }

    // Test 11: Performance basique
    std::cout << "\n--- Test 11: Test de performance basique ---" << std::endl;
    Tableau<int, 1000> t4;
    std::cout << "Insertion de 1000 éléments..." << std::endl;
    for (int i = 0; i < 1000; ++i) {
        t4.push_back(i);
    }
    std::cout << "Insertion terminée." << std::endl;

    // Test 12: Mélange d'itérateurs standards et pairs
    std::cout << "\n--- Test 12: Comparaison itérateurs standard et pair ---" << std::endl;
    std::cout << "Éléments standards: ";
    for (auto it = t1.begin(); it != t1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\nÉléments pairs uniquement: ";
    for (auto it = t1.evenBegin(); it != t1.evenEnd(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "\n=== Fin des tests ===" << std::endl;
    return 0;
}