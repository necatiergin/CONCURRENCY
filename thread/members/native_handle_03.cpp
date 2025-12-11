#include <thread>
#include <iostream>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

void worker()
{
    for (int i = 0; i < 10; ++i) {
        std::cout << "worker on possibly pinned core, iteration " << i << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main()
{
    std::thread t{ worker };

#ifdef _WIN32
    HANDLE h = t.native_handle();

    // Pin thread to CPU 0 (bit 0 = 1)
    DWORD_PTR mask = 1ull << 0;

    DWORD_PTR prev_mask = SetThreadAffinityMask(h, mask);
    if (prev_mask == 0) {
        std::cerr << "SetThreadAffinityMask failed, GetLastError = "
            << GetLastError() << '\n';
    }
    else {
        std::cout << "Thread pinned to CPU 0.\n";
    }
#endif

    t.join();
}
