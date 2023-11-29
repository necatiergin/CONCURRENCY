#include <atomic>
#include <thread>
#include <iostream>

class AtomicCounter {
public:
	AtomicCounter() : m_c(0) {}
	AtomicCounter(int val) : m_c{val}{}
	int operator++() { return ++m_c; }
	int operator++(int) { return m_c++; }
	int operator--() { return --m_c; }
	int operator--(int) { return m_c--; }
	int get() const { return m_c.load(); }
	operator int()const { return m_c.load(); }
private:
	std::atomic<int> m_c;
};

AtomicCounter cnt;

void foo()
{
	for (int i = 0; i < 1'000'000; ++i) {
		++cnt;
	}
}


int main()
{
	std::thread ta[10];

	for (auto& th : ta)
		th = std::thread{ foo };
	
	for (auto& th : ta)
		th.join();

	std::cout << "cnt = " << cnt.get() << '\n';
	std::cout << "cnt = " << cnt << '\n';
}
