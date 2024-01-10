/**
 *  HashTableChained extends a Dictionary as a hash table with chaining.
 *  All objects used as keys must have a valid hashCode() method, which is
 *  used to determine which bucket of the hash table an entry is stored in.
 *  Each object's hashCode() is presumed to return an int between
 *  Integer.MIN_VALUE and Integer.MAX_VALUE.  The HashTableChained class
 *  implements only the compression function, which maps the hash code to
 *  a bucket in the table's range.
 *
 **/

#include "HashTableChained.h"
#include <iostream>
using namespace std;
                  
 /**
  *  Construct a new empty hash table intended to hold roughly sizeEstimate
  *  entries.  (The precise number of buckets is up to you, but we recommend
  *  you use a prime number, and shoot for a load factor between 0.5 and 1.)
  **/
template<typename K, typename V>
HashTableChained<K, V>::HashTableChained(int sizeEstimate) {
    // Your solution here.
    int sz = findPrime((unsigned)(sizeEstimate * 2));
    count = 0;
    arraysize = sz;
    hashTable = new Node * [arraysize];
    for (int i = 0; i < arraysize; i++) {
        hashTable[i] = NULL;
    }

}

/**
 *  Construct a new empty hash table with a default size.  Say, a prime in
 *  the neighborhood of 100.
 **/
template<typename K, typename V>
HashTableChained<K, V>::HashTableChained() {
    // Your solution here.
    hashTable = new Node * [arraysize];
    for (int i = 0; i < arraysize; i++) {
        hashTable[i] = NULL;
    }
    count = 0;
    arraysize = 101;
}

/**
 *  Converts a hash code in the range Integer.MIN_VALUE...Integer.MAX_VALUE
 *  to a value in the range 0...(size of hash table) - 1.
 *  This function should have package protection (so we can test it), and
 *  should be used by insert, find, and remove.
 **/
template<typename K, typename V>
int HashTableChained<K, V>::compFunction(int code) {
    // Replace the following line with your solution.
    return code % arraysize;
}

/**
 *  Returns the number of entries stored in the dictionary.  Entries with
 *  the same key (or even the same key and value) each still count as
 *  a separate entry.
 *  @return number of entries in the dictionary.
 **/
template<typename K, typename V>
int HashTableChained<K, V>::size() {
    // Replace the following line with your solution.
    return count;
}

/**
 *  Tests if the dictionary is empty.
 *
 *  @return true if the dictionary has no entries; false otherwise.
 **/
template<typename K, typename V>
bool HashTableChained<K, V>::isEmpty() {
    // Replace the following line with your solution.
    if (count == 0) {
        return true;
    }
    else 
        return false;
}

/**
 *  Create a new Entry object referencing the input key and associated value,
 *  and insert the entry into the dictionary.
 *  Multiple entries with the same key (or even the same key and
 *  value) can coexist in the dictionary.
 *
 *  This method should run in O(1) time if the number of collisions is small.
 *
 *  @param key the key by which the entry can be retrieved.
 *  @param value an arbitrary object.
 **/
template<typename K, typename V>
void HashTableChained<K, V>::insert(const K& key, const V& value) {
    // Replace the following line with your solution.
    if (typeid(K) == typeid(string)) {
        index = compFunction(key->hashCode());
    }
    Node* newNode = new Node(key, value);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
    count++;

}

/**
 *  Search for an entry with the specified key.  If such an entry is found,
 *  return true; otherwise return false.
 *
 *  This method should run in O(1) time if the number of collisions is small.
 *
 *  @param key the search key.
 *  @return true if an entry containing the key is found, or false if
 *          no entry contains the specified key.
 **/
template<typename K, typename V>
bool HashTableChained<K, V>::find(const K& key) {
    // Replace the following line with your solution.
    index = compFunction(key->hashCode());
    Node* current = hashTable[index];
    while (current != nullptr) {
        cout << key << endl;
        if (current->key == key) {
            //cout << "Found key: " << current->key << endl;
            return true;
        }
        current = current->next;
    }
    return false;
}


/**
 *  Remove an entry with the specified key.  If such an entry is found,
 *  remove it from the table.
 *  If several entries have the specified key, choose one arbitrarily, then
 *  remove it.
 *
 *  This method should run in O(1) time if the number of collisions is small.
 *
 *  @param key the search key.
 */
template<typename K, typename V>
void HashTableChained<K, V>::remove(const K& key) {
    // Replace the following line with your solution.
    index = compFunction(key->hashCode());
    Node* current = hashTable[index];
    Node* previous = nullptr;

    while (current != nullptr) {
        if (find(key) == true) {
            if (previous == nullptr) {
                hashTable[index] = current->next;
            }
            else {
                previous->next = current->next;
            }
            delete current;
            break;
        }
        previous = current;
        current = current->next;
    }
    count--;
    return;
}

/**
 *  Remove all entries from the dictionary.
 */
template<typename K, typename V>
void HashTableChained<K, V>::makeEmpty() {
    // Your solution here.
    for (int i = 0; i < arraysize; i++) {
        delete hashTable[i];
    }
    count = 0;
    return;
}

template<typename K, typename V>
int HashTableChained<K, V>::collision() {
    // Your solution here.
    for (int i = 0; i < count; i++) {
        num = i - arraysize + arraysize * ((1 - 1 / arraysize) ^ i);
    }
    return num;
    
}
