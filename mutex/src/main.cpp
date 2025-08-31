#include <iostream>
#include <mutex>
#include <thread>
#include <typeinfo>
#include <vector>

namespace
{

template <typename t>
struct S
{
    S(const t& iIn) : i{iIn} {}

    // postfix ++ overload (c++ passes a int (0) with the call
    // to make it different to prefix)
    S operator++(int) { return s(i++); }

    // prefix ++ overload
    S operator++() { return S(++i); }

    // friend ostream overload definition
    friend std::ostream& operator<<(std::ostream& os, const S& val)
    {
        os << val.i;
        return os;
    }

    t i;
};

std::mutex mtx;

template <typename... Sv>
void printAndIncrement(const Sv&... sv)
{
    // lock guard takes the mutex lock with an object
    //
    // this has the benefit of giving the lock a lifetime
    // which ensures the lock is returned in the case of
    // an exception being thrown
    std::lock_guard<std::mutex> lock(mtx);

    static S<int> myVal{2};

    ((std::cout << typeid(sv).name() << ' ' << sv << ' ' << ++myVal << '\n'),
     ...);

    std::cout << "------------------------\n"
              << std::this_thread::get_id() << '\n'
              << "------------------------\n";
}

} // namespace

int main()
{
    printAndIncrement<std::string_view, std::string_view>("123", "456");
    printAndIncrement("123", "456", "567", 5.0f, 125LL);

    std::vector<std::jthread> threads;
    threads.emplace_back([] { printAndIncrement("123", "234", "345", 1); });
    threads.emplace_back([] { printAndIncrement("123", "234", 2.5); });
    threads.emplace_back([] { printAndIncrement("123", "234", 5); });
    threads.emplace_back([] { printAndIncrement("123", "234", 5); });
    return 0;
}
