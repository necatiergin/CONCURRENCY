#include <shared_mutex>
#include <mutex>

std::shared_mutex mtx;

void read_data() 
{
    std::shared_lock<std::shared_mutex> lock(mtx);
    // reads data
}

void write_data() 
{
    std::unique_lock<std::shared_mutex> lock(mtx);
    // sets data
}
