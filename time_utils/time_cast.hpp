#ifndef TIME_CAST_HPP
#define TIME_CAST_HPP

#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>

namespace time_utils {

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

}

#endif
