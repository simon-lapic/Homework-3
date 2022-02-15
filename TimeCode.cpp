#include "TimeCode.h"

using namespace std;

TimeCode::TimeCode(unsigned int hr = 0, unsigned int min = 0, long long unsigned int sec = 0) {
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
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec);
    t = ComponentsToSeconds(hr, minutes, sec);
}

void TimeCode::SetSeconds(unsigned int seconds) {
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
    int currT = t;
    
    hr = currT/1200;
    currT%=1200;

    min = currT/60;
    currT%=60;

    sec = currT;
}

long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec) {
    return hr*1200 + min*60 + sec;
}

string TimeCode::ToString() const {
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec);
    return to_string(hr) + ":" + to_string(min) + ":" + to_string(sec);
}

TimeCode TimeCode::operator+(const TimeCode& other) const {
    return TimeCode(t + other.GetTimeCodeAsSeconds());
}

TimeCode TimeCode::operator-(const TimeCode& other) const {
    return TimeCode(t - other.GetTimeCodeAsSeconds());
}

TimeCode TimeCode::operator*(double a) const {
    return TimeCode(int(t * a));
}

TimeCode TimeCode::operator/(double a) const {
    return TimeCode(int(t / a));
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