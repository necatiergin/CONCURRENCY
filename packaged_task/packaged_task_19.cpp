#include <iostream>
#include <future>

void ftask() 
{
    std::cout << "Executing task...\n";
}

int main() 
{
    using std::cout;

    std::packaged_task<void()> task1;  // Default-constructed, initially empty
    std::packaged_task<void()> task2(ftask);  // Initialized with a valid task

    cout << "task1 is " << (task1.valid() ? "valid" : "empty") << '\n';
    cout << "task2 is " << (task2.valid() ? "valid" : "empty") << '\n';

    // Move task2 into task3
    std::packaged_task<void()> task3 = std::move(task2);

    cout << "After moving task2 to task3:\n";
    cout << "task2 is " << (task2.valid() ? "valid" : "empty") << '\n';
    cout << "task3 is " << (task3.valid() ? "valid" : "empty") << '\n';
}
