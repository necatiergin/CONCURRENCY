#include <future>
#include <iostream>

int main()
{
    std::promise<void> prom;
    //std::future<void> f = prom.get_future();
    std::future ft = prom.get_future();

    boolalpha(std::cout);

    std::cout << ft.valid() << '\n';
    prom.set_value();
    std::cout << ft.valid() << '\n';
    ft.get();
    std::cout << ft.valid() << '\n';

    //default constructed std::future object has no shared state
    std::future<int> ft2;
    std::cout << ft2.valid() << '\n';
}
