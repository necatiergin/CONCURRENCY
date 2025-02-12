#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>
#include <syncstream>

using namespace std::literals;

std::string str_data;

bool progress_flag{ false };
bool is_completed{ false };


std::mutex mtx_data;
std::mutex mtx_completed;

// Data fetching thread
void receive_data()
{
	for (int i = 0; i < 10; ++i) {
		std::cout << "receiver thread waiting for data...\n";
		std::this_thread::sleep_for(1s);
		std::lock_guard lock(mtx_data);
		str_data += "Block" + std::to_string(i + 1);
		if (i != 9)
			str_data += '-';
		std::cout << "str_data: " << str_data << '\n';
		progress_flag = true;
	}

	std::cout << "Fetch str_data has ended\n";
	std::lock_guard completed_lck(mtx_completed);
	is_completed = true;
}

void progress_bar()
{
	size_t len = 0;

	while (true) {
		std::cout << "Progress bar thread waiting for data...\n";
		std::unique_lock dlock(mtx_data);
		while (!progress_flag) {
			dlock.unlock();
			std::this_thread::sleep_for(10ms);
			dlock.lock();
		}

		len = str_data.size();
		progress_flag = false;
		dlock.unlock();

		std::cout << "Received " << len << " bytes so far\n";

		std::lock_guard completed_lock(mtx_completed);
		if (is_completed) {
			std::cout << "Progress bar thread has ended\n";
			break;
		}
	}
}

void process_data()
{
	std::cout << "Processing thread waiting for data...\n";

	// Wait until the download is complete
	std::unique_lock completed_lck(mtx_completed);
	while (!is_completed) {
		completed_lck.unlock();
		std::this_thread::sleep_for(10ms);
		completed_lck.lock();
	}

	completed_lck.unlock();

	std::lock_guard data_lck(mtx_data);
	std::cout << "Processing the data received: \n";
	std::cout << "[" << str_data << "]\n";
}

int main()
{
	std::jthread th_fetch(receive_data);
	std::jthread th_prog(progress_bar);
	std::jthread th_process(process_data);
}
