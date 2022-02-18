#include <iostream>
#include <assert.h>
using namespace std;

#include "TimeCode.h"
#include "TimeCode.cpp"

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

	// All 0s
	TimeCode tc = TimeCode(0, 0, 0);
	cout << "(0, 0, 0) -> " << tc.ToString() << " -> ";
	assert(tc.ToString() == "0:0:0");
	cout << "PASSED" << endl;
	
	// Random Values
	TimeCode tc2 = TimeCode(3, 17, 42);
	cout << "(3, 17, 42) -> " << tc2.ToString() << " -> ";
	assert(tc2.ToString() == "3:17:42");
	cout << "PASSED" << endl;
	
	// Roll-over inputs
	TimeCode tc3 = TimeCode(3, 71, 3801);
	cout << "(3, 71, 3801) -> " << tc3.ToString() << " -> ";
	assert(tc3.ToString() == "5:14:21");
	cout << "PASSED" << endl;
	
	
}

void TestCopyConstructor() {
	cout << endl << "=====COPY CONSTRUCTOR TESTS=====" << endl;

	// All 0s in the original TimeCode
	TimeCode tc = TimeCode(0, 0, 0);
	TimeCode newTC = TimeCode(tc);
	cout << "Original 0:0:0 -> " << newTC.ToString() << " -> ";
	assert(newTC.ToString() == "0:0:0");
	cout << "PASSED" << endl;

	// All 0s in the original TimeCode
	TimeCode tc2 = TimeCode(3, 17, 42);
	TimeCode newTC2 = TimeCode(tc2);
	cout << "Original 3:17:42 -> " << newTC2.ToString() << " -> ";
	assert(newTC2.ToString() == "3:17:42");
	cout << "PASSED" << endl;

	// Roll-over inputs
	TimeCode tc3 = TimeCode(3, 71, 3801);
	TimeCode newTC3 = TimeCode(tc3);
	cout << "Original 3:71:3801 -> " << newTC3.ToString() << " -> ";
	assert(newTC3.ToString() == "5:14:21");
	cout << "PASSED" << endl;
}

void TestSetHours() {
	cout << endl << "=====SET HOURS TESTS=====" << endl;

	// Set to 0
	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetHours(0);
	cout << "8:5:9, hr = 0 -> " << tc.ToString() << " -> ";
	assert(tc.ToString() == "0:5:9");
	cout << "PASSED" << endl;

	// Random change
	TimeCode tc2 = TimeCode(8, 5, 9);
	tc2.SetHours(15);
	cout << "8:5:9,  hr = 15 -> " << tc2.ToString() << " -> ";
	assert(tc2.ToString() == "15:5:9");
	cout << "PASSED" << endl;	
}

void TestSetMinutes() {
	cout << endl << "=====SET MINUTES TESTS=====" << endl;

	// Set to 0
	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetMinutes(0);
	cout << "8:5:9, min = 0 -> " << tc.ToString() << " -> ";
	assert(tc.ToString() == "8:0:9");
	cout << "PASSED" << endl;

	// Random change
	TimeCode tc2 = TimeCode(8, 5, 9);
	tc2.SetMinutes(15);
	cout << "8:5:9,  min = 15 -> " << tc2.ToString() << " -> ";
	assert(tc2.ToString() == "8:15:9");
	cout << "PASSED" << endl;

	// Invalid argument
	TimeCode tc3 = TimeCode(8, 5, 9);
	cout << "8:5:9, min = 80 (invalid_argument) -> ";
	try {
		tc3.SetMinutes(80);
		cout << tc3.ToString() << " -> EXCEPTION NOT THROWN" << endl;
		assert(false);
	}
	catch (const invalid_argument &e) { }
	cout << tc3.ToString();
	assert(tc.ToString() == "8:5:9");
	cout << " -> PASSED" << endl;
}

void TestSetSeconds() {
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

void TestComponentsToSeconds() {
	cout << endl << "=====COMPONENTS TO SECONDS TESTS=====" << endl;
	
	// All components are 0
	long long unsigned int t2 = TimeCode::ComponentsToSeconds(0, 0, 0);
	cout << "Components 0:0:0 -> " << t2 << " -> ";
	assert(t2 == 0);
	cout << " PASSED" << endl;

	// Random but "safe" inputs
	long long unsigned int t1 = TimeCode::ComponentsToSeconds(3, 17, 42);
	cout << "Components 3:17:42 -> " << t1 << " -> ";
	assert(t1 == 11862);
	cout << " PASSED" << endl;

	// Rollover test
	long long unsigned int t3 = TimeCode::ComponentsToSeconds(3, 17, 90);
	cout << "Components 3:17:90 -> " << t3 << " -> ";
	assert(t3 == 11910);
	cout << " PASSED" << endl;
	
}

void TestGetComponents() {
	cout << endl << "=====GET COMPONENTS TESTS=====" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	cout << "Regular values: (5, 2, 18) -> " << "h: " << h << ", m: " << m << ", s: " << s << " -> ";
	assert(h == 5 && m == 2 && s == 18);
	cout << "PASSED" << endl;
	
	// Rollover test
	TimeCode tc2 = TimeCode(3, 17, 90);
	tc2.GetComponents(h, m, s);
	cout << "Rollover test: (3, 17, 90) -> " << "h: " << h << ", m: " << m << ", s: " << s << " -> ";
	assert(h == 3 && m == 18 && s == 30);
	cout << " PASSED" << endl;
	
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

	}

	// more tests
	
	cout << "PASSED!" << endl << endl;
}


// Many More Tests...


void RunTests() {
	// Constructors
	TestDefaultConstructor();
	TestComponentConstructor();
	TestCopyConstructor();

	// Setters
	TestSetHours();
	TestSetMinutes();
	TestSetSeconds();

	TestComponentsToSeconds();
	TestGetComponents();
	TestSubtract();
}

int main() {
	RunTests();
	return 0;
}
