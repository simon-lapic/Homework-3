all:
	g++ -Wall TimeCode.cpp TimeCodeTests.cpp -o TimeCodeTests

run: 
	./TimeCodeTests

try: all run