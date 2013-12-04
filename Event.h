/*#############################################################################
#
#  Class:      	Algorithms
#  Project:   	Interval_Scheduling
#  File:        Event.h
#  Authors:     Nicholas Mirolli, Morgan Willis
#  Emails:      ndm28@zips.uakron.edu, mtw16@zips.uakron.edu
#
#############################################################################*/

#ifndef EVENT_H
#define	EVENT_H

#include "Time.h"

using namespace std;

class Event {
    private:
        string name;
        Time startTime;
        Time endTime;
    public:
        Event() {
            name = "Default";
        }
        Event(string n, Time s, Time e, double p) { 
            name = n;
            startTime = s;
            endTime = e;
            assert(name != "");
        }

        string getName() const { return name; }
        Time getStartTime() const { return startTime; }
        Time getEndTime() const { return endTime; }
        
        void setName(const string n) { name = n; }
        void setStartTime(const Time s) { startTime = s; }
        void setStartTime(const short h, const short m) {
            Time s;
            s.setHour(h);
            s.setMinute(m);
            startTime = s;
        } 
        void setEndTime(const Time e) { endTime = e; }
        void setEndTime(const short h, const short m) {
            Time e;
            e.setHour(h);
            e.setMinute(m);
            endTime = e;
        }
        void print() {
            cout << name << " ";
            startTime.print();
            cout << " ";
            endTime.print();
            cout << endl;
        }
};

bool operator==(Event a, Event b) {
    return((a.getName() == b.getName()) &&
    (a.getStartTime() == b.getStartTime()) &&
    (a.getEndTime() == b.getEndTime()));
}

bool operator!=(Event a, Event b) {
    return !(a == b);
}

#endif	/* EVENT_H */

