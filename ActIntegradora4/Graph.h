// Esta clase permite representar grafos dirigidos ponderados
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <map>
#include <fstream>
#include <list>
#include <sstream>

#include "LinkedList.h"
//#include "QueueLinkedList.h"

// https://stackoverflow.com/questions/18429021/why-is-infinity-0x3f3f3f3f
#define INF 0x3f3f3f3f

class Graph {
  private:
    int numNodes;
    int numEdges;
    // Lista de adyacencia (vector de listas ligadas de pares nodo,peso)
    std::vector<LinkedList<std::pair<std::string, int>>> adjList;

    void split(std::string line, std::vector<int> & res);
    void split_string(std::string line, std::vector<std::string> & res);
    std::map<unsigned int, std::pair<int, std::string>> mp;
    std::map<int, std::string> mpAyuda;
    LinkedList<std::pair<std::string, int>> listaGradoSalida;
    std::priority_queue <std::pair<int, std::string>> maxHeap;
    std::string bootMaster;
    std::priority_queue <std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<std::pair<int, std::string>>> minHeap;

    unsigned int convertirIp(std::string line);    
    void modifyDataofLinkedList(int position,std::string ip);
    void listToMaxHeap();
    void creacionLista();


  public:
    Graph();
    ~Graph();
    void loadDirWeightedGraph(std::istream & input);
    void print();
    void BFS(int v);
    void dijkstraAlgorithm(int v);
    void guardarDatosLista();
    void guardarTop5MaxHeap();
    std::string getBootMaster();
    void caminoMasCorto();
    void ipMenorDistancia();


};


#endif // __GRAPH_H_