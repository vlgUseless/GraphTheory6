#include "RBTree.h"
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

Node nil;
Node::Node() : key(0), value(""), height(-1), color(BLACK), left(nullptr),right(nullptr),parent(nullptr) {}

Node::Node(unsigned int _key, string _value) : key(_key), value(_value), height(-1), color(RED), left(&nil), right(&nil), parent(&nil) {}

//int Node::getValue() const { return value; }
//Node* Node::getLeft() const { return left; }
//Node* Node::getRight() const { return right; }
//Node* Node::getParent() const { return parent; }
//Colors Node::getColor() const { return color; }
//void Node::setLeft(Node* node) { left = node; }
//void Node::setRight(Node* node) { right = node; }
//void Node::setParent(Node* node) { parent = node; }
//void Node::setKey(int _key) { key = _key; }
//void Node::setValue(int _value) { value = _value; }
//void Node::setColor(Colors _color) { color = _color; }


bool Node::operator==(const Node& r) {
	return (key == r.key) && (color == r.color);
}

bool Node::operator!=(const Node& r) {
	return !(*this == r);
}

void Node::printTree() {
	if (this == NULL or this == &nil) return;
	if (left != NULL and left != &nil) left->printTree();
	cout << value << " ";
	if (right != NULL and right != &nil) right->printTree();
}

void Node::saveToFileOne(fstream& file, string& sep) {
	if (this == NULL or *this == nil) return;
	if (left != NULL and *left != nil) left->saveToFileOne(file, sep);
	file << value;
	if (right != NULL or *right != nil) {
		file << sep;
		right->saveToFileOne(file, sep);
	}
}

Node::Node(Node* node) {
	key = node->key;
	value = node->value;
	left = node->left;
	right = node->right;
	parent = node->parent;
	color = node->color;
	height = node->height;
}

Node* Node::search(string& value) {
	if (this == NULL or *this == nil) return NULL;
	if (this->value == value) return this;
	return (value < this->value) ? left->search(value) : right->search(value);
}

void Node::deleteTree() {
	if (this == NULL or *this == nil) return;
	if (left != NULL and *left != nil) {
		left->deleteTree();
		delete left;
		left = nullptr; // Обнуляем указатель после удаления
	}
	if (right != NULL and *right != nil) {
		right->deleteTree();
		delete right;
		right = nullptr; // Обнуляем указатель после удаления
	}
}

Node* Node::getMin() {
	if (this == NULL or *this == nil) return NULL;
	if (left == NULL or *left == nil) return this;
	return left->getMin();
}
Node* Node::getMax() {
	if (this == NULL or *this == nil) return NULL;
	if (right == NULL or *right == nil) return this;
	return right->getMin();
}

string Node::getColorAsString() {
	if (color == BLACK) return "BLACK";
	return "RED";
}

void Node::updateHeight() {
	height = max(left->getHeight(), right->getHeight()) + 1;
}

int Node::getHeight() {
	return (this == NULL or *this == nil) ? -1 : height;
}

int Node::getBalance() {
	return (this == NULL or *this == nil) ? 0 : right->getHeight() - left->getHeight();
}

int Node::getChildrenCount() {
	int count = 0;
	if (left != NULL and *left != nil) count++;
	if (right != NULL and *right != nil) count++;
	return count;
}

Node* Node::getChildOrMock() {
	return (left != NULL and *left != nil) ? left : right;
}


void swap(Node* a, Node* b) {
	int a_key = a->key;
	a->key = b->key;
	b->key = a_key;
	string a_value = a->value;
	a->value = b->value;
	b->value = a_value;
}


RBTree::RBTree() { 
	root = new Node();
	//root->left = new Node();
	//root->right = new Node();
}
RBTree::RBTree(Node* _root): root(_root) {}
Node* RBTree::getRoot() const { return root; }
void RBTree::setRoot(Node* newRoot) { root = newRoot; }


void RBTree::insert(unsigned int key, string& value)
{
	Node* currentNode = root;
	Node* parent = &nil;

	while (*currentNode != nil) {
		parent = currentNode;
		if (value < currentNode->value) {
			currentNode = currentNode->left;
		}
		else {
			currentNode = currentNode->right;
		}
	}

	Node* newNode = new Node(key, value);
	newNode->parent = parent;
	if (*parent == nil) {
		root = newNode;
	}
	else if (value < parent->value) {
		parent->left = newNode;
	}
	else {
		parent->right = newNode;
	}
	
	balanceTree(newNode);
}


void RBTree::balanceTree(Node* newNode) {
	Node* uncle;
	while (newNode->parent->color == RED) {
		if (newNode->parent == newNode->parent->parent->left) {
			uncle = newNode->parent->parent->right;
			if (uncle->color == RED) {
				newNode->parent->color = BLACK;
				uncle->color = BLACK;
				newNode->parent->parent->color = RED;
				newNode = newNode->parent->parent;

			}
			else {
				if (newNode == newNode->parent->right) {
					newNode = newNode->parent;
					leftRotate(newNode);
				}
				newNode->parent->color = BLACK;
				newNode->parent->parent->color = RED;
				rightRotate(newNode->parent->parent);
			}
		}
		else {
			uncle = newNode->parent->parent->left;
			if (uncle->color == RED) {
				newNode->parent->color = BLACK;
				uncle->color = BLACK;
				newNode->parent->parent->color = RED;
				newNode = newNode->parent->parent;
				}
			else {
				if (newNode == newNode->parent->left) {
					newNode = newNode->parent;
					rightRotate(newNode);
				}
				newNode->parent->color = BLACK;
				newNode->parent->parent->color = RED;
				leftRotate(newNode->parent->parent);
			}
		}
	}
	root->color = BLACK;
}


void RBTree::rightRotate(Node* node) {
	Node* leftChild = node->left;
	node->left = leftChild->right;
	if (leftChild->right != &nil) {
		leftChild->right->parent = node;
	}
	leftChild->parent = node->parent;
	if (node->parent == &nil) {
		root = leftChild;
	}
	else if (node == node->parent->left) {
		node->parent->left = leftChild;
	}
	else {
		node->parent->right = leftChild;
	}
	leftChild->right = node;
	node->parent = leftChild;
	// Обновление высоты узлов
	node->updateHeight();
	leftChild->updateHeight();
}

//void RBTree::leftRotate(Node* node) {
//	swap(node, node->right);
//	Node* buffer(node->left);
//	node->left = node->right;
//	node->right = node->left->right;
//	node->left->right = node->left->left;
//	node->left->left = buffer;
//
//	node->left->updateHeight();
//	node->updateHeight();
//}

void RBTree::leftRotate(Node* node) {
	Node* rightChild = node->right;
	node->right = rightChild->left;
	if (*rightChild->left != nil) {
		rightChild->left->parent = node;
	}
	rightChild->parent = node->parent;
	if (*node->parent == nil) {
		root = rightChild;
	}
	else if (node == node->parent->left) {
		node->parent->left = rightChild;
	}
	else {
		node->parent->right = rightChild;
	}
	rightChild->left = node;
	node->parent = rightChild;
	// Обновление высоты узлов
	node->updateHeight();
	rightChild->updateHeight();
}


void RBTree::transplantNode(Node* toNode, Node* fromNode) {
	if (toNode == root) {
		root = fromNode;
	}
	else if (toNode == toNode->parent->left) {
		toNode->parent->left = fromNode;
	}
	else {
		toNode->parent->right = fromNode;
	}
	fromNode->parent = toNode->parent;
}

void RBTree::remove(string& value) {
	Node* nodeToDelete = root->search(value);
	Colors removedNodeColor = nodeToDelete->color;
	Node* child;
	if (nodeToDelete->getChildrenCount() < 2) {
		child = nodeToDelete->getChildOrMock();
		transplantNode(nodeToDelete, child);
	}
	else {
		Node* minNode = nodeToDelete->right->getMin();
		nodeToDelete->key = minNode->key;
		nodeToDelete->value = minNode->value;
		removedNodeColor = minNode->color;
		child = minNode->getChildOrMock();
		transplantNode(minNode, child);
	}
	if (removedNodeColor == BLACK) fixRulesAfterRemoval(child);
}

void RBTree::fixRulesAfterRemoval(Node* node) {
	while (node != root and node->color == BLACK) {
		Node* brother;
		if (node == node->parent->left) {
			brother = node->parent->right;
			if (brother->color == RED) {
				brother->color = BLACK;
				node->parent->color = RED;
				leftRotate(node->parent);
				brother = node->parent->right;

			}
			if (brother->left->color == BLACK and brother->right->color == BLACK) {
				brother->color = RED;
				node = node->parent;
			}
			else {
				if (brother->right->color == BLACK) {
					brother->left->color = BLACK;
					brother->color = RED;
					rightRotate(brother);
					brother = node->parent->right;
				}
				brother->color = node->parent->color;
				node->parent->color = BLACK;
				brother->right->color = BLACK;
				leftRotate(node->parent);
				node = root;
			}
		}
		else {
			brother = node->parent->left;
			if (brother->color == RED) {
				brother->color == BLACK;
				node->parent->color = RED;
				rightRotate(node->parent);
				brother = node->parent->left;
			}
			if (brother->left->color == BLACK and brother->right->color == BLACK) {
				rightRotate(node->parent);
				brother = node->parent->left;
			}
			else {
				if (brother->left->color == BLACK) {
					brother->right->color = BLACK;
					brother->color = RED;
					leftRotate(brother);
					brother = node->parent->left;
				}
				brother->color = node->parent->color;
				node->parent->color = BLACK;
				brother->left->color = BLACK;
				rightRotate(node->parent);
				node = root;
			}
		}
	}
	node->color = BLACK;
}


void printIndented(const std::string& text, int level) {
	for (int i = 0; i < level; ++i) {
		std::cout << "        ";
	}
	std::cout << text << std::endl;
}

void Node::printColoredNode(int level) {
	std::string color = getColorAsString();
	std::string value = (color == "RED") ? "\x1B[31m" : "\x1B[34m"; // RED or BLUE
	value += this->value; //+ " (" + color + ")";
	value += "\x1B[0m"; // Reset color
	printIndented(value, level);
}


void Node::printTreeRecursive(int level) {
	if (this == nullptr || this == &nil) {
		printIndented("nil", level);
		return;
	}

	right->printTreeRecursive(level + 1);
	this->printColoredNode(level);
	left->printTreeRecursive(level + 1);
}

void RBTree::printRBTree() {
	if (root == nullptr) {
		std::cout << "Tree is empty." << std::endl;
		return;
	}
	std::cout << "Red-Black Tree:" << std::endl;
	root->printTreeRecursive(0);
}
