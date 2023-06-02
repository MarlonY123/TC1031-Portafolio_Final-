
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
void Graph::loadDirWeightedGraph(std::istream & input) {
  std::string line;
  int i = 0;
  while (std::getline(input, line)) {

    if (i == 0) { 
      std::vector<int> result;
      split(line, result);
      numNodes = result[0];
      numEdges = result[1];
      // Reservar memoria para renglones de la lista de adyacencia
      // Nodos son uno basados (renglon 0 no sera usado)
      adjList.resize(numNodes + 1);
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
      }

    }
    i++;
  }
  
  creacionLista();
  listToMaxHeap();

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
void Graph::guardarDatosLista(){
  //Se abre el archivo grados_ips.txt en caso que no exista se crea
  std::ofstream outfile;
  outfile.open("grados_ips.txt");
  //Se comprueba si el archivo se pudo abrir, en dado caso se guardan los elementos de listaRegistros en el archivo .txt
  if(outfile.is_open())
  {
    NodeLinkedList<std::pair<std::string, int>> *ptrHead = listaGradoSalida.getHead();
    while (ptrHead != nullptr) {
      outfile << "Ip: " <<ptrHead->data.first << "\tGrado salida: " << ptrHead->data.second <<std::endl;
      ptrHead = ptrHead->next;
    }
    outfile.close();
  }
    //Si no se pudo abrir se despliega un mensaje de error
  else
    throw std::invalid_argument("No se pudo abrir el archivo");
}
//Complejidad O(n)
void Graph::creacionLista(){
  for(int i = 1; i<= numNodes;i++){
    std::string ip = mpAyuda[i];
    listaGradoSalida.addLast(std::make_pair(ip, adjList[i].getNumElements()));
  }
}
//Complejidad O(n) 
//https://www.geeksforgeeks.org/priority-queue-of-pairs-in-c-ordered-by-first/
void Graph::listToMaxHeap() {
  NodeLinkedList<std::pair<std::string, int>> *ptrHead = listaGradoSalida.getHead();
  while (ptrHead != nullptr) {
      maxHeap.push(std::make_pair(ptrHead->data.second, ptrHead->data.first));
      ptrHead = ptrHead->next;
  }
    bootMaster = maxHeap.top().second;
  
}
//Complejidad O(n)
//https://www.geeksforgeeks.org/priority-queue-of-pairs-in-c-ordered-by-first/
void Graph::guardarTop5MaxHeap(){
  //Se abre el archivo bitacora_ordenada.txt en caso que no exista se crea
  std::ofstream outfile;
  outfile.open("mayores_grados_ips.txt");
  //Se comprueba si el archivo se pudo abrir, en dado caso se guardan los elementos de listaRegistros en el archivo .txt
  if(outfile.is_open())
  {
    for(int i = 0;i < 5; i++){
        outfile << "Ip: " <<maxHeap.top().second << "\tGrado de salida: "<<maxHeap.top().first << std::endl;
        maxHeap.pop();
    }
  }
    //Si no se pudo abrir se despliega un mensaje de error
  else
    throw std::invalid_argument("No se pudo abrir el archivo");
}


//Complejidad O(1)
std::string Graph::getBootMaster(){
  return bootMaster;
}
//Complejidad O(n^2)
void Graph::caminoMasCorto(){
  unsigned int ip = convertirIp(bootMaster);
  int index = mp[ip].first;
  dijkstraAlgorithm(index);
}

//Complejidad O(n^2)
void Graph::dijkstraAlgorithm(int v) {
  // Crear una priority queue del STL de C++
  // https://www.geeksforgeeks.org/implement-min-heap-using-stl/
  std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;
  // vector de distancias con el resultado del algoritmo
  std::vector<int> dist(numNodes+1, INF);
  // Insertar el nodo de origen v en la priority queue -- pares (dist, vertice)
  pq.push(std::make_pair(0, v)); // la distancia de v a v es cero
  dist[v] = 0;
  // Mientras el priority queue no este vacio
  while (!pq.empty()) {
    // Extraer un vertice de el priority queue
    int nodeU = pq.top().second; // pares (dist, vertice)
    pq.pop();
    // Obtener los vecions del vertice nodeU
    NodeLinkedList<std::pair<std::string, int>> *ptr = adjList[nodeU].getHead();
    while (ptr != nullptr) {
      unsigned int ip = convertirIp(ptr->data.first);
      int index = mp[ip].first;
      std::pair<unsigned int, int> par = std::make_pair(index,ptr->data.second);
      int nodeV = par.first; // nodeV es vecino de nodeU
      int peso = par.second; // peso de la arista (nodoU,nodeV)
      if (dist[nodeV] > dist[nodeU]+peso) {
        // Actualizar la distancia (mas corta) de nodeV
        dist[nodeV] = dist[nodeU] + peso;
        pq.push(std::make_pair(dist[nodeV], nodeV));
      }
      ptr = ptr->next;
    }
  }

  //Se abre el archivo bitacora_ordenada.txt en caso que no exista se crea
  std::ofstream outfile;
  outfile.open("distancia_bootmaster.txt");
  //Se comprueba si el archivo se pudo abrir, en dado caso se guardan los elementos  en el archivo .txt
  if(outfile.is_open())
  {
    outfile << "Vertice\tDistancia desde v" << std::endl;
    for (int i = 1; i <= numNodes; i++) {
    if (dist[i] != INF){
      std::string ip = mpAyuda[i];
      int distancia = dist[i];
      outfile << ip<< "\t\t" << distancia << std::endl;
      minHeap.push(std::make_pair(dist[i],ip));
    }
    else
     outfile << i << "\tINF" << std::endl;
  }
    outfile.close();
  }
    //Si no se pudo abrir se despliega un mensaje de error
  else
    throw std::invalid_argument("No se pudo abrir el archivo");
  minHeap.pop();
  
  
}

void Graph::ipMenorDistancia(){
  std::cout << "Ip con la menor distancia del Boot Master: " << minHeap.top().second << "\tDistancia: " << minHeap.top().first << std::endl;
}