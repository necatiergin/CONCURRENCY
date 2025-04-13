#include <iostream>
#include <thread>
#include <windows.h>

void task() 
{
    std::cout << "Thread is working...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main() 
{
    std::thread t(task);

    HANDLE hThread = t.native_handle();
    HRESULT result = SetThreadDescription(hThread, L"My Custom Thread");

    if (SUCCEEDED(result)) {
        std::wcout << L"Thread name assigned\n.";
    }
    else {
        std::wcerr << L"cannot assign thread name\n";
    }

    t.join();
}
