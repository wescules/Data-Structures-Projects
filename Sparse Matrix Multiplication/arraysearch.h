#pragma once
#ifndef ARRAYSEARCH_H
#define ARRAYSEARCH_H
//searchs vector B for values in vector A.
//returns index of B if found; else returns number of rows in B
int searchArr(vector<vector<double>> &vec, int a, int rows) {

	for (int i = 0; i < rows; i++)
		if (vec[i][0] == a)
			return i;
}
//searches temporary vector
int searchVec(vector<vector<double>> &vec, double a, double b, int rows) {

	for (int i = 0; i < rows; i++)
		if (vec[i][0] == a && vec[i][1] == b)
			return i;
}

//binary search method. returns sizeof(b) if not found
int binSearch(vector<vector<double>> &vec, double a, int rows) {
	double low = 1, high = vec.size();
	while (low <= high) {
		double mid = low + (high - low) / 2;
		if (vec[mid][0] == a)
			return mid;
		if (vec[mid][0] < a)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return rows;
}
#endif