#include <ctime>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#include "TimeCode.h"

/**
 * @brief Given a string, extracts a valid TimeCode, assuming that the seconds on the time code is 0
 * 
 * @param str The string to extract a TimeCode object from
 * @return TimeCode 
 */
TimeCode extract_time_code(string str) {
    str.substr(str.find_first_of(':')-2, 2);
    return TimeCode();
}

/**
 * @brief Generates a list of the TimeCodes in the NASA csv file
 * 
 * @param fileName The name of the NASA csv file
 * @return vector<TimeCode>
 */
vector<TimeCode> get_time_codes(string fileName) {
    fstream file(fileName);
    vector<TimeCode> time_codes;

    string line;
    while(getline(file, line)) {
        time_codes.push_back(extract_time_code(line));
    }
    return vector<TimeCode>();
}

int main() {

}