#include <mutex>

std::mutex mtx;
int x{};

void increment()
{
    std::lock_guard<std::mutex> guard{ mtx };
    ++x;
}

int get()
{
    return x; // korumasız okuma
}
