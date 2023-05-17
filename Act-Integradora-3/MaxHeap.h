#ifndef _MAXHEAP_H_
#define _MAXHEAP_H_

#include <iostream>
#include <stdexcept>
#include <vector>
#include <fstream>

template <class T> class MaxHeap {
private:
  // contiene los elementos del heap
  std::vector<T> data;
  // capacidad maxima del heap
  int maxSize;
  // tamano actual del heap
  int currentSize;

  int parent(int k);
  int left(int k);
  int right(int k);
  void heapify(std::vector<T> &data, int n, int i);
  void deleteRoot(std::vector<T> &data, int& n);

public:
  MaxHeap(int maxCapacity);
  ~MaxHeap();
  bool isEmpty();
  int getMaxCapacity();
  int getCurrentSize();

  void printHeap();
  void push(T key);
  T getTop();
  void guardar();

  // TO-DO
  void pop();
};


//Complejidad O(1)
//Constructor para un arbol heap, la cual se introduce un numero maxumo de capacidad, 
template <class T> MaxHeap<T>::MaxHeap(int maxCapacity) {
  maxSize = maxCapacity;
  currentSize = 0;
  data.resize(maxSize);
}
//Complejidad O(1)
//destructor para liberar la memoria que ocupa el arbol heap
template <class T> MaxHeap<T>::~MaxHeap() {
  maxSize = 0;
  currentSize = 0;
  data.clear();
}

//complejidad O(1)
//Regresa un valor boleando diciendo si la fila priorizada está vacía o tiene datos.
template <class T> bool MaxHeap<T>::isEmpty() { return (currentSize <= 0); }
//Complejidad O(1)
//Regresa el valor de la maxima capacidad del heap
template <class T> int MaxHeap<T>::getMaxCapacity() { return maxSize; }
//Complejidad O(1)
//regresa el tamaño actual del heap
template <class T> int MaxHeap<T>::getCurrentSize() { return currentSize; }
//Complejidad O(n)
//va imprimiento los valores del arbol heap
template <class T> void MaxHeap<T>::printHeap() {
  std::cout << "Contenido del maxheap:" << std::endl;
  for (int i = 0; i < currentSize; i++) {
    std::cout << data[i] << std::endl;
  }
  std::cout << std::endl;
}
//Complejidad O(1)
//Son funciones para poder posicionar a los diferentes nodos, conforme se van agregando los valores, pero estas cooperan con la funcion push.
template <class T> int MaxHeap<T>::parent(int k) { return (k - 1) / 2; }

//Complejidad O(1)
//Retorna la posición del nodo del hijo izquierdo 
template <class T> int MaxHeap<T>::left(int k) { return (2 * k + 1); }

//Complejidad O(1)
//Retorna la posición del nodo del hijo derecho
template <class T> int MaxHeap<T>::right(int k) { return (2 * k + 2); }

//Complejidad de O(n)
//funcion que sirve para ir agregando valores a la fila priorizada
template <class T> void MaxHeap<T>::push(T key) {
  if (currentSize == maxSize) {
    throw std::out_of_range("Overflow: no se puede insertar la llave");
  }
  // Insertamos la nueva llave al final del vector
  int k = currentSize;
  data[k] = key;
  currentSize++;
  // Reparar las propiedades del maxheap si son violadas
  while (k != 0 && data[parent(k)] < data[k]) {
    std::swap(data[k], data[parent(k)]);
    k = parent(k);
  }
}
//Complejidad O(1)
//	Regresa el valor del dato que está con mayor prioridad en la fila priorizada.
template <class T> T MaxHeap<T>::getTop() {
  if (isEmpty()) {
    throw std::out_of_range("El heap esta vacio");
    return {};
  }
  return data[0];
}

//Codigo consultado en GeeksforGeeks. (2023). Heap Sort. GeeksforGeeks. https://www.geeksforgeeks.org/heap-sort/
//Complejidad O(nlog2 n)
//Función que repara el heap para obtener el mayor valor en la raíz
//Recibe de parametros una referencia al heap, su tamaño y la posicion de la raiz
template <class T> void MaxHeap<T>::heapify(std::vector<T> &data, int N, int i)
{
    //Inicializa largest como la posición de la raiz
    int largest = i;
 
    // obtiene la posición del nodo hijo de la izquierda
    int l = 2 * i + 1;
 
     // obtiene la posición del nodo hijo de la derecha
    int r = 2 * i + 2;
 
    // Comprueba si el valor del hijo de la izquierda es mayor que la raiz y asigna la posicion del hijo como la más grande
    if (l < N && data[l] > data[largest])
        largest = l;
 
    // Comprueba si el valor del hijo de la derecha es mayor que la raiz
    if (r < N && data[r] > data[largest])
        largest = r;
 
    // Comprueba si el valor largest no es el mismo que la raiz para intercambiar valores
    if (largest != i) {
        std::swap(data[i], data[largest]);
 
        // Llamada del método heapify para poder acomodar el arbol y que el mayor valor quede en la raiz
        // 
        heapify(data, N, largest);
    }
}

//Codigo consultado en GeeksforGeeks. (2023). Heap Sort. GeeksforGeeks. https://www.geeksforgeeks.org/heap-sort/
// Complejidad O(log2 n)
//Función para borrar el nodo raíz del heap
//Recibe de parametros una referencia al heap y su tamaño actual
template <class T> void MaxHeap<T>::deleteRoot(std::vector<T> &data, int& n)
{
    //Intercambia el valor de la raiz con  el del ultimo nodo
    std::swap(data[0], data[currentSize - 1]);
    // Decrementa el tamaño del heap en 1
    n = n - 1;
 
    // metódo recursivo para ordenar la nueva raíz
    heapify(data, n, 0);
}
 
//Complejidad O(log2n)
//Saca de la fila priorizada el dato que tiene mayor prioridad.
template <class T> void MaxHeap<T>::pop() {
  deleteRoot(data, currentSize);
}

#endif // _MAXHEAP_H_
