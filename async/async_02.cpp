#include <future>
#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <exception>

using namespace std;
using namespace std::chrono;

int task(char ch)
{
    mt19937 eng{ random_device{}() };
    std::uniform_int_distribution dist{ 20, 500 };
    int total_duration{};

    for (int i = 0; i < 20; ++i) {
        auto dur = milliseconds(dist(eng));
        this_thread::sleep_for(dur);
        cout << ch << flush;
        total_duration += static_cast<int>(dur.count());
    }

    return total_duration;
}

int foo()
{
    return task('!');
}

int bar()
{
    return task('?');
}

int main()
{
    cout << "starting foo() in background and bar() in foreground:" << '\n';

    future<int> foo_result = async(foo);

    const auto bar_result = bar();
    const auto result = foo_result.get() + bar_result;

    cout << "\nresult = " << result << '\n';
}
