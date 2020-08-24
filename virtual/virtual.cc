#include <iostream>
#include <vector>

struct A
{
    void func() { std::cout << "A\n"; }
    virtual void func2() = 0;
};

struct B : A
{
    // struct B has access to struct As version of
    // functions/members using the namespace A::
    void func() { std::cout << "B"; A::func();}
    void func2() override { std::cout << "1\n";}
};

struct C : A
{
    void func() { std::cout << "C\n"; }
    void func2() override { std::cout << "2\n";}
};

int main()
{
    // structs B & C inherit from A
    B&& b {};
    C&& c {};

    // we define A pointers to the references
    // allowed because B/C inherit from A
    A*&& a  = &b;
    A*&& a2 = &c;

    // calling func on both gives the derived definition
    // of the function as both B & C define func over the
    // bases definition
    b.func();
    c.func();

    // as func2 is virtual, it means that at runtime it can
    // determine the correct function to go to, even though
    // we have a A pointer to the object
    a->func2();
    a2->func2();

    return 1;
}
