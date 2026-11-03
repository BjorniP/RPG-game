#pragma once
#include"Item.h"
class Inventory
{
private:
	int capacity;
	int nrOfItems;
	Item** itemArray;

	void initialize();
	void nullifying(const unsigned from = 0);
	void freeMemory();
public:
	Inventory(unsigned capacity);
	virtual ~Inventory();
	//Accessors
	const unsigned& Size() const;
	const unsigned& maxSize() const;
	//Modifiers

	//Functions
	void clear();
	const bool empty() const;
	const bool add(Item* item);
	const bool remove(const unsigned index);
	const bool saveToFile(const std::string fileName);
	const bool loadFromFile(const std::string fileName);
};

