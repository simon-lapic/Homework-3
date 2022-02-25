
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


long long int get_time_remaining(DryingSnapShot dss){
	return dss.timeToDry->GetTimeCodeAsSeconds();
}


string drying_snap_shot_to_string(DryingSnapShot dss){

	return "";
}

/**
 * @returns double, the surface area of a sphere given it's radius
 */
double get_sphere_sa(double r){
	return 4*M_PI*pow(r, 2);
}

/**
 * @brief 
 * 
 * @param surfaceArea 
 * @return TimeCode* 
 */
TimeCode *compute_time_code(double surfaceArea){
	return new TimeCode(0, 0, floor(surfaceArea));
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
	cout << sa << endl;
	assert (50.2654 > sa && sa < 50.2655);
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
	// replace with your code
	tests();
	return 0;
}