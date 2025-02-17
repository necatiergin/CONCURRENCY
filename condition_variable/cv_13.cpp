// notify_all_at_thread_exit

#include <iostream>           
#include <thread>             
#include <mutex>              
#include <condition_variable> 

std::mutex mtx;
std::condition_variable cv;
bool ready_flag{ false };

void id_print(int id) 
{
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck, [] {return ready_flag; });
    // ...
    std::cout << "thread " << id << '\n';
}

void foo() 
{
    std::unique_lock<std::mutex> lck(mtx);
    ready_flag = true;                    
    std::notify_all_at_thread_exit(cv, std::move(lck));
}

int main()
{                                          
    constexpr int no_of_threads{ 16 };
    std::jthread jthreads[no_of_threads];

    for (int i = 0; i < no_of_threads; ++i)
        jthreads[i] = std::jthread(id_print, i);

    std::cout << no_of_threads << " threads ready_flag to race...\n";

    std::jthread(foo).detach();   // foo!
}
