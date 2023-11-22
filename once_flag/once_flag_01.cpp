#include <vector>
#include <thread>
#include <mutex>
#include <cassert>
#include <memory>

std::unique_ptr<int> uptr;
std::once_flag init_flag;

void f_init()
{
	uptr = std::make_unique<int>(656);
}

const int& get_value()
{
	std::call_once(init_flag, f_init);
	return *uptr;
}


void do_work()
{
	const int& v = get_value();
	assert(v == 656);
}

int main()
{
	std::vector<std::thread> tvec;
	tvec.reserve(16);

	for (int i{}; i < 16; ++i) {
		tvec.emplace_back(do_work);
	}

	for (auto& th : tvec) {
		th.join();
	}
}
