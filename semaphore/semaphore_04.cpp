#include <semaphore>
#include <thread>
#include <syncstream>
#include <iostream>

int main()
{
    using namespace std;

    binary_semaphore smp(0);
    jthread th([&smp]() {
        osyncstream(cout) << "thread " << this_thread::get_id() << " beklemede\n";
        smp.acquire();
        osyncstream(cout) << this_thread::get_id() << " calisiyor\n";
        });

    this_thread::sleep_for(1200ms);
    osyncstream(cout) << "thread " <<this_thread::get_id() << " thread " << th.get_id() << " i uyandiracak\n";
    smp.release();
}
