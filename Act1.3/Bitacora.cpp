#include "Bitacora.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

//Constructor donde se inicializan la función que lee los datos del archivo.txt 
//std::string filename es el nombre del archivo .txt de donde se va a sacar la información
Bitacora::Bitacora(std::string fileName){ //esta en el main cuando hacer referencia al archivo "bitacora.txt"
  leerDatos(fileName);
}

//Lee los datos del archivo .txt, los separa según mes, dia, hora, minutos y segundos para una vez que se hizo esto guardarlos en un vector de tipo Registro
//std::string fileName es el nombre del archivo .txt de donde se va a sacar la información
void Bitacora::leerDatos(std::string fileName)
{
    std::ifstream in_stream;
    in_stream.open(fileName);
    //Si no se puede abrir el archivo entonces...
    if (in_stream.fail()) { 
        std::cout << "No se pudo abrir el archivo " << fileName << std::endl;
        exit(1);
    }
    std::string input{};
  //Guardar los valores de las lineas del archivo, separados en mes,dia,horario,ip, puerto y falla
    while(getline(in_stream,input)) {
        std::stringstream input_stringstream(input);
        std::string elemento;
        int counter;
        std::vector <std::string> atributos;
        while (getline(input_stringstream, elemento, ' ')) {
            atributos.push_back(elemento);
        }
      std::string falla;
      for(int i = 4; i<= atributos.size()-1;i++)
        {
          falla += atributos[i] + " "; 
        }
      //separa el valor del ip y del puerto del string que se recibió
      int indexPuntos = atributos[3].find(':');
      std::string ip = atributos[3].substr(0,indexPuntos);
      std::string puerto = atributos[3].substr(indexPuntos+1,6);
     
      int indexPrimerDosPuntos = 2, indexSegundoDosPuntos = 5;
      std::string horas, minutos, segundos, mes, dia;
      mes = atributos[0];
      dia = atributos[1];
       //Separa los valores de la hora, minutos y segundos del string que se recibe (00:00:00)
      horas  = atributos[2].substr(0, indexPrimerDosPuntos);
      minutos  = atributos[2].substr(indexPrimerDosPuntos+1, 2);
      segundos = atributos[2].substr(indexSegundoDosPuntos+1, 2);

      //Se elimina el caracter de espacio al final del string falla
      falla.pop_back();
      //Se almacena un objeto de la clase registro en el vector listaRegistros
      listaRegistros.push_back(Registro(mes, dia,horas,minutos,segundos,ip,puerto,falla));
    }
    in_stream.close();
}

//Muestra todos los datos que se encuentran almacenados en el vector de Registros

void Bitacora::mostrarDatos(){
  for(int i = 0; i<=listaRegistros.size()-1;i++)
    {
      std::cout << listaRegistros[i].getAll() << std::endl;
    }
}
//---------------------------------Algoritmos de ordenar Datos--------------------------
//Ordena los datos del vector mediante el uso de los algoritmos de Quick Sort y Selection Sort y nos muestra sus comparaciones y swaps de cada uno
void Bitacora::ordenarDatos(){
  unsigned int comparacionesQuick = 0, swapQuick = 0, comparacionesSelec = 0, swapSelec = 0;

  selectionSort(listaRegistros, listaRegistros.size()-1, comparacionesSelec, swapSelec);
  std::cout << "SELECTION SORT" << std::endl;
  std::cout<< "Comparaciones: " << comparacionesSelec << "\nSwaps: " << swapSelec << std::endl << std::endl ;

  quickSort(listaRegistros, 0, listaRegistros.size()-1, comparacionesQuick, swapQuick);
std::cout << "QUICK SORT" << std::endl;
std::cout<< "Comparaciones: "<< comparacionesQuick << "\nSwaps: " << swapQuick << std::endl << std::endl;

}

//Algoritmo de Quick Sort para ordenar los datos del vector
void Bitacora::quickSort(std::vector<Registro> &A, int low, int high, unsigned int &compara, unsigned int &swap){
    if (low < high) {
    // encontrar la particion
    int pi = partition(A, low, high, compara, swap);
    // ordenar la mitad izquierda y derecha
    quickSort(A, low, pi-1, compara, swap);
    quickSort(A, pi+1, high, compara, swap);
  }
}


//Parte del algoritmo de quick Sort
//std::vector<Registro> &A = referencia al vector con todos los registros que se leyeron del archivo.txt
//int low = el index del primer dato del vector
//int high = el index del ultimo dato del vector
//unsigned int &compara = numero de comparaciones que se van a realizar
//unsigned int &swap = numero de swaps que se realizan
//retorna el index
int Bitacora::partition(std::vector<Registro> &A, int low, int high, unsigned int &compara, unsigned int &swap) {
  time_t pivot = A[high].getFechaHora();
  int i = low - 1;
  for (int j = low; j<high; j++){
    compara++;
    if (A[j].getFechaHora() < pivot ){
      i++;
      std::swap(A[i], A[j]);
      swap++;
    }
  }
  std::swap(A[i+1], A[high]);
  swap++;
  return i+1;
}


//Algoritmo de Selection Sort para ordenar los datos del vector}
//std::vector<Registro> &A = referencia al vector con todos los registros que se leyeron del archivo.txt
//int n = tamaño del vector
//unsigned int &compara = numero de comparaciones que se van a realizar
//unsigned int &swap = numero de swaps que se realizan
void Bitacora::selectionSort(std::vector<Registro> A, int n, unsigned int &compara, unsigned int &swap)
{
  compara = swap = 0;
  for (int i = 0; i < n - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < n; j++) {
      compara++;
      //se compara los valores de la fechaHora
      if (A[j].getFechaHora() < A[minIndex].getFechaHora())
        minIndex = j;
    }
    std::swap(A[i], A[minIndex]);
    swap++;
  }
}


//BUSQUEDA DE DATOS

//Recibe datos del usuario para poder realizar la busqueda de las fechas mediante fechas que sirven como limite superior e inferior.
//mesInicio, diaInicio, horaCompletaI(es un string que contiene hora,minutos y segundos en el formato 00:00:00) se refieren a la fecha de inicio 
//mesFinal, diaFinal, horaCompletaF(es un string que contiene hora,minutos y segundos en el formato 00:00:00) se refieren a la fecha final 
void Bitacora::buscarDatos(std::string mesInicio,std::string diaInicio,std::string horaCompletaI,std::string mesFinal,std::string diaFinal,std::string horaCompletaF)
{
  int indexPrimerDosPuntos = 2, indexSegundoDosPuntos = 5;
  //Se separa la hora, minutos y segundos de inicio del string que recibe la función  
  std::string horaInicio  = horaCompletaI.substr(0, indexPrimerDosPuntos);
  std::string minutosInicio  = horaCompletaI.substr(indexPrimerDosPuntos+1, 2);
  std::string segundosInicio = horaCompletaI.substr(indexSegundoDosPuntos+1, 2);

   //Se separa la hora, minutos y segundos de final del string que recibe la función 
  std::string horaFinal = horaCompletaF.substr(0, indexPrimerDosPuntos);
  std::string minutosFinal = horaCompletaF.substr(indexPrimerDosPuntos+1, 2);
  std::string segundosFinal = horaCompletaF.substr(indexSegundoDosPuntos+1, 2);

  //Se crean e inicializan las variables que se van a ocupar para medir la efectividad de cada uno de los algoritmos medainte las comparaciones y los swaps
  int comparaBinaryInicio = 0, comparaBinaryFinal = 0,comparaSelectionInicio = 0, comparaSelectionFinal = 0;
  int registros = 0;
  int selectionIndexInicio, selectionIndexFinal;
  Registro miRegistroInicio(mesInicio,diaInicio,horaInicio,minutosInicio,segundosInicio,"","","");
  Registro miRegistroFinal(mesFinal,diaFinal,horaFinal,minutosFinal,segundosFinal,"","","");

  
  //BINARY
  //se consigue el index de la fecha de inicio que introdujo el usuario como la de la fecha final mediante la Binary Search
  int inicioIndex = binarySearch(listaRegistros, miRegistroInicio.getFechaHora(), comparaBinaryInicio);
  int finalIndex =  binarySearch(listaRegistros, miRegistroFinal.getFechaHora(), comparaBinaryFinal);
  //Se imprime las comparaciones y swaps
    std::cout << "\nBINARY SEARCH" << std::endl;
    std::cout << "Comparacion Fecha Inicio: " <<comparaBinaryInicio << "\nComparacion Fecha Final: " << comparaBinaryFinal << std::endl<< std::endl;
  //Se muestran e la consola las fechas que se encontraron en el intervalo de las dos fechas que se introdujeron
  registros = (finalIndex - inicioIndex)+1;
  std::cout << "Resultado: " << registros  << " registros" << std::endl;
  for(int i = inicioIndex;i<=finalIndex;i++)
    {
      std::cout << listaRegistros[i].getAll() << std::endl;
    }
}

//--------------------------------Algoritmo de Buscar Datos-----------------------------
//Algoritmo de Binary Search para poder realizar la busqueda de las fechas que se encuentran en el intervalo indicado por el usuario
//std::vector<Registro> &A = referencia al vector con todos los registros que se leyeron del archivo.txt
//time_t key = tiempo de la fecha que sirve como nuestra llave de búsqueda
//int &compara = numero de comparaciones que se van a realizar
//Retorna el index de la información que se esta buscando
int Bitacora::binarySearch(std::vector<Registro> &A, time_t key, int &compara){ //busqueda Binaria
  int low = 0;
  int high = A.size() - 1;
  int mid = 0;
  compara = 0;
  while (low <= high) {
    mid = low + (high - low) / 2;
    compara++;
    if (key == A[mid].getFechaHora()){
      return mid;}
    else if (key < A[mid].getFechaHora()){
      high = mid - 1;}
    else
      low = mid + 1;
  }
  std::cout << "No se encontró la fecha se usará una fecha aproximada" << std::endl;
  return mid;
}

//Toma todo el vector de Registros que se ordeno previamente mediante los algoritmos de ordenamiento y los guarda en un archivo .txt
void Bitacora::guardarDatos()
{
  //Se abre el archivo bitacora_ordenada.txt en caso que no exista se crea
  std::ofstream outfile;
  outfile.open("bitacora_ordenada.txt");

  //Se comprueba si el archivo se pudo abrir, en dado caso se guardan los elementos de listaRegistros en el archivo .txt
  if(outfile.is_open())
  {
    for(int i = 0; i<= listaRegistros.size()-1;i++)
      {
        outfile << listaRegistros[i].getAll() << std::endl;
      }
    outfile.close();
  }
    //Si no se pudo abrir se despliega un mensaje de error
  else
    std::cout << "ERROR!\n" << std::endl;
  
  
}


