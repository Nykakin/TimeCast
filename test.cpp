#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>
#include <iostream>

template <typename T>
class TimeProxy {
public:
    TimeProxy(time_t time) : _time(time) {}
    T operator()(const char* format) {
        std::stringstream ss;
        ss << std::put_time(std::localtime(&_time), format);
        return ss.str();
    }
private:
    time_t _time;
};

template <typename Out, typename In>
TimeProxy<Out> time_cast(In in) {
    // read in to time_t
    time_t time = std::chrono::system_clock::to_time_t(in);

    return TimeProxy<Out>(time);
}

int main() {
    auto now = std::chrono::system_clock::now();

    std::cout << time_cast<std::string>(now)("%c") << std::endl;    // Thu Mar 31 16:10:19 2016
    std::cout << time_cast<std::string>(now)("%x %X") << std::endl; // 03/31/16 16:10:19
}
