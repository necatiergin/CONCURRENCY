#include <iostream>
#include <string>
#include <future>
#include <chrono>

using namespace std::chrono_literals;

int work()
{

	std::cout << "thread id = " << std::this_thread::get_id() << '\n';
	std::this_thread::sleep_for(3s);
	std::cout << "function work is returning...\n";
	return 444;
}

void foo(const std::string& policy = "default policy")
{
	std::future<int> result;

	if (policy == "async")
		result = std::async(std::launch::async, work);
	else if (policy == "deferred")
		result = std::async(std::launch::deferred, work);
	else
		result = std::async(work);

	std::cout << "async call policy is : " << policy << '\n';
	std::this_thread::sleep_for(2s);
	std::cout << "calling get() function\n";
	std::cout << "work result: " << result.get() << '\n';
}

int main()
{
	std::cout << "main thread id : " << std::this_thread::get_id() << '\n';

	foo("deferred");
	foo("async");
	foo("default");
}
