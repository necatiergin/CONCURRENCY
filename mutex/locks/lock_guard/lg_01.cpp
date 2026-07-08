#include <mutex>
#include <vector>

std::mutex mtx;
std::vector<int> ivec;

void push_value(int x)
{
    std::lock_guard<std::mutex> guard{mtx};
    ivec.push_back(x);
}
