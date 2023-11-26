//this code is adapted from the example in Nicholai Jossutis STL book.

#include <future>
#include <thread>
#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

int get_number()
{
    cout << "enter a number: ";
    int num{};
    cin >> num;

    if (!cin) {
        throw runtime_error("no valid number");
    }

    return num;
}

void print_chars(char c, shared_future<int> f)
{
    try {
        // wait for number of characters to print
        int num = f.get();  // get result of get_number()

        for (int i = 0; i < num; ++i) {
            this_thread::sleep_for(chrono::milliseconds(100));
            cout.put(c).flush();
        }
    }
    catch (const exception& e) {
        cerr << "EXCEPTION in thread " << this_thread::get_id()  << ": " << e.what() << endl;
    }
}

int main()
{
    try {
        // start one thread to query a number
        shared_future<int> f = async(get_number);

        // start three threads each processing this number in a loop
        auto f1 = async(launch::async, print_chars, '.', f);
        auto f2 = async(launch::async, print_chars, '+', f);
        auto f3 = async(launch::async, print_chars, '*', f);

        // wait for all loops to be finished
        f1.get();
        f2.get();
        f3.get();
    }
    catch (const exception& e) {
        cout << "\nEXCEPTION: " << e.what() << endl;
    }
    cout << "\ndone\n";
}
