#define CATCH_CONFIG_MAIN

#include <iostream>
#include <chrono>
#include <ctime>

#include "catch.hpp"
#include "../time_utils/time_cast.hpp"

TEST_CASE("Time conversions are correct", "[time_cast]") {
    using time_utils::time_cast;
    using chrono_time = std::chrono::time_point<std::chrono::system_clock>;

    std::time_t time_t_time = 1459439688;
    std::chrono::time_point<std::chrono::system_clock> chrono_time_time = std::chrono::system_clock::from_time_t(time_t_time);
    std::string str_time("Thu Mar 31 17:54:48 2016"); // format "%c"

    SECTION("std::chrono::time_point to std::string") {
        REQUIRE(time_cast<std::string>(chrono_time_time)("%x %X") == "03/31/16 17:54:48");
    }

    SECTION("std::string to std::string") {
        REQUIRE(time_cast<std::string>(str_time, "%c")("%x %X") == "03/31/16 17:54:48");
    }

    SECTION("std::time_t to std::string") {
        REQUIRE(time_cast<std::string>(time_t_time)("%c") == "Thu Mar 31 17:54:48 2016");
    }

    SECTION("std::time_t to std::chrono::time_point") {
        REQUIRE(time_cast<chrono_time>(time_t_time)() == chrono_time_time);
    }

    SECTION("std::string to std::chrono::time_point") {
        REQUIRE(time_cast<chrono_time>(str_time, "%c")() == chrono_time_time);
    }

    SECTION("std::string to std::time_t") {
        REQUIRE(time_cast<std::time_t>(str_time, "%c")() == 1459439688);
    }

    SECTION("std::chrono::time_point to std::time_t") {
        REQUIRE(time_cast<std::time_t>(chrono_time_time)() == 1459439688);
    }

}
