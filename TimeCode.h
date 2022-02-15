#ifndef TIMECODE_H
#define TIMECODE_H

#include <iostream> // Used for the throw "Negative Condition" lines

using namespace std;

class TimeCode {
    public:
        /**
         * @brief Constructs a new Time Code object with given hours, minutes, and seconds
         * 
         * @param hr unsigned int, the number of hours
         * @param min unsigned int, the number of minutes
         * @param sec unsigned int, the number of seconds
         */
        TimeCode(unsigned int hr = 0, unsigned int min = 0, long long unsigned int sec = 0);

        /**
         * @brief Constructs a new Time Code object as a copy of another TimeCode
         * 
         * @param tc TimeCode, the other TimeCode
         */
        TimeCode(const TimeCode& tc);

        /**
         * @brief Destroys the Time Code object
         */
        ~TimeCode(){};

        /**
         * @brief Set the number of hours in the TimeCode
         * 
         * @param hours unsigned int, the number of hours
         */
        void SetHours(unsigned int hours);

        /**
         * @brief Set the number of minutes in the TimeCode
         * 
         * @param minutes unsigned int, the number of minutes
         */
        void SetMinutes(unsigned int minutes);

        /**
         * @brief Set the number of seconds in the TimeCode
         * 
         * @param seconds unsigned int, the number of seconds
         */
        void SetSeconds(unsigned int seconds); 

        /**
         * @brief Resets the time of the TimeCode
         */
        void reset();

        /**
         * @return unsigned int, the number of hours in the Time Code
         */
        unsigned int GetHours() const;

        /**
         * @return unsigned int, the number of minutes in the Time Code
         */
        unsigned int GetMinutes() const;

        /**
         * @return unsigned int, the number of seconds in the Time Code
         */
        unsigned int GetSeconds() const;

        /**
         * @return long long unsigned int, the TimeCode as represented by a total number of seconds
         */
        long long unsigned int GetTimeCodeAsSeconds() const { return t; };

        /**
         * @brief Gets the components of the TimeCode and assigns them to the parameters
         * 
         * @param hr unsigned int, the hours
         * @param min unsigned int, the minutes
         * @param sec unsigned int, the seconds
         */
        void GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const; 

        /**
         * @brief Converts a set of components into a total number of seconds
         * 
         * @param hr unsigned int, the number of hours
         * @param min unsigned int, the number of minutes
         * @param sec unsigned int, the number of seconds
         * @return long long unsigned int, the total number of seconds represented by the components
         */
        static long long unsigned int ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec);

        /**
         * @return string, a string representation of the TimeCode
         */
        string ToString() const;

        // OPERATOR DEFINITIONS
        TimeCode operator+(const TimeCode& other) const;
        TimeCode operator-(const TimeCode& other) const;
        TimeCode operator*(double a) const;
        TimeCode operator/(double a) const;

        bool operator == (const TimeCode& other) const;
        bool operator != (const TimeCode& other) const;

        bool operator < (const TimeCode& other) const;
        bool operator <= (const TimeCode& other) const;

        bool operator > (const TimeCode& other) const;
        bool operator >= (const TimeCode& other) const;
    
    private:
        /**
         * @brief the time, measured in a total number of seconds
         */
        long long unsigned int t = 0;
};

#endif