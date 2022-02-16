#include "TimeCode.h"
#include <iostream>

using namespace std;

TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec) {
    t = ComponentsToSeconds(hr, min, sec);
}

TimeCode::TimeCode(const TimeCode& tc) {
    t = tc.GetTimeCodeAsSeconds();
}

void TimeCode::SetHours(unsigned int hours) {
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec);
    t = ComponentsToSeconds(hours, min, sec);
}

void TimeCode::SetMinutes(unsigned int minutes) {
    if(minutes > 60) {
        throw invalid_argument("Minutes must be less than 60: " + to_string(minutes));
    }
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec);
    t = ComponentsToSeconds(hr, minutes, sec);
}

void TimeCode::SetSeconds(unsigned int seconds) {
    if(seconds > 60) {
        throw invalid_argument("Seconds must be less than 60: " + to_string(seconds));
    }
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec);
    t = ComponentsToSeconds(hr, min, seconds);
}

void TimeCode::reset() {
    t = 0;
}

unsigned int TimeCode::GetHours() const {
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec);
    return hr;
}

unsigned int TimeCode::GetMinutes() const {
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec);
    return min;
}

unsigned int TimeCode::GetSeconds() const {
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec);
    return sec;
}

void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const {
    unsigned long long int currT = t;
    
    hr = currT/3600;
    currT%=3600;

    min = currT/60;
    currT%=60;

    sec = currT;
}

long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec) {
    return hr*3600 + min*60 + sec;
}

string TimeCode::ToString() const {
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec);
    return to_string(hr) + ":" + to_string(min) + ":" + to_string(sec);
}

TimeCode TimeCode::operator+(const TimeCode& other) const {
    unsigned int hr, min, sec;
    unsigned long long int newT = t + other.GetTimeCodeAsSeconds();

    hr = newT/3600;
    newT%=3600;

    min = newT/60;
    newT%=60;

    sec = newT;

    return TimeCode(hr, min, sec);
}

TimeCode TimeCode::operator-(const TimeCode& other) const {
    if(other.GetTimeCodeAsSeconds() > t) {
        throw invalid_argument("Difference between TimeCodes cannot be negative: " + ToString() + " - " + other.ToString());
    }

    unsigned int hr, min, sec;
    unsigned long long int newT = t - other.GetTimeCodeAsSeconds();

    hr = newT/3600;
    newT%=3600;

    min = newT/60;
    newT%=60;

    sec = newT;

    return TimeCode(hr, min, sec);
}

TimeCode TimeCode::operator*(double a) const {
    if(a < 0.0) {
        throw invalid_argument("Negative arguments not allowed: " + to_string(a));
    }

    unsigned int hr, min, sec;
    unsigned long long int newT = int(t * a);

    hr = newT/3600;
    newT%=3600;

    min = newT/60;
    newT%=60;

    sec = newT;

    return TimeCode(hr, min, sec);
}

TimeCode TimeCode::operator/(double a) const {
    if(a < 0.0) {
        throw invalid_argument("Negative arguments not allowed: " + to_string(a));
    }

    unsigned int hr, min, sec;
    unsigned long long int newT = int(t / a);

    hr = newT/3600;
    newT%=3600;

    min = newT/60;
    newT%=60;

    sec = newT;

    return TimeCode(hr, min, sec);
}

bool TimeCode::operator == (const TimeCode& other) const {
    return t == other.GetTimeCodeAsSeconds();
}

bool TimeCode::operator != (const TimeCode& other) const {
    return t != other.GetTimeCodeAsSeconds();
}

bool TimeCode::operator < (const TimeCode& other) const {
    return t < other.GetTimeCodeAsSeconds();
}

bool TimeCode::operator <= (const TimeCode& other) const {
    return t <= other.GetTimeCodeAsSeconds();
}

bool TimeCode::operator > (const TimeCode& other) const {
    return t > other.GetTimeCodeAsSeconds();
}

bool TimeCode::operator >= (const TimeCode& other) const {
    return t >= other.GetTimeCodeAsSeconds();
}
