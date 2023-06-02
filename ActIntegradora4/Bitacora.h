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
#include "Registro.h"
#include "Graph.h"




class Bitacora: public Registro {

public:
  Bitacora(std::istream & input);
  void leerDatos(std::istream & input);
  void mostrarDatos();
  void guardarDatosGradosSalida();
  void guardarTop5();
  void imprimirBootMaster();
  void encontrarCaminoMasCorto();
  void ipMasCercanaAlBootMaster();

  

private:
  std::vector<Registro> listaRegistros;
  std::map<unsigned int,std::string> mp;
  Graph g1;

};

#endif   // FIN _BITACORA_H_