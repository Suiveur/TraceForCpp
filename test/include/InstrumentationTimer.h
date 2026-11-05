#pragma once
#include <chrono>
#include <string>

#ifdef PROFILEING

#ifdef MSC_VER
#define __PRETTY_FUNCTION__ __FUNCSIG__ // MSVC does not support __PRETTY_FUNCTION__,
                                        // but it has __FUNCSIG__ which is similar
#endif

#define PROFILE_SCOPE(name) InstrumentationTimer timer##__FILE__##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__PRETTY_FUNCTION__)

#else
#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION()

#endif


class InstrumentationTimer {
    public:
        InstrumentationTimer(const char* name);
        ~InstrumentationTimer();
        void Stop();
    private:
        const char* m_Name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartPoint;
        bool m_Stopped;
};

