#include <iostream>
#include <thread>
#include <mutex>
#include <typeinfo>
#include <vector>

std::mutex mtx;

template<typename t>
struct S
{

    t i;

    S(const t& iIn): i{iIn} {}

    // postfix ++ overload (c++ passes a int (0) with the call
    // to make it different to prefix)
    S operator++ (int)
    {
        return s(i++);
    }

    // prefix ++ overload
    S operator++ ()
    {
        return S(++i);
    }

    // friend ostream overload definition
    friend std::ostream& operator<<(std::ostream& os,
                                    const S&      val)
    {
        os << val.i;
        return os;
    }
};

S<int> myVal {2}; // GUARDED_BY_MUTEX
int myInt {1};    // GUARDED_BY_MUTEX

template<typename ...Sv >
void printAndIncrement(const Sv... sv) noexcept
{
    // lock guard takes the mutex lock with an object
    //
    // this has the benefit of giving the lock a lifetime
    // which ensures the lock is returned in the case of
    // an exception being thrown
    std::lock_guard<std::mutex> lock(mtx);

    ((std::cout << typeid(sv).name() << ' ' <<
                   sv                << ' ' <<
                   ++myVal           << '\n') , ...);

    std::cout << "------------------------\n";
    std::cout << std::this_thread::get_id() << '\n';
    std::cout << "------------------------\n";
}

int main()
{
    printAndIncrement<std::string_view,
                      std::string_view>("123", "456");
    printAndIncrement("123", "456", "567", 5.0f, 125LL);

    std::vector<std::jthread> threads(4);
    threads[0] = std::jthread([&](){printAndIncrement("123",
                                                      "234",
                                                      "345",
                                                      1);});
    threads[1] = std::jthread([&](){printAndIncrement("123",
                                                      "234",
                                                      2.5);});
    threads[2] = std::jthread([&](){printAndIncrement("123",
                                                      "234",
                                                      5);});
    threads[3] = std::jthread([&](){printAndIncrement("123",
                                                      "234",
                                                      5);});

    for (auto& th : threads) {th.join();}

    return 0;
}
