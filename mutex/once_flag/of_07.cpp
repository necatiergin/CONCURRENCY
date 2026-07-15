#include <iostream>
#include <mutex>
#include <string>

class Logger {
public:
    void write(const std::string& msg)
    {
        std::cout << "[LOG] " << msg << '\n';
    }
};

std::once_flag logger_init_flag;
Logger* global_logger = nullptr;

void init_logger()
{
    global_logger = new Logger;
    std::cout << "Logger initialized\n";
}

void log_message(const std::string& msg)
{
    std::call_once(logger_init_flag, init_logger);
    global_logger->write(msg);
}
