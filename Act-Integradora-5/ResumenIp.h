#ifndef _RESUMENIP_H_
#define _RESUMENIP_H_

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>


class ResumenIp{
public:
  ResumenIp();
  ResumenIp(std::string _ip, unsigned int _valorIp ,int _gradoSalida, int _gradoEntrada);
  void sumarGradoSalida();
  void sumarGradoEntrada();
  void imprimirResumen();
  unsigned int getValorIp();
  std::string getIp();
  int getGradoSalida();
  int getGradoEntrada();
  void agregarIp(unsigned int valorIp, std::string ip);
  
  friend std::ostream& operator<<(std::ostream& os, const ResumenIp& dt);
  

private:
  std::string ip;
  unsigned int valorIp;
  int gradoSalida;
  int gradoEntrada;
  std::vector<std::pair<unsigned int, std::string>> ipAccesaron;
  void sortVector();
  
};



#endif // _NODELINKEDLIST_H_
