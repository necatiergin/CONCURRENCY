// adapted from Reiner Grimm (modified)

#include <iostream>
#include <semaphore>
#include <thread>

std::binary_semaphore smping{0};
std::binary_semaphore smpong{0};

std::atomic counter{ 0 };
constexpr int n = 100;

void ping() 
{
    while (counter <= n) {
        smping.acquire();    
        ++counter;
        std::cout << "ping\n";
        smpong.release();
    }
}

void pong() 
{
    while (counter < n) {
        smpong.acquire();
        ++counter;
        std::cout<< "pong\n";

        smping.release();               
    }
}

int main() {

    smping.release();           
    
    {
        std::jthread t1(ping);
        std::jthread t2(pong);
    }
}
