//Marlon Yahir Martínez Chacón - A01424875
// Emmanuel Lechuga Arreola - A01736241
// Fecha de creación: 15/05/2023

/*** 
Se trata de un programa que lee los registros que se tienen de un intento de hackeo hacia un software donde se especifica el mes, dia y hora del intento de hackeo además de la dirección ip y del puerto, además de la falla que ocurrió; el programa además de leer y almacenar cada uno de los registros los ordena para poder obtener las ips que tuvieron mayor acceso durante el ataque antes mencionado

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
#include "Bitacora.h"
#include "Registro.h"

int main() {
 
  //Se hace referencia al Archivo de Bitacora, haciendo uso de un objeto de la clase bitacora 
  Bitacora bitacora1("bitacoraHeap.txt");
  
  bitacora1.heapSortFunction();

  bitacora1.guardarIpHeap();

  bitacora1.getTop5();

  return 0;
  
}
