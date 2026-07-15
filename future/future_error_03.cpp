#include <future>
#include <iostream>

int main()
{
    std::promise<int> p;

    try {
        p.set_value(10);
        p.set_value(20);
    }
    catch (const std::future_error& ex) {

        std::cout << ex.what() << '\n';

        if (ex.code() ==
            std::make_error_code(std::future_errc::promise_already_satisfied))
        {
            std::cout << "Promise already satisfied\n";
        }
    }
}
