#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx1, mtx2;

int shared_val1{};
int shared_val2{};

void foo() 
{
    std::lock(mtx1, mtx2);  

    std::lock_guard lock1(mtx1, std::adopt_lock);
                    
    shared_val1 += 10;
    std::lock_guard lock2(mtx2, std::adopt_lock);
    shared_val2 += 20;

    std::cout << "Values updated: " << shared_val1 << ", " << shared_val2 << '\n';
}  

int main() 
{
    std::jthread t1(foo);
    std::jthread t2(foo);
    std::jthread t3(foo);
}
