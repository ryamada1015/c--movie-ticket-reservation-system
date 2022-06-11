
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <queue>
#include <list>

template<typename K, typename V, int CAP>
class HashTable
{
	struct Node
	{
		K key;
		V value;
	};

	list<Node> data[CAP]; //chaining
	int(*hashCode)(const K&); //ptr to hashCode function
	int siz;

public:
	HashTable(int(*)(const K&) = 0);
	double loadFactor() const { return 1.0*siz / CAP; }
	V operator[] (const K&) const;
	V& operator[] (const K&);
	bool containsKey(const K&);
	void deleteKey(const K&);
	queue<K> Keys() const;
	int size() const { return siz; }
	void clear();
};

template<typename K, typename V, int CAP>
HashTable<K, V, CAP>::HashTable(int(*hashCode)(const K & key))
{
	this->hashCode = hashCode;
	siz = 0;
}

template<typename K, typename V, int CAP>
V& HashTable<K, V, CAP>::operator[] (const K& key)
{
	int index = hashCode(key) % CAP;
	if (index < 0) index += CAP;

	typename list<Node>::iterator it;
	for (it = data[index].begin(); it != data[index].end(); it++)
		if (it->key == key)
		{
			return it->value;
		}

	if (it == data[index].end()) //not found
	{
		Node n;
		n.key = key;
		data[index].push_back(n);
		--it;
		++siz;
		return it->value;
	}

}

template<typename K, typename V, int CAP>
V HashTable<K, V, CAP>::operator[] (const K& key) const
{
	typename list<Node>::iterator it;
	for (it = data.begin(); it != data.end(); it++)
		if (it->key == key)
			return it->value;
	return V();
}

template<typename K, typename V, int CAP>
bool HashTable<K, V, CAP>::containsKey(const K& key)
{
	int index = hashCode(key) % CAP;
	if (index < 0) index += CAP;
	typename list<Node>::const_iterator it;
	for (it = data[index].begin(); it != data[index].end(); it++)
		if (it->key == key)
			return true;
	if (it == data[index].end())
		return false;
}

template<typename K, typename V, int CAP>
void HashTable<K, V, CAP>::deleteKey(const K& key)
{
	int index = hashCode(key) % CAP;
	if (index < 0) index += CAP;
	typename list<Node>::const_iterator it;
	for (it = data[index].begin(); it != data[index].end(); it++)
		if (it->key == key)
		{
			data[index].erase(it);
			--siz;
			return;
		}
}

template<typename K, typename V, int CAP>
queue<K> HashTable<K, V, CAP>::Keys() const
{
	queue<K> k_queue;

	for (int i = 0; i < CAP; i++)
	{
		if (!data[i].empty())
		{
			typename list<Node>::const_iterator it;
			for (it = data[i].begin(); it != data[i].end(); it++)
				k_queue.push(it->key);
		}
	}
	return k_queue;
}

template<typename K, typename V, int CAP>
void HashTable<K, V, CAP>::clear()
{
	typename list<Node>::const_iterator it;
	for (int i = 0; i < CAP; i++)
		if (!data[i].empty())
		{
			data[i].clear();
			--siz;
		}
}

#endif