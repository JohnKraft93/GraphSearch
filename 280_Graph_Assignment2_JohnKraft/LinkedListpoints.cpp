/*
280
Graph_Assignment2
John Kraft
*/

#include <iostream>
#include "listofpoints.h"
using namespace std;

listofpoints::listofpoints() {
	top = nullptr;
	size = 0;
}

Node* listofpoints::pointtop() {
	return top;
}

void listofpoints::addPoint(char v, int w) {
	if (exist(v) == false) {
		Node* runner = new Node;
		Node* temp = new Node;
		temp->data = v;
		temp->weight = w;
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
		size++;
	}
} //addword

void listofpoints::display() {
	Node* runner = top;
	while (runner != nullptr) {
		cout << runner->data << " " << runner->weight << " ";
		runner = runner->next;
	}
	cout << endl;
} //display

bool listofpoints::exist(char v) {
	Node* runner = top;
	for (int i = 0; i < size; i++) {
		if (runner == NULL) {
			return false;
		}
		if (runner->data == v) {
			return true;
		}
		runner = runner->next;
	}
	return false;
} //exist

int listofpoints::weight(char v) {
	Node* runner = top;
	for (int i = 0; i < size; i++) {
		if (runner->data == v) {
			return runner->weight;
		}
		runner = runner->next;
	}
}