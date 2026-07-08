#include <mutex>

class Counter {
public:
    void increment()
    {
        std::lock_guard<std::recursive_mutex> lock{ mtx_ };
        ++value_;
    }

    void add_twice()
    {
        std::lock_guard<std::recursive_mutex> lock{ mtx_ };

        increment();
        increment();
    }

private:
    int value_{};
    std::recursive_mutex mtx_;
};
