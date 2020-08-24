#include <vector>
#include <string>
#include <iostream>


struct S
{
    std::vector<int>         intVec;
    std::vector<std::string> stVec;

    S(): intVec {1,2,3,4,5} {}
};

int main()
{
    S s;

    std::cout << "int    vector size: " << s.intVec.size() << '\n';
    std::cout << "string vector size: " << s.stVec.size()  << '\n';

    return 0;
}
