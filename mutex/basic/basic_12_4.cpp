//double checked locking

#include <mutex>

class A {
	//...
};

A* gpa{ nullptr };

std::mutex lazy_init_mtx;

void foo()
{
	if (!gpa) {		
		lazy_init_mtx.lock();
		if (!gpa)
			gpa = new A; //thread-safe since C++17 
		lazy_init_mtx.unlock();
	}
	//...
	
}
