#ifndef __TIMER_H__
#define __TIMER_H__

#include <windows.h>

class MyTimer {
private:
    int _freq;
    LARGE_INTEGER _begin;
    LARGE_INTEGER _end;
    double costTime;

public:
    MyTimer() {
        LARGE_INTEGER tmp;
		QueryPerformanceFrequency(&tmp);

		_freq = tmp.QuadPart;
		costTime = 0;
	}

    void start() {
        QueryPerformanceCounter(&_begin);
	}

    void end() {
	    QueryPerformanceCounter(&_end);
	    costTime = (_end.QuadPart-_begin.QuadPart)*1.0/_freq;
	}

    void reset() {
	    costTime = 0;
	}

    double used() {
	    return costTime;
	}
};
#endif
