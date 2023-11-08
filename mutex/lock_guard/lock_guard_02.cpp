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
	
	std::cout << std::endl;
}


int main()
{
	auto ft1 = std::async(std::launch::async, print, "Necati Ergin");
	auto ft2 = std::async(std::launch::async, print, "Ahmet Aksoy");
	auto ft3 = std::async(std::launch::async, print, "Dogukan Yigit Polat");
	
	print("main thread");
}
