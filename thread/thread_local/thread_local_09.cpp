#include <iostream>
#include <thread>
#include <syncstream>
#include <vector>

class Nec{
public:
    inline static thread_local int sval = 0;
    //...
};

void foo() 
{
    Nec::sval += 10;
    std::osyncstream{ std::cout } << "Thread ID: " << std::this_thread::get_id() << ", Value: " << Nec::sval << '\n';
}

int main() 
{
    std::vector<std::jthread> tvec(10);

    {
        for (auto& t : tvec)
            t = std::jthread{ foo };
    }

}
