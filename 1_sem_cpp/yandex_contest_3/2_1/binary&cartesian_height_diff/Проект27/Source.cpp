#include <iostream>
#include <cassert>

using namespace std;

class DecartTree {
	struct DecartNode {
		DecartNode(int key, int prior) :

			key(key),
			priority(prior),
			left_part(nullptr),
			right_part(nullptr),
			parent(nullptr)
		{}

		DecartNode(const DecartNode& state) : DecartNode(state.key, state.priority) {}

		DecartNode& operator=(const DecartNode& state) {
			if (&state == this) {
				return *this;
			}
			priority = state.priority;
			key = state.key;
			//value = state.value;
			left_part = state.left_part;
			right_part = state.right_part;
			parent = state.parent;
			return *this;
		}

		int key;
		int priority;
		DecartNode* left_part;
		DecartNode* right_part;
		DecartNode* parent;
	};
public:
	DecartTree() : _root(nullptr) {}

	static void split(DecartNode *root, DecartNode *& left, DecartNode *& right, const int key)
	{
		if (root == nullptr)
		{
			left = right = nullptr;
			return;
		}
		if (root->key < key)
		{
			split(root->right_part, root->right_part, right, key);
			left = root;
		}
		else
		{
			split(root->left_part, left, root->left_part, key);
			right = root;
		}
	}

	void insertNonMerge(int key, int prior) {
		DecartNode* t = new DecartNode(key, prior);
		_insertNonMerge(_root, t);
	}

	int decartHeight() const {
		return _decartHeight(_root);
	}

	~DecartTree ()
	{
		_deleteTree(_root);
	}

private:
	static int _decartHeight(DecartNode * node)
	{
		if (node == 0) {
			return 0;
		}

		int left, right;
		if (node->left_part != nullptr) {
			left = _decartHeight(node->left_part);
		}
		else {
			left = -1;
		}
		if (node->right_part != nullptr) {
			right = _decartHeight(node->right_part);
		}
		else
			right = -1;
		int max = left > right ? left : right;
		return max + 1;

	}

	static void _insertNonMerge(DecartNode*& root, DecartNode* vertex) {
		if (root == nullptr)
		{
			root = vertex;
			return;
		}
		if (root->priority > vertex->priority)
		{
			if (vertex->key < root->key)
				_insertNonMerge(root->left_part, vertex);
			else
				_insertNonMerge(root->right_part, vertex);
			return;
		}
		split(root, vertex->left_part, vertex->right_part, vertex->key);
		root = vertex;
	}

	static void _deleteTree(DecartNode* value) {
		if (value->left_part != nullptr) {
			_deleteTree(value->left_part);
		}
		if (value->right_part != nullptr) {
			_deleteTree(value->right_part);
		}
		delete value;
	}

	DecartNode* _root;
};

class BinaryTree {
	struct binary_node {
		binary_node(const long n) {
			key = n;
			left_part = nullptr;
			right_part = nullptr;
		};
		long key;
		binary_node* left_part;
		binary_node* right_part;
	};
public:
	BinaryTree() {
		_size = 0;
		_root = nullptr;
	}

	void deleteTree() const {
		deleteTree_(_root);
	}

	void naiveInsert(const long value) {
		naiveInsert_(_root, value);
		_size++;
	}

	int binaryHeight() const {
		return binaryHeight_(_root);
	}

	~BinaryTree() {
		deleteTree_(_root);
	};

private:
	static void deleteTree_(binary_node* value) {
		if (value->left_part != nullptr) {
			deleteTree_(value->left_part);
		}
		if (value->right_part != nullptr) {
			deleteTree_(value->right_part);
		}
		delete value;
	}

	static int binaryHeight_(binary_node* node)
	{
		if (node == nullptr) {
			return 0;
		}
		int left, right;
		if (node->left_part != nullptr) {
			left = binaryHeight_(node->left_part);
		}
		else
			left = -1;
		if (node->right_part != nullptr) {
			right = binaryHeight_(node->right_part);
		}
		else {
			right = -1;
		}
		int max = left > right ? left : right;
		return max + 1;

	}

	static void naiveInsert_(binary_node*& curNode, const long value) {
		if (curNode == nullptr) {
			curNode = new binary_node(value);
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
	binary_node* _root;
	size_t _size;
};

int main() {
	BinaryTree binary_tree;
	DecartTree decart_tree;

	int n, key, prior;
	cin >> n;

	for (size_t i = 0; i < n; i++)
	{
		cin >> key >> prior;
		binary_tree.naiveInsert(key);
		decart_tree.insertNonMerge(key, prior);
	}

	int a, b;
	a = binary_tree.binaryHeight();
	b = decart_tree.decartHeight();
	cout << a - b << endl;

	system("pause");
	return 0;
}

