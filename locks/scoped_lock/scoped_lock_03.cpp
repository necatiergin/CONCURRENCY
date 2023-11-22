#include <iostream>
#include <mutex>
#include <thread>
#include <unordered_set>

class iset {
public:
	bool contains(int i) const 
	{
		std::scoped_lock lock(mtx);
		return mset.find(i) != mset.end();
	}

	void add(int i) 
	{
		std::scoped_lock lock(mtx);
		mset.insert(i);
	}
private:
	std::unordered_set<int> mset;
	mutable std::mutex mtx;
};

iset gset;

 int main() 
 {
	std::jthread t1([]() {
		for (int i = 0; i < 10'000; ++i) { 
			gset.add(2 * i); }
		});
	
	std::jthread t2([]() {
		for (int i = 0; i < 10'000; ++i) {
			gset.add(2 * i + 1); }
		});

	t1.join(); 
	t2.join();

	std::cout << std::boolalpha << gset.contains(1000) << '\n';
}
