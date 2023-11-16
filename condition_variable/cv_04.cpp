#include <mutex>
#include <vector>
#include <condition_variable>
#include <thread>
#include <iostream>

class IStack {
public:
	IStack() {};
	IStack(const IStack&) = delete;
	IStack& operator=(const IStack&) = delete;

	int pop()
	{
		std::unique_lock lock(m_);
		m_cv.wait(lock, [this]() {return !m_vec.empty(); });
		int val = m_vec.back();
		m_vec.pop_back();
		return val;
	}
	void push(int x)
	{
		std::scoped_lock lock(m_);
		m_vec.push_back(x);	
		m_cv.notify_one(); 
	}
private:
	std::vector<int> m_vec;
	mutable std::mutex m_;
	mutable std::condition_variable m_cv;
};

constexpr int n = 1000;
IStack s;

void producer()
{
	for (int i = 0; i < n; ++i)
		s.push(2 * i + 1);
}

void consumer()
{
	for (int i = 0; i < n; ++i)
		std::cout << s.pop() << '\n';
}

int main()
{
	std::thread th1(producer);
	std::thread th2(consumer);
	th1.join();
	th2.join();
}
