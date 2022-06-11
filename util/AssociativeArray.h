
#include <queue>


template<typename K, typename V>
class AssociativeArray
{
	struct Node
	{
		K key;
		V value;
		Node* next;
	};

	Node* firstNode;
	int siz;

public:
	AssociativeArray();
	AssociativeArray(const AssociativeArray&);
	AssociativeArray<K, V> & operator=(const AssociativeArray<K, V>&);
	~AssociativeArray();
	V operator[] (const K&) const;
	V& operator[] (const K&);
	bool containsKey(const K&) const;
	void deleteKey(const K&);
	queue<K> Keys() const;
	void clear();
	int size() { return siz; };
};

template<typename K, typename V>
AssociativeArray<K, V>::AssociativeArray()
{
	siz = 0;
	firstNode = 0;
}

template<typename K, typename V>
AssociativeArray<K, V>::AssociativeArray(const AssociativeArray& original)
{
	firstNode = 0;
	Node* lastNode = 0;
	siz = original.siz;
	for (Node* p = original.firstNode; p; p = p->next)
	{
		Node* temp = new Node;
		temp->value = p->value;
		temp->key = temp->key;
		temp->next = 0;
		if (lastNode) lastNode->next = temp;
		else firstNode = temp;
		lastNode = temp;
	}
}

template<typename K, typename V>
AssociativeArray<K, V>& AssociativeArray<K, V>::operator=(const AssociativeArray<K, V>& original)
{
	//if not self copying
	if (this != &original)
	{
		while (firstNode)
		{
			Node* p = firstNode;
			firstNode->next = firstNode;
			delete p;
		}

		Node* lastNode = 0;
		for (Node* p = original.firstNode; p; p = p->next)
		{
			Node* temp = new Node;
			temp->value = p->value;
			temp->key = p->key;
			temp->next = 0;
			if (lastNode) lastNode->next = temp;
			else firstNode = temp;
			lastNode = temp;
		}
		siz = original.siz;
	}
	return *this;
}

template<typename K, typename V>
AssociativeArray<K, V>::~AssociativeArray()
{
	while (firstNode)
	{
		Node* p = firstNode;
		firstNode = firstNode->next;
		delete p;
	}
}

template<typename K, typename V>
V& AssociativeArray<K, V>::operator[](const K& index)
{
	for (Node* p = firstNode; p; p = p->next)
	{
		if (p->key == index)
			return p->value;
	}
	++siz;
	Node* temp = new Node;
	temp->key = index;
	temp->value = V();
	temp->next = firstNode;
	firstNode = temp;
	return firstNode->value;
}

template<typename K, typename V>
V AssociativeArray<K, V>::operator[](const K& index) const
{
	for (Node* p = firstNode; p; p = p->next)
	{
		if (p->key == index)
			return p->value;
	}
	return V();
}

template<typename K, typename V>
bool AssociativeArray<K, V>::containsKey(const K& index) const
{
	for (Node* p = firstNode; p; p = p->next)
	{
		if (p->key == index)
			return true;
	}
	return false;
}

template<typename K, typename V>
void AssociativeArray<K, V>::deleteKey(const K& index)
{
	Node* p, *prev;
	for (p = firstNode, prev = 0; p; prev = p, p = p->next)
	{
		if (p->key == index)
			break;
	}

	if (p)
	{
		--siz;
		if (prev) prev->next = p->next;
		else firstNode = p->next;
		delete p;
	}
}

template<typename K, typename V>
queue<K> AssociativeArray<K, V>::Keys() const
{
	queue<K> k_queue;
	for (Node* p = firstNode; p; p = p->next)
	{
		k_queue.push(p->key);
	}
	return k_queue;
}

template<typename K, typename V>
void AssociativeArray<K, V>::clear()
{
	while (firstNode)
	{
		Node* p = firstNode;
		firstNode = firstNode->next;
		delete p;
		--siz;
	}
}