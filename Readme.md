# TimeCast

TimeCast is a simple header-only library for conversion between C++ time formats, especially from and to std::string.

### Version
0.0.1

### Using

To cast one time to another use `time_utils::time_cast` template function, passing target type as a template argument. The input type will be deduced:

```C++
output_type out = time_utils::time_cast<output_type>(input_time)();
```
Following types are supported:
* `std::string`
* `std::time_t`
* `std::chrono::time_point<std::chrono::system_clock>`

In order to read strings you also have to pass [strftime format string](http://man7.org/linux/man-pages/man3/strftime.3.html) inside first pair of parentheses:

```C++
std::time_t out = time_utils::time_cast<std::time_t>(input_string, "%T")();
```

In order to get strings strins you have to pass format string in second pair of parentheses:

```C++
std::string out = time_utils::time_cast<std::string>(input_data)("%t")
```

Instead of using strftime format strings you can use following definitions:

| Makro | strftime string        | Description |
| ----- |:----------------------:| ----------- |
| TIMECAST_HOUR           | "%H" | Hour, range 00-23
| TIMECAST_MINUTE         | "%M" | Minute, range 00-59
| TIMECAST_SECOND         | "%S" | Second, range 00-59
| TIMECAST_TIME           | "%T" | Time, format HH:MM:SS
| TIMECAST_SHORT_TIME     | "%R" | Time, format HH:MM
| TIMECAST_YEAR           | "%Y" | Year
| TIMECAST_MONTH          | "%m" | Month, range 01-12
| TIMECAST_DAY            | "%d" | Day, range 01-31
| TIMECAST_DATE           | "%F" | Date, format YY-MM-DD (ISO 8601)
| TIMECAST_LOCAL_TIME     | "%X" | Time, format of current locale
| TIMECAST_LOCAL_DATE     | "%x" | Date, format of current locale
| TIMECAST_LOCAL_DATETIME | "%c" | Datetime, format of current locale
| TIMECAST_EPOCH          | "%s" | Seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC)

These are defined in a separate header, time_utils/time_cast_definitions.hpp, to avoid definition pollution. Using the preprocessor allows an easy concatenation of string literals:

```C++
#include <iostream>

#include "time_utils/time_cast.hpp"
#include "time_utils/time_cast_definitions.hpp"

using time_utils::time_cast;
using chrono_time = std::chrono::time_point<std::chrono::system_clock>;

int main() {
    std::string str_time("1429443688"); // format "%c"

    std::cout << time_cast<std::string>(
        str_time,
        TIMECAST_EPOCH
    )(
        "Hour:" TIMECAST_HOUR ", minute:" TIMECAST_MINUTE
    ) << std::endl;
}
```
```bash
$ g++-5 test.cpp -o test -std=c++11
$ ./test
Hour:13, minute:41
```

### Example

```C++
#include <iostream>
#include <chrono>
#include <ctime>

#include "time_utils/time_cast.hpp"

using time_utils::time_cast;
using chrono_time = std::chrono::time_point<std::chrono::system_clock>;

int main() {
    std::time_t time_t_time = 1459439688;
    std::chrono::time_point<std::chrono::system_clock> tmp, now = std::chrono::system_clock::from_time_t(time_t_time);
    std::string str_time("Thu Mar 31 17:54:48 2016"); // format "%c"

    // std::chrono::time_point to std::string
    std::cout << time_cast<std::string>(now)("%x %X") << std::endl;
    std::cout << std::endl;

    // std::string to std::string
    std::cout << time_cast<std::string>(str_time, "%c")("%x %X") << std::endl;
    std::cout << std::endl;

    // std::string to std::chrono::time_point
    tmp = time_cast<chrono_time>(str_time, "%c")();
    std::cout << time_cast<std::string>(tmp)("%x %X") << std::endl;
    std::cout << std::endl;

    // std::time_t to std::string
    std::cout << time_cast<std::string>(time_t_time)("%c") << std::endl;
    std::cout << std::endl; 

    // std::time_t to std::chrono::time_point
    tmp = time_cast<chrono_time>(time_t_time)();
    std::cout << time_cast<std::string>(tmp)("%x %X") << std::endl;
    std::cout << std::endl;  

    // std::string to std::time_t
    std::cout << time_cast<std::time_t>(str_time, "%c")() << std::endl;
    std::cout << std::endl;

    // std::chrono::time_point to std::time_t
    std::cout << time_cast<std::time_t>(now)() << std::endl;
    std::cout << std::endl;
}

```

### License

MIT
