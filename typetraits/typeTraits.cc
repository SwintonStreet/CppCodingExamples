#include <iostream>
#include <string>
#include <type_traits>

using namespace std::string_literals;

struct testType
{
    // testType(int inVal): val {inVal} {};
    testType()  = default;
    ~testType() = default;

    int val, val2;
};

template <typename t>
constexpr bool is_float = std::is_same<t, float>::value;

template <class c>
const std::string is_Const = std::is_const<c>::value ? "Yes"s : "No"s;

template <typename t1, typename t2>
constexpr t1 AddIfInt(t1 type1, t2 type2)
{
    return std::is_integral<t1>::value && std::is_same<t1, t2>::value
               ? type1 + type2
               : type1;
}

int main()
{

    testType t1{.val = 0, .val2 = 3};

    std::cout << "t1 trivially constructable: "
              << std::is_trivially_constructible<testType>::value << '\n';
    std::cout << "t1 empty                  : "
              << std::is_empty<testType>::value << '\n';
    std::cout << "t1 float                  : " << is_float<testType> << '\n';
    std::cout << "t1 const                  : " << is_Const<testType> << '\n';
    std::cout << "t1 val2                   : " << t1.val2 << '\n';
    std::cout << "add 1                     : " << AddIfInt(1, 1) << '\n';
    std::cout << "add 2                     : " << AddIfInt(5, 2.7) << '\n';
    std::cout << "add 3                     : " << AddIfInt(10L, 15) << '\n';
    std::cout << "add 4                     : " << AddIfInt(20L, 205L) << '\n';

    return 0;
}
