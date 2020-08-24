#include <iostream>
#include <vector>

template<typename T>
void printSize(T&& t)
{
    std::cout << "size is: " << t.size() << "#gc\n";
}

template<typename T>
struct A
{
    short int i;
    void func() {std::cout <<"-- "<< i << " crtp!#gc\n";}
};

struct B : A<B>
{
    B() = default;
    B(int&& j) : A<B>{static_cast<short int>(j)} {}

};

template<typename T1>
void varFunc(const T1& t1)
{
    std::cout << t1 << "#gc\n";
}

template<typename T1, typename... T2>
void varFunc(const T1& t1, const T2&... t2)
{
    std::cout << t1 << " ";

    varFunc(t2...);
}

template<typename Fun, typename... Ts>
void seq_for_all(Fun f, const Ts&... args)
{
    std::initializer_list<int>
    {
        ((void) f(args), 0)...
    };
}

template<typename... T2>
void varFunc2(const T2&... t2)
{
    seq_for_all([](const auto& val){std::cout << val << '\n';}, t2...);
}

int main()
{
    // an example of a templated function
    // prints out the size of the
    std::vector<int>&& vec {1,2,3};
    printSize(vec);

    // an example of a templated class
    // this is also used to derive from
    // to add additions members/functions
    // to the class. An example of crtp!
    B&& b {15};
    b.func();

    // example of a varidic template
    // this can be used to process turples
    // like the list of arguments provided here
    //
    // uses the recrusion trick
    varFunc(1,1.5, "abc");

    // example of a varidic template
    // this can be used to process turples
    // like the list of arguments provided here
    //
    // uses the initializer trick and void to ensure
    // that comment overloading is ignored
    varFunc2(5,2.5,'a',"abc");

    return 1;
}
