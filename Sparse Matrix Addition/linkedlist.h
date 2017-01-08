#pragma once
#ifndef LINKED_LIST
#define LINKED_LIST
#include <iostream>
#include <fstream>
#include "arraylist.h"
using namespace std;


//node struct to hold values
struct node {
	double row;
	double col;
	double value;
	node *next;
	node *prev;
};

//global varialbes so all functions know what is being processed
node *matA, *matB, *matC, *head = NULL, *last = NULL;

//checks if linked list is empty
bool isEmpty(node *head) {
	return head == NULL ? true : false;
}
//inserts nodes into list
void push(node *&mat, double rw, double cl, double val) {
	
	//allocates memory
	node *temp, *tempval;
	temp = new node;
	//assigns variables data
	temp->row = rw;
	temp->col = cl;
	temp->value = val;

	temp->next = NULL;
	if (mat == NULL)
		mat = temp;
	else {
		tempval = mat;
		while (tempval->next != NULL) {
			tempval = tempval->next;
		}
		tempval->next = temp;
	}
}

//reads file into temp array and pushes into doubly linked list
void readFileLL(string filename, node *&number) {
	ifstream infile(filename);
	double tempMat[1000][3];

	while (!infile.eof()) {
		char ch = infile.peek();
		if (ch == '#' || ch == '\n' || isalpha(ch)) {
			infile.ignore(100, '\n');
			continue;
		}
		for (int i = 0; i < numLines(filename); i++) {
			for (int j = 0; j < 3; j++)
				infile >> tempMat[i][j];
			push(number, tempMat[i][0], tempMat[i][1], tempMat[i][2]);
		}
		infile.close();
	}

	if (isEmpty(number)) {
		cerr << "Empty File";
		exit(0);
	}
}

//prints linked list
void printLL(node *&mat, string filename) {
	ofstream write(filename);
	while (mat != NULL) {
		if (mat->value == 0 || mat->row < 0 || mat->col < 0 || (mat->row == mat->value && mat->col == mat->value)) {
			mat = mat->next;
			continue;
		}

		write << mat->row << " " << mat->col << " " << mat->value << " ";
		mat = mat->next;
		cout << endl;
	}
	write.close();
}

//searches list and return value if found; Else returns NULL
int searchLL(node *mat, double a, double b) {
	node * temp = mat;
	for (temp = mat; temp != NULL; temp = temp->next) {
		if (temp->row == a && temp->col == b) {
			return temp->value;
		}
	}
	return NULL;
}

//goes to the nth term and adds return the added values from both lists
double nth(node * mat1, int idx) {
	int count = 0;
	while (mat1 != NULL) {
		if (count == idx)
			return mat1->value;
		count++;
		mat1 = mat1->next;
	}
}

//appends all rows, coloumns and values that werent found in the search function
void appendLL(node * mat, node * mat1) {
	while (mat != NULL) {
		int n = searchLL(mat1, mat->row, mat->col);
		if (n == NULL) {
			push(matC, mat->row, mat->col, mat->value);
		}
		mat = mat->next;
	}
	while (mat1 != NULL) {
		int n = searchLL(mat, mat1->row, mat1->col);
		if (n == NULL) {
			push(matC, mat1->row, mat1->col, mat1->value);
		}
		mat1 = mat1->next;
	}

}

//iterative adding function
void addLL(node * mat, node * mat1, vector<vector<double>> &mat3, int rowsA, vector<vector<double>> &mat2, int rowsB, string output) {
	while (mat != NULL) {
		int n = searchLL(mat1, mat->row, mat->col);
		if (n != NULL) {
			push(matC, mat->row, mat->col, (mat->value + n));
		}
		else {
			appendLL(mat, mat1);
		}

		mat = mat->next;
	}
	add(mat3, rowsA, mat2, rowsB, output);
}

//recursive adding function
void raddLL(node * mat, node * mat1, vector<vector<double>> &mat3, int rowsA, vector<vector<double>> &mat2, int rowsB, string output) {
	if (mat == NULL) {
		add(mat3, rowsA, mat2, rowsB, output);
	}
	if (mat != NULL) {
		int n = searchLL(mat1, mat->row, mat->col);
		if (n != NULL) {
			push(matC, mat->row, mat->col, (mat->value + n));
		}
		else {
			appendLL(mat, mat1);
		}
		

		mat = mat->next;
		raddLL(mat, mat1, mat3, rowsA, mat2, rowsB, output);
	}
}
#endif