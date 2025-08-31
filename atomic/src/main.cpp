#include <array>
#include <atomic>
#include <barrier>
#include <iostream>
#include <thread>

namespace
{

std::atomic_flag af;
constexpr int    MAX_COUNT    = 1000;
constexpr int    THREAD_COUNT = 8;
std::barrier     barrier{THREAD_COUNT};

std::atomic_int i{0};

template <typename T>
void countTo(const T& maxCount) noexcept
{
    int id{i++};

    barrier.arrive_and_wait();

    for (volatile int j = 0; j < maxCount + id;)
    {
        j = j + 1;
    }

    if (!af.test_and_set())
    {
        std::cout << "thread: #" << id << " won!\n";
    }
}

} // namespace

int main()
{
    std::array<std::jthread, THREAD_COUNT> threads{};

    for (auto& th : threads)
    {
        th = std::jthread(countTo<int>, MAX_COUNT);
    }

    return 0;
}
