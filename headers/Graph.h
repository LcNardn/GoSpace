#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

template <typename T>
class Graph
{
    private:
        std::vector<T> nodes;
        std::vector<std::vector<bool>> adjs; // una matrice per le adiacenze

    public:
        Graph();
        Graph(std::vector<T>,std::vector<std::vector<bool>>);
        Graph(const Graph&);

        void addNode(T);
        void addEdge(int,int);
        void addConnectedNode(T,std::vector<int>);

        void removeEdge(int,int);

        int nNodes() const;
        T& operator[](int);
        const T& operator[](int) const;
        const std::vector<int> adj(int) const;

        ~Graph();
};

template <typename T>
Graph<T>::Graph(){      }

template <typename T>
Graph<T>::Graph(std::vector<T> n,std::vector<std::vector<bool>> a) : nodes(n), adjs(a) { }

template <typename T>
Graph<T>::Graph(const Graph& o){
    if (this != &o) {nodes=o.nodes; adjs=o.adjs;}
}

template <typename T>
void Graph<T>::addNode(T newNode){

    nodes.push_back(newNode); // aggiungo il nuovo nodo

    for (std::vector<bool>& neighbors : adjs){ // aggiungo la entry di quel nodo nelle altre liste di adiacenza
        neighbors.push_back(false);
    }

    std::vector<bool> a(nodes.size(),false); // aggiungo la lista di adiacenza di quel nodo
    adjs.push_back(a);
}

template <typename T>
void Graph<T>::addEdge(int a,int b){
    if( a<nodes.size(), b<nodes.size()){
        adjs[a][b]=true;
        adjs[b][a]=true;
    }
}

template <typename T>
void Graph<T>::addConnectedNode(T newNode,std::vector<int> neighbors){
    addNode(newNode);
    for(int i : neighbors){
        addEdge(nodes.size()-1,i);
    }
}

template <typename T>
void Graph<T>::removeEdge(int a,int b){
    if( a<nodes.size(), b<nodes.size()){
        adjs[a][b]=false;
        adjs[b][a]=false;
    }
}

template<typename T>
int Graph<T>::nNodes() const{
    return nodes.size();
}

template<typename T>
T& Graph<T>::operator[](int index){
    if(index<nodes.size()){
        return nodes[index];
    } // else throw std::__throw_runtime_error("Node does not exist");
}

template<typename T>
const T& Graph<T>::operator[](int index) const{
    if(index<nodes.size()){
        return nodes[index];
    } // else throw std::__throw_runtime_error("Node does not exist");
}

template<typename T>
const std::vector<int> Graph<T>::adj(int index) const{

    std::vector<int> ret;

    if(index<nodes.size()){

        for(int i=0;i<adjs[index].size();i++){
            if (adjs[index][i]) ret.push_back(i);
        }

        return ret;
    } // else throw std::__throw_runtime_error("Node does not exist");
}

template <typename T>
Graph<T>::~Graph(){     }

#endif