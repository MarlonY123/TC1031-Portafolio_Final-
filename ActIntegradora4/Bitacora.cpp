// Se incluye la clase bitacora.h
#include "Bitacora.h"

//Complejidad O(1)
Bitacora::Bitacora(std::istream & input){ // esta en el main cuando hacer referencia al
                      // archivo "bitacora.txt"
  //complejidad O(1)
  leerDatos(input);
}

//Complejidad O(1)
void Bitacora::leerDatos(std::istream & input) { // abre el archivo
  g1.loadDirWeightedGraph(input);
}

//Complejidad O(n)
void Bitacora::mostrarDatos() {
  g1.print();
}
//Complejidad O(n)
void Bitacora::guardarDatosGradosSalida(){
  g1.guardarDatosLista();
}
 //Complejidad O(n)
void Bitacora::guardarTop5(){
  g1.guardarTop5MaxHeap();
}
//Complejidad O(1)
void Bitacora::imprimirBootMaster(){
  std::cout << "Boot Master: " << g1.getBootMaster() << std::endl;
}
//Complejidad O(n^2)
void Bitacora::encontrarCaminoMasCorto(){
  g1.caminoMasCorto();
}

void Bitacora::ipMasCercanaAlBootMaster(){
  g1.ipMenorDistancia();
}
