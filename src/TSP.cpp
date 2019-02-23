//============================================================================
// Name        : TSP.cpp
// Author      : Zankhana ZKP
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;
std::string outPut;
std::vector<std::vector<int> > graphVector;
std::vector<int> output_vector;
int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
//this method will convert string to Integer
int stringToInt(string strInput)
{
	stringstream strToInt(strInput);
	int intValue =0;
	strToInt >> intValue;
	return intValue;
}
//this method will convert string to vector array

