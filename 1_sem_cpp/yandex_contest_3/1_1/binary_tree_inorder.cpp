#include <iostream>
#include <cassert>
using namespace std;



class BinaryTree {
private:
	struct BinaryNode;

public:
	BinaryTree() {
		_size = 0;
		_root = nullptr;
	}

	void naiveInsert(long value) {
		naiveInsert_(_root, value);
		_size++;
	}

	void inorderGo() {
		inorderGo_(_root);
	}

	~BinaryTree() {
		deleteTree_(_root);
	};

private:
	void deleteTree_(BinaryNode* value) {
		if (value->left_part != nullptr) {
			deleteTree_(value->left_part);
		}
		if (value->right_part != nullptr) {
			deleteTree_(value->right_part);
		}
		delete value;
	}

	void naiveInsert_(BinaryNode*& curNode, long value) {
		if (curNode == nullptr) {
			curNode = new BinaryNode(value);
			return;
		}
		if (curNode->key > value) {
			naiveInsert_(curNode->left_part, value);
		}
		else {
			naiveInsert_(curNode->right_part, value);
		}
	}

private:
	friend istream& operator>>(istream&, BinaryNode&);
	struct BinaryNode {
		BinaryNode(long n) {
			key = n;
			left_part = nullptr;
			right_part = nullptr;
		};
		long key;
		BinaryNode* left_part;
		BinaryNode* right_part;
	};

	void inorderGo_(BinaryNode* value) const {
		if (value->left_part != nullptr) {
			inorderGo_(value->left_part);
		}
		cout << value->key << " ";
		if (value->right_part != nullptr) {
			inorderGo_(value->right_part);
		}
	}

	BinaryNode* _root;
	size_t _size;
};

istream& operator>>(istream& is, BinaryTree::BinaryNode& input_value) {
	is >> input_value.key;
	return is;
}

istream& readTree(istream& is, BinaryTree& myTree) {
	int n, value;
	is >> n;
	assert(n >= 0);
	for (size_t i = 0; i < n; i++)
	{
		is >> value;
		myTree.naiveInsert(value);
	}

	return is;
}

int main() {
	BinaryTree Tree;
	readTree(cin, Tree);
	Tree.inorderGo();
	system("pause");
}
