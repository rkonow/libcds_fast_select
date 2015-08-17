/* TestPerf.cpp
 * Copyright (C) 2012, Francisco Claude, Rodrigo Canovas and Roberto Konow all rights reserved.
 *
 * Timer Class
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef SRC_UTIL_TIMER_H_
#define SRC_UTIL_TIMER_H_

#include <sys/resource.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <ctime>

class Timer {
public:
    /** Creates and starts the timer.
    */
    Timer() {
        Restart();
    }

    /** Restarts the timer.
    */
    void Restart() {
        wstart_ = std::chrono::high_resolution_clock::now();
        getrusage(RUSAGE_SELF, &ru_);
        cstart_ = ru_.ru_utime;
    }

    /** Stops the timer.
    */
    void Stop() {
        wend_ = std::chrono::high_resolution_clock::now();
        getrusage(RUSAGE_SELF, &ru_);
        cend_ = ru_.ru_utime;
    }

    // * Computes the number of microsecond elapsed from start to stop
    //  * This time is for wall-clock time
    double ElapsedTime() {
        std::chrono::nanoseconds duration = wend_ - wstart_;
        return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    }

    /** Computes the number of microsecond elapsed from start to stop
    * This time is for  process CPU usage
    */
    double ElapsedTimeCPU() {
        return (cend_.tv_sec - cstart_.tv_sec) * 1000000 + (cend_.tv_usec - cstart_.tv_usec);
    }

protected:
    std::chrono::high_resolution_clock::time_point wstart_, wend_;
    struct timeval cstart_, cend_;
    struct rusage ru_;
};

#endif  // SRC_UTIL_TIMER_H_
