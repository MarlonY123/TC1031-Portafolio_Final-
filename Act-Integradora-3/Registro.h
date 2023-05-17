#ifndef _REGISTRO_H_
#define _REGISTRO_H_

#include <string>
#include <vector>
// transformar una fecha a numero decimal
#include <ctime>  
#include <iostream>

//Representar un evento (registro) dentro de la bitacora
class Registro {
  private:
    std::string mes, dia, hora, ip, puerto, falla;
    unsigned int valorIp;
  public:
    Registro();
    Registro(std::string _mes, std::string _dia, std::string _hora, std::string _ip, std::string _puerto, std::string _falla);
    std::string getAll();
    unsigned int getValorIp(){return valorIp;}
    std::string getIp(){return ip;}

    // Sobre carga de operadores
    bool operator ==(const Registro&);
    bool operator !=(const Registro&);
    bool operator >(const Registro&);
    bool operator <(const Registro&);
    bool operator >=(const Registro&);
    bool operator <=(const Registro&);

};



#endif   // _REGISTRO_H_
