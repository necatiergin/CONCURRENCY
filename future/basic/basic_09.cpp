#include <iostream>
#include <future>
#include <chrono>

constexpr int x = 47;

long long fib(int n)
{
    return n < 3 ? 1 : fib(n - 1) + fib(n - 2);
}

int main()
{
    using namespace std::literals;

    auto ftr = std::async(fib, x);

    std::cout << "wait for answer!\n";
    while (ftr.wait_for(10ms) == std::future_status::timeout)
        std::cout << '.' << std::flush;

    auto result = ftr.get();

    std::cout << "\nfib(" << x << ") is : " << result << '\n';
}
