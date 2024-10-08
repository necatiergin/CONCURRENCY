#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <string>

using namespace std::literals;

std::string str_data;
bool progress_flag{ false };
bool is_completed{ false };

std::mutex mtx_data;
std::mutex mtx_completed;

std::condition_variable cv_data;
std::condition_variable cv_completed;

void receive_data()
{
	for (int i = 0; i < 10; ++i) {
		std::cout << "Fetcher thread waiting for data...\n";
		std::this_thread::sleep_for(1s);
		std::unique_lock ulock(mtx_data);
		str_data += "Block" + std::to_string(i + 1);
		if (i != 9)
			str_data += '-';
		std::cout << "str_data: " << str_data << '\n';
		progress_flag = true;
		ulock.unlock();
		cv_data.notify_all();
	}

	std::cout << "receiving data has ended\n";

	std::lock_guard lock(mtx_completed);
	is_completed = true;
	cv_completed.notify_all();
}

void progress_bar()
{
	size_t len = 0;

	while (true) {
		std::cout << "Progress bar thread waiting for data...\n";
		std::unique_lock<std::mutex> data_lck(mtx_data);
		cv_data.wait(data_lck, [] { return progress_flag; });
		len = str_data.size();

		progress_flag = false;
		data_lck.unlock();

		std::cout << "Received " << len << " bytes so far\n";

		std::unique_lock<std::mutex> compl_lck(mtx_completed);

		if (cv_completed.wait_for(compl_lck, 10ms, [] { return is_completed; })) {
			std::cout << "Progress bar thread has ended\n";
			break;
		}
	}
}

void process_data() 
{
	std::this_thread::sleep_for(200ms);
	std::cout << "Processing thread waiting for data...\n";

	std::unique_lock compl_lck(mtx_completed); 

	cv_completed.wait(compl_lck, [] { return is_completed; });
	compl_lck.unlock();

	std::lock_guard<std::mutex> data_lck(mtx_data);
	std::cout << "Processing str_data: " << str_data << '\n';

	// Process the data...
}

int main()
{
	std::jthread th_fetch(receive_data);
	std::jthread th_prog(progress_bar);
	std::jthread th_process(process_data);
}
