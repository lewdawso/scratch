#include <iostream>
#include <string>

using namespace std;

class Test {
    public:
        Test();
        int x;
        int print() const;
};

Test::Test() {
    x = 10;
}

int Test::print() const {
    cout << this->x << endl;
    //this is what const => you can't do
    //this->x = 2;
    cout << (1 << 2) << endl;
    return 0;
}

int main() {
    Test t;
    t.print();
    return 0;
}
