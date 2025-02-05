#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <syncstream>


using namespace std::literals;

class DatabaseConnection {
public:
    DatabaseConnection() 
    {
        m_os << "Thread " << std::this_thread::get_id() << ": Database Connection Established\n";
    }

    ~DatabaseConnection() {
        m_os << "Thread " << std::this_thread::get_id() << ": Database Connection Closed\n";
    }

    void executeQuery(const std::string& query) 
    {
        m_os << "Thread " << std::this_thread::get_id() << ": Executing Query - " << query << '\n';
        std::this_thread::sleep_for(100ms);  
    }
private:
    std::osyncstream m_os{ std::cout };
};


thread_local DatabaseConnection db_connection;

void worker(int thread_id) 
{
    db_connection.executeQuery("SELECT * FROM users WHERE id = " + std::to_string(thread_id));
    db_connection.executeQuery("UPDATE users SET last_login = NOW() WHERE id = " + std::to_string(thread_id));
}

int main() 
{
    constexpr int num_threads = 4;

    std::vector<std::jthread> tvec;


    for (int i = 0; i < num_threads; ++i) {
        tvec.emplace_back(worker, i);
    }
}
