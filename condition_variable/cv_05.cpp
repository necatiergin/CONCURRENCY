/*
#### lost wakeup

+ _condition_variable_ sınıfının _wait_ fonksiyonu sınıfın _notify_ fonksiyonu çağrılana kadar _thread_'i bloke eder.
+ eğer _writer thread_'de _notify_ fonksiyonu _reader thread_'deki _wait_ çağrısından daha önce gerçekleştirilirse 
+ bir sinyal _(notification)_ gönderilmiş olmasına karşın henüz beklemekte olan bir _thread_ yoktur.
+ bu durumda _reader thread_ hiçbir şekilde uyanamaz ve bloke olarak kalır.
+ bu duruma _lost-wakeup_ denir. 
*/

#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>
#include <iomanip>

std::string	shared_data;
std::mutex mtx;
std::condition_variable	cv;

using namespace std::chrono_literals;

void reader()
{
	std::cout << "READER thread is locking the mutex\n";
	std::unique_lock ulock(mtx);
	std::cout << "READER thread has locked the mutex\n";
	std::cout << "READER thread sleeping...\n";
	cv.wait(ulock);

	std::cout << "READER thread wakes up\n";
	std::cout << "Data is " << std::quoted(shared_data) << '\n';
}


void writer()
{
	{
		std::cout << "WRITER thread is locking mutex\n";
		std::lock_guard lg(mtx);
		std::this_thread::sleep_for(2s); //!!
		std::cout << "WRITER thread has locked the mutex\n";
		std::cout << "WRITER thread is modifying the data...\n";
		shared_data = "shared data is ready now";
	}

	std::cout << "WRITER thread is sending notification\n";
	cv.notify_one();
}

int main()
{
	shared_data = "data is not ready yet";

	std::cout << std::quoted(shared_data) << '\n';
	std::jthread write(writer);
	std::this_thread::sleep_for(500ms);
	std::jthread read(reader);
}
