//Se incluye la clase bitacora.h
#include "Bitacora.h"


//Constructor donde se inicializan la función que lee los datos del archivo.txt 
//std::string filename es el nombre del archivo .txt de donde se va a ontener la información
Bitacora::Bitacora(std::string fileName){ //esta en el main cuando hacer referencia al archivo "bitacora.txt"
  leerDatos(fileName);
}


//Lee los datos del archivo.txt, los separa según mes, dia, hora, minutos y segundos para una vez que se hizo esto guardarlos en una lista 
//std::string fileName es el nombre del archivo .txt de donde se va a obtener la información
void Bitacora::leerDatos(std::string fileName)
{//abre el archivo
    std::ifstream in_stream;
    in_stream.open(fileName);
    //Si no se puede abrir el archivo entonces, envía un 1 para confirmar que no se pudo abrir...
    if (in_stream.fail()) { 
        std::cout << "No se pudo abrir el archivo " << fileName << std::endl;
        exit(1);
    }
    std::string input{};
  //Guardar los valores de las lineas del archivo, separados en mes,dia,hora,ip, puerto y falla
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
      //Se almacena un objeto de la clase registro en el doubly linked list listaRegistros
      listaRegistros.addFirst(Registro(mes, dia,horas,minutos,segundos,ip,puerto,falla));
    }
    in_stream.close();//cerramos archivo una vez se hizo el registro y divisiones.
}
//Función que muestra los datos que se encuentran en la lista doble mediante el uso de la función print de la lista
//Complejidad O(1)
void Bitacora::mostrarDatos(){
  listaRegistros.printList();
}
//Función que muestra los datos que se encuentran en la lista doble mediante el uso de la función print de la lista
//Se mandan a llamar las funciones merge y quick para ordenar los datos
//Complejidad O(n log n) --> merge sort
void Bitacora::ordenarDatos_merge(){
  listaRegistros.merge_sort();
}
//complejidad O(n log n) --> QuikSort
void Bitacora::ordenarDatos_quick(){
  listaRegistros.sort();
}
//Esta funcion se ocupa desde el main, con el fin de darle datos tanto de la fecha de incio como de la fecha final, del intervalo a buscar
void Bitacora::buscarDatos(std::string mesInicio,std::string diaInicio,std::string horaCompletaI,std::string mesFinal,std::string diaFinal,std::string horaCompletaF){
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
  int registros = 0;
  Registro miRegistroInicio(mesInicio,diaInicio,horaInicio,minutosInicio,segundosInicio,"","","");
  Registro miRegistroFinal(mesFinal,diaFinal,horaFinal,minutosFinal,segundosFinal,"","","");

  //BINARY SEARCH --> complejidad O(log 2 n) complejidad promedio
  //se consigue el nodo de la fecha de inicio que introdujo el usuario como la de la fecha final mediante el Binary Search
  //Nodo que tiene el index del inicio
  DLLNode<Registro> *inicioIndex = listaRegistros.binarySearch(listaRegistros.getHead(), miRegistroInicio);
  //Nodo que tiene el index del final
  DLLNode<Registro> *finalIndex = listaRegistros.binarySearch(listaRegistros.getHead(), miRegistroFinal);
  //Comprueba si es que la fecha que se introdujo si existe dentro de la lista
  if(inicioIndex == nullptr){
    if(finalIndex == nullptr){
      std::cout << "No se encontró la fecha de final " << std::endl;
    }
    std::cout << "No se encontró la fecha de inicio " << std::endl;
  }
    //En el caso que si exista se empieza a buscar los intervalos para desplegarlos y guardarlos
  else{
      //Se imprime las comparaciones y swaps
      DLLNode<Registro> *ptrInicio = inicioIndex;
      //Se abre el archivo bitacora_ordenada.txt en caso que no exista se crea
      std::ofstream outfile;
      outfile.open("resultado_busqueda.txt");
      //Se comprueba si el archivo se pudo abrir, en dado caso se guardan los elementos de listaRegistros en el archivo .txt
      if(outfile.is_open())
      {
        DLLNode<Registro> *ptrInicio = inicioIndex;
        while (ptrInicio != finalIndex->next) {
          //se ocupa la funcion getall para imprimir toda lo almacenado 
          std::cout << ptrInicio->data.getAll() << std::endl;
          outfile << ptrInicio->data.getAll()<<std::endl;
          ptrInicio = ptrInicio->next;
        }
        //se cierra el archivo
        outfile.close();
      }
        //Si no se pudo abrir se despliega un mensaje de error
      else
        std::cout << "ERROR!\n" << std::endl;
  }
  
}

//Toma toda la lista de Registros que se ordeno previamente mediante los algoritmos de ordenamiento y los guarda en un archivo .txt
void Bitacora::guardarDatos()
{
  //Se abre el archivo bitacora_ordenada.txt en caso que no exista se crea
  std::ofstream outfile;
  outfile.open("bitacora_ordenada.txt");
  //Se comprueba si el archivo se pudo abrir, en dado caso se guardan los elementos de listaRegistros en el archivo .txt
  
  if(outfile.is_open())
  {
    DLLNode<Registro> *ptrHead = listaRegistros.getHead();
    while (ptrHead != nullptr) {
      outfile << ptrHead->data.getAll()<<std::endl;
      ptrHead = ptrHead->next;
    }
    outfile.close();
  }
    //Si no se pudo abrir se despliega un mensaje de error
  else
    std::cout << "ERROR!\n" << std::endl;
}






