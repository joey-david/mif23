#include <iostream>

class String {
private:
    char * str;
    int size;
public:
    String() : str(new char[1]), size(0) {
        str[0] = '\0';
        std::cout << "String::String() with size = " << size << "\n";
    }

    String(char c) : str(new char[2]), size(1) {
        str[0] = c;
        str[1] = '\0';
        std::cout << "String::String(char) with size = " << size << "\n";
    }

    String(const char * s, int size) : str(new char[size + 1]), size(size) {
        std::cout << "String::String(const char *, int) with size = " << size << "\n";
        for (int i = 0; i < size; i++) {
            str[i] = s[i];
        }
        str[size] = '\0';
    }
    
    String(const char* s) : str(nullptr), size(0) {
        while (s && s[size] != '\0') {
            size++;
        }
        str = new char[size + 1];
        for (int i = 0; i < size; i++) {
            str[i] = s[i];
        }
        str[size] = '\0';
        std::cout << "String::String(const char *) with size = " << size << "\n";        
    }

    String(const String & s) : str(new char[s.size + 1]), size(s.size) {
        std::cout << "String::String(const String &) with size = " << size << "\n";
        for (int i = 0; i < size; i++) {
            str[i] = s.str[i];
        }
        str[size] = '\0';
    }

    String(String && s) noexcept : str(s.str), size(s.size) {
        std::cout << "String::String(String &&) with size = " << size << "\n";
        s.str = nullptr;
        s.size = 0;
        
    }

    operator const char*() const {
        return str;
    }

    String operator+(const String & s) const {
        String newStr;
        newStr.size = size + s.size;
        newStr.str = new char[newStr.size + 1];
        for (int i = 0; i < size; i++) {
            newStr.str[i] = str[i];
        }
        for (int i = 0; i < s.size; i++) {
            newStr.str[size + i] = s.str[i];
        }
        newStr.str[newStr.size] = '\0';
        return newStr;
    }

    bool operator==(const String & s) const {
        if (size != s.size) return false;
        for (int i = 0; i < size; i++) {
            if (str[i] != s.str[i]) return false;
        }
        return true;
    }

    bool operator!=(const String & s) const {
        return !(*this == s);
    }

    bool operator<(const String & s) const {
        for (int i = 0; i < size && i < s.size; i++) {
            if (str[i] < s.str[i]) return true;
            if (str[i] > s.str[i]) return false;
        }
        return size < s.size;
    }

    bool operator>(const String & s) const {
        return s < *this;
    }

    bool operator<=(const String & s) const {
        return !(*this > s);
    }

    bool operator>=(const String & s) const {
        return !(*this < s);
    }

    char & operator[](int index) {
        return str[index];
    }

    const char & operator[](int index) const {
        return str[index];
    }

    int length() const {
        return size;
    }

    bool empty() const {
        return size == 0;
    }

    String substring(int start, int end) const {
        if (start < 0 || end >= size || start > end) {
            return String();
        }
        String subStr;
        subStr.size = end - start + 1;
        subStr.str = new char[subStr.size + 1];
        for (int i = 0; i < subStr.size; i++) {
            subStr.str[i] = str[start + i];
        }
        subStr.str[subStr.size] = '\0';
        return subStr;
    }

    ~String() {
        delete[] str;
        std::cout << "String::~String() with size = " << size << "\n";
    }

    friend std::ostream & operator << (std::ostream & os, const String & s) {
        for (int i = 0; i < s.size; i++) {
            os << s.str[i];
        }
        return os;
    }
};

int main() {
    String s1;
    String s2('A');
    String s3("Hello");
    String s4("World", 5);
    String s5(s3);
    String s6(std::move(s4));

    std::cout << "s1: " << s1 << "\n";
    std::cout << "s2: " << s2 << "\n";
    std::cout << "s3: " << s3 << "\n";
    std::cout << "s4: " << s4 << "\n";
    std::cout << "s5: " << s5 << "\n";
    std::cout << "s6: " << s6 << "\n";

    String s7 = s3 + s6;
    std::cout << "s7 (s3 + s6): " << s7 << "\n";

    std::cout << "s3 == s5: " << (s3 == s5) << "\n";
    std::cout << "s3 != s6: " << (s3 != s6) << "\n";
    std::cout << "s3 < s6: " << (s3 < s6) << "\n";
    std::cout << "s3 > s6: " << (s3 > s6) << "\n";
    std::cout << "s3 <= s5: " << (s3 <= s5) << "\n";
    std::cout << "s3 >= s6: " << (s3 >= s6) << "\n";

    std::cout << "s3[1]: " << s3[1] << "\n";
    s3[1] = 'a';
    std::cout << "s3 after modification: " << s3 << "\n";

    std::cout << "s3 length: " << s3.length() << "\n";
    std::cout << "s1 empty: " << s1.empty() << "\n";

    String s8 = s3.substring(1, 3);
    std::cout << "s8 (substring of s3 from 1 to 3): " << s8 << "\n";
}
