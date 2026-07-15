#include <iostream>
#include <mutex>
#include <string>

struct Config {
    std::string server_ip;
    int port;
};

std::once_flag config_flag;
Config config;

void load_config()
{
    std::cout << "Reading config file...\n";

    config.server_ip = "127.0.0.1";
    config.port = 8080;
}

Config get_config()
{
    std::call_once(config_flag, load_config);
    return config;
}
