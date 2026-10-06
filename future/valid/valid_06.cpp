#include <future>
#include <iostream>

int main()
{
    std::future<int> ftr;

    {
        std::promise<int> p;
        ftr = p.get_future();

    } // promise destroyed

    std::cout << std::boolalpha << ftr.valid() << '\n';

}
