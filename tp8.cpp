#include <iostream>
#include <type_traits>

struct NullType {};

// template<typename H, typename T = NullType>
// struct TypeList {
//     typedef H Head;
//     typedef T Tail;
// };

// template<typename TList>
// struct Length {
//     static const int value = 1 + Length<typename TList::Tail>::value;
// };

// template<>
// struct Length<NullType> {
//     static const int value = 0;
// };

template<typename H, typename... Ts>
struct Length {
    static constexpr std::size_t value = 1 + Length<Ts...>::value;
};

template<typename H>
struct Length<H> {
    static constexpr std::size_t value = 1;
};

// template<std::size_t I, typename Head, typename... Tail>

// template<typename... Ts>

// template<std::size_t I, typename List>


int main() {
    std::cout << "Length<int, double, char, float>;" << Length<int, double, char, float>::value << std::endl;
    return 0;
}