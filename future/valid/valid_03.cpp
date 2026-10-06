#include <future>
#include <iostream>
#include <thread>

int main()
{
    std::promise<int> prm;
    std::future ftr_1 = prm.get_future();   //CTAD

    boolalpha(std::cout);

    std::cout << "[1] ftr_1.valid() = " << ftr_1.valid() << '\n';

    prm.set_value(12);
    std::cout << "[2] ftr_1.valid() = " << ftr_1.valid() << '\n';

    auto ftr_2 = std::move(ftr_1); //ftr_2 move constructed

    std::cout << "[3] ftr_1.valid() = " << ftr_1.valid() << '\n';
    std::cout << "[4] ftr_2.valid() = " << ftr_2.valid() << '\n';

    std::cout << "value is : " << ftr_2.get() << '\n';

    std::cout << "[5] ftr_2.valid() = " << ftr_2.valid() << '\n';
}
