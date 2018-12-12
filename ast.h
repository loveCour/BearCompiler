#ifndef __TREE_H__
#define __TREE_H__
#include <iostream>
#include <vector>
#include <array>
#include <string>

using namespace std;

static const int MaxNumOfChilds = 4;
// createNode<노드이름> ($1,$2,....); 만들고 인자들을 집어넣으면서 갯수 넘는지 체크 인자들을 집어넣으면서 갯수모자란지 체크
// root.typechecking()<-심볼테이블만들고 타입체킹시작
// root.gentargetcode() 타겟코드생성

class AST {
public:
	virtual void PrintCode() = 0;
protected:
	string symbol;
};

//자식의 갯수가 고정되어있는 노드들의 부모클래스
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

//리프노드들
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
