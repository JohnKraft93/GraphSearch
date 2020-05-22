/*
280
Graph_Assignment2
John Kraft
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include "listofpoints.h"

using namespace std;


const int INFINITE = 9999;

struct startNode {
	char data;
	startNode* next;
	listofpoints points;
};

class startLinkedList {
private:
	startNode* top;
	int count;
	int num;
	void DFS(int v, vector<bool>& visited);
	void CONNECTED(int v, vector<bool>& visited);
	void BFS(int v, vector<bool>& visited);

public:
	startLinkedList();
	void addto(char w, char v, int weight);
	void append(char w);
	bool exist(char v);
	void display();
	startNode* find(char v);
	char findData(int v);
	int findPos(char v);
	void buildMatrix();
	void displayMatrix();
	void ADJACENT(char v);
	void BFS(char v);
	void DFS(char v);
	bool CONNECTED();
	void dijkstra(char startVertex, char desiredVertex);

};

startLinkedList::startLinkedList() {
	top = nullptr;
	count = 0;
	num = 0;
}

startNode* startLinkedList::find(char v) {
	startNode* temp = top;
	for (int i = 0; i < count; i++) {
		if (temp->data == v) {
			return temp;
		}
		else {
			temp = temp->next;
		}
	}
	return nullptr;
} //FIND

int startLinkedList::findPos(char v) {
	startNode* temp = top;
	for (int i = 0; i < count; i++) {
		if (temp->data == v) {
			return i;
		}
		else {
			temp = temp->next;
		}
	}
	return NULL;
} //LOCATE POSITION BY VERTEX

char startLinkedList::findData(int v) {
	startNode* temp = top;
	for (int i = 0; i < count; i++) {
		if (i == v) {
			return temp->data;
		}
		else {
			temp = temp->next;
		}
	}
	return NULL;
} //LOCATE VERTEX BY POSITION

bool startLinkedList::exist(char v) {
	startNode* runner = top;
	for (int i = 0; i < count; i++) {
		if (runner == nullptr) {
			return false;
		}
		if (runner->data == v) {
			return true;
		}
		runner = runner->next;
	}
	return false;
} //EXIST

void startLinkedList::addto(char w, char v, int weight) {
	startNode* tmp = find(w);
	tmp->points.addPoint(v, weight);
} //ADD VERTEX

void startLinkedList::append(char w) {
	if (exist(w) != true) {
		startNode* runner = new startNode;
		startNode* temp = new startNode;
		temp->data = w;
		if (top == nullptr) {
			temp->next = nullptr;
			top = temp;
		}
		else if (temp->data <= top->data) {
			temp->next = top;
			top = temp;
		}
		else {
			runner = top;
			while (runner->next != nullptr && runner->next->data < temp->data) {
				runner = runner->next;
			}
			temp->next = runner->next;
			runner->next = temp;
		}
		count++;
	}
} //APPEND

vector<vector<int>> graph;

void startLinkedList::buildMatrix() {
	graph.resize(count, vector<int>(count));
	startNode* runner = top;
	for (int i = 0; i < count; i++) {
		startNode* tmp = top;
		for (int j = 0; j < count; j++) {
			if (runner->points.exist(tmp->data) && runner->data != tmp->data) {
				graph[i][j] = runner->points.weight(tmp->data);
			}
			else if (i == j) {
				graph[i][j] = 0;
			}
			else {
				graph[i][j] = -1;
			}
			tmp = tmp->next;
		}
		runner = runner->next;
	}
} //BUILD MATRIX

void startLinkedList::displayMatrix() {
	cout << "Matrix:" << endl;
	for (int i = 0; i < count; i++) {
		cout << "{ ";
		for (int j = 0; j < count; j++) {
			cout << graph[i][j] << " ";
		}
		cout << " }" << endl;
	}
} //DISPLAY MATRIX

void startLinkedList::ADJACENT(char v) {
	int pos = findPos(v);
	startNode* tmp = new startNode;
	cout << "ADJACENT OF " << v << ": ";
	for (int i = 0; i < count; i++) {
		if (graph[pos][i] >= 1) {
			cout << findData(i) << " ";
		}
	}
	cout << endl << endl;
} //ADJACENT

void startLinkedList::DFS(int v, vector<bool>& visited) {
	stack<int> stack;
	startNode* tmp = top;
	stack.push(v);

	while (!stack.empty()) {
		v = stack.top();
		stack.pop();
		if (!visited[v]) {
			cout << findData(v) << " ";
			visited[v] = true;
		}
		for (int i = 0; i < count; i++) {
			if (!visited[i] && graph[v][i] >= 1) {
				stack.push(i);
			}
		}
	}
} //DFS helper

void startLinkedList::DFS(char v) {
	cout << "DFS OF " << v << ": ";
	// Mark all the vertices as not visited 
	vector<bool> visited(count, false);
	int x = findPos(v);
	if (!visited[x]) { DFS(x, visited); }
	cout << endl << endl;
} //DFS

void startLinkedList::CONNECTED(int v, vector<bool>& visited) {
	//int num = 0;
	stack<int> stack;
	startNode* tmp = top;
	stack.push(v);

	while (!stack.empty()) {
		num++;
		v = stack.top();
		stack.pop();
		if (!visited[v]) {
			//cout << findData(v) << " ";
			visited[v] = true;
		}
		for (int i = 0; i < count; i++) {
			if (!visited[i] && graph[v][i] >= 1) {
				stack.push(i);
			}
		}
	}
}//CONNECTED Helper

bool startLinkedList::CONNECTED() {
	// Mark all the vertices as not visited 
	for (int i = 0; i < count; i++) {
		vector<bool> visited(count, false);
		if (!visited[i]) { CONNECTED(i, visited); }

		if (num < count) {
			return false;
		}
		num = 0;
	}
	return true;
} //CONNECTED

void startLinkedList::BFS(int v, vector<bool>& visited) {
	//int num = 0;
	queue<int> queue;
	startNode* tmp = top;
	queue.push(v);

	while (!queue.empty()) {
		num++;
		v = queue.front();
		queue.pop();
		if (!visited[v]) {
			cout << findData(v) << " ";
			visited[v] = true;
		}
		for (int i = 0; i < count; i++) {
			if (!visited[i] && graph[v][i] >= 1) {
				queue.push(i);
			}
		}
	}
}

void startLinkedList::BFS(char v) {
	cout << "BFS OF " << v << ": ";
	// Mark all the vertices as not visited 
	vector<bool> visited(count, false);
	int x = findPos(v);
	if (!visited[x]) { BFS(x, visited); }
	cout << endl << endl;
}

void startLinkedList::display() {
	cout << "Character Linked List: " << endl;
	startNode* tmp = top;
	while (tmp != nullptr) {
		cout << tmp->data << endl;
		tmp->points.display();
		tmp = tmp->next;
	}
	cout << endl;
} //display

void startLinkedList::dijkstra(char startVertex, char desiredVertex) {
	vector<char> from(count, -1);
	vector<int> distance(count);
	vector<bool> finished(count, false);
	int sV = findPos(startVertex);
	int dV = findPos(desiredVertex);
	for (int i = 0; i < count; i++) {
		if (graph[sV][i] != -1) {
			distance[i] = graph[sV][i];
		}
		else {
			distance[i] = INFINITE;
		}
	}
	finished[0] = true;
	from[0] = startVertex;
	for (int i = 0; i < count; i++) {
		int v = INFINITE;
		int pos = 0;
		for (int itr = 0; itr < count; itr++) {
			if (distance[itr] < v && finished[itr] == false) {
				v = distance[itr];
				pos = itr;
			}
		}
		finished[pos] = true;
		if (distance[dV] == INFINITE && finished[dV] == true) {
			cout << "DISTANCE FROM " << startVertex << " TO " << desiredVertex << ": DNE." << endl << endl;
			return;
		}
		else if (finished[dV] == true) {
			cout << "DISTANCE FROM " << startVertex << " TO " << desiredVertex << ": " << distance[dV] << endl;
			cout << "\tEdges: ";
			from[count - 1] = desiredVertex;
			for (int e = 0; e < count; e++) {
				if (from[e] != -1 && e != 0) {
					cout << "->";
				}
				if (from[e] != -1) {
					cout << from[e];
				}
			}
			cout << endl << endl;
			return;
		}
		for (int j = 0; j < count; j++) {
			if (v + graph[pos][j] < distance[j] && graph[pos][j] != -1) {
				distance[j] = v + graph[pos][j];
				if (j == findPos(desiredVertex)) {
					from[j - 1] = findData(pos);
				}
			}
		}
	}
	cout << "DISTANCE FROM " << startVertex << " TO " << desiredVertex << ": DNE." << endl << endl;
}

int main() {
	startLinkedList cll = startLinkedList();
	string str;
	ifstream ifile("vertice.txt");

	while (getline(ifile, str)) {
		for (int i = 0; i < str.size(); i += 4) {
			cll.append(str[i]);
			if (i != 0) {
				cll.addto(str[0], str[i], int(str[i + 2]) - 48);
			}
		}
	}
	ifile.close();
	//cll.display();
	cll.buildMatrix();
	cll.displayMatrix();

	string command;
	char vertex;
	char toNode;
	ifstream cfile("commands.txt");

	while (cfile >> command) {
		if (command == "ADJACENT") {
			cfile >> vertex;
			cll.ADJACENT(vertex);
		}
		else if (command == "DFS") {
			cfile >> vertex;

			cll.DFS(vertex);
		}
		else if (command == "BFS") {
			cfile >> vertex;
			cll.BFS(vertex);
		}
		else if (command == "CONNECTED") {
			if (cll.CONNECTED() == true) {
				cout << "THE GRAPH IS CONNECTED." << endl << endl;
			}
			else {
				cout << "THE GRAPH IS NOT CONNECTED." << endl << endl;
			}
		}
		else if (command == "DIJKSTRA") {
			cfile >> vertex >> toNode;
			cll.dijkstra(vertex, toNode);
		}
	}
	cfile.close();
} //main