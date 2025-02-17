#include <iostream>
#include <future>

// member function get of shared_future class may be called several times

int main() 
{
    std::future<int> future = std::async([]() {
        // long lasting operation
        return 42;
        });

    std::shared_future<int> sharedFuture = future.share();

    std::cout << "Result 1: " << sharedFuture.get() << '\n';
    std::cout << "Result 2: " << sharedFuture.get() << '\n';
}
