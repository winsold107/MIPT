#include <iostream>
#include <cassert>

using namespace std;

class AVLTree {
	struct AVLNode;

public:
	AVLTree() : _root(nullptr), _size(0) { }

	int treeHeight() const
	{
		return height(_root);
	}

	int findPlace(const int key) const
	{
		return findPlace_(_root, key, 0 );
	}

	void insert(const int value) {
		_insert(_root, value);
		_size++;
	}

	void deletePlace(const int place)
	{
		_root = _deletePlace(_root, place);
		//        reverseInorder();
	}

	~AVLTree() {
		deleteTree_(_root);
	};

private:
	struct AVLNode {
		int key = 0;
		int treeSize = 1;
		AVLNode* left = nullptr;
		AVLNode* right = nullptr;
		int height = 1;
		

		explicit AVLNode(const int key) : key(key) {}
	};

	static int treeSize(AVLNode* node) {
		return node == nullptr ? 0 : node->treeSize;
	}

	friend istream& operator>>(istream&, AVLNode&);

	inline static int rotateNeed(AVLNode* p)
	{
		return height(p->right) - height(p->left);
	}

	inline static int height(AVLNode* p)
	{
		return p ? p->height : 0;
		/*if (value->right != nullptr) {
			(value->right, number);
		}
		if (value->left != nullptr) {
			height(value->left, number);
		}
		value->place = number++;
		return number;*/
	}

	inline static void fixheight(AVLNode* p)
	{
		const int hl = height(p->left);
		const int hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;

		const int sl = treeSize(p->left);
		const int sr = treeSize(p->right);
		p->treeSize = sr + sl + 1;
	}


	static AVLNode* rotateRight(AVLNode* p) // правый поворот вокруг l
	{
		AVLNode* q = p->left;
		p->left = q->right;
		q->right = p;
		fixheight(p);
		fixheight(q);
		return q;
		
		//
		//        AVLNode* r = l->left;
		//        l->left = r->right;
		//        r->right = l;
		//        fixheight(l);
		//        fixheight(r);
		//        return r;
	}

	static AVLNode* rotateLeft(AVLNode* r) // левый поворот вокруг r
	{
		AVLNode* l = r->right;
		r->right = l->left;
		l->left = r;
		fixheight(r);
		fixheight(l);
		return l;
	}

	static AVLNode* balance(AVLNode* curnode) // балансировка узла curnode
	{
		fixheight(curnode);
		if (rotateNeed(curnode) > 1)
		{
			if (rotateNeed(curnode->right) < 0)
				curnode->right = rotateRight(curnode->right);
			return rotateLeft(curnode);
		}
		if (rotateNeed(curnode) < -1)
		{
			if (rotateNeed(curnode->left) > 0)
				curnode->left = rotateLeft(curnode->left);
			return rotateRight(curnode);
		}
		return curnode;
	}

	void _insert(AVLNode*& curNode, const int value) {
		if (curNode == nullptr) {
			curNode = new AVLNode(value);
			return;
		}
		if (curNode->key > value) {
			_insert(curNode->left, value);
		}
		else {
			_insert(curNode->right, value);
		}
		curNode = balance(curNode);
	}

	static AVLNode* removeMin(AVLNode *current)
	{
		if (current->left == nullptr) {
			return current->right;
		}
		current->left = removeMin(current->left);
		return balance(current);
	}

	static AVLNode* findMin(AVLNode* p)
	{
		return p->left ? findMin(p->left) : p;
	}

	static int findPlace_(AVLNode* node, const int key, const int elements)
	{
		if (node == nullptr) {
			return 0;
		}
		if (node->key == key) {
			return elements+treeSize(node->right);
		}
		if (key > node->key) {
			return findPlace_(node->right, key, elements);
		}

		return findPlace_(node->left, key, treeSize(node->right))+elements+1;
	}

	AVLNode* _deletePlace(AVLNode *curnode, const int place)
	{
		if (!curnode) {
			return nullptr;
		};
		if (place > treeSize(curnode->right))
			curnode->left = _deletePlace(curnode->left, place - treeSize(curnode->right) - 1);
		else if (place < treeSize(curnode->right))
			curnode->right = _deletePlace(curnode->right, place);
		else
		{
			AVLNode* q = curnode->left;
			AVLNode* r = curnode->right;
			delete curnode;

			if (!r) {
				return q;
			}

			AVLNode* minimum = findMin(r);
			minimum->right = removeMin(r);
			minimum->left = q;

			//            if (curnode == _root) {
			//                _root = minimum;
			//            }

			return balance(minimum);
		}
		//        if ((curnode->left != nullptr) && (curnode->place != place)) {
		//            curnode->left = _deletePlace(curnode->left, place);
		//        }

		return balance(curnode);
	}

	static void deleteTree_(AVLNode* value) {
		if (value != nullptr) {
			deleteTree_(value->left);
			deleteTree_(value->right);
			delete value;
		}
	}

	AVLNode* _root;
	size_t _size;
};

istream& operator>>(istream& is, AVLTree::AVLNode& input_value) {
	is >> input_value.key;
	return is;
}

int main() {
	AVLTree myTree;

	std::ios_base::sync_with_stdio(false);

	int n, value, place, command;
	cin >> n;
	assert(n >= 0);
	for (size_t i = 0; i < n; i++)
	{
		cin >> command;
		if (command == 1) {
			cin >> value;
			myTree.insert(value);
			const int pl = myTree.findPlace(value);
			cout << pl << " ";
		}
		else if (command == 2)
		{
			cin >> place;
			myTree.deletePlace(place);
		}
	}

	return 0;
}