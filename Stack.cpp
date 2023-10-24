#include "Stack.h"

Stack::Stack()
{
	this->firstStack = this->lastStack = nullptr;
}


void Stack::addToStack(string state)
{
	ElemStack* tmp = new ElemStack;
	tmp->next = nullptr;
	tmp->state = state;

	if (this->firstStack == nullptr) {
		this->firstStack = this->lastStack = tmp;
	}
	else {
		this->lastStack->next = tmp;
		this->lastStack = tmp;
	}
}

void Stack::removeFromStack()
{
	ElemStack* curr = this->firstStack;
	while (curr->next->next != nullptr) curr = curr->next;//trazimo pretposlednji element liste
	curr->next = nullptr;
	ElemStack* tmp = this->lastStack;
	this->lastStack = curr;
	delete tmp;
}

string Stack::getPreviousState()
{
	return this->lastStack->state;
}

ElemStack* Stack::getHead()
{
	return this->firstStack;
}

void Stack::deleteStack()
{
	ElemStack* curr = this->firstStack;
	ElemStack* old;
	while (curr != nullptr) {
		old = curr;
		curr = curr->next;
		delete old;
	}

}
