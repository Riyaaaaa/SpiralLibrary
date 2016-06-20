
#ifndef Timer_hpp
#define Timer_hpp

#include "Macro.h"
#include <chrono>

class Timer {
public:
    Timer(bool isClockStart = true) {
        if(isClockStart) {
            isClock = true;
            _startTime = std::chrono::system_clock::now();
        }
    }
    
    void start() {
        isClock = true;
        _startTime = std::chrono::system_clock::now();
    }
    
    template<class Duration>
    Duration elapsedTime();
    
    template<class Duration>
    Duration end();
    
private:
    bool isClock;
    std::chrono::system_clock::time_point _startTime;
};

template<class Duration>
Duration Timer::elapsedTime() {
    if(isClock) {
        return std::chrono::duration_cast<Duration>(std::chrono::system_clock::now() - _startTime);
    }
    return std::chrono::duration_cast<Duration>(std::chrono::system_clock::now() - std::chrono::system_clock::now());
}

template<class Duration>
Duration Timer::end() {
    if(isClock) {
        isClock = false;
        return std::chrono::duration_cast<Duration>(std::chrono::system_clock::now() - _startTime);
    }
    return std::chrono::duration_cast<Duration>(std::chrono::system_clock::now() - std::chrono::system_clock::now());
}

#endif /* Timer_hpp */
