#include <mutex>

class A {
	//...
};

A* gpa{ nullptr };

std::mutex lazy_init_mtx;

void foo()
{
	lazy_init_mtx.lock();
	if (!gpa) {		   //thread-safe but costly
		gpa = new A;
	}
	lazy_init_mtx.unlock();
	//...
	
}
