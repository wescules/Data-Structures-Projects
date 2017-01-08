#include <iostream>
#include <vector>
#include<list>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <map>
#include <stack>
#include "ArgumentManager.h"
#include "arraysort.h"
#include "arraysearch.h"
#include "Stack.h"
#include "Hash.h"
using namespace std;

//global variable to keep track of number of entries in the result matrix
int k;
//global variable for final result matrix
int w;
vector<int> holder;
class DFSmatrix
{
protected:
	int a;
	list<int> *dfsmat;    //array for storing matrix
	
public:
	DFSmatrix(int V);   // Constructor
	void addEdge(int v, int w);   // adds edges to graph
	void  DFSrecursive(int v, bool visited[]);
	void DFS(int v);

};

DFSmatrix::DFSmatrix(int V) {
	//points to vaiable in protected class so all fucntions can use it
	this->a = V;
	dfsmat = new list<int>[V];
}

void DFSmatrix::addEdge(int v, int w) { dfsmat[v].push_back(w); }

void DFSmatrix::DFSrecursive(int v, bool visited[]){
	
	//current is marteked as true or 1
	visited[v] = true;
	holder.push_back(v);
	//same code as shown in lab
	list<int>::iterator i;
	for (i = dfsmat[v].begin(); i != dfsmat[v].end(); ++i) {
		if (!visited[*i]) {
			DFSrecursive(*i, visited);
		}
	}
}

//needs to be its own function since dfs is recursive
void DFSmatrix::DFS(int v)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[a];
	for (int i = 0; i < a; i++)
		visited[i] = false;
	//call recursive function
	DFSrecursive(v, visited);
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
		if (ch == '#' || ch == '\n' || isalpha(ch)) {
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
	while (getline(myfile, line) && j<i + 1) {
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

void readFile1(string filename) {
	ofstream write(filename);
	string fileA = "1a.txt";
	vector< vector<double> > mat;
	int t = countNumOfLines(fileA);
	string newFile1 = writefile1(t, fileA);
	int rowsA = numLines(fileA);
	mat = readFile(newFile1, rowsA);
	vector<double> vec;

	for (int i = 0; i < rowsA; i++) {
		vec.push_back(mat[i][1]);
	}
	sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	for (int i = 0; i < vec.size(); i++) {
		write << vec[i] << endl;
	}
	write.close();
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
vector<vector<double>> res;
//multiplication algorithim
void mult(vector<vector<double>> &a, int sizeA, vector<vector<double>> &b, int sizeB, string output, string fileA, int source) {


	//statically allocated result matrix
	double result[20000][3];
	ofstream write(fileA);
	write << "1" << " " << source << " " << "1.00" << endl;

	//SORTS vector first by second rowm, then by first row. this aligns them properly and is sorted correctly every time
	Nlognsort(a, 1);
	Nlognsort(a, 0);
	//same algorithim as hw2p2
	for (int i = 0; i < sizeA; i++) {

		//IMPLEMENTATION OF BINARY SEARCH
		int n = binSearch(b, a[i][1], sizeB);

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

	for (int i = 0; i < k; i++) {
		vector<double> temp;
		for (int j = 0; j < 3; j++) {
			temp.push_back(result[i][j]);
		}
		res.push_back(temp);
	}

	//writes maltipolicants to output file
	for (int i = 0; i < k; i++) {
		if (res[i][2] == 0 || res[i][0] != 1)				continue;
		write << res[i][0] << fixed << setprecision(0) << " " << res[i][1] << setprecision(2) << " " << res[i][2] << fixed << setprecision(0) << endl;

	}

	write.close();
}

void m(int source, string fileB) {

	string fileA = "1a.txt", output = "hello.txt";
	ofstream file1("1a.txt", ios::app);
	file1 << "1" << " " << source << " " << "1" << endl;


	vector< vector<double> > mat, mat2;

	int t = countNumOfLines(fileA);
	int m = countNumOfLines(fileB);

	string newFile1 = writefile1(t, fileA);
	string newFile2 = writefile2(m, fileB);

	int rowsA = numLines(fileA);
	int rowsB = numLines(fileB);

	mat = readFile(newFile1, rowsA);
	mat2 = readFile(newFile2, rowsB);

	mult(mat, rowsA, mat2, rowsB, output, fileA, source);
}


int main(int argc, char *argv[]) {
	ArgumentManager am(argc, argv);


	string a = am.get("E");
	string b = am.get("labels");
	string c = am.get("result");
	string src = am.get("source");
	string dfs = am.get("dfs");
	
	string fileA = a.c_str(), label = b.c_str(), output = c.c_str(), source = src.c_str(), depthSearch = dfs.c_str();
	int srcs = stoi(source);
	vector< vector<double> > mat;
	int t = countNumOfLines(fileA);
	string newFile1 = writefile1(t, fileA);
	int rowsA = numLines(fileA);
	mat = readFile(newFile1, rowsA);


	//labels stuff
	
	int q = countNumOfLines(label);
	string labelNew = writefile1(q, label);
	int rowsLabel = numLines(label);

	//reads labels file into hashtable
	ifstream infile(label);
	string textline;
	HashMap hash;
	int key; string value;
	while (getline(infile, textline)) {
		string space;
		istringstream text_stream(textline);
		text_stream >> key;
		getline(text_stream, space, ' '); // Read characters after number until space.
		text_stream >> value;
		hash.insert(key, value);				//reads into hastable
	}

	infile.close();
	ofstream write(output);
	
	//vector matrix multiplication using binary search and sorting
	if (depthSearch == "no" || depthSearch == "no") {
		Stack g(100000);
		for (int i = 0; i < rowsA; i++) {
			g.addEdge(mat[i][0], mat[i][1]);
		}
		vector<int> iterativeVector = g.DFSiterative(srcs);
		int vecSize = iterativeVector.size();
		for (int i = 0; i < vecSize; i++) {
			write<< iterativeVector[i] << " " << hash.get(iterativeVector[i]) << endl;
		}
	}

	//recursive dfs inmplentation
	else if (depthSearch == "yes" || depthSearch == "Yes" || depthSearch == "recursive" || depthSearch == "Recursive") {
		DFSmatrix g(100000);
		for (int i = 0; i < rowsA; i++) {
			g.addEdge(mat[i][0], mat[i][1]);
		}
		g.DFS(srcs);
		sort(holder.begin(), holder.end());
		int vecSize = holder.size();
		for (int i = 0; i < vecSize; i++) {
			write << holder[i] << " " << hash.get(holder[i])<<endl;
		}
	}

	//stack implementation
	else if (depthSearch == "iterative" || depthSearch == "Iterative") {
		Stack g(100000);
		for (int i = 0; i < rowsA; i++) {
			g.addEdge(mat[i][0], mat[i][1]);
		}
		vector<int> iterativeVector = g.DFSiterative(srcs);
		int vecSize = iterativeVector.size();
		for (int i = 0; i < vecSize; i++) {
			write << iterativeVector[i] << " " << hash.get(iterativeVector[i])<<endl;
		}
	}
	return 0;
}
