#include "ResumenIp.h"

ResumenIp::ResumenIp(){
  
}
//Complejidad O(1)
ResumenIp::ResumenIp(std::string _ip, unsigned int _valorIp,int _gradoSalida, int _gradoEntrada){
  ip = _ip;
  valorIp = _valorIp;
  gradoSalida = _gradoSalida;
  gradoEntrada = _gradoEntrada; 
}
//Complejidad O(1)
void ResumenIp::sumarGradoSalida(){
  gradoSalida++;
}
//Complejidad O(1)
void ResumenIp::sumarGradoEntrada(){
  gradoEntrada++;
}
//Complejidad O(n)
void ResumenIp::imprimirResumen(){
  sortVector();
  std::cout << "\nInformación de la Ip solicitada\nIp: " << ip << "\nValor ip: " <<valorIp <<"\nGrado salida: " << gradoSalida << "\nGrado entrada: " << gradoEntrada << std::endl;
  std::cout << "\nLista completa de direcciones accesadas desde la IP recibida: " << std::endl;
  for(int i = 0; i<ipAccesaron.size(); i++){
    std::cout << ipAccesaron[i].second << std::endl;
  }
}
//Funciones que obtienen el 
//Complejidad O(1)
//Valor de la Ip
unsigned int ResumenIp::getValorIp(){
  return valorIp;
}
//Complejidad O(1)
//La Ip
std::string ResumenIp::getIp(){
  return ip;
}
//Complejidad O(1)
//Grado de salida de la ip
int ResumenIp::getGradoSalida(){
  return gradoSalida;
}
//Complejidad O(1)
//Grado de entrada de la ip
int ResumenIp::getGradoEntrada(){
  return gradoSalida;
}
//Complejidad O(1)
//Agrega las ips accesadas a un vector
void ResumenIp::agregarIp(unsigned int valorIp, std::string ip){
  ipAccesaron.push_back(std::make_pair(valorIp, ip));
}

//Código consultado en GeeksforGeeks. (2023). Sorting a vector in C. GeeksforGeeks. https://www.geeksforgeeks.org/sorting-a-vector-in-c/
//Complejidad O(n)
//Función que ordena el vector de las ip accesadas en orden descendente
void ResumenIp::sortVector(){
  std::sort(ipAccesaron.begin(), ipAccesaron.end(), std::greater<std::pair<unsigned int, std::string>>());
}
//Complejidad O(1)
std::ostream& operator<<(std::ostream& os, const ResumenIp& ri)
{
    os<< "Ip: " << ri.ip << "\tValor ip: " << ri.valorIp << "\tGrado salida: " << ri.gradoSalida << "\tGrado entrada: " << ri.gradoEntrada << std::endl;
    return os;
}
