#include <atomic>
#include <iostream>
#include <thread>

std::atomic<bool> ready{false};
std::atomic_flag  af{ATOMIC_FLAG_INIT};

int i{1};

template <typename t>
void countToTen(const t& inMaxCount) noexcept
{
    int id{i++};
    while (!ready)
    {
        std::this_thread::yield();
    }

    for (volatile int j = 0; j < inMaxCount; j++)
    {
    }

    if (!af.test_and_set())
    {
        std::cout << "thread: #" << id << " won!\n";
    }
}

int main()
{
    std::thread threads[8];

    int maxCount = 1000;
    for (auto& th : threads)
    {
        th = std::move(std::thread(countToTen<int>, maxCount));
        maxCount += 050;
    }

    ready = true;

    for (auto& th : threads)
    {
        th.join();
    }

    return 0;
}
