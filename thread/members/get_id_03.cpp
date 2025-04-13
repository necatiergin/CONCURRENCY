#include <thread>
#include <iostream>

std::thread::id main_thread_id;

void func()
{
	//func'ın hangi thread'den çağrıldığına bağlı olarak farklı işler yapılıyor
	if (std::this_thread::get_id() == main_thread_id) {
		std::cout << "call from the main thread\n";
	}
	else {
		std::cout << "call from a child thread\n";
	}
}

int main()
{
	main_thread_id = std::this_thread::get_id();

	func();

	std::thread t{ func };
	t.join();
}
