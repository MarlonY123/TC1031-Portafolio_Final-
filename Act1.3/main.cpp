//Marlon Yahir Martínez Chacón - A01424875
// Emmanuel Lechuga Arreola - A01736241
//Fecha de creación: 21/03/2023

/*** 
Se trata de un programa que lee los registros que se tienen de un intento de hackeo hacia un software donde se especifica el mes, dia y hora del intento de hackeo además de la dirección ip y del puerto, además de la falla que ocurrió; el programa además de leer y almacenar cada uno de los registros los ordena para realizar la busqueda de las fechas que el usuario solicite para su análisis, esta busqueda mediante las fechas en que sucedió la falla y por último también guarda en un archivo .txt la información ordenada.

**/

/** 
* Ejemplo que implementa objetos de la clase Registro
* que contienen una fecha-hora convertida a Linux timestamp
* para realizar comparaciones (sobrecarga de operadores)
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
  /*
  // Crear objetos de la clase Registro (un renglon de la bitacora)
  Registro a("Jan", "01", "00", "01", "02", "1.1.1.1", "123", "Falla 1");
  Registro b("Feb", "04", "00", "01", "02", "1.1.1.3", "1234", "Falla 2");
  Registro c("Dec", "01", "00", "01", "02", "1.1.1.1", "123", "Falla 1");

  Registro key("Jan", "01", "00", "01", "02", "", "", "");
  std::cout << "Key " << std::endl;
  std::cout << key.getAll() << std::endl;

  
  std::vector<Registro> listaRegistros;
  listaRegistros.push_back(a);
  listaRegistros.push_back(b);
  listaRegistros.push_back(c);
  
  // Comparacion de dos objetos de la clase registro
  // gracias a la sobrecarga de operadores de comparacion
  if (listaRegistros[0] < listaRegistros[1]) std::cout << "a es menor que b" << std::endl;
  if (listaRegistros[0] == listaRegistros[2]) std::cout << "a es igual a c" << std::endl;

  
  for (int i = 0; i < (int)listaRegistros.size(); i++) {
    if (key == listaRegistros[i]) {
      std::cout << "found in " << i << std::endl;
      std::cout << listaRegistros[i].getAll() << std::endl;
    }
  }
*/
  //Se hace referencia al Archivo de Bitacora, haciendo uso de un objeto de la clase bitacora
  Bitacora bitacora1("bitacora.txt");
  //se llama a la función de ordenarDatos para el objeto bitacora1
  std::cout << "Ordenamiento de los datos: " << std::endl;
  bitacora1.ordenarDatos();
//Se manda a pantalla la parte en que el usuario introduzca los datos de la fecha para su busqueda
  std::cout << "Introduzca las fechas limites para la busqueda (inicio y fin) " << std::endl;
  //El usuario deberá de introducir una fecha de inicio y se le da un ejemplo
  std::cout << "FECHA INICIO (e.g., Jun 01 00:22:36): ";
  std::string mesI, diaI, horaCompletaI;
  std::cin >> mesI >> diaI >> horaCompletaI;
//El usuario deberá de introducir una fecha final para obtener un intervalo y se le da un ejemplo
  std::cout << "FECHA FINAL (e.g., Jun 01 00:22:36): ";
  std::string mesF, diaF, horaCompletaF;
  std::cin >> mesF >> diaF >> horaCompletaF;

  std::cout << std::endl;


//Los datos ingresados por el usuario son mandados al metodo de la clase bitacora,buscarDatos, los cuales son buscados por medio de la busqueda binaria, para que cuando se encuentren sean desplegados en la consola
  bitacora1.buscarDatos(mesI, diaI, horaCompletaI, mesF, diaF, horaCompletaF);

//Con esto decimos que los datos se guarden en en archivo txt, del vector donde estan todos los datos, pero estos ya estan ordenados.
  bitacora1.guardarDatos();


  
  return 0;
  
}
