
/*=============================================================================
 Copyright (c) 2011-2016 Riyaaaaa
 https://github.com/Riyaaaaa/SpiralLibrary
 Distributed under the Boost Software License, Version 1.0. (See accompanying
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

#ifndef Timer_hpp
#define Timer_hpp

#include "Macro.h"
#include <chrono>
#include <iostream>
#include <time.h>

NS_LIBSPIRAL_BEGIN

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
    
    double endSeconds() {
        if (isClock) {
            auto microSecounds = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - _startTime).count());
            return microSecounds / 1000000.0f;
        }
        return 0;
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

NS_LIBSPIRAL_END

#endif /* Timer_hpp */
