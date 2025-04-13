// from cpp.reference.com

#include <chrono>
#include <future>
#include <iostream>
#include <string>
#include <thread>

std::string time()
{
    static auto start = std::chrono::steady_clock::now();
    std::chrono::duration<double> d = std::chrono::steady_clock::now() - start;
    return "[" + std::to_string(d.count()) + "s]";
}

int main()
{
    using namespace std::chrono_literals;

    {
        std::cout << time() << " launching thread\n";
        std::future<int> f = std::async(std::launch::async, []
            {
                std::this_thread::sleep_for(1s);
                return 7;
            });

        std::cout << time() << " waiting for the future, f.valid() = "  << f.valid() << '\n';
        int n = f.get();
        std::cout << time() << " f.get() returned " << n << ", f.valid() = " << f.valid() << '\n';
    }

    {
        std::cout << time() << " launching thread\n";
        std::future<int> f = std::async(std::launch::async, []
            {
                std::this_thread::sleep_for(1s);
                return true ? throw std::runtime_error("7") : 7;
            });
        std::cout << time() << " waiting for the future, f.valid() = "
            << f.valid() << '\n';

        try
        {
            int n = f.get();
            std::cout << time() << " f.get() returned " << n
                << ", f.valid() = " << f.valid() << '\n';
        }
        catch (const std::exception& e)
        {
            std::cout << time() << " caught exception " << e.what()
                << ", f.valid() = " << f.valid() << '\n';
        }
    }
}
