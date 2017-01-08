#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "ArgumentManager.h"
#include "arraylist.h"
#include "linkedlist.h"

using namespace std;


int main(int argc, char *argv[]) {
	ArgumentManager am(argc, argv);
	string op = am.get("operation");
	string str = am.get("storage");
	string rec = am.get("recursive");
	string a = am.get("A");
	string b = am.get("B");
	string c = am.get("result");

	//preloads data into memory instead of copy/pasting code 4 times;
	string fileA = a.c_str(), fileB = b.c_str(), output = c.c_str();
	string operation = op.c_str(), storage = str.c_str(), recursive = rec.c_str();


		vector< vector<double> > mat, mat2, mat3;
		int rowsA = numLines(fileA);
		int rowsB = numLines(fileB);
		int i = 0, j = 0;					//i j values for the recursive functions
		matA = NULL, matB = NULL, matC = NULL;			//initilizes the head of all lists to NULL //GLOBAL VARIABLE
			
		//reads file into arrays
		mat = readFile(fileA, rowsA);
		mat2 = readFile(fileB, rowsB);
		
		//reads file into doubly linked lists
		readFileLL(fileA, matA);
		readFileLL(fileB, matB);
	
	
		if((str == "array" || str == "Array") && (rec == "N" || rec == "n"))
			add(mat, rowsA, mat2, rowsB, output);
		if ((str == "array" || str == "Array") && (rec == "Y" || rec == "y")) {
			int i = 0, j = 0;
			radd(mat, rowsA, mat2, rowsB, output, i, j);
		}
		if((str == "LinkedList" || str == "linkedlist") && (rec == "N" || rec == "n"))
				addLL(matA, matB, mat, rowsA, mat2, rowsB, output);
		if ((str == "LinkedList" || str == "linkedlist") && (rec == "Y" || rec == "y"))
				raddLL(matA, matB, mat, rowsA, mat2, rowsB, output);


	return 0;
}
