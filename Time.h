/*#############################################################################
#
#  Class:      	Algorithms
#  Project:   	Interval_Scheduling
#  File:        Time.h
#  Authors:     Nicholas Mirolli, Morgan Willis
#  Emails:      ndm28@zips.uakron.edu, mtw16@zips.uakron.edu
#
#############################################################################*/

#ifndef TIME_H
#define	TIME_H

#include <cassert>
#include <cstdlib>
#include <iomanip>

using namespace std;

class Time {
    private:
        short hour;
        short minute;
    public:
        Time() {
            hour = 0;
            minute = 0;
        }
        Time(short h, short m) {
            hour = h;
            minute = m;
            assert(hour < 24 && hour >= 0);
            assert(minute <= 59 && minute >= 0);
        }
        Time(const Time &t) {
            hour = t.getHour(); 
            minute = t.getMinute();
            assert(t.getHour() < 24 && t.getHour() >= 0);
            assert(t.getMinute() <= 59 && t.getMinute() >= 0);
        }

        short getHour() const { return hour; }
        short getMinute() const { return minute; }

        void setHour(const short h) { hour = h; }
        void setMinute(const short m) { minute = m; }
        
        void print() {
            cout << hour << ":" << setw(2) << setfill('0') << minute;
        }
};

bool operator==(Time a, Time b) {
            return((a.getHour() == b.getHour()) && (a.getMinute() == b.getMinute()));
        }

bool operator!=(Time a, Time b) {
    return !(a == b);
}

bool operator<(Time a, Time b) {
    if(a.getHour() < b.getHour()) { return true; }
    else if(a.getHour() == b.getHour()) { 
        if(a.getMinute() < b.getMinute()) { return true; }
        else { return false; }
    }
    else { return false; }
}

#endif	/* TIME_H */

