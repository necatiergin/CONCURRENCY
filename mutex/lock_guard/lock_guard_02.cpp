#include <future>
#include <mutex>
#include <iostream>
#include <string>

std::mutex print_mutex;

void print(const std::string& s)
{
	std::lock_guard<std::mutex> guard(print_mutex);

	for (char c : s) {
		std::cout.put(c);
	}

	std::cout << '\n';
}


int main()
{
	{
		std::jthread t1{ print, "necati ergin" };
		std::jthread t2{ print, "kaan aslan" };
		std::jthread t3{ print, "oguz karan" };
	}

	print("main thread");
}
