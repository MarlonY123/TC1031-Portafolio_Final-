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
#include <stdexcept>
#include <map>

#include "Graph.h"
#include "HashTable.h"




class Bitacora {

public:
  Bitacora();
  void leerDatos(std::string titulo);
  void mostrarDatos();
  void mostrarVector();
  void conversionHashTable();
  void numeroTotalColisiones();
//pruebas de getipsumary

  void obtenerResumenIp(std::string ip);
  void obtenerMaxSize();

  

private:
  Graph g1;
  std::vector<ResumenIp> resumenIp;
  
  void setResumenIp();
  HashTable<unsigned int, ResumenIp> myHashTable;
  //int maxSize = 14009;
  int maxSize = 15541;
  int totalColisiones = 0;

};

#endif   // FIN _BITACORA_H_