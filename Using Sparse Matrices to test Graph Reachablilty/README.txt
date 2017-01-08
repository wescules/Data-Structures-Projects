Compile the code using the command:
g++ -std=c++11 *.cpp -o reachability

Run the executable with the command:
./reachability "E=<FILE>;labels=<FILE>;result=<FILE>;source=<INTEGER>;dfs=<no|recursive|iterative>"
 




used information on Wikipedia and pseudocode posted on website to program DFS and Stack implementation, 
also used code from lab to help create a hashtable
took inspiration for dfs from:
http://www.geeksforgeeks.org/depth-first-traversal-for-a-graph/


			*****************************************************
			*		EXTRA CREDIT FOR HW3		    *
			*****************************************************





			*****************************************************
			*		SEARCH ALGORITHIM		    *
			*****************************************************

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



			*****************************************************
			*			SORTING		            *
			*****************************************************


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

