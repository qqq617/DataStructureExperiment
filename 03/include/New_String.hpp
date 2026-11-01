#include<iostream>
#include<stdexcept>
using namespace std;
class New_String {
private:
    char* s = nullptr;
    int len = 0;

    void Nstrcpy(const New_String& target) {
        len = target.len;
        delete[] s;
        s = new char [len + 1];
        for (int i = 0; i < len + 1; i++) {
            s[i] = target.s[i];
        }
    }

    void get_next(const New_String& str, int* next) {
        next[0] = 0;
        int k = 0;
        for (int i = 1; i < str.len; i++ ) {
            while (k > 0 && str[i] != str[k]) {
                k = next[k-1];
            }
            if (str[i] == str[k]) {
                k++;
            }
            next[i] = k;
        } 
    }

public:
    New_String (const char* string) {
        int n = 0;
        while (string[n] != '\0') {
            n++;
        }

        s = new char [n+1];
        len = n;

        for (int i = 0; i <= n; i++) {
            s[i] = string[i];
        }
    }

    New_String (const New_String& other) {
        Nstrcpy(other);
    }

    New_String () {
        s = new char [1];
        s[0] = '\0';
    }

    New_String& operator=(const New_String& other) {
        if (this != &other) {
            Nstrcpy(other);
        }
        return *this;
    }

    ~New_String() {
        delete[] s;
    }

    int length() const {
        return len;
    }

    bool empty() const {
        if (len == 0) return true;
        return false;
    }

    const char* c_str() const {
        return s ? s : "";
    } 

    void clear() {
        len = 0;
        delete[] s;
        s = new char[1];
        s[0] = '\0';
    }

    char& operator[](const size_t i) {
        return s[i];
    }

    const char& operator[](const size_t i) const {
        return s[i];
    }

    const char& at(const size_t i) const{
        if (i >= len ) {
            throw out_of_range("Index out of range");
        }

        return s[i];
    }

    char& at(const size_t i) {
        if (i >= len ) {
            throw out_of_range("Index out of range");
        }

        return s[i];
    }

    char* begin() {
        return s;
    }

    const char* begin() const {
        return s;
    }

    char* end() {
        return s + len;
    }
    
    const char* end() const {
        return s + len;
    }


    New_String& operator+=(const New_String& other) {
        int newlen = len + other.len;
        char* sum = new char [newlen + 1];
        for (int i = 0; i < this->len; i++) {
            sum[i] = this->s[i];
        }
        for (int i = 0; i <= other.len; i++) {
            sum[this->len + i] = other.s[i];
        }
        delete[] s;
        s = sum;
        len = newlen;
        return *this;
    }

    int find_kmp(const New_String& model) {
        if (model.len == 0) return 0;
        if (model.len > len) return -1;
        int* next = new int [model.len];
        get_next(model,next);
        int j = 0;
        for (int i = 0; i < len; i++) {
            while (s[i] != model[j] && j != 0) {
                j = next[j - 1]; 
            }
            if (s[i] == model[j]) j++;
            if (j == model.len) {
                delete[] next;
                return i - model.len + 1;
            }
        }
        delete[] next;
        return -1;
    }

};

inline New_String operator+(New_String s1, const New_String s2) {
    s1 += s2;
    return s1;
}

inline bool operator==(const New_String& s1, const New_String& s2) {
    if (s1.length() != s2.length()) return false;

    for (int i = 0; i < s1.length(); i++) {
        if(s1[i] != s2[i]) return false;
    }

    return true;
}

inline bool operator!=(const New_String& s1, const New_String& s2) {
    return !(s1==s2);
}

inline bool operator<(const New_String& s1, const New_String& s2) {
    int n = s1.length() > s2.length() ? s2.length() : s1.length();

    for (int i = 0; i < n; i++) {
        if (s1[i] == s2[i]) continue;
        return s1[i] < s2[i];
    }

    return s1.length() < s2.length();
}

inline ostream&  operator<<(ostream& os, const New_String& str) {
    os << str.c_str();
    return os;
}

inline istream& operator>>(istream& is, New_String& str) {
    str.clear();
    char ch;
    if (!(is >> ch)) {
        return is;
    }

    char* tmp = new char [1<<10];
    int i = 0;
    tmp[i] = ch;
    while (is.get(ch)) {
        if (isspace(static_cast<unsigned char>(ch))) {
            is.unget();
            break;
        }
        tmp[++i] = ch;
    }
    tmp[++i] = '\0';
    str = New_String(tmp);
    delete[] tmp;
    return is;
}
