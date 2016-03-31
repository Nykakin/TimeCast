#include <iostream>
#include <chrono>
#include <ctime>

#include "time_utils/time_cast.hpp"

// tests

using time_utils::time_cast;
using chrono_time = std::chrono::time_point<std::chrono::system_clock>;

int main() {
    std::chrono::time_point<std::chrono::system_clock> tmp, now = std::chrono::system_clock::now();
    std::string str_time("Thu Mar 31 16:10:19 2016"); // format "%c"
    std::time_t time_t_time = time(NULL);

    // std::chrono::time_point to std::string
    std::cout << time_cast<std::string>(now)("%x %X") << std::endl; // 03/31/16 17:03:10
    std::cout << std::endl;


    // std::string to std::string
    std::cout << time_cast<std::string>(str_time, "%c")("%x %X") << std::endl; // 03/31/16 16:10:19
    std::cout << std::endl;

    // std::string to std::chrono::time_point
    tmp = time_cast<chrono_time>(str_time, "%c")();
    std::cout << time_cast<std::string>(tmp)("%x %X") << std::endl; // 03/31/16 16:10:19
    std::cout << std::endl;

    // std::time_t to std::string
    std::cout << time_cast<std::string>(time_t_time)("%c") << std::endl; // Thu Mar 31 17:03:10 2016
    std::cout << std::endl; 

    // std::time_t to std::chrono::time_point
    tmp = time_cast<chrono_time>(time_t_time)();
    std::cout << time_cast<std::string>(tmp)("%x %X") << std::endl; // 03/31/16 17:03:10
    std::cout << std::endl;  

    // std::string to std::time_t
    std::cout << time_cast<std::time_t>(str_time, "%c")() << std::endl; // 1459433419
    std::cout << std::endl;

    // std::chrono::time_point to std::time_t
    std::cout << time_cast<std::time_t>(now)() << std::endl; // 1459439087
    std::cout << std::endl;
}

































