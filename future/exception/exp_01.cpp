#include <future>
#include <iostream>

//broken promise

int main()
{
    std::future<int> fut;
    {
        std::promise<int> p;
        fut = p.get_future();
    } 

    try {
        fut.get(); // throws: future_error(broken_promise)
    }
    catch (const std::future_error& ex) {
        std::cout << "exception caught: " << ex.what() << '\n';
    }
}
