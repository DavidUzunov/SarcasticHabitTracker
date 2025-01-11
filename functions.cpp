#include <iostream>
#include <ctime>

#include "functions.h"

int main() {
    time_t now = time(0);
    tm* localTime = localtime(&now);

    std::cout << "Year: " << 1900 + localTime->tm_year << std::endl;
    std::cout << "Month: " << 1 + localTime->tm_mon << std::endl;
    std::cout << "Day: " << localTime->tm_mday << std::endl;
    std::cout << "Hour: " << localTime->tm_hour << std::endl;
    std::cout << "Minute: " << localTime->tm_min << std::endl;
    std::cout << "Second: " << localTime->tm_sec << std::endl;

    return 0;
}string x = "blah blah blah";
print(heloworld);