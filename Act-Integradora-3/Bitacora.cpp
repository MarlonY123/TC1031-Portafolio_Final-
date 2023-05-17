// Se incluye la clase bitacora.h
#include "Bitacora.h"

// Constructor donde se inicializan la función que lee los datos del archivo.txt
// std::string filename es el nombre del archivo .txt de donde se va a obtener la información
//Complejidad O(1)
Bitacora::Bitacora(
    std::string fileName) : myMaxHeap(750) { // esta en el main cuando hacer referencia al
                      // archivo "bitacora.txt"
  //complejidad O(1)
  leerDatos(fileName);
}

// Lee los datos del archivo.txt, los separa según mes, dia, hora, minutos y
// segundos para una vez que se hizo esto guardarlos en una lista std::string
// fileName es el nombre del archivo .txt de donde se va a obtener la
// información
//Complejidad general: O(n^2)
void Bitacora::leerDatos(std::string fileName) { // abre el archivo
  //complejidad O(1)
  std::ifstream in_stream;
  in_stream.open(fileName);
  // Si no se puede abrir el archivo entonces, envía un 1 para confirmar que no
  // se pudo abrir...
  //complejidad O(1)
  if (in_stream.fail()) {
    //std::cout << "No se pudo abrir el archivo " << fileName << std::endl;
     throw std::invalid_argument("No se pudo abrir el archivo");
    exit(1);
  }
  std::string input{};
  // Guardar los valores de las lineas del archivo, separados en
  // mes,dia,hora,ip, puerto y falla
// Complejidad de: O(n^2)
  while (getline(in_stream, input)) {
    std::stringstream input_stringstream(input);
    std::string elemento;
    std::vector<std::string> atributos;
    while (getline(input_stringstream, elemento, ' ')) {
      atributos.push_back(elemento);
    }
    std::string falla;
    for (int i = 4; i <= int(atributos.size()) - 1; i++) {
      falla += atributos[i] + " ";
    }
    // separa el valor del ip y del puerto del string que se recibió
    //Complejidad O(n)
    int indexPuntos = atributos[3].find(':');
    std::string ip = atributos[3].substr(0, indexPuntos);
    std::string puerto = atributos[3].substr(indexPuntos + 1, 6);

    //Les asigna los valores del vector a las variables correspondientes
    std::string hora, mes, dia;
    mes = atributos[0];
    dia = atributos[1];
    hora = atributos[2];
    // Se elimina el caracter de espacio al final del string falla
    falla.pop_back();
    // Se almacena un objeto de la clase registro en el vector de listaRegistros
    listaRegistros.push_back(Registro(mes, dia, hora,ip, puerto, falla));
  }
  //complejidad O(1)
  in_stream.close(); // cerramos archivo una vez se hizo el registro y divisiones.
}
// Función que muestra los datos que se encuentran en la lista doble mediante el
// uso de la función print de la lista Complejidad O(1)
//para este siguiente algoritmo tiene una complejidad de: O(n)
void Bitacora::mostrarDatos() {
  //Complejidad O(n)
  for (int i = 0; i <= int(listaRegistros.size()-1); i++) {
    std::cout << listaRegistros[i].getAll() << std::endl;
  }
}

//Codigo consultado en GeeksforGeeks. (2023). Heap Sort. GeeksforGeeks. https://www.geeksforgeeks.org/heap-sort/
//complejidad de: O(log n)
void Bitacora::heapify(std::vector<Registro> &registros, int N, int i)
{
    //Inicializa largest como la posición de la raiz
    int largest = i;
 
    // obtiene la posición del nodo hijo de la izquierda
    int l = 2 * i + 1;
 
    // obtiene la posición del nodo hijo de la izquierda
    int r = 2 * i + 2;
 
    // Comprueba si el valor del hijo de la izquierda es mayor que la raiz y asigna la posicion del hijo como la más grande
    if (l < N && registros[l] > registros[largest])
        largest = l;
 
    // Comprueba si el valor del hijo de la derecha es mayor que la raiz y le asigna la posición de mayor
    if (r < N && registros[r] > registros[largest])
        largest = r;
 
    // Comprueba si el valor largest no es el mismo que la raiz para intercambiar valores
    if (largest != i) {
        std::swap(registros[i], registros[largest]);
 
        // Llamada del método heapify para poder acomodar el arbol y que el mayor valor quede en la raiz
        // sub-tree
        heapify(registros, N, largest);
    }
}
// Main function to do heap sort
//Codigo consultado en GeeksforGeeks. (2023). Heap Sort. GeeksforGeeks. https://www.geeksforgeeks.org/heap-sort/
//complejidad de O(n log n)
void Bitacora::heapSort(std::vector<Registro> &registros, int N)
{
    // Repara el heap para que este en la raiz el mayor
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(registros, N, i);
 
    // Extrae cada uno de los elementos de la raiz 
    for (int i = N - 1; i > 0; i--) {
 
        // Intercambia el valor de la raiz con el ultimo
        std::swap(registros[0], registros[i]);
 
        // llama a la función heapify en el heap reducido
        heapify(registros, i, 0);
    }
}

//complejidad de O(n log n)
//Función que llama  a la función heapSort y le pasa el vector donde se encuentran los registros y el tamaño
void Bitacora::heapSortFunction()
{
  heapSort(listaRegistros, listaRegistros.size());
}

//Complejidad O(n)
//Guarda los datos de la ip, el valor de la ip y los accesos de esa ip que se encuentran en el vector dentro de un binary heap (priority queue), para esto obtiene el valor de los accesos contando cuantas veces aparece la ip 
void Bitacora::guardarIpHeap(){
  //Inicializa los accesos en 1
  int accesos = 1;
  //Recorrido para pasar por todo el vector y contar las veces que aparece cada ip, es decir, el numero de accesos
  for(int i = 0;i< int(listaRegistros.size());i++){
      //Si el valor de la ip es igual al siguiente significa que aparece otra vez la ip 
      if(listaRegistros[i] == listaRegistros[i+1]){
        //Se aumenta el valor de los accesos 
        accesos++;
      }
        //Si el valor es diferente significa que ya no aparece por lo que ya se puede guardar en el heap junto a los accesos y el valor de la ip
      else if(listaRegistros[i] != listaRegistros[i+1]){
        //se guarda en el heap ip, accesos y valorIp
        myMaxHeap.push(Ip(listaRegistros[i].getIp(), listaRegistros[i].getValorIp(), accesos));
        //Se inicializa accesos en 1 para empezar otra vez
        accesos = 1;
      } 
      
    }
}


// Complejidad temporal O(log n)
void Bitacora::getTop5(){
  Ip myIp;
  //Complejidad O(log n)
  for(int i = 0;i<5;i++){
      myIp = myMaxHeap.getTop();
      std::cout << myIp << std::endl;
      myMaxHeap.pop();
    }
}