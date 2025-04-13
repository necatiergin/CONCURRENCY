#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <shared_mutex>
#include <syncstream>
#include <fstream>

using namespace std::literals;

int cnt = 0;
std::shared_mutex mtx;

void writer()
{
	for (int i = 0; i < 10; ++i) {
		{
			std::scoped_lock lock(mtx);
			++cnt;
		}
		std::this_thread::sleep_for(100ms);
	}
}

void reader(int id, std::ofstream& ofs)
{
	for (int i = 0; i < 100; ++i) {
		int c;
		{
			std::shared_lock lock(mtx);
			c = cnt;
		}
		std::osyncstream{ ofs } << "thread id : " << id << "\t\t\t" << c << '\n';
		std::this_thread::sleep_for(10ms);
	}
}

int main()
{
	std::ofstream ofs{ "out.txt" };
	if (!ofs) {
		std::cerr << "out.txt dosyasi olusturulamadi\n";
		exit(EXIT_FAILURE);
	}

	std::vector<std::jthread> tvec;

	tvec.reserve(16);
	tvec.emplace_back(writer);

	for (int i = 0; i < 16; ++i)
		tvec.emplace_back(reader, i, std::ref(ofs));

}
