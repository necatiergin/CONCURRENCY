#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>
#include <iomanip>

using namespace std;
using namespace chrono;

string				shared_data;
mutex				mtx;
condition_variable	cv;

void reader()
{
	cout << "READER thread is locking the mutex\n";
	unique_lock ulock(mtx);
	cout << "READER thread has locked the mutex\n";
	cout << "READER thread sleeping...\n";
	cv.wait(ulock);

	cout << "READER thread wakes up\n";
	cout << "Data is " << std::quoted(shared_data) << '\n';
}


void writer()
{
	{
		cout << "WRITER thread is locking mutex\n";
		lock_guard lg(mtx);
		this_thread::sleep_for(2s); //!!

		cout << "WRITER thread has locked the mutex\n";
		cout << "WRITER thread is modifying the data...\n";
		shared_data = "shared data is ready now";
	}

	cout << "WRITER thread is sending notification\n";
	cv.notify_one();
}

int main()
{
	shared_data = "data is not ready yet";

	cout << std::quoted(shared_data) << '\n';

	jthread write(writer);
	this_thread::sleep_for(500ms);
	jthread read(reader);
}
