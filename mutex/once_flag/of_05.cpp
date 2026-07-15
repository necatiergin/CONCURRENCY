#include <iostream>
#include <mutex>
#include <syncstream>
#include <vector>
#include <fstream>

class Singleton {
public:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	static Singleton* get_instance()
	{
		call_once(m_init_flag, Singleton::init);

		return m_instance;
	}

	static void init()
	{
		m_instance = new Singleton();
	}
private:
	inline static std::once_flag m_init_flag{};
	inline static Singleton* m_instance{};
	Singleton() = default;
};


void func()
{
	std::osyncstream{ std::cout } << Singleton::get_instance() << '\n';
}

int main()
{
	std::vector<std::jthread> tvec;
	for (int i = 0; i < 100; ++i) {
		tvec.emplace_back(func);
	}

}
