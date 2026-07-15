#include <future>
#include <iostream>
#include <thread>

void produce_reference(std::promise<int&> prom, int& value)
{
    value *= 2;

    prom.set_value(value);
}

int main()
{
    int x = 21;

    std::promise<int&> prom;
    std::future<int&> ftr = prom.get_future();

    std::thread worker{
        produce_reference,
        std::move(prom),
        std::ref(x)
    };

    int& result = ftr.get();

    result += 10;

    worker.join();

    std::cout << "x: " << x << '\n';
    std::cout << "result: " << result << '\n';
}
