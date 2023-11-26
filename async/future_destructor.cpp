#include <future>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

using namespace std;
using namespace literals;

void work_task()
{
	this_thread::sleep_for(5s);
	cout << "work_task produced the result\n";
}

void foo()
{
	cout << "calling async function\n";
	auto result = std::async(launch::async, work_task);
}

int main()
{
	foo();
	cout << "work_task started\n";
}
