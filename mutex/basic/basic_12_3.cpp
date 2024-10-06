#include <mutex>

class A {
	//...
};

A* gpa{ nullptr };

std::mutex lazy_init_mtx;

void foo()
{
	if (!gpa) {		//not-thread_safe
		lazy_init_mtx.lock();
		gpa = new A;
		lazy_init_mtx.unlock();
	}
	//...
}
