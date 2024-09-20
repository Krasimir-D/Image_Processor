#pragma once
#include "PbmImporter.h"
#include "PgmImporter.h"
#include "PpmImporter.h"
#include "BmpImporter.h"
#include "PbmExporter.h"
#include "PgmExporter.h"
#include "PpmExporter.h"
#include "BmpExporter.h"

template<class Type>
class HeterogenicArray
{
public:
	HeterogenicArray();
	HeterogenicArray(const HeterogenicArray<Type>& other);
	HeterogenicArray<Type>& operator=(const HeterogenicArray<Type>& other);
	HeterogenicArray(HeterogenicArray<Type>&& other) noexcept;
	HeterogenicArray<Type>& operator=(HeterogenicArray<Type>&& other) noexcept;
	~HeterogenicArray();

	size_t getSize() const;
	size_t getCapacity() const;

	void push_back(const Type* obj);
	void removeAt(unsigned index);

	const Type& operator[](size_t index) const;
	Type& operator[](size_t index);
		
private:
	void copyFrom(const HeterogenicArray<Type>& other);
	void free();
	void resize(unsigned newCapacity);
	void moveFrom(HeterogenicArray<Type>&& other);

private:
	Type** data;
	unsigned size;
	unsigned capacity;
};

template<typename Type>
void HeterogenicArray<Type>::copyFrom(const HeterogenicArray<Type>& other)
{
	Type** temp = new Type * [other.capacity] {};
	for (size_t i = 0; i < other.size; i++)
	{
		temp[i] = other.data[i]->clone();
	}
	
	for (size_t i = 0; i < size; i++)
	{
		delete data[i];
	}
	delete[] data;

	data = temp;
	size = other.size;
	capacity = other.capacity;
}

template<typename Type>
void HeterogenicArray<Type>::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete data[i];
	}

	delete[] data;
	data = nullptr;
	size = 0;
	capacity = 0;
}

template<typename Type>
void HeterogenicArray<Type>::resize(unsigned newCapacity)
{
	Type** temp = new Type * [newCapacity] {};
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = data[i];
	}

	delete[] data;
	data = temp;
	capacity = newCapacity;
}

template<class Type>
inline void HeterogenicArray<Type>::moveFrom(HeterogenicArray<Type>&& other)
{
	data = other.data;
	size = other.size; 
	capacity = other.capacity;
	other.data = nullptr;
	other.size = other.capacity = 0;
}

template<typename Type>
HeterogenicArray<Type>::HeterogenicArray()
{
	size = 0;
	capacity = 1;
	data = new Type * [capacity];
}

template<typename Type>
HeterogenicArray<Type>::HeterogenicArray(const HeterogenicArray<Type>& other)
	: HeterogenicArray()
{
	copyFrom(other);
}

template<class Type>
inline HeterogenicArray<Type>& HeterogenicArray<Type>::operator=(const HeterogenicArray<Type>& other)
{
	if (this != &other)
		copyFrom(other);
	return *this;
}

template<class Type>
inline HeterogenicArray<Type>::HeterogenicArray(HeterogenicArray<Type>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<class Type>
inline HeterogenicArray<Type>& HeterogenicArray<Type>::operator=(HeterogenicArray<Type>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<class Type>
inline HeterogenicArray<Type>::~HeterogenicArray()
{
	free();
}

template<class Type>
inline size_t HeterogenicArray<Type>::getSize() const
{
	return size;
}

template<class Type>
inline size_t HeterogenicArray<Type>::getCapacity() const
{
	return capacity;
}

template<class Type>
inline void HeterogenicArray<Type>::push_back(const Type* obj)
{
	if (size == capacity)
		resize(capacity * 2);

	Type* temp = obj->clone();
	if (!temp)
	{
		std::cerr << "Unable to clone object!\n";
		return;
	}

	data[size++] = temp;
}

template<class Type>
inline void HeterogenicArray<Type>::removeAt(unsigned index)
{
	if(index >= size)
		throw std::invalid_argument("Index was out of range!");

	delete data[index];
	for (size_t i = index; i < size - 1; i++)
	{
		data[i] = data[i + 1];
	}

	data[size - 1] = nullptr;
	size--;
}

template<class Type>
inline const Type& HeterogenicArray<Type>::operator[](size_t index) const
{
	if (index >= size)
		throw std::invalid_argument("Index was out of range!");

	return *data[index];
}

template<class Type>
inline Type& HeterogenicArray<Type>::operator[](size_t index)
{
	if (index >= size)
		throw std::invalid_argument("Index was out of range!");

	return *data[index];
}


