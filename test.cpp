#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>
#include <iostream>

using chrono_time = std::chrono::time_point<std::chrono::system_clock>;

// TimeProxy
template <typename T>
class TimeProxy {
};

template <>
class TimeProxy<std::string> {
public:
    TimeProxy(std::time_t time) : _time(time) {}
    std::string operator()(const char* format) {
        std::stringstream ss;
        ss << std::put_time(std::localtime(&_time), format);
        return ss.str();
    }
private:
    std::time_t _time;
};

template <>
class TimeProxy<chrono_time> {
public:
    TimeProxy(std::time_t time) : _time(time) {}
    chrono_time operator()() {
        return std::chrono::system_clock::from_time_t(_time);
    }
private:
    std::time_t _time;
};

template <>
class TimeProxy<std::time_t> {
public:
    TimeProxy(std::time_t time) : _time(time) {}
    std::time_t operator()() {
        return _time;
    }
private:
    std::time_t _time;
};

// time_cast
template <typename Out, typename In>
TimeProxy<Out> time_cast(In in);

template <typename Out>
TimeProxy<Out> time_cast(std::string in, const char* format) {
    // read in to std::time_t
    struct tm bk_time;  
    strptime(in.c_str(), format, &bk_time);
    std::time_t time = mktime(&bk_time);
    return TimeProxy<Out>(time);
}

template <typename Out>
TimeProxy<Out> time_cast(std::time_t time) {
    // pass time_t directly
    return TimeProxy<Out>(time);
}

template <typename Out>
TimeProxy<Out> time_cast(chrono_time in) {
    // read in to std::time_t
    std::time_t time = std::chrono::system_clock::to_time_t(in);
    return TimeProxy<Out>(time);
}

// tests

int main() {
    chrono_time tmp, now = std::chrono::system_clock::now();
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

































