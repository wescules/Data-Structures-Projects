#pragma once
#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

//sorts values in column 0
bool sorti(const vector<double>& p1,
	const vector<double>& p2) {
	return p1[0] < p2[0];
}

//sorts values in column 0
bool sortj(const vector<double>& p1,
	const vector<double>& p2) {
	return p1[1] < p2[1];
}

//counts number of rows in file
int numLines(string filename) {
	ifstream file(filename);
	string str;
	int rows = 0;
	while (!file.eof()) {
		char ch = file.peek();

		if (ch == '#' || ch == '\n' || isalpha(ch)) {
			file.ignore(100, '\n');
			str.erase(remove(str.begin(), str.end(), '\n'), str.end());
			continue;
		}
		while (getline(file, str)) {
			if (str == "" || str == "\n") {
				file.ignore(100, '\n');
			}
			else
				rows++;
		}
	}
	if (rows == 0) {
		cerr << "File is empty";
		return 0;
	}

	file.close();
	return rows;
}

//reads file into 2d vector
vector< vector<double> > readFile(string filename, int rows) {
	ifstream infile(filename);
	vector< vector<double> >vec1;
	double num;
	if (!infile.is_open()) {
		cerr << "File Not Found";
	}

	//reads file, stores in 2d vector
	while (!infile.eof()) {
		char ch = infile.peek();
		if (ch == '#' || ch == '\n' || isalpha(ch)) {
			infile.ignore(100, '\n');
			continue;
		}

		for (int i = 0; i < rows; i++) {
			vector<double> temp;
			for (int j = 0; j < 3; j++) {
				infile >> num;
				temp.push_back(num);
			}
			vec1.push_back(temp);
		}

	}

	infile.close();
	return vec1;
}

//prints output matrix to output file
void printMat(vector<vector<double>> &a, int sizeA, string output) {
	sort(a.begin(), a.end(), sortj);
	sort(a.begin(), a.end(), sorti);
	ofstream write(output);
	
	for (int i = 0; i < a.size(); i++) {
		
		if (a[i][2] == 0 || a[i][0] < 0 || a[i][1] < 0 || (a[i][0] == a[i][2] && a[i][1] == a[i][2])) {
			continue;
		}
		else
			write << a[i][0] << fixed << setprecision(0) << " " << a[i][1] << setprecision(2) << " " << a[i][2] << fixed << setprecision(0) << endl;
	}
	write.close();
}

//searchs vector B for values in vector A.
//returns index of B if found; else returns number of rows in B
int searchArr(vector<vector<double>> &vec, int a, int b, int rows) {

	for (int i = 0; i < rows; i++)
		if (vec[i][0] == a && vec[i][1] == b)
			return i;
}
void append(vector<vector<double>> &a, int sizeA, vector<vector<double>> &b, int sizeB) {
	for (int i = 0; i < sizeB; i++) {
		int n = searchArr(a, b[i][0], b[i][1], sizeA);
		vector<double> temp;
		if (n == sizeA) {
			temp.push_back(b[i][0]);
			temp.push_back(b[i][1]);
			temp.push_back(b[i][2]);
		}
		else
			continue;
		a.push_back(temp);
	}
}
//recursive add function
void radd(vector<vector<double>> &a, int sizeA, vector<vector<double>> &b, int sizeB, string output, int i, int j) {
	if (i < sizeA) {

		int n = searchArr(b, a[i][0], a[i][1], sizeB);

		//if matching elements found increment values in the 3rd column
		if (n != sizeB) {
			a[i][2] += b[n][2];
		}
		radd(a, sizeA, b, sizeB, output, i + 1, j);
	}
	if (i == sizeA) {
		append(a, sizeA, b, sizeB);
		printMat(a, sizeA, output);
		//eix
	}
}

//add using loops
void add(vector<vector<double>> &a, int sizeA, vector<vector<double>> &b, int sizeB, string output) {
	for (int i = 0; i < sizeA; i++) {
		int n = searchArr(b, a[i][0], a[i][1], sizeB);

		if (n == sizeB)
			continue;

		else if ((a[i][0] == b[n][0]) && (a[i][1] == b[n][1])) {
			a[i][2] += b[n][2];
		}
	}
	append(a, sizeA, b, sizeB);
	printMat(a, sizeA, output);
}

#endif