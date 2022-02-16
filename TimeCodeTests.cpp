#include <iostream>
#include <assert.h>
using namespace std;

#include "TimeCode.h"
#include "TimeCode.cpp"


void TestComponentsToSeconds() {
	cout << endl << "=====COMPONENTS TO SECONDS TESTS=====" << endl;
	
	// Random but "safe" inputs
	long long unsigned int t1 = TimeCode::ComponentsToSeconds(3, 17, 42);
	cout << "Components 3:17:42 -> " << t1 << " -> ";
	assert(t1 == 11862);
	cout << " PASSED" << endl;
	
}


void TestDefaultConstructor() {
	cout << endl << "=====DEFAULT CONSTRUCTOR TESTS=====" << endl;
	TimeCode tc;
	
	// Check the default constructor's value
	cout << "Default values -> " << tc.ToString() << " -> ";
	assert(tc.ToString() == "0:0:0");
	cout << "PASSED" << endl;
}


void TestComponentConstructor() {
	cout << endl << "=====COMPONENTS CONSTRUCTOR TESTS=====" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	// more tests go here!
	
	// Roll-over inputs
	TimeCode tc3 = TimeCode(3, 71, 3801);
	//cout << "tc3: " << tc3.ToString() << endl;
	assert(tc3.ToString() == "5:14:21");
	
	// More tests go here!
	
	cout << "PASSED!" << endl << endl;
}


void TestGetComponents() {
	cout << endl << "=====GET COMPONENTS TESTS=====" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	
	// More tests go here!
	
	cout << "PASSED!" << endl << endl;
}


void TestSubtract() {
	cout << endl << "=====SUBTRACTION TESTS=====" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	
	
	TimeCode tc4 = TimeCode(1, 15, 45);
	try{
		TimeCode tc5 = tc1 - tc4;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just leave this empty
		// and keep doing more tests
	}

	// more tests
	
	cout << "PASSED!" << endl << endl;
}


void TestSetMinutes() {
	cout << endl << "=====SET MINUTES TESTS=====" << endl;

	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetMinutes(15); // test valid change
	assert(tc.ToString() == "8:15:9");

	try
	{
		tc.SetMinutes(80);  // test invalid change
		assert(false);
	}
	catch (const invalid_argument &e)
	{
		// cout << e.what() << endl;
	}

	assert(tc.ToString() == "8:15:9");

	cout << "PASSED!" << endl << endl;
}


// Many More Tests...


void RunTests() {
	TestComponentsToSeconds();
	TestDefaultConstructor();
	TestComponentConstructor();
	TestGetComponents();
	TestSubtract();
	TestSetMinutes();
}

int main() {
	RunTests();
	return 0;
}
