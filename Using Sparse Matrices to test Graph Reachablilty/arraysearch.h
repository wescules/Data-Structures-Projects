#pragma once
#ifndef ARRAYSEARCH_H
#define ARRAYSEARCH_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

//searches temporary vector
int searchVec(vector<vector<double>> &vec, double a, double b, int rows) {

	for (int i = 0; i < rows; i++)
		if (vec[i][0] == a && vec[i][1] == b)
			return i;
}

//binary search method. returns sizeof(b) if not found
int binSearch(vector<vector<double>> &vec, double a, int rows) {
	double low = vec[0][0], high = vec[vec.size()][0];
	
	//over time the algoritim will get tighter bounds until searched term is reached
	while (low <= high) {
		double mid = low + (high - low) / 2;

		//immediately reurn mid term if value is found
		if (vec[mid][0] == a)
			return mid;
		
		//if the mid value is less than searched term it has to increase the low by mid+1
		if (vec[mid][0] < a)
			low = mid + 1;

		//if mid value is higher than searched term the high value is decremented
		else
			high = mid - 1;
	}
	//if the loops reaches this point, the value is not in the matrix
}
#endif