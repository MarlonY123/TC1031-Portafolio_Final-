#ifndef _HASH_NODE_H
#define _HASH_NODE_H

#include <vector>
#include <algorithm>
#include <iterator>

template <class K, class T>
class HashNode {
  private:
    K key;
    T data;
    int status;  // 0 empty,  1 used,  2 deleted
    std::vector<int> overflow; // used to easily find collision elements

  public:
    HashNode();
    ~HashNode();
    K getKey();
    T getData();
    int getStatus();
    void setKey(K keyValue);
    void setData(T dataValue);
    void setStatus(int statusValue);
    void clearData();
    void addToOverflow(int hashIndex);
    int getOverflowSize();
    int getOverflowAt(int index);
    void removeFromOverflow(int index);
    
};

template <class K, class T>
HashNode<K, T>::HashNode() {
  key = 0;
  data = {};
  status = 0;
  overflow.clear();
}

template <class K, class T>
HashNode<K, T>::~HashNode() {
  key = 0;
  data = {};
  status = 0;
  overflow.clear();
}
//Complejidad O(1)
template <class K, class T>
K HashNode<K, T>::getKey() {
  return key;
}
//Complejidad O(1)
template <class K, class T>
T HashNode<K, T>::getData() {
  return data;
}
//Complejidad O(1)
template <class K, class T>
int HashNode<K, T>::getStatus() {
  return status;
}
//Complejidad O(1)
template <class K, class T>
void HashNode<K, T>::setKey(K keyValue) {
  key = keyValue;
}
//Complejidad O(1)
template <class K, class T>
void HashNode<K, T>::setData(T dataValue) {
  data = dataValue;
  status = 1; // 1 used
}
//Complejidad O(1)
template <class K, class T>
void HashNode<K, T>::setStatus(int statusValue) {
  status = statusValue;
}
//Complejidad O(1)
template <class K, class T>
void HashNode<K, T>::clearData() {
  data = {};
  status = 0; // 0 empty
}
//Complejidad O(1)
template <class K, class T>
void HashNode<K, T>::addToOverflow(int hashIndex) {
  overflow.push_back(hashIndex);
}
//Complejidad O(1)
template <class K, class T>
int HashNode<K, T>::getOverflowSize() {
  return overflow.size();
}
//Complejidad O(1)
template <class K, class T>
int HashNode<K, T>::getOverflowAt(int index) {
  return overflow[index];
}
//Complejidad O(1)
template <class K, class T>
void HashNode<K, T>::removeFromOverflow(int index) {
  std::vector<int>::iterator it = std::find(overflow.begin(), overflow.end(), index);
  // if index was found
  if (it != overflow.end()) {
    overflow.erase(overflow.begin()+(it - overflow.begin()));
  }
}

#endif  // _HASH_NODE_H
