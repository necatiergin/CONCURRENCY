#include <semaphore>
#include <string>
#include <iostream>
#include <thread>

std::string name{};

std::binary_semaphore smp(0);          

void prepare() 
{
    name = "tamer dundar";
    std::cout << "data is ready now\n";
    smp.release();               
}

void use() 
{
    std::cout << "use is waiting the data\n";
    smp.acquire();                 
    std::cout << "name is " << name << '\n';
}

int main() 
{
    std::jthread t1(prepare);
    std::jthread t2(use);
}
