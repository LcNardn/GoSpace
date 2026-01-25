#include "./headers/Galaxy.h"
#include "./headers/DestroyedPlanet.h"
#include "./headers/Planet.h"
#include "./headers/Explorer.h"

#include <string>
#include <algorithm>
#include <set>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <mutex>
#include <atomic>
#include <fstream>
#include <iostream>
#include <exception>
using namespace std;

mutex access;
atomic <bool> finish{false}; // per segnalare alle thread che devono terminare

void asteroidThread(shared_ptr<Galaxy>);
void playerThread(shared_ptr<Galaxy>);

int main(int argc, char* argv[]){

    if (argc != 3){
        cerr<<"Wrong usage of program.\n";
        cout<<"Use expected: <exec_name> <input_file> <save_file>\n";
        exit(1);
    }

    // capisco quale file devo aprire per leggere in input
    int choice;
    fstream in;
    cout<<"Continue exploration (1) or begin a new one (2)?";
    cin>>choice;

    if (choice==1){
        in.open(argv[2],fstream::in);
    } else if (choice==2){
        in.open(argv[1],fstream::in);
    } else {
        cerr<<"Choice not known.\n";
        cout<<"Exiting program. Check the error file for more information.\n";
        exit(2);
    }

    if(!in){
        cerr<<"Error in opening input file.\n";
        cout<<"Exiting program. Check the error file for more information.\n";
        exit(2);
    }

    // creo la galassia
    unique_ptr<Explorer> exp(new Explorer());
    shared_ptr<Planet> des(new DestroyedPlanet());
    shared_ptr<Galaxy> gal; // viene condivisa da più thread
    try {
        gal.reset(new Galaxy(in,argv[2],exp,weak_ptr<Planet>(des)));
    } catch (domain_error e){
        cerr<<"Input not formed correctly.\n";
        cout<<"Exiting program. Check the error file for more information.\n";
        exit(2);
    } catch (...) {
        cerr<<"An unknown error has occurred.\n";
        cout<<"Exiting program. Check the error file for more information.\n";
        exit(3);
    }

    in.close();

    // thread player
    thread pT(playerThread,shared_ptr<Galaxy>(gal));

    // thread asteroidi
    thread aT(asteroidThread,shared_ptr<Galaxy>(gal));

    pT.join();
    aT.join();

    cout<<"Done.\n";

    return 0;
}

void asteroidThread(shared_ptr<Galaxy> gal){

    srand(time(NULL));

    while(!finish.load()){
        this_thread::sleep_for(chrono::seconds(60));
        int spawn = rand()%10;
        if (spawn==0 && access.try_lock()){ // lazy evaluation mi impedisce situazioni di deadlock, cosa non vera se scambio le condizioni
            gal->spawnAsteroid(); // modifico la galassia
            access.unlock(); // sblocco l'accesso alla galassia
        }
    }

}

void playerThread(shared_ptr<Galaxy> gal){

    int nTurns=1;
    string choice;
    getline(cin,choice); // pulisco il buffer di input

    while (!finish.load()){
        cout<<"Turn "<<nTurns<<endl<<*gal;
        cout<<endl<<"1) Action\t4) Rest\n2) Travel\t5) Restore planet\n3) Repair ship\t6) Save and exit\n";
        cout<<"What do you want to do? ";
        
        getline(cin,choice);

        if(choice.compare("Action")==0 || choice.compare("action")==0 || choice.compare("ACTION")==0 || choice.compare("1")==0){

            cout<<"On the planet or on the asteroid? ";
            getline(cin,choice);

            if (choice.compare("1")==0 || choice.compare("planet")==0 || choice.compare("Planet")==0 || choice.compare("PLANET")==0){
                gal->action();
            } else if (choice.compare("2")==0 || choice.compare("asteroid")==0 || choice.compare("Asteroid")==0 || choice.compare("ASTEROID")==0){
                gal->destroyAsteroid();
            } else {cout<<choice<<"is an unknown action.\n";}

        } else if (choice.compare("Rest")==0 || choice.compare("rest")==0 || choice.compare("REST")==0 || choice.compare("4")==0){

            try{
                access.lock(); // visto che il metodo accede alla mappa, devo assicurarmi che l'altra thread non la stia modificando in contemporanea
                gal->beginTurn();
                access.unlock();
                nTurns++;
            } catch (logic_error e){
                cout<<"You have run out of oxygen. Game over.\n";
                finish=true;
            } catch (...) {
                cerr<<"An unknown error has occurred.\n";
            }

        } else if (choice.compare("Travel")==0 || choice.compare("travel")==0 || choice.compare("TRAVEL")==0 || choice.compare("2")==0){

            try{
                access.lock(); // visto che il metodo accede alla mappa, devo assicurarmi che l'altra thread non la stia modificando in contemporanea
                gal->travel();
                access.unlock();
                getline(cin,choice); // pulisco lo stream
            } catch (logic_error e){
                cout<<"Your ship has been destroyed. Game over.\n";
                finish=true;
            } catch (...) {
                cerr<<"An unknown error has occurred.\n";
            }

        } else if(choice.compare("Restore")==0 || choice.compare("restore")==0 || choice.compare("RESTORE")==0 || choice.compare("5")==0){

            gal->regenerate();
        
        } else if(choice.compare("Repair")==0 || choice.compare("repair")==0 || choice.compare("REPAIR")==0 || choice.compare("3")==0){
        
            gal->repair();
        
        } else if (choice.compare("Save")==0 || choice.compare("save")==0 || choice.compare("SAVE")==0 || choice.compare("6")==0){
        
            finish=true;
        
        } else {cout<<choice<<"is an unknown action.\n";}

        cout<<"====================================\n";

    }

    cout<<"Closing game...\n";

}