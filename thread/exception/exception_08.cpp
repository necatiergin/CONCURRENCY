#include <thread>
#include <exception>
#include <iostream>
#include <stdexcept>

void worker(std::exception_ptr& eptr)
{
    try {
        throw std::runtime_error{ "worker thread error" };
    }
    catch (...) {
        eptr = std::current_exception();
    }
}

int main()
{
    std::exception_ptr eptr;

    std::thread t{ worker, std::ref(eptr) };

    t.join();

    if (eptr) {
        try {
            std::rethrow_exception(eptr);
        }
        catch (const std::exception& ex) {
            std::cout << "exception caught in the main thread: "
                << ex.what() << '\n';
        }
    }
}
