 #ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "DLLNode.h"
#include <iostream>
#include <stdexcept>

template <class T> class DLinkedList {
private:
  DLLNode<T> *head;
  DLLNode<T> *tail;
  int numElements;
  //Quick sort --> complejidad O(n log n)
  void quickSort(DLLNode<T> *head, DLLNode<T> *tail, unsigned int &comparaQS, unsigned int &swapsQS);
  DLLNode<T> *partition(DLLNode<T> *head, DLLNode<T> *tail, unsigned int &comparaQS, unsigned int &swapsQS);
  void swapData(DLLNode<T> *nodo1, DLLNode<T> *nodo2);
  //Merge sort --> complejidad O(n log n)
  DLLNode<T> *merge(DLLNode<T> *first, DLLNode<T> *second,unsigned int &comparaMS);
  DLLNode<T> *mergeSort(DLLNode<T> *head,unsigned int &comparaMS);
  DLLNode<T> *split(DLLNode<T> *head);
  
  
  DLLNode<T> *middleElement(DLLNode<T>* start, DLLNode<T>* last);


public:
  DLinkedList();
  ~DLinkedList();
  int getNumElements();
  void printList();
  void printListReversed();
  void addFirst(T value);
  void addLast(T value);
  bool deleteData(T value);
  bool deleteAt(int position);
  T getData(int position);

  void updateData(T value, T newValue);
  void updateAt(int position, T newValue);
  int findData(T value);
  void invert();
  void sort();
  void merge_sort();
  DLLNode<T> *getHead();
  DLLNode<T> *binarySearch(DLLNode<T> *head, T value);
  DLinkedList<T> getReversedSublist(int ini, int fin);
  DLinkedList<T> getSublist(DLLNode<T> *start, DLLNode<T> *end);

};

// Complejidad O(1)
template <class T> DLinkedList<T>::DLinkedList() {
  // std::cout << "---> Creando una lista doblemente ligada vacia: " << this <<
  // std::endl;
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

// Liberacion de memoria --> Complejidad O(n)
template <class T> DLinkedList<T>::~DLinkedList() {
  // Liberando memoria de la lista doblemente ligada

  DLLNode<T> *p, *q;
  p = head;
  while (p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

// Complejidad O(1) funcion para obtener el numero de elementos en la DLinkedList
template <class T> int DLinkedList<T>::getNumElements() { return numElements; }

// Complejidad O(n) metodo que imprime la lista completa
template <class T> void DLinkedList<T>::printList() {
  DLLNode<T> *ptr = head;
  while (ptr != nullptr) {
    std::cout << ptr->data.getAll()<<std::endl;
    ptr = ptr->next;

  }
  std::cout<< std::endl;
}

// Complejidad O(n) funcion que imprime la lista completa al revés
template <class T> void DLinkedList<T>::printListReversed() {
  DLLNode<T> *ptr = tail;
  while (ptr != nullptr) {
    std::cout << ptr->data << " ";
    ptr = ptr->prev;
  }
  std::cout << std::endl;
}

// Complejidad O(1) metodo para agregar un elemento al inicio de la lista
template <class T> void DLinkedList<T>::addFirst(T value) {
  // 1. crear un newNode
  DLLNode<T> *newNode = new DLLNode<T>(value);
  // Si la lista esta vacia
  if (head == nullptr && tail == nullptr) {
    head = newNode;
    tail = newNode;
  } else {
    // 2. apuntar newNode->next a donde esta head
    newNode->next = head;
    // 3. apuntar head->prev al newNode
    head->prev = newNode;
    // 3. Actualizar head para apuntar al newNode
    head = newNode;
  }
  numElements++;
}

// Complejidad O(1) metodo que agrega una variable tipo T al final de la lista y incrementa el numero de elementos.
template <class T> void DLinkedList<T>::addLast(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr)
    addFirst(value);
  else {
    // 1. crear un newNode
    DLLNode<T> *newNode = new DLLNode<T>(value);
    // 2. apuntar tail->next a newNode
    tail->next = newNode;
    newNode->prev = tail;
    // 3. actualizar tail para apuntar al newNode
    tail = newNode;
    numElements++;
  }
}

// Complejidad O(n) metodo para borrar alguna variable tipo T, de cualquier ligar de la lista
template <class T> bool DLinkedList<T>::deleteData(T value) {
  // Si La lista esta vacia regresa un valor booleano falso (false)
  if (head == nullptr && tail == nullptr)
    return false;
  else {
    //si la lista no esta vacia entonces...
    DLLNode<T> *p = head;
    DLLNode<T> *previous = nullptr;
    while (p != nullptr && p->data != value) {
      previous = p;
      p = p->next;
    }
    // si no existe el value <T> en la lista
    if (p == nullptr)
      return false;
    // si debo borrar el primer elemento de la lista
    if (p != nullptr && p == head) {
      head = p->next;
      if (head == nullptr) // habia solo un nodo en la lista
        tail = nullptr;
      else
        head->prev = nullptr;
    } else if (p->next == nullptr) { // debo borrar el ultimo nodo
      previous->next = nullptr;
      tail = previous;
    } else { // debo borrar cualquier otro nodo
      previous->next = p->next;
      p->next->prev = previous;
    }
    delete p;
    p = nullptr;
    numElements--; //se reduce el numero de elementos
    return true;
  }
}

// Complejidad O(n) funcion que borra el elemento segun la posicion elegida
template <class T> bool DLinkedList<T>::deleteAt(int position) {
  if (position < 0 || position >= numElements) {//solo actua si la posicion estan fuera de los limites del numero de elementos.
    throw std::out_of_range("Indice fuera de rango");
  } else if (position == 0) {
    DLLNode<T> *p = head;
    // si la lista contiene un solo nodo...
    if (head != nullptr && head->next == nullptr) {
      head = nullptr;
      tail = nullptr;
    } else {
      head = p->next;
      head->prev = nullptr; // cambio
    }
    delete p;
    p = nullptr;
    numElements--;
    return true;
  } else { // borrar cualquier otro elemento de la lista segun su posicion
    DLLNode<T> *p = head;
    DLLNode<T> *previous = nullptr;
    int index = 0;
    // buscar el indice del elemento a borrar
    while (index != position) {
      previous = p;
      p = p->next;
      index++;
    }
    // si debo borrar el ultimo elemento
    if (p->next == nullptr) {
      previous->next = nullptr;
      tail = previous;
    } else { // borrar cualquier otro nodo
      previous->next = p->next;
      p->next->prev = previous; // cambio
    }
    delete p;
    p = nullptr;
    numElements--;
    return true;
  }
}

// Complejidad O(n) funcion con la cual obtendremos el valor de un elemento de la lista.
template <class T> T DLinkedList<T>::getData(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else {
    if (position == 0) { // si es el primero de la lista
      return head->data;
    }
    // debemos buscar el elemento
    DLLNode<T> *p = head;
    int index = 0;
    // buscar el indice del elemento a borrar
    while (p != nullptr) {
      if (index == position)
        return p->data;
      p = p->next;
      index++;
    }
    return {};
  }
}
//Métodos en clase
//Update Data ---- complejidad O(n)
//Actualiza un elemento mediante el viejo valor que recibe y el nuevo valor
template <class T> 
void DLinkedList<T>::updateData(T value, T newValue) {
    // debemos buscar el elemento 
    DLLNode<T> *p = head;
    int index = 0;
    // buscar el indice del elemento a borrar 
    while (p != nullptr || index == -1) { 
      //cambiar el elemento a borrar si este cumple con los parametros y regresar un valor diferente de index para romper el ciclo.
      if (p->data == value){ 
        p->data = newValue;
        index = -2;
      }
      p = p->next;
      index++;
    }
  //Si el index es igual al numero de elementos, es como si se confirmara un error y quiere decir que no se pudo realizar la actualizacion.
    if(index == numElements)
    {
      throw std::out_of_range("No se pudo actualizar");
    }
}

//Update At ---- complejidad O(n)
//Actualiza un elemento mediante la posicion que recibe y el nuevo valor
template <class T> 
void DLinkedList<T>::updateAt(int position, T newValue) {
  //if statement, que se realiza con el fin de poder correr adecuadamente el update at, asi descartamos que la posicion sea una que no existe en la lista.
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else {
    if (position == 0) { // si es el primero de la lista actualizamos head
      head->data = newValue;
    }
    // debemos buscar el elemento
    DLLNode<T> *p = head;
    int index = 0;
    // buscar el indice del elemento a cambiar siempre y cuando la lista no llegue al final
    while (p != nullptr) {
      if (index == position)
        p->data = newValue;
      p = p->next;
      index++;
    }
  }
}

//Find Data ---- Complejidad  O(n)
//Encuentra la posición de un elemento mediante el valor que recibe
template <class T> 
int DLinkedList<T>::findData(T value) {
  DLLNode<T> *p = head;
  int index = 0;
  //buscamos mediante un while, mientras que no llegue el apuntador a nullptr
  while (p != nullptr) {
    //se activa solo cuando se encuentra el valor en la lista y regresa la posición
    if (p->data == value) { 
      return index;
    }
    p = p->next;
    index++;
  }
  //Cuando no se logra encontrar el valor regresa un -1, confirmando que no se encontró.
  return -1;
}

//----------Métodos de la actividad 2-2-----------
//Consulta de codigo para invertir la lista
//GeeksforGeeks. (2023f). Reverse a Doubly Linked List. GeeksforGeeks. https://www.geeksforgeeks.org/reverse-a-doubly-linked-list/

//Metodo que invierte la lista que se tiene
//Complejidad O(n)
template <class T> void DLinkedList<T>::invert() {
  //Se crean nodos que apuntan al head y tail
  DLLNode<T> *ptrHead = head, *ptrTail = tail;
  //Contador para poder terminar el bucle a la mitad
  int contador = 0;
  //Bucle que termina cuando llega el apuntador de tail a la mitad
  while (contador != (numElements / 2)) {
    //Variable que servira para guardar de manera temporal el valor de head
    T tempData = ptrHead->data;
    //Se cambia el valor de head al valor de tail
    ptrHead->data = ptrTail->data;
    //Se cambia el valor de tail al de head que esta en la variable
    ptrTail->data = tempData;
    //Se retrocede uno en tail
    ptrTail = ptrTail->prev;
    //Se avanza al siguiente de head
    ptrHead = ptrHead->next;
    contador++;
  }
}

//Método que recibe dos nodos(nodo1 y nodo2) para intercambiar sus valores de data
//Complejidad O(1)
template <class T>
void DLinkedList<T>::swapData(DLLNode<T> *nodo1, DLLNode<T> *nodo2) {
  //Variable temporal para almacenar el valor de data del nodo1
  T nuevoDato = nodo1->data;
  //Se cambia la data del nodo1 por la data del nodo2
  nodo1->data = nodo2->data;
  //Se cambia la data del nodo2 por la data de la variable temporal (data de head)
  nodo2->data = nuevoDato;
}
//Metodo parte del quick sort que particiona los datos mediante un pivote recibe el nodo que apunta a head y el nodo que apunta a tail
//Complejidad O(n)
template <class T>
DLLNode<T> *DLinkedList<T>::partition(DLLNode<T> *head, DLLNode<T> *tail, unsigned int &comparaQS, unsigned int &swapsQS) {
  //Se toma como pivote el ultimo valor de la lista
  T pivot = tail->data;
  //Se crea un nuevo nodo que apunta al prev de head en este caso seria null
  DLLNode<T> *i = head->prev;
  //Bucle para recorre la lista mediante un nodo j que apunta a head y va avanzando un lugar hasta que alcance a tail y termine
  for (DLLNode<T> *j = head; j != tail; j=j->next) {
    comparaQS++;
    //Comprueba que la data de j sea menor o igual que el valor del pivote
    if (j->data <= pivot) {
      //Si i sigue apuntando a null en el prev de head entonces se le da el valor de head
      if (i == nullptr)
        i = head;
      //En caso de no apunte a null avanza un lugar en la lista
      else
        i = i->next;
      //Se intercambia los valores de data de los nodos i y j
      swapData(i, j);
      swapsQS++;
    }
  }
  //Si i sigue apuntando a null en el prev de head entonces se le da el valor de head
  if (i == nullptr)
    i = head;
  //En caso de no apunte a null avanza un lugar en la lista
  else
    i = i->next;
  //Se intercambia los valores de data de los nodos i y tail
  swapData(i, tail);
  swapsQS++;
  //Regresa el nodo i
  return i;
}
//Quick sort
//Consulta de código
//GeeksforGeeks. (2023a). QuickSort on Doubly Linked List. GeeksforGeeks. https://www.geeksforgeeks.org/quicksort-for-linked-list/
//-------------------------------------------------
//Método del algoritmo quickSort para ordenar los datos de la lista mediante los parámetros de nodos que apunten a head y tail de la lista
//Complejidad -->  O(nlog(n))
template <class T>
void DLinkedList<T>::quickSort(DLLNode<T> *head, DLLNode<T> *tail,unsigned int &comparaQS, unsigned int &swapsQS) {
  //Se comprueba que la lista no este vacía o solo tenga un elemento
  if (tail != nullptr && head != tail && head != tail->next) {
    // encontrar la particion que regresa el nodo 
    DLLNode<T> *ptr = partition(head, tail,comparaQS, swapsQS);

    // ordenar la mitad izquierda y derecha mediante quick sort
    quickSort(head, ptr->prev, comparaQS, swapsQS);
    quickSort(ptr->next, tail, comparaQS, swapsQS);
  }
}

//Método que llama a la función quickSort para pasarle los nodos head y tail que apuntan al principio y al final de la lista
//Complejidad O(1)
template <class T> 
void DLinkedList<T>::sort() { 
  unsigned int comparaQS = 0;
  unsigned int swapsQS = 0;
  //Llama a la función quick sort y le pasa los nodos head y tail
  quickSort(head, tail,comparaQS, swapsQS);
  std::cout << "Comparaciones quick Sort: " << comparaQS << std::endl;
}
//Método que crea una sublista invertida de la lista mediante los párametros que son índices del inicio y fin de donde se quiere la sublista, se regresa un objeto lista invertido
//Reverse --> Complejidad O(n) 
template <class T>
DLinkedList<T> DLinkedList<T>::getReversedSublist(int ini, int fin){
  //contador para saber cual es el indice de cada nodo
  int contador = 0;
  //Nodo que apunta a head para empezar a recorrer la lista
  DLLNode<T> *ptr = head;
  //Sublista que será invertida y devuelta
  DLinkedList<T> subListaInversa;
  //Bucle que no termina hasta que se llega al indice fin mediante un contador
  while(contador <= fin){
    //Comprueba si es que el contador ya es igual o mayor que el indice de inicio para empezar a crear la lista
    if(contador >= ini){
      //Se añaden los datos de la lista a la sublista mediante addFirst para sea invertida
      subListaInversa.addFirst(ptr->data);
    }
    //Se avanza el puntero hacia el siguiente nodo
    ptr = ptr->next;
    //Se incrementa en 1 el contador
    contador++;
  }
  //Se retorna la sub-lista invertida
  return subListaInversa;
}

//Merge --> complejidad O(n log n) combina las dos listas
template <class T>
DLLNode<T> *DLinkedList<T>::merge(DLLNode<T> *first, DLLNode<T> *second, unsigned int &comparaMS){
  comparaMS++;
  if(!first)
    return second;
  if(!second)
    return first;
  if(first->data < second->data){
    first->next = merge(first->next,second, comparaMS);
    first->next->prev = first;
    first->prev = nullptr;
    return first;
  }
  else{
    second->next = merge(first,second->next,comparaMS);
    second->next->prev = second;
    second->prev = nullptr;
    return second;
  }
}
//Consulta del código para merge Sort
//GeeksforGeeks. (2023b). Merge Sort for Doubly Linked List. GeeksforGeeks. https://www.geeksforgeeks.org/merge-sort-for-doubly-linked-list/

//Merge Sort ----->   complejidad (n log n)
//Divide la lista en dos mitades recursivamente, se llama a sí mismo para las dos mitades y después une ambas mitades ordenadas
template <class T>
DLLNode<T> *DLinkedList<T>::mergeSort(DLLNode<T> *head, unsigned int &comparaMS){
  if(!head || !head->next)
    return head;
  DLLNode<T> *second = split(head);

  head = mergeSort(head,comparaMS);
  second = mergeSort(second,comparaMS);

  return merge(head,second,comparaMS);
}
// complejidad O(n)--> funcion que obtiene el elemento de en medio para poder dividir la lista en dos mitades
template <class T>
DLLNode<T> *DLinkedList<T>::split(DLLNode<T> *head){
  DLLNode<T> *fast = head, *slow = head;
  while(fast->next && fast->next->next){
    fast = fast->next->next;
    slow = slow->next;
  }
  DLLNode<T> *temp = slow->next;
  slow->next = nullptr;
  return temp;
}

//Complejidad O(1)--> funcion de ordenamiento de datos
template <class T>
void DLinkedList<T>::merge_sort(){
  //Variable para saber las comparaciones que hizo el merge sort
  unsigned int comparaMS = 0;
  //se va cambiando el valor de head para poder unir la lista 
  head = mergeSort(head, comparaMS);
  std::cout << "Comparaciones merge Sort: " << comparaMS << std::endl;
}
//Complejidad O(1) funcion llamada para obtener el primer valor de la lista 
template<class T>
 DLLNode<T> *DLinkedList<T>::getHead(){
   //Obtiene el head de la lista
   return head;
 }
//metodo  parte de busqueda binaria que divide en este caso la lista de doble nodo en 2 para el procesamiento con binary search.
//Binary search ---> Complejidad O(n)
template <class T>
DLLNode<T>* DLinkedList<T>::middleElement(DLLNode<T>* start, DLLNode<T>* last)
{
  //Checa que la lista no este vacia
    if (start == nullptr)
        return nullptr;
    //Apunta un nodo a start y otro al siguiente de start
    DLLNode<T>* slow = start;
    DLLNode<T>* fast = start -> next;
  //Bucle que no termina hasta que fast sea igual a last
    while (fast != last)
    {
        //Se mueve en uno el apuntador fast
        fast = fast -> next;
        //Se comprueba si todavia fast no llega a last
        if (fast != last)
        {
          //Se avanza un lugar cada apuntador
            slow = slow -> next;
            fast = fast -> next;
        }
    }
    //Una vez que se termine el bucle regresa el valor de en medio de la lista
    return slow;
}
//Consulta de código 
// GeeksforGeeks. (2023a). Binary Search on Singly Linked List. GeeksforGeeks. https://www.geeksforgeeks.org/binary-search-on-singly-linked-list/
//Algoritmo encargado de la busqueda binaria.


//Binary Search --> complejidad O(log2 n) 
//algoritmo de busqueda el cual sigue un metodo de divide y encontraras,mas o menos. se divide la lista entera en partes iguales, despues se busca el valor en ambos lados, pero primero busca en una mitad y luego busca e la otra.
template<class T>
DLLNode<T> *DLinkedList<T>::binarySearch(DLLNode<T> *head, T value){
  //Se declaran dos punteros que apuntan a head y null
  DLLNode<T> *first =head;
  DLLNode<T> *last = nullptr;

  do{
    //se obtiene el elemento de en medio en este caso un nodo
    DLLNode<T> *mid = middleElement(first, last);
    //Se checa que el elemento de en medio tenga un valor
    if(mid==nullptr)
      return nullptr;
    //Si el de en medio es igual al valor se retorna el elemento
    if(mid->data == value)
      return mid;
    //Se comproba si es que el elemento de en medio es mayor menor que el valor para saber si ir a la primera mitad o a la segunda
    else if(mid->data < value)
      first = mid->next;
    else
      //Se va hacia la segunda mitad que es mayor para seguir buscando
      last = mid;
  }while(last ==nullptr || last != first);
  //Bucle que no termina mientras el puntero last sea igual a null o sea diferente a first
  //En caso de que no se encuentre se retorna null como resultado
  return nullptr;

}



#endif // _LINKEDLIST_H_
