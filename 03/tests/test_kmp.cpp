#include"New_String.hpp"
#include<iostream>
using namespace std;
int main(){
    New_String* str = new New_String("ABABABC");
    int p = str->find_kmp("ABABC");
    cout << p << endl;
}