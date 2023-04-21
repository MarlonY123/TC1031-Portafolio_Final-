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
#include "DLinkedList.h"
#include "DLLNode.h"

class Bitacora: public Registro {

public:
  Bitacora(std::string);
  void leerDatos(std::string file = "");
  void ordenarDatos_merge();
  void ordenarDatos_quick();
  void buscarDatos(std::string,std::string,std::string,std::string,std::string,std::string);
  void mostrarDatos();
  void guardarDatos();  

private:
  DLinkedList<Registro> listaRegistros;
  

};

#endif   // FIN _BITACORA_H_