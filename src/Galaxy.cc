#include "./headers/Galaxy.h"
#include "./headers/PlanetInclude.h"
#include "./headers/Graph.h"
#include "./headers/Explorer.h"

#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <set>
#include <iostream>
#include <exception>
#include <memory>
#include <algorithm>
#include <queue>
#include <map>

Planet* getNewPlanet(const std::string& line) { // throws domain_error, runtime_error

    Planet* retVal = NULL;
    
    // cerco il tipo di pianeta
    int start=0;
    auto findNextS = [&line, &start]() {

        // Salto eventuali spazi iniziali
        while (start < line.size() && line[start] == ' ') {
            start++;
        }

        if (start >= line.size()) {
            throw std::runtime_error("Input not formed correctly.\n");
        }

        // Trovo la fine della parola
        int end = line.find_first_of(' ', start);
        if (end == line.npos) {
            end = line.size(); // ultima parola fino alla fine
        }

        std::string retVal = line.substr(start, end - start);

        // Avanzo il cursore oltre la parola
        start = end + 1;

        return retVal; // non posso tornare puntatori a oggetti locali, quindi devo ritrnare per valore
    };

    
    std::string type(findNextS());

    // uso un set per evitare una linea continua di condizioni dentro l'if
    std::set<std::string> types({"W","F","E","S","I","A","D"}); // tutti i tipi di pianeti che ci sono, meno efficiente ma più leggibile
    if (types.find(type) == types.end()){ // questo tipo di pianeta non è conosciuto, lancio un eccezzione

        std::string errorMessage("There is no planet type called ");
        errorMessage.append(type);
        throw std::domain_error(errorMessage);

    } else if (type == "A"){ // se è un asteroide che devo aggiungere non mi serve altro
        retVal = new Asteroid();
    } else if (type == "D") {
        retVal = new DestroyedPlanet();
    }else {

        // cerco il nome
        std::string name(findNextS());

        // cerco il valore di energia
        float energy = atof(findNextS().c_str());

        // da ora in poi dipende dal tipo di pianeta che si vuole creare
        if (type.compare("W") == 0){ // water Planet

            // cerco i pesci
            int fish = atoi(findNextS().c_str());

            retVal = new WaterPlanet(name,fish,energy);


        } else if (type.compare("F") == 0){

            // cerco il valore di energia supplementare
            float energySup = atof(findNextS().c_str());

            retVal = new FirePlanet(name,energySup,energy);

        } else if (type.compare("E") == 0){

            // cerco il minerale
            objType mineral = ((findNextS() == "mineral_2") ? mineral_2 : mineral_1); // la stessa operazione che farebbe il costruttore

            retVal = new EarthPlanet(name,mineral,energy);

        } else if (type.compare("S") == 0){

            // cerco i pesci
            int fish = atoi(findNextS().c_str());

            // cerco il valore di energia supplementare
            float energySup = atof(findNextS().c_str());

            // cerco l'ossigeno
            int O = atoi(findNextS().c_str());

            retVal = new SteamPlanet(name,fish,energySup,O,energy);
            
        } else if (type.compare("I") == 0){

            // cerco il valore di energia supplementare
            float energySup = atof(findNextS().c_str());

            // cerco il minerale
            objType mineral = ((findNextS() == "mineral_2") ? mineral_2 : mineral_1); // la stessa operazione che farebbe il costruttore

            retVal = new IndustryPlanet(name,energySup,mineral,energy);
            
        } // non mi serve l'else perchè ho fatto il controllo fatto prima e sono sicuro che almeno in un if è entrato
    }

    return retVal;
}

Galaxy::Galaxy(std::fstream& _in, std::string _save, std::unique_ptr<Explorer>& _exp, int _currentPlanet) : saveFile(_save), exp(std::move(_exp)){ // throws domain_error
    
    currentPlanet=_currentPlanet;
    
    //inizio a leggere i pianeti
    std::string line;
    Planet* pp; // non serve l'inizializzazione
    std::getline(_in,line);
    while ( line[0] != '%'){ // prima della linea %%% ci sono le definizioni dei pianeti, mentre dopo c'è la mappa
        
        if (line.empty()){
            std::getline(_in,line);
            continue;
        }
        
        try {
            pp = getNewPlanet(line);
        } catch (std::domain_error e) {
            std::cerr<<"Planet no "<<map.nNodes()<<": "<<e.what()<<std::endl;
            throw e;
        } catch (std::runtime_error e){
            std::cerr<<"Planet no "<<map.nNodes()<<": "<<e.what()<<std::endl;
            pp = new DestroyedPlanet();
        } catch (...) {
            std::cerr<<"An unknown error has occurred.\n";
            pp = new DestroyedPlanet();
        }
        map+=pp;
        std::getline(_in,line);
    }

    // inizio a leggere i collegamenti
    unsigned int from,to;
    while (!_in.eof()){
        _in>>from>>to;
        map+={from,to};
    }

}

Galaxy::Galaxy(const Galaxy& g) : map(g.map), saveFile(g.saveFile){ // il costruttore di copia di map lo uso per salvarmi gli archi
    
    currentPlanet=g.currentPlanet;
    exp.reset(new Explorer(*g.exp)); // copio l'esploratore
    
    for(int i=0;i<map.nNodes();i++){
        switch (g.map[i]->getType()) { // devo creare manualmente i nuovi pianeti visto che il costruttore di copia di Graph ha solo copiato i puntatori
            case Water: map[i] = new WaterPlanet( *dynamic_cast<WaterPlanet*>(g.map[i]) ); break;
            case Fire: map[i] = new FirePlanet( *dynamic_cast<FirePlanet*>(g.map[i]) ); break;
            case Earth: map[i] = new EarthPlanet( *dynamic_cast<EarthPlanet*>(g.map[i]) ); break;
            case Steam: map[i] = new SteamPlanet( *dynamic_cast<SteamPlanet*>(g.map[i]) ); break;
            case Industry: map[i] = new IndustryPlanet( *dynamic_cast<IndustryPlanet*>(g.map[i]) ); break;
            case AsteroidT: map[i] = new Asteroid( *dynamic_cast<Asteroid*>(g.map[i]) ); break;
            case Destroyed: map[i] = new DestroyedPlanet(); break;
        }
    }
}

Galaxy& Galaxy::operator=(const Galaxy& g){

    currentPlanet=g.currentPlanet;
    exp.reset(new Explorer(*g.exp));
    // saveFile=g.saveFile;

    for(int i=0;i<map.nNodes();i++){ // libero dalla memoria i vecchi pianeti
        delete map[i];
    }

    map=g.map;

    for(int i=0;i<map.nNodes();i++){
        switch (g.map[i]->getType()) { // devo creare manualmente i nuovi pianeti visto che l'operatore di assrgnamento di Graph ha solo copiato i puntatori
            case Water: map[i] = new WaterPlanet( *dynamic_cast<WaterPlanet*>(g.map[i]) ); break;
            case Fire: map[i] = new FirePlanet( *dynamic_cast<FirePlanet*>(g.map[i]) ); break;
            case Earth: map[i] = new EarthPlanet( *dynamic_cast<EarthPlanet*>(g.map[i]) ); break;
            case Steam: map[i] = new SteamPlanet( *dynamic_cast<SteamPlanet*>(g.map[i]) ); break;
            case Industry: map[i] = new IndustryPlanet( *dynamic_cast<IndustryPlanet*>(g.map[i]) ); break;
            case AsteroidT: map[i] = new Asteroid( *dynamic_cast<Asteroid*>(g.map[i]) ); break;
            case Destroyed: map[i] = new DestroyedPlanet(); break;
        }
    }

    return *this;

}

Galaxy::Galaxy(Galaxy&& g) : saveFile(std::move(g.saveFile)), map(std::move(g.map)){
    
    currentPlanet = g.currentPlanet;
    g.currentPlanet = 0;
    exp=std::move(g.exp);
    // g.saveFile.clear();

    for(int i=0;i<map.nNodes();i++){ // mi assicuro che i Planet* siano a null in g
        g.map[i]=NULL;
    }

}

Galaxy& Galaxy::operator=(Galaxy&& g){

    exp=std::move(g.exp);
    // saveFile=g.saveFile;
    currentPlanet=g.currentPlanet;
    // g.saveFile.clear();

    map=std::move(g.map);

    for (int i=0;i<g.map.nNodes();i++){
        map[i]=NULL;
    }

    return *this;

}

void Galaxy::spawnAsteroid(){
    srand(time(NULL));
    
    int planetAdj1 = rand()%(map.nNodes()); // scelgo la posizione dove posizionare l'asteroide
    int planetAdj2 = rand()%(map.adj(planetAdj1).size());

    map-={planetAdj1,planetAdj2}; // tolgo il collegamento

    map.addConnectedNode(new Asteroid(),{planetAdj1,planetAdj2}); // aggiungo l'asteroide sul cammino
}

void Galaxy::destroyAsteroid(){

    bool done=false;

    const std::vector<int> adj = map.adj(currentPlanet);
    
    std::for_each(adj.begin(),adj.end(),
        [&](int adj) {
            if (map[adj]->getType() == AsteroidT && !done){
                try {
                    *exp-=rocket;
                    // devo togliere il nodo e collegare i due suoi vicini
                    const std::vector<int> adjAsteroid = map.adj(adj);
                    // l'asteroide ha sempre due vicini
                    map+={adjAsteroid[0],adjAsteroid[1]};
                    // tolgo il nodo
                    map-=map[adj];
                    done = true;
                    exp->consumeEnergy(4.0);
                } catch (std::logic_error e){
                    std::cerr<<e.what()<<std::endl;
                    std::cout<<"There are no rockets to shoot.\n";
                } catch (...){
                    std::cerr<<"An unknown error has occurred.\n";
                }
            }
        });

}

void Galaxy::beginTurn(){ // throws logic_error
    
    try{
        exp->rest();
    } catch (std::logic_error e){ // ho finto l'ossigeno. Non posso continuare
        throw;
    } catch (...) {
        std::cerr<<"An unknown error has occurred.\n";
    }

    srand(time(NULL));
    // cerco gli asteroidi rimasti per distruggere i pianeti
    for(int i=0;i<map.nNodes();i++){
        if(map[i]->getType() == AsteroidT){
            int des = rand()%2; // gli asteroidi hanno solo due vicini
            map[map.adj(i)[des]]->destroy(); // provo a distruggere il pianeta
        }
    }
}

void Galaxy::action() const{
    map[currentPlanet]->action(*exp);
}

void Galaxy::regenerate() const {
    map[currentPlanet]->regenerate(*exp);
}

void Galaxy::travel(){ // throws logic_error
    
    // calcolo i pianeti adiacenti con BFS
    std::vector<int> to; // conterrà i pianeti in cui posso viaggiare
    bool visited[map.nNodes()] = {};
    std::queue<int> Q;
    std::map<int,int> predecessor; // mi serve per capire che percorso faccio e quanto danno prendo
    
    Q.push(currentPlanet);
    predecessor[currentPlanet] = currentPlanet;
    visited[currentPlanet] = true;

    while (!Q.empty()) {
        int index = Q.front(); Q.pop();

        if(map[index]->getType()!=AsteroidT) to.push_back(index);

        for(const auto& adj : map.adj(index)){
            if (!visited[adj] && (index==currentPlanet || map[index]->getType() == AsteroidT) ){
                Q.push(adj);
                predecessor[adj] = index;
                visited[adj]=true;
            }
        }
    }

    // stampo i pianeti accessibili
    std::cout<<"Planets:\n ";
    int i=1;
    for (const auto& des : to){
        std::cout<<"\t"<<i<<": "<<*map[des]<<std::endl;
        i++;
    }

    std::cout<<"Where to?";
    std::cin>>i;
    
    if(i<=to.size()){
        currentPlanet=to[i-1];
        i=to[i-1]; // trovo il pianeta da raggiungere
        while(map[predecessor[i]]->getType() == AsteroidT){ // ripercorro il percorso trovato
            i=predecessor[i]; // mi sposto
            try {
                map[i]->action(*exp); // dannegio l'astronave
            } catch (std::logic_error e) { // ho finito la vita
                throw;
            } catch (...) {
                std::cerr<<"An unknown error has occurred.\n";
            }
        }
    } else {
        std::cout<<"Destination unreachable.\n";
    }

}

Galaxy::~Galaxy(){
    std::fstream save;
    save.open(saveFile,std::fstream::out);
    if(!save){
        std::cerr<<"Error in saving the game.\n";
    } else { // salvo lo stato della galassia nel file e poi dealloco tutto quello che serve
        
        // pianeti
        for(int i=0;i<map.nNodes();i++){
            save<<map[i]->toString()<<std::endl;
        }
        
        save<<"%%%\n";
        
        // collegamenti
        for(int i=0;i<map.nNodes();i++){
            const std::vector<int> adj = map.adj(i);
            for(auto it = adj.begin(); it != adj.end(); it++){
                save<<i<<" "<<*it<<"\n";
            }
        }

        // // collegamenti
        // for(int i=0;i<map.nNodes();i++){
        //     for(const auto it : map.adj(i)){
        //         save<<i<<" "<<it<<"\n";
        //     }
        // }
    }

    // libero la memoria, exp si arrangia a gestire la deallocazione poichè è uno smart pointer
    for(int i=0;i<map.nNodes();i++){
        delete map[i];
        map[i]=NULL;
    }
}

std::ostream& operator<<(std::ostream& out, const Galaxy& g){

    out<<*(g.exp);
    out<<"\n\nCurrently in "<<*g.map[g.currentPlanet]<<std::endl;
    out<<"\nNeighbors:\n";
    for (const auto& v : g.map.adj(g.currentPlanet)){
        if (g.map[v]->getType() != AsteroidT)
            out<<"\t"<<*g.map[v]<<"\n";
    }
    out<<std::endl;

    return out;

}