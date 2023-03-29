#ifndef _BITACORA_H_ //INICIO
#define _BITACORA_H_

#include <iostream>
#include <vector>
#include <ctime>
#include "Registro.h"

class Bitacora: public Registro {

public:
  Bitacora(std::string);
  void leerDatos(std::string file = "");
  void ordenarDatos();
  void buscarDatos(std::string,std::string,std::string,std::string,std::string,std::string);
  void mostrarDatos();
  void guardarDatos();

private:
  std::vector<Registro> listaRegistros;
  int partition(std::vector<Registro> &A, int low, int high, unsigned   int &compara, unsigned int &swap);
  void quickSort(std::vector<Registro>&, int, int, unsigned int &, unsigned int &);
  void selectionSort(std::vector<Registro>, int, unsigned int &, unsigned int &);
  int binarySearch(std::vector<Registro>&, time_t, int&);


};

#endif   // FIN _BITACORA_H_