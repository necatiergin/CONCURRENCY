#include <condition_variable>
#include <thread>
#include <iostream>

std::mutex mtx;
bool g_data_ready = false;
int g_data{};
std::condition_variable g_cv;

void producer()
{
	for (int i = 0; i < 10; ++i) {
		std::unique_lock ulock{ mtx };
		g_data = (i + 1) * 20;
		g_data_ready = true;
		g_cv.notify_one();
		g_cv.wait(ulock, [] {return !g_data_ready; });
	}
}

void consumer()
{
	std::this_thread::sleep_for(std::chrono::milliseconds{ 200 });
	for (int i = 0; i < 10; ++i) {
		std::unique_lock ulock(mtx);
		g_cv.wait(ulock, [] {return g_data_ready; });
		std::cout << g_data << '\n';
		g_data_ready = false;
		g_cv.notify_one();
	}
}

int main()
{
	std::jthread t_pro{ producer };
	std::jthread t_con{ consumer};
}
