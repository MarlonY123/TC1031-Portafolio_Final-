
#include "Graph.h"

//Complejidad O(1)
Graph::Graph() {
  adjList.clear();
}
//Complejidad O(1)
Graph::~Graph() {
  adjList.clear();
}

//Complejidad O(n)
void Graph::split(std::string line, std::vector<int> & res) {
    size_t strPos = line.find(" ");
    size_t lastPos = 0;
    while (strPos != std::string::npos) {
      res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
      lastPos = strPos + 1;
      strPos = line.find(" ", lastPos);
    }
    res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

//Complejida O(n )
void Graph::split_string(std::string line, std::vector<std::string>& res) {
    size_t strPos = line.find(" ");
    size_t lastPos = 0;
    while (strPos != std::string::npos) {
      res.push_back(line.substr(lastPos, strPos - lastPos));
      lastPos = strPos + 1;
      strPos = line.find(" ", lastPos);
    }
    res.push_back(line.substr(lastPos, line.size() - lastPos));
}

//Complejidad O(1)
unsigned int Graph::convertirIp(std::string ip){
  int indexPunto1 = ip.find('.');
  int indexPunto2 = ip.find('.', indexPunto1+1);
  int indexPunto3 = ip.find('.', indexPunto2+1);
  //Separa los valores de la direccion ip y los convierte en int
  int primerIp = std::stoi(ip.substr(0, indexPunto1));
  int segundoIp = std::stoi(ip.substr(indexPunto1+1, (indexPunto2-indexPunto1)-1));
  int tercerIp = std::stoi(ip.substr(indexPunto2+1, (indexPunto3-indexPunto2)-1));
  int cuartoIp = std::stoi(ip.substr(indexPunto3+1, (ip.size())-indexPunto3));
  //Calcula el valorIp mediante cada uno de los valores de la ip multiplicando por la potencia de 256
  unsigned int valorIp = (primerIp*16777216) + (segundoIp*65536) + (tercerIp*256) + cuartoIp;

  return valorIp;
}

//Complejidad O(n^2)
void Graph::loadDirWeightedGraph(std::string fileName) {
  std::ifstream in_stream;
  in_stream.open(fileName);
  if (in_stream.fail()) {
    //std::cout << "No se pudo abrir el archivo " << fileName << std::endl;
     throw std::invalid_argument("No se pudo abrir el archivo");
    exit(1);
  }
  
  std::string line;
  int i = 0;
  while (std::getline(in_stream, line)) {
    if (i == 0) { 
      std::vector<int> result;
      split(line, result);
      numNodes = result[0];
      numEdges = result[1];
      // Reservar memoria para renglones de la lista de adyacencia
      // Nodos son uno basados (renglon 0 no sera usado)
      adjList.resize(numNodes + 1);
      resumenIp.push_back(ResumenIp("",0,0,0));
      // Declarar un lista vacia para cada renglon y se almacena en el vector
      for (int k = 1; k <= numNodes; k++) {
        LinkedList<std::pair<std::string, int>> tmpList;
        adjList[k] = tmpList;
      }
    }
    if (i > 0) {
      if(i <= numNodes){
        std::string ip = line;

        unsigned int valorIp = convertirIp(ip);

        mp.insert(make_pair(valorIp, make_pair(i,ip)));
        mpAyuda.insert(make_pair(i, ip));
        resumenIp.push_back(ResumenIp(ip, valorIp ,0, 0));
        //resumenIp[i].imprimirResumen();
        //std::cout << std::endl;
      }
      else if( i > numNodes){
        // Lectura de aristas del grafo
        std::vector<std::string> result;
        split_string(line, result);
        
        int indexPuntos = result[3].find(":");
        std::string ip_nodoU = result[3].substr(0, indexPuntos);
        
        indexPuntos = result[4].find(':');
        std::string ip_nodoV = result[4].substr(0, indexPuntos);
        
        unsigned int valorIpNodoU = convertirIp(ip_nodoU);
        unsigned int valorIpNodoV = convertirIp(ip_nodoV);
    
        std::pair<int, std::string> nodoU = mp[valorIpNodoU];
        std::pair<int, std::string> nodoV = mp[valorIpNodoV];

        int weight = std::stoi(result[5]);
        //grafo dirigido agregar aristas (u,v) unicamente
        adjList[nodoU.first].addLast(std::make_pair(nodoV.second, weight));
        resumenIp[nodoU.first].sumarGradoSalida();
        resumenIp[nodoV.first].sumarGradoEntrada();
        resumenIp[nodoU.first].agregarIp(valorIpNodoV, nodoV.second);
        
      }

    }
    i++;
  }

}

 //Complejidad O(n^2)
void Graph::print() {
  std::cout << "numNode: " << numNodes << std::endl;
  std::cout << "numEdges: " << numEdges << std::endl;
  std::cout << "Adjacency List" << std::endl;
  for (int nodeU = 1; nodeU <= numNodes; nodeU++) {
    std::cout << "vertex " << nodeU << ": ";
    NodeLinkedList<std::pair<std::string, int>> *ptr = adjList[nodeU].getHead();
    while (ptr != nullptr) {
      std::pair<std::string, int> par = ptr->data;
      std::cout << "{" << par.first << "," << par.second << "} ";
      ptr = ptr->next;
    }
    std::cout << std::endl;
  }
}

//Complejidad O(n)
void Graph::imprimirVector(){
  
  for(int i = 1;i<=numNodes; i++){
    resumenIp[i].imprimirResumen();
    std::cout << std::endl;
  }
  //std::cout << resumenIp.size();
}
//Complejidad O(1)
std::vector<ResumenIp> Graph::getResumenIp(){
  return resumenIp;
}
