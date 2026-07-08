#include <mutex>

class Nec {
public:
    void foo()
    {
        std::lock_guard<std::recursive_mutex> lock{ mtx_ };
        // kritik bölge
    }

private:
    mutable std::recursive_mutex mtx_;
};
