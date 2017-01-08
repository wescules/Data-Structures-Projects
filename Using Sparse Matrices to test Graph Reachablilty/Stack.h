#pragma once
#ifndef STACK
#define STACK

class Stack {
protected:
	int a;
	list<int> *dfsmat;    
public:
	Stack(int V);   // Constructor
	void addEdge(int v, int w);   // adds edges to graph
	vector<int> DFSiterative(int v);
};
Stack::Stack(int V) {
	//points to vaiable in protected class so all fucntions can use it
	this->a = V;
	dfsmat = new list<int>[V];
}
void Stack::addEdge(int v, int w) {
	dfsmat[v].push_back(w);
}
vector<int> Stack::DFSiterative(int v) {
	//mark all vertives as not visited
	bool *visited = new bool[a];
	for (int i = 0; i < a; i++) {
		visited[i] = false;
	}

	stack<int> stack;
	//mark current node as visited and pop it off the stack
	visited[v] = true;
	stack.push(v);
	list<int>::iterator i;

	vector<int> ithold;
	while (!stack.empty()) {
		//pops and prints each vertex
		v = stack.top();
		ithold.push_back(v);
		stack.pop();
		for (i = dfsmat[v].begin(); i != dfsmat[v].end(); i++) {
			if (!visited[*i]) {
				visited[*i] = true;
				stack.push(*i);
			}
		}
	}
	sort(ithold.begin(), ithold.end());
	return ithold;
}


#endif