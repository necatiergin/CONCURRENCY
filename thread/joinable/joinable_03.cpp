#include <iostream>
#include <thread>
#include <chrono>

void foo()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
    std::cout << std::boolalpha;

    std::thread tx{ foo };
    std::thread ty;

    std::cout << "is tx joinable ? : " << (tx.joinable() ? "yes" : "no") << '\n';
    std::cout << "is ty joinable ? : " << (ty.joinable() ? "yes" : "no") << '\n';
    ty = std::move(tx);
    std::cout << "after assignment\n";
    std::cout << "is tx joinable ? : " << (tx.joinable() ? "yes" : "no") << '\n';
    std::cout << "is ty joinable ? : " << (ty.joinable() ? "yes" : "no") << '\n';
    ty.join();
}
