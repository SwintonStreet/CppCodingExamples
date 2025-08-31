#include <algorithm>
#include <chrono>
#include <future>
#include <iostream>
#include <vector>

struct noIncrement
{
    int val;

    noIncrement(int inVal) noexcept : val{inVal} {}

    friend std::ostream& operator<<(std::ostream& os, const noIncrement& ni)
    {
        os << ni.val;
        return os;
    }

    noIncrement operator++(int) { return noIncrement(val++); }
};

template <typename t>
std::vector<std::future<t>> createFutureVec(const std::vector<int>&& waits)
{
    std::vector<std::future<t>> fus;
    t                           i = 1;
    for (const auto& w : waits)
    {
        fus.emplace_back(std::async(
            [i](const int& wt)
            {
                std::this_thread::sleep_for(std::chrono::seconds(wt));
                return i;
            },
            w));
        i++;
    }

    return fus;
}

int main()
{
    auto fus{createFutureVec<noIncrement>({1, 2, 3, 5})};

    const auto timeout = std::chrono::milliseconds(10);

    while (std::any_of(
        begin(fus), end(fus), [](const auto& fu) { return fu.valid(); }))
    {
        for (auto& fu : fus)
        {
            if (fu.valid() && fu.wait_for(timeout) == std::future_status::ready)
            {
                std::cout << "Thread " << fu.get() << " is done!\n";
            }
        }
    }

    return 0;
}
