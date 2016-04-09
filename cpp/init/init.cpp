#include <iostream>
#include <string>

using namespace std;

class Blargh {
    public:
        Blargh();
        int init();
        int a;
};

Blargh::Blargh() {
    cout << "constructor called " << endl;
}

int Blargh::init() {
    cout << "init called" << endl;
    return 1;
}

int main() {
    Blargh b;
    return 1;
}   
