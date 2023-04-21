//Marlon Yahir Martínez Chacón - A01424875
// Emmanuel Lechuga Arreola - A01736241
//Fecha de creación: 17/04/2023

/*** 
Se trata de un programa que lee los registros que se tienen de un intento de hackeo hacia un software donde se especifica el mes, dia y hora del intento de hackeo además de la dirección ip y del puerto, además de la falla que ocurrió; el programa además de leer y almacenar cada uno de los registros los ordena para realizar la busqueda de las fechas que el usuario solicite para su análisis guardando en un archivo txt los resultados de dicha busqueda, esta busqueda mediante las fechas en que sucedió la falla y por último también guarda en un archivo .txt la información ordenada.

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
 
  //Se hace referencia al Archivo de Bitacora, haciendo uso de un objeto de la clase bitacora para crear la doubly linked list
  Bitacora bitacora1("bitacora.txt");
  Bitacora bitacora2("bitacora.txt");
  //Se ordena una de las listas mediante merge sort para comparar la eficiencia 
  bitacora1.ordenarDatos_merge();
  //Se ordena una de las listas mediante quick sort para comparar la eficiencia 
  //Y se deslpliegan ambos datos de comparacion
  bitacora2.ordenarDatos_quick();
  //Se manda a pantalla la parte en que el usuario introduzca los datos de la fecha para su busqueda
  std::cout << "Introduzca las fechas limites para la busqueda (inicio y fin) " << std::endl;
  //El usuario deberá de introducir una fecha de inicio para obtener un intervalo y se le da un ejemplo
  std::cout << "FECHA INICIO (e.g., Jun 01 00:22:36): ";
  std::string mesI, diaI, horaCompletaI;
  std::cin >> mesI >> diaI >> horaCompletaI;
//El usuario deberá de introducir una fecha final para obtener un intervalo y se le da un ejemplo
  std::cout << "FECHA FINAL (e.g., Jun 01 00:22:36): ";
  std::string mesF, diaF, horaCompletaF;
  std::cin >> mesF >> diaF >> horaCompletaF;
//Los datos ingresados por el usuario son mandados al metodo de la clase bitacora,buscarDatos, los cuales son buscados por medio de la busqueda binaria, para que cuando se encuentren sean desplegados en la consola, además de que los resultados los guarde en un archivo txt por separado
  bitacora1.buscarDatos(mesI, diaI, horaCompletaI, mesF, diaF, horaCompletaF);
  //Con esto decimos que los datos se guarden en en archivo txt, de la lista donde estan todos los datos, pero estos ya estan ordenados.
  bitacora1.guardarDatos();


  
  return 0;
  
}
