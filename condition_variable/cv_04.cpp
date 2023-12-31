#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>
#include <iomanip>


using namespace std;
using namespace chrono;

string				shared_data;
mutex				mtx;
condition_variable	        cv;
bool				cflag{ false };

void reader()
{
	cout << "READER thread is locking the mutex\n";
	unique_lock ulock(mtx);

	cout << "READER thread has locked the mutex\n";
	cout << "READER thread is going to sleep...\n";

	cv.wait(ulock, [] {return cflag; });

	cout << "READER thread wakes up\n";

	cout << quoted(shared_data) << '\n';
	cout << "Reader thread unlocks the mutex\n";
}

void writer()
{
	{
		cout << "WRITER thread is locking the mutex\n";

		scoped_lock slock(mtx);
		cout << "WRITER thread has locked the mutex\n";

		this_thread::sleep_for(2s);

		// Modify the string
		cout << "WRITER thread modifying data...\n";
		shared_data = "shared data is ready now";
		cflag = true;
		cout << "WRITER thread unlocks the mutex\n";
	}

	cout << "WRITER thread is sending a notification\n";
	cv.notify_one();
}

int main()
{
	shared_data = "not ready yet.";

	cout << "shared_data value is : " << quoted(shared_data) << '\n';

	jthread twriter(writer);
	this_thread::sleep_for(500ms);
	jthread treader(reader);
}
