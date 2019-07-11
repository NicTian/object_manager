#include "singleton.h"
#include <iostream>
using namespace std;
class A
{
public:
    A(){cout << "A constructor" << endl;;}
    ~A(){cout << "A deconstructor" << endl;}
};

class B
{
public:
    B(){cout << "B constructor" << endl;}
    ~B(){cout << "B deconstructor" << endl;}
};

int main(int argc, char* argv[])
{
    ObjectManager obj;
    A* a = Singleton<A>::instance();
    B* b = Singleton<B>::instance();
	return 0;
}

