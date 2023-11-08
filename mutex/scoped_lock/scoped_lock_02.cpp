#include <iostream>
#include <mutex>
#include <thread>
#include <set>

class iset {
public:
	bool contains(int i) const
	{
		std::scoped_lock lock(m_mtx);
		return m_set.contains(i);
	}
	void add(int i) 
	{
		std::scoped_lock lock(m_mtx);
		m_set.insert(i);
	}
	
	std::size_t size()const
	{
		std::scoped_lock lock(m_mtx);
		return m_set.size();
	}

private:
	std::set<int> m_set;
	mutable std::mutex m_mtx;
};

iset s;

void foo()
{
	for (int i{}; i < 10'000; ++i)
	{
		s.add(2 * i);
	}
}

void bar()
{
	for (int i{}; i < 10'000; ++i)
	{
		s.add(2 * i + 1);
	}
}

int main()
{
	std::jthread t1(foo);
	std::jthread t2(bar);
	t1.join(); 
	t2.join();
	std::cout << s.size() << '\n';
}
