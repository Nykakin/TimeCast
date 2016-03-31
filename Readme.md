# TimeCast

TimeCast is a simple. header-only helper library for conversion between C++ time formats, especially from and to std::string.

### Version
0.0.1

### Using

To cast one time to another use `time_utils::time_cast` template function, passing target type as a template argument. The input type will be deduced:

```C++
time_utils::time_cast<output_type>(input_time)();
```
Following types are supported:
* `std::string`
* `std::time_t`
* `std::chrono::time_point<std::chrono::system_clock>`

In order to read strings you also have to pass [strftime format](http://man7.org/linux/man-pages/man3/strftime.3.html) inside first pair of parentheses:

```C++
time_utils::time_cast<std::time_t>(input_string, "%T")();
```

In order to write to strins you have to pass format string in second pair of parentheses:

```C++
time_utils::time_cast<std::string>(input_data)(%t)
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
