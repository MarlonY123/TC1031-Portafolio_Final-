#ifndef _BITACORA_H_ //INICIO
#define _BITACORA_H_

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "Registro.h"
#include "MaxHeap.h"
#include "Ip.h"


class Bitacora: public Registro {

public:
  Bitacora(std::string);
  void leerDatos(std::string file = "");
  void mostrarDatos();
  void guardarDatos();
  void heapSortFunction();
  void guardarIpHeap();
  void guardarDatosHeap();
  void getTop5();
  

private:
  std::vector<Registro> listaRegistros;
  void heapify(std::vector<Registro> &registros, int N, int i);
  void heapSort(std::vector<Registro> &registros, int N);
  MaxHeap<Ip> myMaxHeap; 
  
};

#endif   // FIN _BITACORA_H_