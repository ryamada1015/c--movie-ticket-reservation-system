//Rikako Yamada
//1665648

#ifndef StaticArray_h
#define StaticArray_h


template<typename T, int CAP>
class StaticArray
{
private:
	T val[CAP];
	T dummy;

public:
	StaticArray();
	int capacity() const { return CAP; }
	const T& operator[](int) const;
	T& operator[](int);

};

template<typename T, int CAP>
StaticArray<T, CAP>::StaticArray()
{
	for (int i = 0; i < CAP; i++)
		val[i] = T();
	dummy = T();
}

template<typename T, int CAP>
T& StaticArray<T, CAP>::operator[](int index)
{
	if (index < 0 || index >= CAP)
		return dummy;
	return val[index];
}

template<typename T, int CAP>
const T& StaticArray<T, CAP>::operator[](int index) const
{
	if (index < 0 || index >= CAP)
		return T();
	return val[index];
}

#endif /* StaticArray_h */

#pragma once

