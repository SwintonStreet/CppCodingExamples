#include <iostream>
#include <string>
#include <vector>

class emptyClass
{
};

struct emptyStruct
{
};

int main()
{

    std::string myEmptyString;
    emptyClass  myEmptyClass;
    emptyStruct myEmptyStruct;

    std::cout << "empty string  :" << sizeof(myEmptyString) << '\n';
    std::cout << "empty string 2:" << sizeof(std::string) << '\n';
    std::cout << "\"\"            :" << sizeof("") << '\n';
    std::cout << "size_t        :" << sizeof(size_t) << '\n';
    std::cout << "empty class   :" << sizeof(myEmptyClass) << '\n';
    std::cout << "empty struct  :" << sizeof(myEmptyStruct) << '\n';
    std::cout << "int           :" << sizeof(int) << '\n';
    std::cout << "int*          :" << sizeof(int*) << '\n';
    std::cout << "long int      :" << sizeof(long int) << '\n';
    std::cout << "long int*     :" << sizeof(long int*) << '\n';
    std::cout << "char          :" << sizeof(char) << '\n';
    std::cout << "char*         :" << sizeof(char*) << '\n';
    std::cout << "unsigned char :" << sizeof(unsigned char) << '\n';
    std::cout << "unsigned char*:" << sizeof(unsigned char*) << '\n';

    return 0;
}
