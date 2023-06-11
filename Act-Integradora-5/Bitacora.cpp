// Se incluye la clase bitacora.h
#include "Bitacora.h"

//Complejidad O(1)
Bitacora::Bitacora(){ // esta en el main cuando hacer referencia al
                      // archivo "bitacora.txt"
  //complejidad O(1)
  leerDatos("bitacoraGrafos.txt");
}

//Complejidad O(1)
void Bitacora::leerDatos(std::string titulo) { // abre el archivo
  g1.loadDirWeightedGraph(titulo);
}

//Complejidad O(n)
void Bitacora::mostrarDatos() {
  //g1.print();
  g1.imprimirVector();
}

//Complejidad O(n)
void Bitacora::conversionHashTable(){
  setResumenIp();
  myHashTable.setMaxSize(maxSize);
  //std::cout << "Num elements: " << myHashTable.getNumElements() << std::endl;
  for(int i = 1; i< resumenIp.size(); i++){
    myHashTable.add(resumenIp[i].getValorIp(),resumenIp[i]);
  }
  //std::cout << "Num elements: " << myHashTable.getNumElements() <<std::endl;
  
}
//Complejidad O(n)
void Bitacora::mostrarVector() {
  setResumenIp();
  for(int i = 1;i< resumenIp.size(); i++){
    resumenIp[i].imprimirResumen();
    std::cout << std::endl;
  }
}
//Complejidad O(1)
//Funcion que obtiene el vector con toda la información de las ip
void Bitacora::setResumenIp(){
  resumenIp = g1.getResumenIp();
}
//Complejidad O(1)
//Función que muestra el numero total de colisiones
void Bitacora::numeroTotalColisiones(){
  std::cout << "Numero de colisiones: "<< myHashTable.getTotalCollisions() << std::endl;
}
//Complejidad O(1)
//Función que obtiene la información de una ip dada por el usuario mediante la función getIPSummary
void Bitacora::obtenerResumenIp(std::string ip){
  myHashTable.getIPSummary(ip);
}

//Complejidad O(1)
//Función que obtiene el tamaño maximo de la tabla hash
void Bitacora::obtenerMaxSize(){
  std::cout  << "El tamaño maximo de la tabla hash es: " << myHashTable.getMaxSize() << std::endl;
}


