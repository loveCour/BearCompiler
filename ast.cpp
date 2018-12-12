#include "ast.h"


NUM_Leaf::NUM_Leaf()
{
}

void NUM_Leaf::PrintCode() {
}

void NUM_Leaf::SetValue(int i)
{
	ival = i;
}

ID_Leaf::ID_Leaf()
{
}

void ID_Leaf::PrintCode()
{
	cout << sval;
}

void ID_Leaf::SetValue(string s)
{
	sval = s;
}

UnFixedNumOfChildNode::UnFixedNumOfChildNode(string str, int i)
	:symbol(str), val(i)
{
}


void UnFixedNumOfChildNode::AddChild(AST * newNode)
{
	Childs.push_back(newNode);
}


void dparams::PrintCode()
{
	int size = Childs.size();
	for (int i = 0; i < size ; i++)
	{
		Childs[i]->PrintCode();
		if (i < size - 1) cout << ", ";
	}
}

dparams::dparams()
	: UnFixedNumOfChildNode("dparams")
{
}


FixedNumOfChildNode::FixedNumOfChildNode(const int max, string s, int i)
	: MAX(max), symbol(s),Val(i), curNum(0)
{
}

bool FixedNumOfChildNode::AddChild(AST * newNode)
{
	if (curNum < MAX) {
		Childs[curNum] = newNode;
		curNum++;
	}
	else {
		cout << symbol << " overflow!";
		return false;
	}
	return true;
}

inline bool FixedNumOfChildNode::isChildNumOK()
{
	return MAX == curNum;
}

void deffunc::PrintCode()
{
	if (!isChildNumOK()) {
		cout << symbol << "의 자식이 부족하다!";
		return;
	}
	cout << RetType << " ";
	Childs[0]->PrintCode();
	cout << "(";
	Childs[1]->PrintCode();
	cout << ")";
	cout << "{";
	Childs[2]->PrintCode();
	cout << "}";
}

deffunc::deffunc() : FixedNumOfChildNode(NUMOFCHILD, "deffunc")
{
}

void param::PrintCode()
{
	cout << type <<" ";
	Childs[0]->PrintCode();
}

param::param() : FixedNumOfChildNode(1, "param")
{
}

void param::SetType(string t)
{
	type = t;
}

void defproc::PrintCode()
{
	if (!isChildNumOK()) {
		cout << symbol << "의 자식이 부족하다!";
		return;
	}
	cout << "void ";
	Childs[0]->PrintCode();
	cout << "(";
	Childs[1]->PrintCode();
	cout << ")\n{\n	";
	Childs[2]->PrintCode();
	cout << "\n}";
}

defproc::defproc() : FixedNumOfChildNode(NUMOFCHILD, "defproc")
{
}

