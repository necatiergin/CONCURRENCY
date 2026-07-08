#include <mutex>

class Counter {
public:
    void increment()
    {
        std::lock_guard<std::mutex> guard{ mtx_ };
        ++value_;
    }

    int get() const
    {
        std::lock_guard<std::mutex> guard{ mtx_ };
        return value_;
    }

private:
    mutable std::mutex mtx_;
    int value_{};
};
