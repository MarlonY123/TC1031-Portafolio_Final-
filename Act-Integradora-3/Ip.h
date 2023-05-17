#ifndef _IP_H_
#define _IP_H_
#include <string>
#include <iostream>

class Ip{
private:
  std::string ip;
  unsigned int valorIp, accesos;
public:
  Ip();
  Ip(std::string _ip, unsigned int _valorIp, unsigned int _accesos );
  //Retorna un string con toda la información del registro
  std::string getAll() {
  return ip + " " + std::to_string(valorIp) + " " + std::to_string(accesos);
  //return fechaHora;
}
  // Sobre carga de operadores
  bool operator ==(const Ip&);
  bool operator !=(const Ip&);
  bool operator >(const Ip&);
  bool operator <(const Ip&);
  bool operator >=(const Ip&);
  bool operator <=(const Ip&);
  friend std::ostream& operator<<(std::ostream& os, const Ip& ip);
};

#endif // _IP_H_