#include <iostream>

struct s
{
    int i;

    s(int in)
    {
        i = in; /*ctor print*/
        std::cout << "ctor i: " << i << '\n';
    }

    friend std::ostream& operator<<(std::ostream& o, const s& inS)
    {
        o << inS.i;
        return o;
    }
};

class c
{
    const s i{15};

  public:
    c() : i{10} {};
    c(int /*test*/){};

    void operator()() { std::cout << "value: " << i << '\n'; }
};

int main()
{
    c myObj{};
    c myObj2{1};

    myObj();
    myObj2();
}
