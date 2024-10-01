#include <iostream>
#include <string>
#include <future>

using namespace std;

int work()
{
	cout << "thread id = " << this_thread::get_id() << '\n';
	this_thread::sleep_for(3s);
	cout << "function work is returning...\n";
	return 444;
}

void foo(const string& policy = "default policy")
{
	future<int> result;

	if (policy == "async")
		result = std::async(std::launch::async, work);
	else if (policy == "deferred")
		result = std::async(std::launch::deferred, work);
	else
		result = std::async(work);

	cout << "async call policy is : " << policy;
	this_thread::sleep_for(2s);
	cout << "calling get() function\n";
	cout << "work result: " << result.get() << '\n';
}

int main()
{
	cout << "main thread id : " << this_thread::get_id() << '\n';

	foo("deferred");
	foo("async");
	foo("default");
}
