#pragma once
#include <string>

using namespace std;

enum Colors {
	BLACK = 0,
	RED = 1
};

class Node {
protected:
	unsigned int key;
	string value;
	int height;
	Node* left;
	Node* right;
	Node* parent;
	Colors color;

	
public:
	friend class RBTree;
	friend void swap(Node* a, Node* b);
	Node();
	Node(unsigned int _key, string _value);
	Node(Node* node);

	Node* search(string& value);

	Node* getMin();
	Node* getMax();
	//int getValue() const;
	//Node* getLeft() const;
	//Node* getRight() const;
	//Node* getParent() const;
	//Colors getColor() const;
	//void setLeft(Node* node);
	//void setRight(Node* node);
	//void setParent(Node* node);
	//void setKey(int _key);
	//void setValue(int _value);
	//void setColor(Colors _color);
	void updateHeight();
	int getHeight();
	int getBalance();
	string getColorAsString();
	void createNode(unsigned int _key, string _value);

	void printTree();
	void saveToFileOne(fstream& file, string& sep);
	int getChildrenCount();
	Node* getChildOrMock();

	void deleteTree();

	bool operator==(const Node& r);
	bool operator!=(const Node& r);

	void printTreeRecursive(int level);
	void printColoredNode(int level);

};


class RBTree {
	Node* root;
public:
	RBTree();
	RBTree(Node* _root);

	Node* getRoot() const;

	void setRoot(Node* newRoot);
	void balanceTree(Node* newNode);
	void leftRotate(Node* node);
	void rightRotate(Node* node);
	void transplantNode(Node* toNode, Node* fromNode);
	void fixRulesAfterRemoval(Node* node);

	void insert(unsigned int key, string& value);
	void remove(string& value);

	void printRBTree();
};

void swap(Node* a, Node* b);
