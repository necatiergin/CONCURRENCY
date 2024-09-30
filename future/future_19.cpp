#include <future>
#include <iostream>
#include <thread>

int main()
{
    std::promise<int> prm;
    std::future ftr = prm.get_future();   //CTAD

    std::thread th([&prm]
        {
            try
            {
                // some code here
                throw std::runtime_error("error!!!");
            }
            catch (...)
            {
                try
                {
                    prm.set_exception(std::current_exception());
                }
                catch (...) {} // set_exception() may also throw
            }
        });

    try
    {
        std::cout << ftr.get();
    }
    catch (const std::exception& ex)
    {
        std::cout << "exception caught from the thread: " << ex.what() << '\n';
    }
    
    th.join();
}
