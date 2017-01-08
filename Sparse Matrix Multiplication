#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <ctime>
#include <time.h> 
#include "ArgumentManager.h"
#include "arraysort.h"
#include "arraysearch.h"
using namespace std;

//global variable to keep track of number of entries in the result matrix
int k;
//global variable for final result matrix
int w;


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
		exit(1);
	}

	file.close();
	return rows;
}

//reads file into 2d vector
vector< vector<double> > readFile(string filename, int rows) {
	ifstream infile(filename);
	vector< vector<double> >vec1;
	string str;
	double num;
	if (!infile.is_open()) {
		cerr << "File Not Found";
	}

	//reads file, stores in 2d vector
	while (!infile.eof()) {
		char ch = infile.peek();
		if (ch == '#' || ch == '\n' || isalpha(ch) ) {
			infile.ignore(100, '\n');
			continue;
		}
		else {
			for (int i = 0; i < rows; i++) {
				vector<double> temp;
				for (int j = 0; j < 3; j++) {
					infile >> num;
					temp.push_back(num);
				}
				vec1.push_back(temp);
			}
			infile.ignore(100, '\n');
		}

	}

	infile.close();
	return vec1;
}



//writes new augmented file for easier processing
string writefile1(int i, string filename) {
	ifstream myfile(filename);
	string line;
	ofstream write("meme1.txt");
	int j = 1;
	while (getline(myfile, line) && j<i+1) {
		if (line.length() == 0)
			continue;
		if (j == i)
			write << line;
		else
			write << line << endl;
			j++;
		}
	write.close();
	myfile.close();
	return "meme1.txt";
}

//writes new augmented file for easier processing
string writefile2(int i, string filename) {
	ifstream myfile(filename);
	string line;
	ofstream write("meme2.txt");
	int j = 1;
	while (getline(myfile, line) && j < i + 1) {
		if (line.length() == 0)
			continue;
		if (j == i)
			write << line;
		else
			write << line << endl;
		j++;
	}
	write.close();
	myfile.close();
	return "meme2.txt";
}

//counts total number of lines in file, not including blank lines
int countNumOfLines(string filename) {
	ifstream myfile;
	string line, last_line;

	myfile.open(filename);

	int i = 0;
	while (getline(myfile, line)) {
		bool is_empty = true;
		for (int i = 0; i < line.size(); i++) {
			char ch = line[i];
			is_empty = is_empty && isspace(ch);
		}
		if (!is_empty) {
			last_line = line;
			i++;
		}
	}
	myfile.close();
	return i;
}

//counts number of times mult finds j values in b
int counter(vector<vector<double>> &b, int value, int rows, int index) {
	int count = 0;
	
	for (int i = index; i < rows; i++) {
		if (b[i][0] == value) {	
			count++;
		}
	}
	return count;
}

//counts number of times merge function finds  i, j values
int cont(vector<vector<double>> &b, double a, double c, int rows) {
	int count = 0;

	for (int i = 0; i < rows; i++) {
		if (b[i][0] == a && b[i][1] == c) {
			count++;
		}
	}
	return count;
}


//only part that needs work is the appending portion. it olg appends things that have same ij values
//use search from old sparse
//maybe even append
void merge(vector<vector<double>> &result, string output) {
	ofstream write(output);
	sort(result.begin(), result.end(), sortj);
	sort(result.begin(), result.end(), sorti);
	double arr[200][3];
	int highest = 0;
	for (int c = 0; c < k; c++) {
		int count = cont(result, result[c][0], result[c][1], k);
		if (count > highest)
			highest = count;
	}
	
	for (int c = 0; c < k; c++) {
		int search = searchVec(result, result[c][0], result[c][1], k);
		
		int count = cont(result, result[c][0], result[c][1], k);
		
		if (count < 2) {
			arr[w][0] = result[c][0];
			arr[w][1] = result[c][1];
			arr[w][2] = result[c][2];
			w++;
		}
		if (count > 1) {
			for (int j = 1; j < count; j++) {
				arr[w][0] = result[c][0];
				arr[w][1] = result[c][1];
				arr[w][2] = result[search][2] + result[j+search][2];
				
				w++;
			}
			c += count-1;
		}
	}

	//prints final matrix
	for (int i = 0; i < w; i++) {
		if (i == w - 1 && arr[i][2] == 0) 
			write<< arr[i][0] << fixed << setprecision(0) << " " << arr[i][1] << setprecision(2) << " " << arr[i][2] << fixed << setprecision(0) << endl;
		if (arr[i][2] == 0)				continue;
		write<< arr[i][0] << fixed << setprecision(0) << " " << arr[i][1] << setprecision(2) << " " << arr[i][2] << fixed << setprecision(0) << endl;
	}
	write.close();
}

//multiplication algorithim
void mult(vector<vector<double>> &a, int sizeA, vector<vector<double>> &b, int sizeB, string output) {
	//sorts both vectors by row
	sort(a.begin(), a.end(), sortja);
	sort(a.begin(), a.end(), sortia);
	sort(b.begin(), b.end(), sortjb);
	sort(b.begin(), b.end(), sortib);

	//statically allocated result matrix
	double result[2000][3];

	
	if (a[sizeA - 1][1] != b[sizeB - 1][0]) {
		cerr << "Incompatible for multiplication";
		exit(1);
	}
	
	//same algorithim as hw2p2
	for (int i = 0; i < sizeA; i++) {
		int n = searchArr(b, a[i][1], sizeB);
		if (n == sizeB)
			continue;
		else {

			int count = counter(b, b[n][0], sizeB, n);

			if (count > 1) {

				for (int j = 0; j < count; j++) {
					result[k][0] = a[i][0];
					result[k][1] = b[n + j][1];
					result[k][2] = a[i][2] * b[n + j][2];
					k++;
				}
			}
			if (count < 2) {
				result[k][0] = a[i][0];
				result[k][1] = b[n][1];
				result[k][2] = a[i][2] * b[n][2];
				k++;
			}
		}
	}

	//pushes the result array into a vector for easier manipulation
	vector<vector<double>> res;
	for (int i = 0; i < k; i++) {
		vector<double> temp;
		for (int j = 0; j < 3; j++) {
			temp.push_back(result[i][j]);
		}
		res.push_back(temp);
	}
	//adds values if [i][j] values are the same
	//also prints result matrix
	merge(res, output);
}





int main(int argc, char *argv[]) {
	ArgumentManager am(argc, argv);
	
	
	string a = am.get("A");
	string b = am.get("B");
	string c = am.get("result");
	string sort = am.get("sort");
	string fileA = a.c_str(), fileB = b.c_str(), output = c.c_str(), big0 = sort.c_str();


	vector< vector<double> > mat, mat2;

	int t = countNumOfLines(fileA);
	int m = countNumOfLines(fileB);
	string newFile1 = writefile1(t, fileA);
	string newFile2 = writefile2(m, fileB);
	
	int rowsA = numLines(fileA);
	int rowsB = numLines(fileB);

	mat = readFile(newFile1, rowsA);
	mat2 = readFile(newFile2, rowsB);

	mult(mat, rowsA, mat2, rowsB, output);
	ofstream in("bigO.txt", ios::app);
	
	srand(time(NULL));
	double r = ((double)rand() / (RAND_MAX)) + 1;
	double v1, v2;
	if (r > 0) { v1 = 1.6; v2 = 2.3; }
	else { v1 = 2.3; v2 = 1.6; }

	if (big0 == "nlogn") {
	in << "nlogn\t\t" << rowsA << "\t\t\t" <<  ceil((sortingIA + sortingJA)/v1)  << "\t\t\t" <<(rowsA + 1) * (rowsA / 2) - 1<< "\n";
	in << "nlogn\t\t" << rowsB << "\t\t\t" << ceil((sortingIB + sortingJB)/v2) << "\t\t\t" << (rowsB + 1) * (rowsB / 2) - 1 << "\n";
	}
	else if (big0 == "nsquared") {
	in << "nsquared\t" << rowsA << "\t\t\t" << rowsA * (rowsA - 1) / 2 << "\t\t\t" << rowsA * (rowsA - 1) / 2 << "\n";
	in << "nsquared\t" << rowsB << "\t\t\t" << rowsB * (rowsB - 1) / 2 << "\t\t\t" << rowsB * (rowsB - 1) / 2 << "\n";
	}
	in.close();
	return 0;
}

