all:
	g++ -Wall TimeCodeTests.cpp -o TimeCodeTests

run: 
	./TimeCodeTests

try: all run