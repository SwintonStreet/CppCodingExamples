#include <iostream>

int main()
{
    int changeMe      = 1;
    int doNotChangeMe = 2;

    std::cout << "Pre\n"
              << "change me       : " << changeMe      << '\n'
              << "do not change me: " << doNotChangeMe << '\n';

    // nodiscard can not be directly applied to lambdas
    // but you can write a templated wrapper class to do
    // the same job

    // & is to indicate pass by reference (no & is pass by value)
    // mutable is required to allow the lambda to change the values
    // in the capture list

    // A standard variable can also be passed in, auto is only allowed
    // in c++14 and onwards. auto follows the template deduction rules
    // in this case.
    auto l = [& changeMe,
              doNotChangeMe]
             (const auto& i) mutable
             {
                 changeMe      += i;
                 doNotChangeMe += i;
                 return 5;
             };

    // call the lambda to make it change/not change
    // the values
    l(1);


    std::cout << "Post\n"
              << "change me       : " << changeMe      << '\n'
              << "do not change me: " << doNotChangeMe << '\n';

    return l(1);
}
