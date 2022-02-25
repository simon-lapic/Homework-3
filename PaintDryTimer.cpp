
#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's (duh)

using namespace std;

/**
 * @brief 
 */
struct DryingSnapShot {
	string name;
	time_t startTime;
	TimeCode *timeToDry;
};

/**
 * @param dss DryingSnapShot, the Drying Snapshot to look at
 * @return long long int, the number of seconds remaining for this batch
 */
long long int get_time_remaining(DryingSnapShot dss){
	return dss.timeToDry->GetTimeCodeAsSeconds();
}

/**
 * @param dss DryingSnapShot, the Drying Snapshot to look at
 * @return string, a string representation of the DryingSnapShot
 */
string drying_snap_shot_to_string(DryingSnapShot dss){
	return "Batch-" + dss.name + " will dry in " + dss.timeToDry->ToString();
}

/**
 * @returns double, the surface area of a sphere given it's radius
 */
double get_sphere_sa(double r){
	return 4*M_PI*pow(r, 2);
}

/**
 * @brief Computes a TimeCode representation of the time required to dry a sphere with a given surface area
 * 
 * @param surfaceArea double, the surface area of the ball
 * @return TimeCode*, a pointer to the TimeCode representation
 */
TimeCode *compute_time_code(double surfaceArea){
	return new TimeCode(0, 0, floor(surfaceArea));
}

/**
 * @brief Updates the time remaining for a given DryingSnapShot and checks if it has been completed
 * @param dss DryingSnapShot
 * @returns true if the DryingSnapShot is completed, otherwise false
 */
void check_batch(DryingSnapShot dss) {
	// if (dss.timeToDry != nullptr) {
		time_t currTime = time(0);
		long long int elapsed = currTime - dss.startTime;
		long long int remaining = dss.timeToDry->GetTimeCodeAsSeconds() - elapsed;

		if(remaining > 0) {
			dss.timeToDry = new TimeCode(0, 0, remaining);
			cout << drying_snap_shot_to_string(dss) << endl;
		} else {
			delete dss.timeToDry;
		}
	// } 
}


// UI

/**
 * @brief Prompts the user for an input with a given message
 * 
 * @param message string, the message to give the user
 * @return string, the user's input
 */
string get_input(string message) {
	cout << message;
	string input;
	cin >> input;
	return input;
}

/**
 * @brief Adds a new DryingSnapShot to a given list of DryingSnapShots
 * 
 * @param vec vector<DryingSnapShot>, the list of snapshots
 */
void add_snapshot(vector<DryingSnapShot> &vec) {
	DryingSnapShot dss;
	srand(time(0));
	dss.startTime = time(0);
	dss.timeToDry = compute_time_code(get_sphere_sa(stod(get_input("ball radius: "))));
	dss.name = to_string(rand());

	vec.push_back(dss);
	cout << drying_snap_shot_to_string(dss) << endl;
}

/**
 * @brief Prints a view of all the batches currently being tracked, and updates them
 * 
 * @param vec vector<DryingSnapShot>, the list of 
 */
void view_snapshots(vector<DryingSnapShot> &vec) {
	cout << "Tracking " << vec.size() << " batch(es)" << endl;
	for(int i = 0; i<vec.size(); i++) {
		check_batch(vec.at(i));
		if(vec.at(i).timeToDry == nullptr) {
			vec.erase(vec.begin() + i);
		}
	}
}

/**
 * @brief Handles the user input for the program
 */
void handle_input() {
	vector<DryingSnapShot> snapshots;

	while(true){
		string input = get_input("Choose an option: (A)dd Batch, (V)iew Current Batches, (Q)uit: ");
		if (input == "a" || input == "A") {
			add_snapshot(snapshots);
		} else if (input == "v" || input == "V") {
			view_snapshots(snapshots);
		} else if (input == "q" || input == "Q") {
			return;
		} else {
			cout << "Invalid Input." << endl;
		}
	}
}

void tests(){
	// get_time_remaining
	DryingSnapShot dss;
	dss.startTime = time(0);
	TimeCode tc = TimeCode(0, 0, 7);
	dss.timeToDry = &tc;
	long long int ans = get_time_remaining(dss);
	assert(ans > 6 && ans < 8);
	// add more tests here


	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2656);
	// add more tests here


	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	//cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;


	// add more tests here


	cout << "ALL TESTS PASSED!" << endl;

}

int main(){
	handle_input();
	return 0;
}