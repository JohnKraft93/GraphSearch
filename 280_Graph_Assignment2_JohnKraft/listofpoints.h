/*
280
Graph_Assignment2
John Kraft
*/

#include <iostream>
using namespace std;

struct Node {
	char data;
	int weight;
	int dist;
	Node* next;
};

class listofpoints {
private:
	Node* top;
	int size;
public:
	listofpoints();
	void addPoint(char, int);
	void display();
	bool exist(char);
	Node* pointtop();
	int weight(char);
};