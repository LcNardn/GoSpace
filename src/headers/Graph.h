#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <exception>

template <typename T>
class Graph
{
    private:
        std::list<T> nodes;
        std::multimap<int,int> adjs; // adiacenze // non uso T poichè potrebbe non essere ordinabile

        void removeOneEdge(int,int);
        
        public:
        //costruttori
        Graph()=default;
        Graph(const std::vector<T>&, const std::vector<std::vector<int>>&);
        Graph(const std::list<T>&,const std::multimap<int,int>&);
        Graph(const Graph&);

        // move semantics visto che T potrebbero essere gestiti in maniera dinamica
        Graph(Graph&&)=default;
        Graph& operator=(Graph&&)=default;
        
        //modifiche
        void addNode(T);
        void addEdge(int,int);
        Graph<T>& operator+=(T);
        Graph<T>& operator+=(std::pair<int,int>);
        void addConnectedNode(T,std::vector<int>);

        void removeEdge(int,int);
        void removeNode(int);
        Graph<T>& operator-=(T);
        Graph<T>& operator-=(std::pair<int,int>);

        //accessi
        int nNodes() const;
        int getPos(const T&) const;
        T& operator[](int); // throws logic_error
        const T& operator[](int) const; // throws logic_error
        const std::vector<int> adj(int) const; // throws logic_error

        ~Graph();
};

template<typename T>
void Graph<T>::removeOneEdge(int from,int to){
    auto it = adjs.find(from);
    while (it!=adjs.end() && it->second!=to && it->first==from){ // trovo il collegamento
        it++;
    }

    if (it!=adjs.end() && it->first==from){ // se ho trovato l'arco lo elimino
        adjs.erase(it);
    }
}

template <typename T>
Graph<T>::Graph(const std::vector<T>& n, const std::vector<std::vector<int>>& a) : nodes(n.begin(),n.end()) {

    int minLenght = (a.size() < n.size() ? a.size() : n.size()); // prendo il minimo per evitare incorrettezze
    
    for (int i=0; i<minLenght; i++){ 
        for (int pos : a[i]){
            adjs.emplace(pos,i);
        }
    }
}

template <typename T>
Graph<T>::Graph(const std::list<T>& n,const std::multimap<int,int>& a) : nodes(n), adjs(a) {  }

template <typename T>
Graph<T>::Graph(const Graph& o){
    if (this != &o) {nodes=o.nodes; adjs=o.adjs;}
}

template <typename T>
void Graph<T>::addNode(T newNode){

    nodes.push_back(newNode); // aggiungo il nuovo nodo

}

template <typename T>
void Graph<T>::addEdge(int a,int b){
    if( a<nodes.size() && b<nodes.size()){
        adjs.emplace(a,b);
        adjs.emplace(b,a);
    }
}

template <typename T>
Graph<T>& Graph<T>::operator+=(T newN){
    addNode(newN);
    return *this;
}

template <typename T>
Graph<T>& Graph<T>::operator+=(std::pair<int,int> edge){
    addEdge(edge.first,edge.second);
    return *this;
}

template <typename T>
void Graph<T>::addConnectedNode(T newNode,std::vector<int> neighbors){
    addNode(newNode);
    for(int i : neighbors){
        addEdge(nodes.size()-1,i); // nodes.size()-1 è il nuovo nodo appena aggiunto
    }
}

template <typename T>
void Graph<T>::removeEdge(int a,int b){
    if( a<nodes.size() && b<nodes.size()){
        removeOneEdge(b,a);
        removeOneEdge(a,b);
    }
}

template<typename T>
void Graph<T>::removeNode(int index){

    if (index >= nodes.size() || index<0) return;

    auto it = nodes.begin();
    std::advance(it,index);
    nodes.erase(it); // rimuovo il nodo

    adjs.erase(index); // rimuovo tutti gli archi che partono dal nodo 

    auto itM = adjs.begin(); // rimuovo l'altra metà
    while (itM != adjs.end()){
        if (itM->second == index){
            itM = adjs.erase(itM);
        } else itM++;
    }

    std::multimap<int,int> updated; // aggiorno le adiacenze in modo che siano corrette

    std::for_each(adjs.begin(), adjs.end(), [&](const auto& p) {
        int from = p.first > index ? p.first - 1 : p.first;
        int to = p.second > index ? p.second - 1 : p.second;
        updated.emplace(from, to);
    });
    adjs = std::move(updated);
    
}

template<typename T>
Graph<T>& Graph<T>::operator-=(T node){
    removeNode(getPos(node));
    return *this;
}

template<typename T>
Graph<T>& Graph<T>::operator-=(std::pair<int,int> edge){
    removeEdge(edge.first,edge.second);
    return *this;
}

template<typename T>
int Graph<T>::nNodes() const{
    return nodes.size();
}

template<typename T>
int Graph<T>::getPos(const T& node) const{
    for (int i=0;i<nodes.size();i++){
        if ((*this)[i]==node){
            return i;
        }
    }
    return -1; //non lo ho trovato;
}

template<typename T>
T& Graph<T>::operator[](int index){
    if(index<nodes.size()){
        auto it = nodes.begin();
        std::advance(it,index);
        return *it;
    } else throw std::logic_error("Node does not exist");
}

template<typename T>
const T& Graph<T>::operator[](int index) const{
    if(index<nodes.size()){
        auto it = nodes.begin();
        std::advance(it,index);
        return *it;
    } else throw std::logic_error("Node does not exist");
}

template<typename T>
const std::vector<int> Graph<T>::adj(int index) const{

    std::vector<int> ret;

    if(index<nodes.size()){

        auto range = adjs.equal_range(index);
        for (auto it = range.first; it!= range.second; it++){
            ret.push_back(it->second);
        }

        return ret;
    } else throw std::logic_error("Node does not exist");
}

template <typename T>
Graph<T>::~Graph(){     }

#endif
