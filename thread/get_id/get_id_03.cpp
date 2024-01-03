#include <thread>
#include <iostream>

std::thread::id main_thread_id;

void func()
{
	//func'ın hangi thread'den çağrıldığına bağlı olarak farklı işler yapılıyor
	if (std::this_thread::get_id() == main_thread_id) {
		std::cout << "cagri main thread'den yapildi\n";
	}
	else {
		std::cout << "cagri ikincil threadlerden yapildi\n";
	}

}

int main()
{
	main_thread_id = std::this_thread::get_id();

	func();

	std::thread t{ func };
	t.join();
}
