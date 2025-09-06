#include <iostream>
#include <string_view>
#include <type_traits>

namespace
{

struct testType
{
    int val{};
    int val2{};
};

template <typename t>
constexpr bool is_float = std::is_same<t, float>::value;

template <class c>
const std::string_view is_Const = std::is_const<c>::value ? "Yes" : "No";

template <typename t1, typename t2>
constexpr t1 AddIfInt(t1 type1, t2 type2)
{
    return std::is_integral<t1>::value && std::is_same<t1, t2>::value
               ? type1 + type2
               : type1;
}

} // namespace

int main()
{

    auto t1 = testType{0, 3};

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
