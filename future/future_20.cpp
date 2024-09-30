#include <future>
#include <iostream>
#include <thread>

int main()
{
    std::promise<int> prm;
    std::future ftr_1 = prm.get_future();   //CTAD

    boolalpha(std::cout);

    std::cout << "ftr_1.valid() = " << ftr_1.valid() << '\n';

    prm.set_value(12);

    auto ftr_2 = std::move(ftr_1); //ftr_2 move constructed
    
    std::cout << "ftr_1.valid() = " << ftr_1.valid() << '\n';
    std::cout << "ftr_2.valid() = " << ftr_2.valid() << '\n';

    std::cout << "value is : " << ftr_2.get() << '\n';

    std::cout << "ftr_2.valid() = " << ftr_2.valid() << '\n';
}
