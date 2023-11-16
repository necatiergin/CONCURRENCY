#include <iostream>
#include <thread>

class Nec
{
public:
    void func(int x)const
    {
        std::cout << x << '\n';
    }
};

int main()
{
    Nec nec;
    // Create and execute the thread
    std::thread t{ &Nec::func, &nec, 13 };

    t.join();
}
