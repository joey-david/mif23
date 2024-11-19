#include <algorithm>
#include <iterator>
#include <iostream>
#include <deque>
#include <set>
#include <list>
#include "../TP3/Generator.cpp"

int main() {
    std::deque<int> d(5);
    Generator g(4); // 0 0 0 0 0
    std::generate(d.begin(), d.end(), std::ref(g));  // Fills with: 4, 8, 12, 16, 20
    std::copy(d.begin(), d.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::set<int> s1(d.begin(), d.end());
    d.clear();
    std::set<int> s2;
    for (int i = 0; i < 10; i++)
        s2.insert(i*2);
    std::set<int> s3;
    std::generate_n(std::inserter(s3, s3.begin()), 6, [n = 1]() mutable { return n++ * 3; });
    std::copy(s1.begin(), s1.end(), std::ostream_iterator<int>(std::cout, "; "));
    std::cout << std::endl;
    std::copy(s2.begin(), s2.end(), std::ostream_iterator<int>(std::cout, "; "));
    std::cout << std::endl;
    std::copy(s3.begin(), s3.end(), std::ostream_iterator<int>(std::cout, "; "));
    std::cout << std::endl;
    std::list<int> l;
    std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(l, l.begin()));
    std::copy(l.begin(), l.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::set_union(s1.begin(), s1.end(), s3.begin(), s3.end(), std::ostream_iterator<int>(std::cout, "; "));
    std::cout << std::endl;
    return 0;
}