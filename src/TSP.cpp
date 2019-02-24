//============================================================================
// Name        : TSP.cpp
// Author      : Zankhana ZKP
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <limits.h>

using namespace std;
int final_cost = 0, vertices, max_value = INT_MAX, visited_all_node_value = 0,
		first_node_val = 0, first_visited_count = 1, output_Vector_Size_Count =
				0;
std::string outPut;
std::vector<std::vector<int> > graphVector;
std::vector<int> output_vector;

//this method will convert string to Integer
int stringToInt(string strInput) {

	stringstream strToInt(strInput);
	int intValue = 0;
	strToInt >> intValue;

	return intValue;

}
//this method will converting vector array from String
vector<int> splitStringToIntegerArray(string file_line) {
	vector<int> result_vector;
	std::istringstream iss(file_line);
	for (std::string line; iss >> line;)
		result_vector.push_back(stringToInt(line));
	return result_vector;
}

//method for left shift operation with Integer
int leftShiftOperation(int input) {
	return 1 << input;
}

//Init value for first node
int initVisitedAllNodeValue() {
	int leftShift = leftShiftOperation(vertices);
	return leftShift - 1;
}

//This method will check if all node is already visited or not
bool allNodeIsVisited(int visitedNode) {
	if (visitedNode == visited_all_node_value) {
		return true;
	} else {
		return false;
	}
}

//AND operation with two Integer
int andOperation(int firstInput, int secondInput) {
	return firstInput & secondInput;
}

//OR operation with two Integer
int orOperation(int firstInput, int secondInput) {
	return firstInput | secondInput;
}

//this method will check for next coming node in cycle
bool checkConditionForNextNode(int currentNode, int nextNode, int visitedNode) {

	int leftShift = leftShiftOperation(nextNode);
	int visited = andOperation(visitedNode, leftShift);

	if ((graphVector[currentNode][nextNode] != 0) && (visited == 0)) {
		return true;
	} else {
		return false;
	}

}

//find minimum value from two integer
int findMinimumCost(int finalCost, int cost) {
	return min(finalCost, cost);
}

//this method is providing minimum weight for hamiltonian cycle
int travelingSalesmanProblem(int visitedNode, int currentNode) {

	if (allNodeIsVisited(visitedNode)) {
		return graphVector[currentNode][0];
	}

	int finalCost_Count = max_value;

	for (int nextNode = 0; nextNode < vertices; nextNode++)

	{

		if (checkConditionForNextNode(currentNode, nextNode, visitedNode)) {

			int leftShift = leftShiftOperation(nextNode);
			int visited = orOperation(visitedNode, leftShift);
			int cost = graphVector[currentNode][nextNode]
					+ travelingSalesmanProblem(visited, nextNode);

			finalCost_Count = findMinimumCost(finalCost_Count, cost);

		}

	}
	return finalCost_Count;

}

//adding data set in to vector then called to travelingSalesmanProblem method
void fillGraphVector(string uvw_value_string) {
	graphVector.clear();
	graphVector.resize(vertices, std::vector<int>(vertices, 0));
	std::istringstream f(uvw_value_string);
	while (std::getline(f, uvw_value_string)) {
		vector<int> result = splitStringToIntegerArray(uvw_value_string);
		int u = result[0];
		int v = result[1];
		int w = result[2];

		graphVector[u][v] = w;
		graphVector[v][u] = w;
	}
	visited_all_node_value = initVisitedAllNodeValue();
	final_cost = travelingSalesmanProblem(first_visited_count, first_node_val);

		output_vector[output_Vector_Size_Count] = final_cost;
		output_Vector_Size_Count++;
}

//this method will convert string to vector array
//main method to start the program,
//reading data from the first argument and writing result in a file with the same path.
int main(int argument, char** argumentArray) {
	std::string inputFileName = argumentArray[1];
	std::string outputFileName = argumentArray[2];
	std::ifstream file(argumentArray[1]);
	std::ofstream resultFileData;
	std::string str_line;
	std::string file_data_String;
	std::string uvw_value_string;
	while (std::getline(file, str_line)) {
		file_data_String += str_line;
		file_data_String.push_back('\n');
	}
	std::istringstream f(file_data_String);
	std::string file_line_string;

	int edges = 0;
	int count = 0;
	while (std::getline(f, file_line_string)) {
		vector<int> result_vector = splitStringToIntegerArray(file_line_string);
		if (result_vector.size() == 1) {
			output_vector.clear();
			output_vector.resize(result_vector[0], 0);
		} else if (result_vector.size() == 1) {
			vertices = result_vector[0];
			edges = result_vector[1];
			count = 0;
			uvw_value_string.clear();

		} else if (result_vector.size() = 3) {
			uvw_value_string += file_line_string;
			uvw_value_string.push_back('\n');
			count++;
			if (count == edges) {
				fillGraphVector(uvw_value_string);
			}
		}

	}
	resultFileData.open(argumentArray[2]);

		for (int i = 0; i < output_vector.size(); i++) {
			resultFileData << output_vector[i];
			resultFileData << "\n";
		}

		resultFileData.close();

		return 0;

}
