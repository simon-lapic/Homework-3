
#include <iostream>
#include <assert.h>
#include "TimeCode.h"
#include <unordered_map>

using namespace std;

class CustomTest
{
public:
	string test_name;
	string expected_answer;
	string student_answer;
	string test_result;
	unordered_map<string, string> test_data;

	CustomTest(string test_name, string expected_answer, string student_answer, unordered_map<string, string> test_data)
	{
		this->test_name = test_name;
		this->expected_answer = expected_answer;
		this->student_answer = student_answer;
		this->test_result = student_answer == expected_answer ? "PASS" : "FAIL";
		this->test_data = test_data;
	}

	void print()
	{
		if (test_result == "FAIL")
		{
			cout << endl
				 << "⚠️"
				 << endl
				 << "Test name: " << test_name << " Test result: " << test_result << endl;
			cout << "Expected answer: " << expected_answer << " Student answer: " << student_answer << endl;
			// print unordered map of test data
			cout << "Test Values:" << endl;
			for (auto it = test_data.begin(); it != test_data.end(); ++it)
			{
				cout << it->first << ": " << it->second << endl;
			}
			cout << endl;
		}
		else
		{
			cout << "Test name: " << test_name << " Test result: " << test_result << endl;
		}
	}
};

void TestComponentsToSeconds()
{
	cout << endl
		 << "------Testing ComponentsToSeconds------" << endl;

	long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
	long long unsigned int t2 = TimeCode::ComponentsToSeconds(0, 0, 0);
	long long unsigned int t3 = TimeCode::ComponentsToSeconds(900000, 0, 0);

	// test 1
	CustomTest test1 = CustomTest("TestComponentsToSeconds-1", "0", to_string(t2), {{"Components", "0,0,0"}});
	// test 2, Random but "safe" inputs
	CustomTest test2 = CustomTest("TestComponentsToSeconds-2", "11862", to_string(t), {{"Components", "3,17,42"}});
	// test 3, t3 is bigger than a 32 bit signed int
	CustomTest test3 = CustomTest("TestComponentsToSeconds-3", "3240000000", to_string(t3), {{"Components", "900000,0,0"}});

	test1.print();
	test2.print();
	test3.print();

	cout << "------TestComponentsToSeconds Finsished------" << endl;
}

void TestDefaultConstructor()
{
	cout << endl
		 << "------TestDefaultConstructor------" << endl;
	TimeCode tc;
	CustomTest t0 = CustomTest("TestDefaultConstructor-1", "0:0:0", tc.ToString(), {{"Components", "0,0,0"}});
	t0.print();
	cout << "------TestDefaultConstructor Finsished------" << endl;
}

void TestComponentConstructor()
{
	cout << endl
		 << "------TestComponentConstructor------" << endl;

	// test 1
	TimeCode tc = TimeCode(0, 0, 0);
	// test 2, Random but "safe" inputs
	TimeCode tc2 = TimeCode(3, 17, 42);
	// test3, Roll-over inputs
	TimeCode tc3 = TimeCode(3, 71, 3801);
	// test 4, default values
	TimeCode tc4 = TimeCode(3, 5);
	TimeCode tc5 = TimeCode(3);
	// test 6, Really really big seconds value
	TimeCode tc6 = TimeCode(0, 0, 13241341347);

	CustomTest t0 = CustomTest("TestComponentConstructor-1", "0:0:0", tc.ToString(), {{"Components", "0,0,0"}});
	CustomTest t1 = CustomTest("TestComponentConstructor-2", "3:17:42", tc2.ToString(), {{"Components", "3,17,42"}});
	CustomTest t2 = CustomTest("TestComponentConstructor-3", "5:14:21", tc3.ToString(), {{"Components", "3,71,3801"}});
	CustomTest t3 = CustomTest("TestComponentConstructor-4", "3:5:0", tc4.ToString(), {{"Components", "3,5,0"}});
	CustomTest t4 = CustomTest("TestComponentConstructor-5", "3:0:0", tc5.ToString(), {{"Components", "3,0,0"}});
	CustomTest t5 = CustomTest("TestComponentConstructor-6", "3678150:22:27", tc6.ToString(), {{"Components", "0,0,13241341347"}});

	t0.print();
	t1.print();
	t2.print();
	t3.print();
	t4.print();
	t5.print();

	cout << "------TestComponentConstructor Finsished------" << endl;
}

void TestGetComponents()
{
	cout << endl
		 << "------TestGetComponents------" << endl;

	unsigned int h;
	unsigned int m;
	unsigned int s;
	// test is not designed for multiple values together so had to test seperately
	//  test 1, Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	CustomTest t0 = CustomTest("TestGetComponents-1", "5", to_string(h), {{"Components", "5,2,18"}, {"Hours", "5"}});
	CustomTest t1 = CustomTest("TestGetComponents-2", "2", to_string(m), {{"Components", "5,2,18"}, {"Minutes", "2"}});
	CustomTest t2 = CustomTest("TestGetComponents-3", "18", to_string(s), {{"Components", "5,2,18"}, {"Seconds", "18"}});
	t0.print();
	t1.print();
	t2.print();

	// test2, Rollover values
	TimeCode tc2 = TimeCode(6, 72, 89);
	tc2.GetComponents(h, m, s);
	CustomTest t3 = CustomTest("TestGetComponents-4", "7", to_string(h), {{"Components", "6,72,89"}, {"Hours", "7"}});
	CustomTest t4 = CustomTest("TestGetComponents-5", "13", to_string(m), {{"Components", "6,72,89"}, {"Minutes", "13"}});
	CustomTest t5 = CustomTest("TestGetComponents-6", "29", to_string(s), {{"Components", "6,72,89"}, {"Seconds", "29"}});
	t3.print();
	t4.print();
	t5.print();

	cout << "------TestGetComponents Finsished------" << endl;
}

void TestGetTimeCodeAsSeconds()
{
	cout << endl
		 << "------TestGetTimeCodeAsSeconds------" << endl;

	TimeCode tc = TimeCode(7, 16, 18);
	CustomTest t0 = CustomTest("TestGetTimeCodeAsSeconds-1", "26178", to_string(tc.GetTimeCodeAsSeconds()), {{"Components", "7,16,18"}});
	t0.print();

	cout << "------TestGetTimeCodeAsSeconds Finsished------" << endl;
}

void TestCopyConstructor()
{
	cout << endl
		 << "------TestCopyConstructor------" << endl;

	// test 1
	TimeCode tc = TimeCode(3, 17, 42);
	TimeCode tc2 = TimeCode(tc);
	CustomTest t0 = CustomTest("TestCopyConstructor-1", "3:17:42", tc2.ToString(), {{"Components", "3,17,42"}});

	// test 2
	TimeCode tc3 = TimeCode(3, 71, 3801);
	TimeCode tc4 = TimeCode(tc3);
	CustomTest t1 = CustomTest("TestCopyConstructor-2", "5:14:21", tc4.ToString(), {{"Components", "3,71,3801"}});

	t0.print();
	t1.print();

	cout << "------TestCopyConstructor Finsished------" << endl;
}

void TestGetHours()
{
	cout << endl
		 << "------TestGetHours------" << endl;

	TimeCode tc = TimeCode(8, 5, 9);
	CustomTest t0 = CustomTest("TestGetHours-1", "8", to_string(tc.GetHours()), {{"Components", "8,5,9"}, {"Hours", "8"}});
	t0.print();

	cout << "------TestGetHours Finsished------" << endl;
}

void TestGetMinutes()
{
	cout << endl
		 << "------TestGetMinutes------" << endl;

	TimeCode tc = TimeCode(8, 5, 9);
	CustomTest t0 = CustomTest("TestGetMinutes-1", "5", to_string(tc.GetMinutes()), {{"Components", "8,5,9"}, {"Minutes", "5"}});
	t0.print();

	cout << "------TestGetMinutes Finsished------" << endl;
}

void TestGetSeconds()
{
	cout << endl
		 << "------TestGetSeconds------" << endl;

	TimeCode tc = TimeCode(8, 5, 9);
	CustomTest t0 = CustomTest("TestGetSeconds-1", "9", to_string(tc.GetSeconds()), {{"Components", "8,5,9"}, {"Seconds", "9"}});
	t0.print();

	cout << "------TestGetSeconds Finsished------" << endl;
}

void TestSetHours()
{
	cout << endl
		 << "------TestSetHours------" << endl;

	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetHours(18);
	CustomTest t0 = CustomTest("TestSetHours-1", "18:5:9", tc.ToString(), {{"Components", "18,5,9"}, {"New Hours", "18"}, {"Old Hours", "8"}});
	t0.print();

	tc.SetHours(600);
	CustomTest t1 = CustomTest("TestSetHours-2", "600:5:9", tc.ToString(), {{"Components", "600,5,9"}, {"New Hours", "600"}, {"Old Hours", "18"}});
	t1.print();

	tc.SetHours(0);
	CustomTest t2 = CustomTest("TestSetHours-3", "0:5:9", tc.ToString(), {{"Components", "0,5,9"}, {"New Hours", "0"}, {"Old Hours", "600"}});
	t2.print();

	cout << "------TestSetHours Finsished------" << endl;
}

void TestSetMinutes()
{
	cout << endl
		 << "------TestSetMinutes------" << endl;

	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetMinutes(15);
	CustomTest t0 = CustomTest("TestSetMinutes-1", "8:15:9", tc.ToString(), {{"Components", "8,15,9"}, {"New Minutes", "15"}, {"Old Minutes", "5"}});
	t0.print();

	try
	{
		tc.SetMinutes(80);
	}
	catch (const invalid_argument &e)
	{
		// cout << e.what() << endl;
	}
	assert(tc.ToString() == "8:15:9");
	CustomTest t1 = CustomTest("TestSetMinutes-2", "8:15:9", tc.ToString(), {{"Components", "8,15,9"}, {"New Minutes", "80"}, {"Old Minutes", "15"}, {"New Minutes", "15"}});
	t1.print();

	cout << "------TestSetMinutes Finsished------" << endl;
}

void TestSetSeconds()
{
	cout << endl
		 << "------TestSetSeconds------" << endl;

	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetSeconds(19);
	CustomTest t0 = CustomTest("TestSetSeconds-1", "8:5:19", tc.ToString(), {{"Components", "8,5,19"}, {"New Seconds", "19"}, {"Old Seconds", "9"}});
	t0.print();

	try
	{
		tc.SetSeconds(80);
	}
	catch (const invalid_argument &e)
	{
	}

	CustomTest t1 = CustomTest("TestSetSeconds-2", "8:5:19", tc.ToString(), {{"Components", "8,5,19"}, {"New Seconds", "19"}, {"Old Seconds", "19"}});
	t1.print();

	cout << "------TestSetSeconds Finsished------" << endl;
}

void TestReset()
{
	cout << endl
		 << "------TestReset------" << endl;

	TimeCode tc1 = TimeCode(57, 62, 39);
	CustomTest t0 = CustomTest("TestReset-1", "58:2:39", tc1.ToString(), {{"Components", "57,62,39"}});
	t0.print();

	// reset values
	tc1.reset();
	CustomTest t1 = CustomTest("TestReset-1", "0:0:0", tc1.ToString(), {{"Components", "0,0,0"}});
	t1.print();

	cout << "------TestReset Finsished------" << endl;
}

void TestAdd()
{
	cout << endl
		 << "------TestAdd------" << endl;

	// test 1
	TimeCode tc1 = TimeCode(5, 58, 0);
	TimeCode tc2 = TimeCode(0, 1, 65);
	TimeCode tc3 = tc1 + tc2;
	CustomTest t0 = CustomTest("TestAdd-1", "6:0:5", tc3.ToString(), {{"Components", "5,58,0"}, {"Add Components", "0,1,65"}, {"Result", "6:0:5"}});
	t0.print();

	// test 2
	TimeCode tc4 = TimeCode(0, 0, 60);
	TimeCode tc5 = TimeCode(0, 0, 60);
	TimeCode tc6 = tc4 + tc5;
	CustomTest t1 = CustomTest("TestAdd-2", "0:2:0", tc6.ToString(), {{"Components", "0,0,60"}, {"Add Components", "0,0,60"}, {"Result", "0:2:0"}});
	t1.print();

	cout << "------TestAdd Finsished------" << endl;
}

void TestSubtract()
{
	cout << endl
		 << "------TestSubtract------" << endl;

	// test 1
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	CustomTest t0 = CustomTest("TestSubtract-1", "0:10:0", tc3.ToString(), {{"Components", "1,0,0"}, {"Subtract Components", "0,50,0"}, {"Result", "0:10:0"}});

	// test 2
	TimeCode tc4 = TimeCode(1, 15, 45);
	try
	{
		TimeCode tc5 = tc1 - tc4;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch (const invalid_argument &e)
	{
	}
	t0.print();
	cout << "------TestSubtract Finsished------" << endl;
}

void TestMultiply()
{
	cout << endl
		 << "------TestMultiply------" << endl;

	// test 1
	TimeCode tc1 = TimeCode(0, 1, 0);
	TimeCode tc2 = tc1 * 2;
	CustomTest test1 = CustomTest("TestMultiply-1", "0:2:0", tc2.ToString(), {{"Components", "0,1,0"}, {"Multiply Number", "2"}, {"Result", "0:2:0"}});

	// test 2
	TimeCode tc3 = TimeCode(3, 5, 17);
	TimeCode tc4 = tc3 * 5.5;
	CustomTest test2 = CustomTest("TestMultiply-2", "16:59:3", tc4.ToString(), {{"Components", "3,5,17"}, {"Multiply Number", "5.5"}, {"Result", "16:59:3"}});

	// test 3
	TimeCode tc5 = TimeCode(0, 5, 0);
	TimeCode tc6 = tc5 * 2.5;
	CustomTest test3 = CustomTest("TestMultiply-3", "0:12:30", tc6.ToString(), {{"Components", "0,5,0"}, {"Multiply Number", "2.5"}, {"Result", "0:12:30"}});

	// test 4
	TimeCode tc7 = TimeCode(0, 5, 0);
	TimeCode tc8 = tc7 * 0.5;
	CustomTest test4 = CustomTest("TestMultiply-4", "0:2:30", tc8.ToString(), {{"Components", "0,5,0"}, {"Multiply Number", "0.5"}, {"Result", "0:2:30"}});

	// test 5, negative number test
	try
	{
		TimeCode tc10 = tc7 * -2;
		cout << "tc10:" << tc10.ToString() << endl;
		assert(false);
	}
	catch (const invalid_argument &e)
	{
	}

	// test 6, multiply by 0
	TimeCode tc12 = tc7 * 0;
	assert(tc12.ToString() == "0:0:0");
	CustomTest test5 = CustomTest("TestMultiply-5", "0:0:0", tc12.ToString(), {{"Components", "0,5,0"}, {"Multiply Number", "0"}, {"Result", "0:0:0"}});

	test1.print();
	test2.print();
	test3.print();
	test4.print();
	test5.print();

	cout << "------TestMultiply Finsished------" << endl;
}

void TestDivide()
{
	cout << endl
		 << "------TestDivide------" << endl;

	// test 1
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = tc1 / 4;
	assert(tc2.ToString() == "0:15:0");
	CustomTest test1 = CustomTest("TestDivide-1", "0:15:0", tc2.ToString(), {{"Components", "1,0,0"}, {"Divide Number", "4"}, {"Result", "0:15:0"}});

	// test 2
	TimeCode tc3 = TimeCode(0, 15, 0);
	TimeCode tc4 = tc3 / 0.5;
	assert(tc4.ToString() == "0:30:0");
	CustomTest test2 = CustomTest("TestDivide-2", "0:30:0", tc4.ToString(), {{"Components", "0,15,0"}, {"Divide Number", "0.5"}, {"Result", "0:30:0"}});

	// test 3 (negative value test)
	try
	{
		TimeCode tc5 = tc3 / -3.0;
		cout << "tc5:" << tc5.ToString() << endl;
		assert(false);
	}
	catch (const invalid_argument &e)
	{
	}

	test1.print();
	test2.print();
	cout << "------TestDivide Finsished------" << endl;
}

void TestEquals()
{
	cout << endl
		 << "------TestEquals------" << endl;

	TimeCode tc1 = TimeCode(87, 32, 64);
	TimeCode tc2 = TimeCode(87, 32, 64);
	TimeCode tc3 = TimeCode(1, 2, 3);

	CustomTest test1 = CustomTest("TestEquals-1", "true", tc1 == tc2 ? "true" : "false", {{"Components", "87,32,64"}, {"Compare Components", "87,32,64"}, {"Result", "true"}});
	CustomTest test2 = CustomTest("TestEquals-2", "false", tc1 == tc3 ? "true" : "false", {{"Components", "87,32,64"}, {"Compare Components", "1,2,3"}, {"Result", "false"}});

	test1.print();
	test2.print();

	cout << "------TestEquals Finsished------" << endl;
}

void TestLessThan()
{
	cout << endl
		 << "------TestLessThan------" << endl;

	TimeCode tc1 = TimeCode(2, 0, 0);
	TimeCode tc2 = TimeCode(0, 15, 0);
	TimeCode tc3 = TimeCode(2, 0, 0);

	assert(!(tc1 < tc2)); // test 1
	assert(tc2 < tc1);	  // test 2
	assert(tc1 <= tc3);	  // 3
	assert(!(tc1 < tc3)); // 4

	CustomTest test1 = CustomTest("TestLessThan-1", "false", tc1 < tc2 ? "true" : "false", {{"Components", "2,0,0"}, {"Compare Components", "0,15,0"}, {"Result", "true"}});
	CustomTest test2 = CustomTest("TestLessThan-2", "true", tc2 < tc1 ? "true" : "false", {{"Components", "0,15,0"}, {"Compare Components", "2,0,0"}, {"Result", "false"}});
	CustomTest test3 = CustomTest("TestLessThan-3", "true", tc1 <= tc3 ? "true" : "false", {{"Components", "2,0,0"}, {"Compare Components", "2,0,0"}, {"Result", "true"}});
	CustomTest test4 = CustomTest("TestLessThan-4", "false", tc1 < tc3 ? "true" : "false", {{"Components", "2,0,0"}, {"Compare Components", "2,0,0"}, {"Result", "false"}});

	test1.print();
	test2.print();
	test3.print();
	test4.print();

	cout << "------TestLessThan Finsished------" << endl;
}

void TestGreaterThan()
{
	cout << endl
		 << "------TestGreaterThan------" << endl;

	TimeCode tc1 = TimeCode(3, 0, 0);
	TimeCode tc2 = TimeCode(0, 40, 0);
	TimeCode tc3 = TimeCode(3, 0, 0);

	CustomTest test1 = CustomTest("TestGreaterThan-1", "false", tc2 > tc1 ? "true" : "false", {{"Components", "0,40,0"}, {"Compare Components", "3,0,0"}, {"Result", "true"}});
	CustomTest test2 = CustomTest("TestGreaterThan-2", "true", tc1 > tc2 ? "true" : "false", {{"Components", "3,0,0"}, {"Compare Components", "0,40,0"}, {"Result", "false"}});
	CustomTest test3 = CustomTest("TestGreaterThan-3", "true", tc1 >= tc3 ? "true" : "false", {{"Components", "3,0,0"}, {"Compare Components", "3,0,0"}, {"Result", "true"}});
	CustomTest test4 = CustomTest("TestGreaterThan-4", "false", tc1 > tc3 ? "true" : "false", {{"Components", "3,0,0"}, {"Compare Components", "3,0,0"}, {"Result", "false"}});

	test1.print();
	test2.print();
	test3.print();
	test4.print();

	cout << "------TestGreaterThan Finsished------" << endl;
}

void TestAverage()
{
	cout << endl
		 << "------TestAverage------" << endl;

	// test 1
	TimeCode tc1 = TimeCode(5, 0, 0);
	TimeCode tc2 = TimeCode(6, 0, 0);
	TimeCode ans = TimeCode(5, 30, 0);
	CustomTest test1 = CustomTest("TestAverage-1", "5:30:0", ((tc1 + tc2) / 2.0).ToString(), {{"Components", "5,0,0"}, {"Add Components", "6,0,0"}, {"Result", "5:30:0"}});

	// test 2
	TimeCode tc3 = TimeCode(2, 15, 30);
	TimeCode tc4 = TimeCode(3, 45, 5);
	TimeCode tc5 = TimeCode(1, 28, 31);
	ans = TimeCode(2, 29, 42);
	TimeCode res = (tc3 + tc4 + tc5) / 3.0;
	CustomTest test2 = CustomTest("TestAverage-2", "2:29:42", res.ToString(), {{"Components", "2,15,30"}, {"Add Components", "3,45,5"}, {"Add Components", "1,28,31"}, {"Result", "2:29:42"}});

	test1.print();
	test2.print();

	cout << "------TestAverage Finsished------" << endl;
}

int main()
{

	TestComponentsToSeconds();
	TestDefaultConstructor();
	TestComponentConstructor();
	TestGetComponents();
	TestGetTimeCodeAsSeconds();
	TestCopyConstructor();

	TestGetHours();
	TestGetMinutes();
	TestGetSeconds();

	TestSetHours();
	TestSetMinutes();
	TestSetSeconds();

	TestReset();

	TestAdd();
	TestSubtract();
	TestMultiply();
	TestDivide();

	TestEquals();
	TestLessThan();
	TestGreaterThan();

	TestAverage();

	cout << endl
		 << "FINISHED TESTING!!!" << endl;
	return 0;
}
