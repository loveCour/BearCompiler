#ifndef __TREE_H__
#define __TREE_H__
#include <iostream>
#include <vector>
#include <array>
#include <string>

using namespace std;

static const int MaxNumOfChilds = 4;
// createNode<����̸�> ($1,$2,....); ����� ���ڵ��� ��������鼭 ���� �Ѵ��� üũ ���ڵ��� ��������鼭 �������ڶ��� üũ
// root.typechecking()<-�ɺ����̺���� Ÿ��üŷ����
// root.gentargetcode() Ÿ���ڵ����

class AST {
public:
	virtual void PrintCode() = 0;
protected:
	string symbol;
};

//�ڽ��� ������ �����Ǿ��ִ� ������ �θ�Ŭ����
class FixedNumOfChildNode : public AST {
public:
	bool AddChild(AST* newNode);
protected:
	FixedNumOfChildNode(const int max, const string s = " ",const int i = 0);
	array<AST*, MaxNumOfChilds> Childs;
	inline bool isChildNumOK();
	int Val;
	int curNum;	
	const int MAX;
	string symbol;
};

class UnFixedNumOfChildNode : public AST {
public:
	void AddChild(AST* newNode);
protected:
	UnFixedNumOfChildNode(string str = " ", int i = 0);
	int val;
	vector<AST*> Childs;
	string symbol;
};

class deffunc : public FixedNumOfChildNode {
public:
	static const int NUMOFCHILD = 4;
	virtual void PrintCode();
	deffunc();
private:
	string RetType;
};

class defproc : public FixedNumOfChildNode {
public:
	static const int NUMOFCHILD = 3;
	virtual void PrintCode();
	defproc();
};

class param : public FixedNumOfChildNode {
public:
	static const int NUMOFCHILD = 1;
	virtual void PrintCode();
	param();
	void SetType(string t);
private:
	string type;
};

class dparams : public UnFixedNumOfChildNode {
public:
	virtual void PrintCode();
	dparams();
};

//��������
class NUM_Leaf : public AST{
public :
	NUM_Leaf();
	virtual void PrintCode();
	void SetValue(int i);
private:
	int ival;
};

class ID_Leaf : public AST {
public:
	ID_Leaf();
	virtual void PrintCode();
	void SetValue(string s);
private:
	string sval;
};

class ctest :public AST {
public:
	ctest() {};
	int a;
	virtual void PrintCode() {
		cout << a;
	}

};




#endif
