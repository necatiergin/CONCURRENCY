//notify_all

#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>
#include <iomanip>

using namespace std::chrono;


std::string shared_data;
std::mutex mtx;
std::condition_variable cv;
bool ready_flag{ false };


void reader()
{
	auto id = std::this_thread::get_id();
	std::cout << "reader thread " << id << " is locking the mutex\n";
	std::unique_lock ulock(mtx);
	std::cout << "reader thread " << id  << " has locked the mutex\n";
	std::cout << "reader thread " << id  << " has locked the mutex\n";
	
	std::cout << "Reader thread start sleeping...\n";
	cv.wait(ulock, [] {return ready_flag; });
	std::cout << "Reader thread " << id << " wakes up\n";
	std::cout << "Data is " << std::quoted(shared_data) << '\n';
	std::cout << "Reader thread unlocks the mutex\n";
}

void writer()
{
	{
		std::cout << "Writer thread locking mutex\n";
		std::lock_guard lock(mtx);
		std::cout << "Writer thread has locked the mutex\n";
		std::this_thread::sleep_for(2s);
		std::cout << "Writer thread modifying data...\n";
		shared_data = "necati ergin";
		ready_flag = true;
		std::cout << "Writer thread unlocks the mutex\n";
	}

	std::cout << "Writer thread sends notification\n";

	cv.notify_all();
}

int main()
{
	shared_data = "not ready";
	std::cout << "data is " << std::quoted(shared_data) << '\n';

	std::jthread tw(writer);
	std::jthread tr1(reader);
	std::this_thread::sleep_for(20ms);
	std::jthread tr2(reader);
	std::this_thread::sleep_for(20ms);
	std::jthread tr3(reader);
	std::this_thread::sleep_for(20ms);
}
