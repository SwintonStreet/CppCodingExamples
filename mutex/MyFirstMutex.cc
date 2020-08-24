#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <utility>
#include <typeinfo>
#include <vector>

std::mutex mtx;

template<typename t>
struct s
{

    t i;

    s(const t& iIn): i{iIn} {}

    // postfix ++ overload (c++ passes a int (0) with the call
    // to make it different to prefix)
    s operator++ (int)
    {
        return s(i++);
    }

    // prefix ++ overload
    s operator++ ()
    {
        return s(++i);
    }

    // friend ostream overload definition
    friend std::ostream& operator<<(std::ostream& os,
                                    const s&      val)
    {
        os << val.i;
        return os;
    }
};

s<int> myVal {2};
int myInt {1};

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

//template<typename Sv >
//void printAndIncrement(const Sv sv)
//{
//    mtx.lock();
//
//    {
//        std::cout << sv << ' ' << ++myVal << '\n';
//    }
//
//    mtx.unlock();
//}

int main()
{
    printAndIncrement<std::string_view,
                      std::string_view>("123", "456");
    printAndIncrement("123", "456", "567", 5.0f, 125LL);

    std::vector<std::thread> threads(4);
    threads[0] = std::move(std::thread([&](){printAndIncrement("123",
                                                               "234",
                                                               "345",
                                                               1);}));
    threads[1] = std::move(std::thread([&](){printAndIncrement("123",
                                                               "234",
                                                               2.5);}));
    threads[2] = std::move(std::thread([&](){printAndIncrement("123",
                                                               "234",
                                                               5);}));
    threads[3] = std::move(std::thread([&](){printAndIncrement("123",
                                                               "234",
                                                               5L);}));

    for (auto& th : threads) {th.join();}

    return 0;
}
