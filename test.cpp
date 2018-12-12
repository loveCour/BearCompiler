#include <iostream>
#include <cstdarg>
#include "ast.h"

using namespace std;

template <typename T>
T* createNode(AST* ch1, ...)
{
	va_list ap;
	va_start(ap, ch1);
	T* newNode = new T();
	bool isSuccessed = newNode->AddChild(ch1);
	if (!isSuccessed) {
		delete newNode;
		return nullptr;
	}
	for (int i = 0; i < T::NUMOFCHILD - 1; i++) {
		isSuccessed = newNode->AddChild(va_arg(ap, AST*));
		if (!isSuccessed) {
			delete newNode;
			return nullptr;
		}
	}
	va_end(ap);
	return newNode;
}

template <typename T>
T* createNode()
{
	return new T();
}

int main() {
	ctest* c1 = createNode<ctest>();
	c1->a = 1;
	ctest* c2 = createNode<ctest>();
	c2->a = 2;
	ctest* c3 = createNode<ctest>();
	c3->a = 3;
	ctest* c4 = createNode<ctest>();
	c4->a = 4;
	defproc* dp = createNode<defproc>(c1, c2,c3,c4);
	dp->PrintCode();
}