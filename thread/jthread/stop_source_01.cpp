#include <chrono>
#include <thread>
#include <iostream>

int main()
{
    using namespace std::literals::chrono_literals;

    std::stop_source st_src;

    std::thread 
        foo([stoken = st_src.get_token()]() {
        while (!stoken.stop_requested()) {
            std::cout.put('*');
            std::this_thread::sleep_for(50ms);
        }
            });

    std::thread
        bar([stoken = st_src.get_token()]() {
        while (!stoken.stop_requested()) {
            std::cout.put('.');
            std::this_thread::sleep_for(1s);
        }
            });

    std::this_thread::sleep_for(5s);

    st_src.request_stop();
    std::cout << "\nstopped\n";
    
    foo.join();
    bar.join();
}
