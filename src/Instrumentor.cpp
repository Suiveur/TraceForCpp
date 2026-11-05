#include "Instrumentor.h"
#include <algorithm>
#include <sstream>


Instrumentor::Instrumentor()
    : m_CurrentSession(nullptr), m_ProfileCount(0) {
}

void Instrumentor::BeginSession(const std::string& name, const std::string& filepath) {
    m_OutputStream.open(filepath);
    if (m_OutputStream.is_open()) {
        m_CurrentSession = new InstrumentationSession{ name };
        m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
        m_OutputStream.flush();
    }
}

void Instrumentor::EndSession() {
    if (m_CurrentSession) {
        m_OutputStream << "]}";
        m_OutputStream.flush();
        m_OutputStream.close();
        delete m_CurrentSession;
        m_CurrentSession = nullptr;
        m_ProfileCount = 0;
    }
}

void Instrumentor::WriteProfile(const ProfileResult& result) {
    std::stringstream ss;
    if (m_CurrentSession) {
        if (m_ProfileCount++ > 0) {
            ss << ",";
        }

        std::string name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\''); // replace quotes in name to prevent JSON errors
        ss << "{";
        ss << "\"cat\":\"function\",";
        ss << "\"dur\":" << (result.End - result.Start) << ',';
        ss << "\"name\":\"" << name << "\",";
        ss << "\"ph\":\"X\",";
        ss << "\"pid\":" << result.ProcessID << ",";
        ss << "\"tid\":" << result.ThreadID << ",";
        ss << "\"ts\":" << result.Start;
        ss << "}";

        std::unique_lock<std::mutex> lock(m_Mutex); // Lock the mutex for thread-safe writing
        m_OutputStream << ss.str();
        m_OutputStream.flush();
        lock.unlock(); // Unlock the mutex after writing
    }
}

Instrumentor& Instrumentor::Get() {
    static Instrumentor* instance = new Instrumentor();
    return *instance;
}