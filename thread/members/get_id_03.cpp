#include <thread>
#include <iostream>

std::thread::id main_thread_id;

void func()
{
    // different operations are performed depending on the thread from which func is called
    if (std::this_thread::get_id() == main_thread_id) {
        std::cout << "call from the main thread\n";
    }
    else {
        std::cout << "call from a child thread\n";
    }
}

int main()
{
    main_thread_id = std::this_thread::get_id();

    func();

    std::thread t{ func };
    t.join();
}
