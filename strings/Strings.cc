#include <iostream>
#include <string>

struct howLongDoesItLive
{
    [[nodiscard]] inline const char* testString(const int& i) const
    {
        return i > 4 ? "reset" : "";
    };
};

int main()
{

    std::cout << "test\n";

    const char* tmp = "";
    (void)tmp;

    {

        howLongDoesItLive how;
        tmp = how.testString(6);
    }

    const char* tmp2 = "test123";

    int i = 1;

    int* pi = &i;

    (void)pi;

    // For this to work, the 'rvalue' const char* data must be statically
    // stored by the program, thus a pointer to it will always work?
    std::cout << (const void*)tmp << " - " << tmp << '\n'
              << (const void*)tmp2 << " - " << tmp2 << '\n'
              << ((const int*)tmp2 - (const int*)tmp) << '\n';

    std::string st{""};

    std::cout << "String length:   " << sizeof(st.length()) << '\n'
              << "String capacity: " << sizeof(st.capacity()) << '\n'
              << "String capacity: " << st.capacity() << '\n'
              << "sizeOf string:   " << sizeof(st) << '\n';
}
