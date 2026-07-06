#include <thread>
#include <vector>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

void worker(int id, std::exception_ptr& eptr)
{
    try {
        if (id % 2 == 0) {
            throw std::runtime_error{ "exception from worker, thread id " + std::to_string(id)};
        }
    }
    catch (...) {
        eptr = std::current_exception();
    }
}

int main()
{
    constexpr std::size_t n = 8;

    std::vector<std::thread> threads;
    std::vector<std::exception_ptr> exceptions(n);

    for (std::size_t i = 0; i < n; ++i) {
        threads.emplace_back(worker, i, std::ref(exceptions[i]));
    }

    for (auto& t : threads) {
        t.join();
    }

    for (auto& eptr : exceptions) {
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            }
            catch (const std::exception& ex) {
                std::cout << "exception caught: " << ex.what() << '\n';
            }
        }
    }
}
