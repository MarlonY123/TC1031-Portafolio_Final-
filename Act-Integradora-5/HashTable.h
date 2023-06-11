#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include "HashNode.h"
#include "ResumenIp.h"

template <class K, class T>
class HashTable {
  private:
    std::vector<HashNode<K, T>> table;
    int numElements;
    // Preferible usar un numero primo
    // https://numerosprimos.org/numeros-primos-de-1-a-100000/
    int maxSize;
    int totalColisiones;
//para la clase getipsummary
    unsigned int convertirIp(std::string ip);

  public:
    HashTable();
    HashTable(int selectedMaxSize);
    void setMaxSize(int selectedMaxSize);
    // Funcion hash
    int getHashIndex(K key);
    int getNumElements();
    void print();
    void add(K keyValue, T dataValue);
    int find(K keyValue);
    T getDataAt(int index);
    void remove(K keyValue);
    int getTotalCollisions();
    int getMaxSize();
//pruebas de getipsummary
    void getIPSummary(std::string ip);
};

//Complejidad O(1)
template <class K, class T>
HashTable<K, T>::HashTable() {
  maxSize = 0;
  numElements = 0;
  table = std::vector<HashNode<K,T>>(maxSize);
}
//Complejidad O(1)
template <class K, class T>
HashTable<K, T>::HashTable(int selectedMaxSize) {
  maxSize = selectedMaxSize;
  numElements = 0;
  table = std::vector<HashNode<K,T>>(maxSize);
}
//Complejidad O(1)
template <class K, class T>
void HashTable<K, T>::setMaxSize(int selectedMaxSize) {
  maxSize = selectedMaxSize;
  numElements = 0;
  table = std::vector<HashNode<K,T>>(maxSize);
}
//Complejidad O(1)
template<class K, class T>
int HashTable<K, T>::getHashIndex(K keyVal) {
  // metodo de residuales (llave mod maxSize)
  return keyVal % maxSize;
}
//Complejidad O(1)
template<class K, class T>
int HashTable<K, T>::getNumElements() {
  return numElements;
}

//Complejidad O(1)
template<class K, class T>
int HashTable<K, T>::getMaxSize() {
  return maxSize;
}
//Complejidad O(n)
template<class K, class T>
void HashTable<K,T>::print() {
  std::cout << "Content of the hash table: " << std::endl;
  for (int i = 0; i < maxSize; i++) {
    // status:  0 empty, 1 used, 2 deleted
    if (table[i].getStatus() == 1) // Cell is used
      std::cout << "Cell: " << i << " Key: " << table[i].getKey() << ", Value: " << table[i].getData() << ", Overflow.size: " << table[i].getOverflowSize() << std::endl;
  }
}
//Complejidad O(1+a)
template<class K, class T>
void HashTable<K,T>::add(K keyVal, T value) {
  if (numElements == maxSize) {
    throw std::out_of_range("Hash Table is full");
  }
  if (find(keyVal) != -1) {
    throw std::out_of_range("Element is already in the Hash Table");
  }
  // Compute the index of the table using a key and a hash function
  int hashVal = getHashIndex(keyVal); 
  HashNode<K, T> node = table[hashVal];
  // status:  0 empty, 1 used, 2 deleted
  if (node.getStatus() != 1) { // Cell is free
    node.setKey(keyVal);
    node.setData(value);
    table[hashVal] = node;
  }
  else { // Cell is already taken
    // Find next free space using quadratic probing
    // https://www.geeksforgeeks.org/quadratic-probing-in-hashing/
    int i = 1;
    int currentHashVal = getHashIndex(hashVal + i * i);
    HashNode<K, T> currentNode = table[currentHashVal];
    while (currentNode.getStatus() == 1) { // Cell is used
      i++;
      currentHashVal = getHashIndex(hashVal + i * i);
      currentNode = table[currentHashVal];
    }
    // A free cell was found
    currentNode.setKey(keyVal);
    currentNode.setData(value);
    node.addToOverflow(currentHashVal);
    table[currentHashVal] = currentNode;
    table[hashVal] = node;
  }
  numElements++;
}
//Complejidad O(n)
template<class K, class T>
int HashTable<K,T>::find(K keyVal) {
  int hashVal = getHashIndex(keyVal); 
  HashNode<K, T> node = table[hashVal];
  // status:  0 empty, 1 used, 2 deleted
  if (node.getStatus() == 1) { // Cell is used
    if (node.getKey() == keyVal) {
      return hashVal;
    }
    for (int i = 0; i < (int)node.getOverflowSize(); i++) {
      int overflowIndex = node.getOverflowAt(i);
      if (table[overflowIndex].getKey() == keyVal) {
        return overflowIndex;
      }
    }
    return -1;
  }
  return -1;
}
//Complejidad O(1)
template<class K, class T>
T HashTable<K,T>::getDataAt(int index) {
  return table[index].getData();
}
//Complejidad O(1)
template<class K, class T>
void HashTable<K,T>::remove(K keyVal) {
  int pos, hashVal;
  pos = find(keyVal);
  if (pos == -1) {
    throw std::invalid_argument("Element does not exist in hash table");
  }
  hashVal = getHashIndex(keyVal);
  if (pos != hashVal) { // collision element 
    HashNode<K, T> node = table[hashVal];
    node.removeFromOverflow(pos);
    table[hashVal] = node;
  }
  table[pos].clearData(); 
  numElements--;
}
 //Complejidad O(n)
template<class K, class T>
int HashTable<K,T>::getTotalCollisions() {
  totalColisiones = 0;
  for (int i = 0; i < maxSize; i++) {
    // status:  0 empty, 1 used, 2 deleted
    if (table[i].getStatus() == 1){
        totalColisiones += table[i].getOverflowSize();
    } // Cell is used
  }
  return totalColisiones;
}
//;______________________________________________________
//metodo creado para ayudar a la funcion getipsummary.
//Complejidad O(1)
template <class K, class T>
unsigned int HashTable<K, T>::convertirIp(std::string ip) {
  int indexPunto1 = ip.find('.');
  int indexPunto2 = ip.find('.', indexPunto1 + 1);
  int indexPunto3 = ip.find('.', indexPunto2 + 1);
  // Separa los valores de la dirección IP y los convierte en enteros
  int primerIp = std::stoi(ip.substr(0, indexPunto1));
  int segundoIp = std::stoi(ip.substr(indexPunto1 + 1, (indexPunto2 - indexPunto1) - 1));
  int tercerIp = std::stoi(ip.substr(indexPunto2 + 1, (indexPunto3 - indexPunto2) - 1));
  int cuartoIp = std::stoi(ip.substr(indexPunto3 + 1, (ip.size()) - indexPunto3));
  // Calcula el valor de la IP mediante cada uno de los valores de la IP multiplicando por la potencia de 256
  unsigned int valorIp = (primerIp * 16777216) + (segundoIp * 65536) + (tercerIp * 256) + cuartoIp;

  return valorIp;
}
//-----------> GetIpSummary <--------
//Complejidad O(n)
template <class K, class T>
void HashTable<K, T>::getIPSummary(std::string ip) {
  // Convertir la dirección IP a un entero sin signo
  unsigned int valorIp = convertirIp(ip);

  // Buscar el índice de la IP en la tabla hash
  int index = find(valorIp);

  // Si se encontró la IP en la tabla hash entonces...
  if (index != -1) {
    // Imprimir el resumen completo de la IP recibida
    ResumenIp resumen = getDataAt(index);
    resumen.imprimirResumen();
    std::cout << std::endl;
  } else {
    // La IP no se encontró en la tabla hash
    std::cout << "\nLa dirección IP " << ip << " no se encontró en la bitácora." << std::endl;
  }
}

#endif  // _HASH_TABLE_H