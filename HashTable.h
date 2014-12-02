//DO NOT CHANGE THIS FILE
//Author: Bo Brinkman
//Date: 2013/07/24
#include "USet.h"

/*
 * Note: Just above your template declaration when you use this class, you
 * must define method called "hash" that takes a Key as input, and returns
 * an unsigned long (which is the hash value)
 *
 * For example, you might do:
 * unsigned long hash(char c){ return 10*((unsigned long)c)%13; }
 * HashTable<char,int> mySillyTable;
 *
 * If you don't define an appropriate hash function, the class won't compile.
 */

template <class Key, class T>
class HashTable : public USet <Key, T> {
 private:
  class HashRecord {
  public:
    Key k;
    T x;

    //If the slot in the hash table is totally empty, set this to true.
    bool isNull;

    //If the slot used to have something in it, but doesn't now, set
    // isDel to true, and isNull to false. isNull is only for slots
    // that have never been used
    bool isDel;

    HashRecord() { isNull = true; isDel = false; };
  };

 public:
  //See USet.h for documentation of these methods
  virtual unsigned long size();
  virtual void add(Key k, T x);
  virtual void remove(Key k);
  virtual T find(Key k);
  virtual bool keyExists(Key k);

  //Initialize all private member variables.
  HashTable();
  //Delete any dynamically allocated memory.
  virtual ~HashTable();

private:
  //A pointer to the array that holds the hash table data
  HashRecord* backingArray;

  //Whenever numItems + numRemoved >= backingArraySize/2, call
  // grow(). grow() should make a new backing array that is twice the
  // size of the old one, similar to what we did in the ArrayQueue
  // lab.
  //Note: You cannot just loop through the old array and copy it to the
  // new one! Since the backing array size has changed, each item will likely
  // map to a different slot in the array. You may just want to use add()
  // after initializing the new array.
  void grow();
  
  //This helper method should take a key, and return the index for that
  // item within the hash table. If the item already exists, return the
  // index of the existing item. If the item doesn't exist, return the index
  // where it OUGHT to be. This function can then be used as a helper method in
  // your other methods.
  unsigned long calcIndex(Key k);

  unsigned long numItems; //Number of items in the hash table

  //Note: Ordinarily, these OUGHT to be private. In this case I have
  // made them public for easy of testing.
 public:
  unsigned long numRemoved; //Number of slots that have been removed but not re-used. Those that have isDel == true
  unsigned long backingArraySize;
};

//You will need this so you can make a string to throw in
// remove
#include <string>

/**
* Authored By: Chris Dieter with help from Dr. Brinkman and 
* Open Data Structures textbook, written by Pat Morin. After loosely
* basing calcIndex, find, and keyExists after an implementation of 
* find function in the book, all other functions were modeled after previous
* homework assignments and in class lectures.
*/
template <class Key, class T>
HashTable<Key,T>::HashTable(){
	
	numItems = 0;
	numRemoved = 0; 
	backingArraySize = hashPrimes[0];
	backingArray = new HashRecord[backingArraySize];
}

template <class Key, class T>
HashTable<Key,T>::~HashTable() {
	delete[] backingArray;
}

template <class Key, class T>
unsigned long HashTable<Key,T>::calcIndex(Key k){
  int i = hash(k) % backingArraySize;
  while(backingArray[i].isNull == false){
	  if(backingArray[i].isDel == false && backingArray[i].k == k)
		  return i; // returns this only if there is a key k
	  i = (i == backingArraySize-1) ? 0: i + 1;
  }

  if(i >= hash(k)% backingArraySize)
	  return i;
  else if(hash(k)% backingArraySize > backingArraySize)
	return numItems;//This indicates failure, since it is an impossible value
}

template <class Key, class T>
void HashTable<Key,T>::add(Key k, T x){
	
	if(numItems + numRemoved >= backingArraySize/2){
		grow();
	} 
	int j = calcIndex(k);
	backingArray[j].isNull = false;
	backingArray[j].isDel = false;
	backingArray[j].x = x;
	backingArray[j].k = k;
	//T x = backingArray[j].x;
	numItems++;
	
}

template <class Key, class T>
void HashTable<Key,T>::remove(Key k){

	int j = calcIndex(k);
	backingArray[j].isDel = true;
	numItems--;
	numRemoved++;
}

template <class Key, class T>
T HashTable<Key,T>::find(Key k){
	
	if(!keyExists(k))
		throw std::string("Key does not exist!");
	
	if(backingArray[calcIndex(k)].x != NULL)
		return backingArray[calcIndex(k)].x;
	return NULL;

}

template <class Key, class T>
bool HashTable<Key,T>::keyExists(Key k){
	int i = calcIndex(k);
	if(i > backingArraySize)
		return false;
	else{
		
		while(backingArray[i].isNull == false){
			if(backingArray[i].isDel == false && backingArray[i].k == k)
				return true; // returns this only if there is a key k
			i = (i == backingArraySize-1) ? 0: i + 1;
		}
		return false;
	}
}

template <class Key, class T>
unsigned long HashTable<Key,T>::size(){
  return numItems;
}

template <class Key, class T>
void HashTable<Key,T>::grow(){
	int j = 0;
	int i = 53;
	while(i <= backingArraySize){
		j++;
		i = hashPrimes[j];
	}
	

	HashRecord* copyArray = new HashRecord[hashPrimes[j]];
	
	for(int i = 0; i < backingArraySize; i++){
		if(backingArray[i].isNull == false && backingArray[i].isDel == false){
			
			Key k = backingArray[i].k;
			T x = backingArray[i].x;
			copyArray->add(k, x);
			/*int p = hash(k) % hashPrimes[j];
			while(copyArray[p].isNull == false)
				p = (p == hashPrimes[j] - 1) ? 0 : p + 1;
			copyArray[p].k = k;
			copyArray[p].x = x;
			copyArray[p].isNull = false;
			copyArray[p].isDel = false;*/
		} 
	}

	numRemoved = 0;
	backingArraySize = hashPrimes[j];
	delete[] backingArray;
	backingArray = copyArray;
}

