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
#include "ResumenIp.h"


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
    std::vector<ResumenIp> resumenIp;

    unsigned int convertirIp(std::string line);    


  public:
    Graph();
    ~Graph();
    void loadDirWeightedGraph(std::string titulo);
    void print();
    void BFS(int v);
    void dijkstraAlgorithm(int v);
    void imprimirVector();
    std::vector<ResumenIp> getResumenIp();



};


#endif // __GRAPH_H_