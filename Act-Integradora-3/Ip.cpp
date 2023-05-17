#include "Ip.h"

//Complejidad O(1)
//Constructor que inicializa los valores de la clase ip en 0
Ip::Ip(){
  ip = "";
  valorIp = 0;
  accesos = 0;
}

//Complejidad O(1)
//Constructor que inicializa los valores de la clase ip con los parametros que recibe
Ip::Ip(std::string _ip, unsigned int _valorIp, unsigned int _accesos ){
  ip = _ip;
  valorIp = _valorIp;
  accesos = _accesos;
}

//Sobrecarga de operadores con el valor de accesos
bool Ip::operator==(const Ip &other) {
  return this->accesos == other.accesos;
}

bool Ip::operator!=(const Ip &other) {
  return this->accesos != other.accesos;
}

bool Ip::operator>=(const Ip &other) {
  return this->accesos >= other.accesos;
}

bool Ip::operator<=(const Ip &other) {
  return this->accesos <= other.accesos;
}

bool Ip::operator>(const Ip &other) {
  return this->accesos > other.accesos;
}

bool Ip::operator<(const Ip &other) {
  return this->accesos < other.accesos;
}

//Sobrecarga del operador << para imprimir los valores  de la clase ip
std::ostream& operator<<(std::ostream& os, const Ip& ip)
{
    os << ip.ip << ' ' << ip.valorIp << ' ' << ip.accesos;
    return os;
}