#include <iostream>
#include <future>
#include <thread>

int sum(int x, int y) 
{
    return x + y;
}

int main() 
{
    std::packaged_task<int(int, int)> task(sum); 
    std::future<int> sonuc = task.get_future();

    task(33, 67); 
    std::cout << "result : " << sonuc.get() << '\n';

    task.reset(); 
    sonuc = task.get_future(); 

    std::thread(std::move(task), 99, 101).detach(); 
    std::cout << "result: " << sonuc.get() << '\n';
}
