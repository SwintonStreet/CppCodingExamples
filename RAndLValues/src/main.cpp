#include <iostream>
#include <vector>

struct A
{
    int arr[5];
};

int main()
{
    int arr[5];

    int(&&ar_ref)[5]  = static_cast<int(&&)[5]>(arr);
    int(&&ar_ref2)[5] = A().arr;

    ar_ref[3] = 1;

    for (const int& j : arr)
    {
        std::cout << "--" << j << "\n";
    }

    for (const int& k : ar_ref2)
    {
        std::cout << "--" << k << "\n";
    }

    return 1;
}
