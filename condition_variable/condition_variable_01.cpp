#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>
#include <format>

using namespace std;
using namespace literals;

string	shared_data{};
bool	update_flag{ false };
bool	completed_flag{ false };
mutex	data_mutex;
mutex	completed_mutex;


void receive_data()
{
	for (int i = 0; i < 10; ++i) {
		cout << "receive data thread is waiting for data..." << '\n';
		this_thread::sleep_for(1s);

		scoped_lock shared_data_lock(data_mutex);
		shared_data += format("chunk{:<2} ", i);
		cout << shared_data << '\n';
		update_flag = true;
	}

	cout << "receiving data operation has ended\n";

	scoped_lock completed_lock(completed_mutex);
	completed_flag = true;
}

void display_progress()
{
	while (true) {
		cout << "display progress thread waiting for data...\n";

		unique_lock shared_data_lock(data_mutex);
		while (!update_flag) {
			shared_data_lock.unlock();
			this_thread::sleep_for(20ms);
			shared_data_lock.lock();
		}

		update_flag = false;
		shared_data_lock.unlock();

		cout << "received " << shared_data.length() << " bytes so far\n";

		lock_guard completed_lock(completed_mutex);
		if (completed_flag) {
			cout << "display_progress thread has ended\n";
			break;
		}
	}
}

void process_data()
{
	cout << "process data thread waiting for data...\n";

	unique_lock completed_lock(completed_mutex);

	while (!completed_flag) {
		completed_lock.unlock();
		this_thread::sleep_for(10ms);
		completed_lock.lock();
	}

	completed_lock.unlock();

	lock_guard shared_data_lock(data_mutex);
	cout << "processing shared_data: " << shared_data << '\n';
	// ...	
}

int main()
{
	jthread receiver(receive_data);
	jthread progress(display_progress);
	jthread processor(process_data);
}
