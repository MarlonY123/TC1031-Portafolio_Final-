
#include "Registro.h"

//Complejidad O(1)
Registro::Registro() {
  mes = "";
  dia = "";
  hora = ""; 
  ip = ""; 
  puerto = ""; 
  falla = "";
}
//Complejidad O(1)
//constructor de la clase registro.
Registro::Registro(std::string _mes, std::string _dia, std::string _hora, std::string _ip, std::string _puerto, std::string _falla) {
  //Asigna valores a cada variable para la fecha
  mes = _mes;
  dia = _dia;
  hora = _hora; 
  ip = _ip; 
  puerto = _puerto; 
  falla = _falla;
  //Encuentra la posición de los . que se encuentran en la dirección ip
  int indexPunto1 = ip.find('.');
  int indexPunto2 = ip.find('.', indexPunto1+1);
  int indexPunto3 = ip.find('.', indexPunto2+1);
  
  //Separa los valores de la direccion ip y los convierte en int
  int primerIp = std::stoi(ip.substr(0, indexPunto1));
  int segundoIp = std::stoi(ip.substr(indexPunto1+1, (indexPunto2-indexPunto1)-1));
  int tercerIp = std::stoi(ip.substr(indexPunto2+1, (indexPunto3-indexPunto2)-1));
  int cuartoIp = std::stoi(ip.substr(indexPunto3+1, (ip.size())-indexPunto3));

  //Calcula el valorIp mediante cada uno de los valores de la ip multiplicando por la potencia de 256
  valorIp = (primerIp*16777216) + (segundoIp*65536) + (tercerIp*256) + cuartoIp;



}
//Complejidad O(1)
//Retorna un string con toda la información del registro
std::string Registro::getAll() {
  return mes + " " + dia + " " + hora + " " + ip + ":" + puerto + " " + falla;
}

//Sobrecarga de operadores para poder comparar el valorIp de cada registros
bool Registro::operator==(const Registro &other) {
  return this->valorIp == other.valorIp;
}

bool Registro::operator!=(const Registro &other) {
  return this->valorIp != other.valorIp;
}

bool Registro::operator>=(const Registro &other) {
  return this->valorIp >= other.valorIp;
}

bool Registro::operator<=(const Registro &other) {
  return this->valorIp <= other.valorIp;
}

bool Registro::operator>(const Registro &other) {
  return this->valorIp > other.valorIp;
}

bool Registro::operator<(const Registro &other) {
  return this->valorIp < other.valorIp;
}
