#define PROFILEING  // Enable profiling, if you want to disable profiling, comment out this line

#include <thread>
#include <ctime>
#include "testFunc.h"
#include "Instrumentor.h"

void runTest() {
    PROFILE_FUNCTION();
    std::cout << "runTest # " << std::endl;
    std::thread t1([]() {function1();});
    std::thread t2([]() {function2();});
    t1.join();
    t2.join();
}

std::string generate_filename(std::string prefix) {
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm *localtime_result = std::localtime(&now_time_t); // Convert to local time
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "_%Y%m%d%H%M%S", localtime_result);

    return prefix.replace(prefix.find_last_of('.'), 0, buffer);
}

int main() {
    BEGIN_SESSION("PROFILE", generate_filename("results.json"));
    runTest();
    END_SESSION();
    return 0;
}