#pragma once
#ifndef ARRAYSORT_H
#define ARRAYSORT_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

//N^2 algorithim
vector<vector<double> > bubbleSortI( vector<vector<double>> &vec) {
	//temp variable that stores up to 3 ints
	int temp[3];
	for (int i = 0; i < (vec.size() / 3) - 1; i++) {
		for (int j = 0; j < (vec.size() - i) - 1; j++) {
			//if an i value is greater than the one proceeding it: swap
			if (vec[j][0] > vec[j+1][0]) {
				temp[0] = vec[j][0];
				temp[1] = vec[j][1];
				temp[2] = vec[j][2];
				vec[j][0] = vec[j + 1][0];
				vec[j][1] = vec[j + 2][1];		//swaps i, j, v values if an i value is greater
				vec[j][2] = vec[j + 3][2];
				vec[j + 1][0] = temp[0];
				vec[j + 2][0] = temp[1];
				vec[j + 1][0] = temp[2];
			}
		}
	}
	//returns sorted vector
	return vec;
}

//O(nlogn) sort
//sorts by colomn
void Nlognsort(vector<vector<double> >& matrix, int col) {

	//uses sorting algoritim from algorithm library for sort
	//sorts vector based on immediate comparisons to vector above and below current vector in a 2d vector
	sort(matrix.begin(), matrix.end(), [col](const vector<double>& lhs, const vector<double>& rhs) {
		return lhs[col] > rhs[col];
	});
}
#endif