#include <ctime>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#include "TimeCode.h"


/**
 * @brief Splits a given string along a given delimiter
 * 
 * @param str string, the string to split
 * @param delim char, the delimiter to split along
 * @return vector<string>, a list of the substrings between each delimiter
 */
vector<string> split(string str, char delim) {
    vector<string> substrs;
    int curr_start = 0;
    for(int i = 0; i<str.size(); i++) {
        if(str.at(i) == delim) {
            substrs.push_back(str.substr(curr_start, i-curr_start));
            curr_start = i+1;
        }
    }
    return substrs;
}

/**
 * @brief Given a string, extracts a valid TimeCode, assuming that the seconds on the time code is 0
 * 
 * @param str The string to extract a TimeCode object from
 * @return TimeCode 
 */
TimeCode extract_time_code(string str) {
    int index = str.find_first_of(':');
    if(index < str.size()) {
        unsigned int hrs = stoi(str.substr(index-2, 2));
        unsigned int mins = stoi(str.substr(index+1, 2));

        return TimeCode(hrs, mins, 0);
    } else {
        throw invalid_argument("No TimeCode in str");
    }
}

/**
 * @brief Generates a list of the TimeCodes in the NASA csv file
 * 
 * @param fileName The name of the NASA csv file
 * @return vector<TimeCode>
 */
vector<TimeCode> get_time_codes(string fileName, int& count) {
    fstream file(fileName);
    vector<TimeCode> time_codes;

    string line;
    getline(file, line);
    while(getline(file, line)) {
        // Get the TimeCode from the 4th column of the csv line
        vector<string> columns = split(line, '\"');
        try {
            time_codes.push_back(extract_time_code(columns.at(1)));
            count++;
        } catch(invalid_argument) { }
    }
    return time_codes;
}

/**
 * @brief Averages a vector of TimeCodes
 * 
 * @param time_codes vector<TimeCode>, the list of TimeCodes to average
 * @return TimeCode 
 */
TimeCode avg_time_codes(vector<TimeCode> time_codes) {
    double counter = 0;
    TimeCode sum;
    for(TimeCode tc : time_codes) {
        counter++;
        sum = sum + tc;
    }

    return sum / counter;
}

int main() {
    int num_data_points = 0;
    TimeCode avg = avg_time_codes(get_time_codes("Space_Corrected.csv", num_data_points));
    cout << num_data_points << " data points" << endl;
    cout << "Average Launch Time: " << avg.ToString() << endl;
}