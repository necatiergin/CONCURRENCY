#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>
#include <iomanip>

std::string	shared_data;
std::mutex	mtx;
std::condition_variable cv;
bool cflag{ false };

using namespace std::chrono_literals;

void reader()
{
	std::cout << "READER thread is locking the mutex\n";
	std::unique_lock ulock(mtx);

	std::cout << "READER thread has locked the mutex\n";
	std::cout << "READER thread is going to sleep...\n";

	cv.wait(ulock, [] {return cflag; });

	std::cout << "READER thread wakes up\n";
	std::cout << quoted(shared_data) << '\n';
	std::cout << "Reader thread unlocks the mutex\n";
}

void writer()
{
	{
		std::cout << "WRITER thread is locking the mutex\n";

		std::scoped_lock slock(mtx);
		std::cout << "WRITER thread has locked the mutex\n";

		std::this_thread::sleep_for(2s);

		// Modify the string
		std::cout << "WRITER thread modifying data...\n";
		shared_data = "shared data is ready now";
		cflag = true;
		std::cout << "WRITER thread unlocks the mutex\n";
	}

	std::cout << "WRITER thread is sending a notification\n";
	cv.notify_one();
}

int main()
{
	shared_data = "not ready yet.";

	std::cout << "shared_data value is : " << quoted(shared_data) << '\n';

	std::jthread twriter(writer);
	std::this_thread::sleep_for(500ms);
	std::jthread treader(reader);
}
