#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

#include "TimeCode.h"
#include "TimeCode.cpp"

/**
 * @brief Given a string, extracts a valid TimeCode, assuming that the seconds on the time code is 0
 * 
 * @param str The string to extract a TimeCode object from
 * @return TimeCode 
 */
TimeCode extract_time_code(string str) {

}

/**
 * @brief Generates a list of the TimeCodes in the NASA csv file
 * 
 * @param fileName The name of the NASA csv file
 * @return vector<TimeCode>
 */
vector<TimeCode> get_time_codes(string fileName) {
    fstream file(fileName);

}

int main() {

}