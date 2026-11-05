#include "InstrumentationTimer.h"
#include "Instrumentor.h"
InstrumentationTimer::InstrumentationTimer(const char* name)
    : m_Name(name), m_Stopped(false) {
    m_StartPoint = std::chrono::high_resolution_clock::now();
}

void InstrumentationTimer::Stop() {
    if (!m_Stopped) {
        auto endPoint = std::chrono::high_resolution_clock::now();
        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id()); // Get the current thread ID
        uint32_t processID = getpid(); // Get the current process ID (platform-dependent)
        Instrumentor::Get().WriteProfile({ 
            m_Name, 
            std::chrono::time_point_cast<std::chrono::microseconds>(m_StartPoint).time_since_epoch().count(), 
            std::chrono::time_point_cast<std::chrono::microseconds>(endPoint).time_since_epoch().count(),
            threadID,
            processID
        });
        m_Stopped = true;
    }
}

InstrumentationTimer::~InstrumentationTimer() {
    Stop();
}
