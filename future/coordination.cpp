#include <future>
#include <iostream>

void stage1(std::promise<int> p) 
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    p.set_value(10); // produce value
}

void stage2(std::future<int> f) 
{
    int x = f.get(); // waits for stage1
    std::cout << "Stage 2 got the value: " << x * 2 << '\n';
}

int main() 
{
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::thread t1(stage1, std::move(p));
    std::thread t2(stage2, std::move(f));

    t1.join();
    t2.join();
}
