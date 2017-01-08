#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "ArgumentManager.h"
using namespace std;

//function to count the number of lines
int NumLines(string filename) {
	ifstream file;
	string str;
	short rows = 0;
	file.open(filename);
	file.ignore(100, '\n');
	//counts rows
	while (!file.eof()) {
		getline(file, str);
		rows++;
	}
	file.close();
	return rows;
}

int main(int argc, char *argv[]){
	ArgumentManager am(argc, argv);
	string a = am.get("A");
	string c = am.get("C");
	ifstream file(a.c_str());
	ofstream write(c.c_str());
	if(!file.is_open()){
		cout<<"File doesn't exist"<<endl;
		return 0;
	}
	
	
	//ignores first line that's supposed to be commented;
	file.ignore(100, '\n');
	double num;
	short numOfLines  = (NumLines(a));
	vector<double> mat;
	
	

	//stores numbers in the matrix vector
	while (file >> num) {
		mat.push_back(num);
	}
	
	//error checks for rectangular matrixes or empty matrixes
	int num1 = mat.size();
	if (num1 != (numOfLines * numOfLines) || (num1 == 0 && numOfLines == 0)) {
		cout << "Error Matrix is either empty or not square" << endl;
		return 0;
	}
		
	
	int k = 0;
	//initializes result matrix to 0's got error messages if i didn't initialize
	double mat2[20][20], result[20][20] = {0};
	
	//converts 1d array to 2d array
	for (int i = 0; i < numOfLines; i++) {
		for (int j = 0; j < numOfLines; j++) {
			mat2[i][j] = mat[k];
			k++;
		}
	}
	
	double temp;

	//matrix multiplication algorithm
	for (int i = 0; i < numOfLines; i++) {
		for (int j = 0; j < numOfLines; j++) {
			temp = 0;
			for (int k = 0; k < numOfLines; k++) {
				temp += mat2[i][k] * mat2[k][j];
				result[i][j] = temp;
			}
		}
	}

	//prints matrix
	for (int i = 0; i < numOfLines; i++) {
		for (int j = 0; j < numOfLines; j++) {
			write << fixed << setprecision(2) << result[i][j] << " ";
		}
		write << endl;
	}
	write.close();
	file.close();
	return 0;
}

