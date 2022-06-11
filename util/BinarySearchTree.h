#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include <queue>

template<typename K, typename V>
class BinarySearchTree
{
	struct Node
	{
		K key;
		V value;
		Node* left;
		Node* right;
	};

	Node* rootNode;
	int siz;
	void Keys(const Node*, queue<K>&) const;
	void clear(Node*);
	void copyTree(Node*, const Node*);

public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree&); //copy
	BinarySearchTree<K, V>& operator=(const BinarySearchTree<K, V>&); //assignment
	~BinarySearchTree() { clear(); }

	int size() { return siz; }
	V operator[] (const K&) const;
	V& operator[] (const K&);
	bool containsKey(const K&) const;
	void deleteKey(const K&);
	queue<K> Keys() const;
	void clear();
};

template<typename K, typename V>
BinarySearchTree<K, V>::BinarySearchTree()
{
	rootNode = 0;
	siz = 0;
}

template<typename K, typename V>
BinarySearchTree<K, V>::BinarySearchTree(const BinarySearchTree& original)
{
	Node* rootNode = 0;
	if (original.rootNode) copyTree(rootNode = new Node, original.rootNode);
	siz = original.siz;
}

template<typename K, typename V>
void BinarySearchTree<K, V>::copyTree(Node* p, const Node* copiedTree)
{
	if (!p) return;
	p->key = copiedTree->key;
	p->value = copiedTree->value;
	p->left = p->right = 0;
	if (copiedTree->left) copyTree(p->left = new Node, copiedTree->left);
	if (copiedTree->right) copyTree(p->right = new Node, copiedTree->right);
}

template<typename K, typename V>
BinarySearchTree<K, V>& BinarySearchTree<K, V>::operator=(const BinarySearchTree& original)
{
	if (this == &original) return *this;

	clear();
	Node* rootNode = 0;
	if (original.rootNode) copyTree(rootNode = new Node, original.rootNode);
	siz = original.siz;
	return *this;
}

template<typename K, typename V>
V BinarySearchTree<K, V>::operator[](const K& key) const
{
	Node* p = rootNode;
	while (p)
	{
		if (p->key == key) break;
		if (p->key < key) p = p->right;
		else p = p->left;
	}
	if (p) return p->value;
	return V();
}

template<typename K, typename V>
V& BinarySearchTree<K, V>::operator[](const K& key)
{
	Node* p = rootNode;
	Node* prev = 0;
	while (p)
	{
		if (p->key == key) break;
		prev = p; //save p's position before advancing it
		if (p->key < key) p = p->right; //go to the right 
		else p = p->left; //go to the left 
	}

	if (!rootNode) //if empty, or prev == 0
	{
		siz++;
		rootNode = new Node;
		rootNode->key = key;
		rootNode->value = V();
		rootNode->left = rootNode->right = 0;
		return rootNode->value;
	}

	if (p) return p->value; //matching key found

	//create a new node 
	p = new Node;
	p->key = key;
	p->value = V();
	p->left = p->right = 0;
	siz++;

	//add the new node, prev is the parent
	if (prev->key < key) prev->right = p;
	else prev->left = p;
	return p->value;
}

template<typename K, typename V>
bool BinarySearchTree<K, V>::containsKey(const K& key) const
{
	Node* p = rootNode;
	while (p)
	{
		if (p->key == key) return true;
		else if (p->key < key) p = p->right;
		else p = p->left;
	}
	return false;
}

template<typename K, typename V>
void BinarySearchTree<K, V>::deleteKey(const K& key)
{
	Node* p = rootNode;
	Node* prev = 0;
	while (p)
	{
		if (p->key == key) break;
		prev = p;
		if (p->key < key) p = p->right;
		else p = p->left;
	}

	if (!p) return; //if empty or not found

	if (!prev && !p->left && !p->right) //if root is the only node in the tree and is the key im looking for 
	{
		delete p;
		rootNode = 0;
		--siz;
	}

	//if p has no descendants
	else if (!p->left && !p->right)
	{
		delete p;
		if (prev->left == p) prev->left = 0;
		else prev->right = 0;
		--siz;
	}

	//no left child
	else if (!p->left)
	{
		Node* temp = p;
		prev = p; //so p can proceed 
		p = p->right;
		while (p->left) //look for the smallest key until theres no more left child 
		{
			prev = p;
			p = p->left;
		}
		//found the smallest key from the right branches of the deleted key
		temp->key = p->key;
		temp->value = p->value;
		if (prev->left == p) prev->left = p->right;
		else prev->right = p->right; //in case there is only the right child and no left descandants 
		//delete p;
		--siz;
	}

	else
	{
		Node* temp = p;
		prev = p;
		p = p->left;
		while (p->right) //looks for the smallest key from the left branches of the deleted key 
		{
			prev = p;
			p = p->right;
		}
		temp->key = p->key;
		temp->value = p->value;
		if (prev->right == p) prev->right = p->left;
		else prev->left = p->left;
		delete p;
		--siz;
	}

}

template<typename K, typename V>
queue<K> BinarySearchTree<K, V>::Keys() const
{
	queue<K> keys;
	Keys(rootNode, keys);
	return keys;
}

template<typename K, typename V>
void BinarySearchTree<K, V>::Keys(const Node* p, queue<K>& keys) const
{
	if (!p) return;
	Keys(p->left, keys);
	keys.push(p->key);
	Keys(p->right, keys);
}

template<typename K, typename V>
void BinarySearchTree<K, V>::clear()
{
	clear(rootNode);
	rootNode = 0;
	siz = 0;
}

template<typename K, typename V>
void BinarySearchTree<K, V>::clear(Node* p)
{
	if (!p) return;
	clear(p->left);
	clear(p->right);
	delete p;
}



#endif
