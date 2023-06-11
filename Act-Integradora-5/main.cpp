//Marlon Yahir Martínez Chacón - A01424875
// Emmanuel Lechuga Arreola - A01736241
// Fecha de creación: 08/06/2023

/*** 
Se trata de un programa que lee los registros que se tienen de un intento de hackeo hacia un software donde se especifica el mes, dia y hora del intento de hackeo además de la dirección ip y del puerto, además de la falla que ocurrió; pero primero se nos dan el número de nodos y las conexiones que se realizaron entre cada nodo para el ataque junto a un peso para cada una de las conexiones

**/

/** 
*
*
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -O3 -o main *.cpp 
* Ejecucion:
*    ./main
**/
#include <iostream>
#include <string>
#include <sstream>
#include "Bitacora.h"

int main() {
  //Se hace referencia al Archivo de Bitacora, haciendo uso de un objeto de la clase bitacora 
  Bitacora bitacora1;
  bitacora1.conversionHashTable();
  bitacora1.numeroTotalColisiones();
  std::string direccionIp;
  std::cout << "Introduzca la direccion IP a buscar: ";
  getline(std::cin, direccionIp);
  
  
  //direccionIp = "3.12.191.184";
  //direccionIp = "1.1.1.1";

  bitacora1.obtenerResumenIp(direccionIp);
  return 0;
}
