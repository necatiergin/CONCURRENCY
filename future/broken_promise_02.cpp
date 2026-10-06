#include <future>
#include <iostream>


bool some_error()
{
    // ...
    return true;
}

void worker(std::promise<int> prom)
{
    if (some_error())
        return;

    prom.set_value(42);
}

int main()
{
    std::promise<int> prom;
    auto ft = prom.get_future();
    std::thread t{ worker, std::move(prom) };
    try {
        std::cout << ft.get();
    }
    catch (const std::future_error& ex) {
        std::cout << "exception caught: " << ex.what() << '\n';
    }
    t.join();
}


