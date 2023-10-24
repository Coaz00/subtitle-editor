#ifndef STACK_H
#define STACK_H

#include<string>
using namespace std;

typedef struct element_stack {
	string state;
	struct element_stack* next;

}ElemStack;

class Stack {
public:
	Stack();

	void addToStack(string txt);
	void removeFromStack();
	string getPreviousState();

	ElemStack* getHead();

	void deleteStack();
private:
	ElemStack* firstStack;
	ElemStack* lastStack;
};

#endif