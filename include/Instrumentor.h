#pragma once
#include <fstream>
#include <string>
#include <mutex>

#include <thread>
#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#endif

#ifdef PROFILEING
#define BEGIN_SESSION(name, filepath) Instrumentor::Get().BeginSession(name, filepath)
#define END_SESSION() Instrumentor::Get().EndSession()
#else
#define BEGIN_SESSION(name, filepath)
#define END_SESSION()
#endif

struct ProfileResult {
    std::string Name;
    long long Start, End;   // in microseconds
    uint32_t ThreadID;
    uint32_t ProcessID; // Optional: you can add this if you want to track the process ID as well
};

struct InstrumentationSession {
    std::string m_Name;
};

class Instrumentor {
    public:
        Instrumentor(const Instrumentor&) = delete; // Delete copy constructor
        Instrumentor& operator=(const Instrumentor&) = delete; // Delete copy assignment operator
        void BeginSession(const std::string& name, const std::string& filepath = "results.json");
        void EndSession();
        void WriteProfile(const ProfileResult& result);
        static Instrumentor& Get();

    private:
        Instrumentor();
        InstrumentationSession* m_CurrentSession;
        std::ofstream m_OutputStream;
        int m_ProfileCount; // number of profiles written in the current session
        std::mutex m_Mutex; // mutex for thread-safe operations
};