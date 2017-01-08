#pragma once
#ifndef ARRAYSORT_H
#define ARRAYSORT_H
#include <iostream>
#include <vector>
using namespace std;
//global variables for diffrent sorts
int sortingI = 0, sortingJ = 0, sortingIA = 0, sortingIB = 0, sortingJA = 0, sortingJB = 0;

bool sorti(const vector<double>& p1,
	const vector<double>& p2) {
	return p1[0] < p2[0];
}
bool sortj(const vector<double>& p1,
	const vector<double>& p2) {
	return p1[1] < p2[1];
}

//sorts values in column 0
bool sortia(const vector<double>& p1,
	const vector<double>& p2) {
	sortingIA++;
	return p1[0] < p2[0];
}

bool sortib(const vector<double>& p1,
	const vector<double>& p2) {
	sortingIB++;
	return p1[0] < p2[0];
}
//sorts values in column 1
bool sortja(const vector<double>& p1,
	const vector<double>& p2) {
	sortingJA++;
	return p1[1] < p2[1];
}
bool sortjb(const vector<double>& p1,
	const vector<double>& p2) {
	sortingJB++;
	return p1[1] < p2[1];
}

double bubbleSort(const vector<vector<double>> &vec) {
	for (int i = 0; i < vec.size(); i++) {
		int counter = 0;
		for (int j = 0; j < vec.size(); j++) {
			if (vec[i][0] > vec[i][1]) {
				vec[i][0] == vec[i][1];
			}
		}return counter;
	}
	
}
#endif