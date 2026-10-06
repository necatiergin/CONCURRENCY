#include <future>
#include <iostream>

int main()
{
    std::promise<void> vprm;
    //std::future<void> vftr = vprm.get_future();
    std::future vftr = vprm.get_future(); //CTAD

    std::boolalpha(std::cout);

    std::cout << vftr.valid() << '\n';
    vprm.set_value();
    std::cout << vftr.valid() << '\n';
    vftr.get();
    std::cout << vftr.valid() << '\n';
}
