#include <future>
#include <iostream>
#include <thread>

int main()
{
    std::packaged_task<int(int, int)> task([](int a, int b)
        { return a * a + b * b; }); // wrap the function
   
    std::future f = task.get_future(); // get a future from a std::packaged_task<>
    
    std::thread th(std::move(task), 3, 6); // launch on a thread moving the task

    f.wait(); //blocks until getting the value

    std::cout << "the value is: " << f.get() << '\n';

    th.join();
}
