#include <thread>
#include <iostream>

int main()
{
	std::thread t;
	std::cout << std::boolalpha;

	std::cout << (t.get_id() == std::thread::id()) << '\n';
	t = std::thread([] {});
	std::cout << (t.get_id() == std::thread::id()) << '\n';
	auto th = std::move(t);
	std::cout << (t.get_id() == std::thread::id()) << '\n';
	std::cout << (th.get_id() == std::thread::id()) << '\n';
	th.join();
	std::cout << (th.get_id() == std::thread::id()) << '\n';
}
