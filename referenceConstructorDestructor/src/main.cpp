#include <iostream>
#include <vector>

struct A
{
    int     a;
    int16_t c;

    A() : a{2}, c{3} { std::cout << "A constructor 1#gc\n"; }

    A(const int& /*i*/, const int16_t& j) : a{j}, c{j}
    {
        std::cout << "A constructor 2#gc\n";
    }

    virtual ~A()
    {
        std::cout << "A destructor 1#gc\n";
        std::cout << c << "#gc\n";
    }
};

struct B : A
{
    int b;

    B() : A{1, 2}, b{1} { std::cout << "B constructor#gc\n"; }

    B(const int& i) : A{i, static_cast<int16_t>(i)}, b{1}
    {
        std::cout << "B constructor 2#gc\n";
    }

    virtual ~B() { std::cout << "B destructor#gc\n"; }
};

int main()
{
    // constructing B as a reference requires
    // that it be a const
    const B& tempB = B{};

    // tempB A constructor called
    // tempB B constructor called

    // constructing an object of A from B is fine
    // because B inherits from A, thus it will create
    // A as part of its constructor, this will be copied
    // to the tempA object, note the object is then desctroyed
    // as it will lose all references to it
    A tempA = B{4};

    // A constructor called
    // B constructor called
    // B destructor called
    // A destructor called

    // it can also create a reference, this isnt a copy so
    // the destructor isnt called as a reference to the
    // object continues to exist
    [[maybe_unused]] const A& tempA2 = B{6};

    // tempA2 A constructor called
    // tempA2 B constructor called

    // tempA2 B destructor called
    // tempA2 A destructor called
    // tempA1 B destructor called
    // tempA1 A destructor called
    // tempB  B destructor called
    // tempB  A destructor called

    // destructors are called in reverse order
    return 1;
}
