#include "boid.h"
#include <iostream>

#define VECTOR_DIM 50

using namespace std;

int main(){

    cout << "------ TEST ------ \n";
     
    srand (static_cast <unsigned> (time(0))); // seed generation for boid creation

   cout << "1) Inizializzando un vettore di boid ... \n"; 
   vector<boid> boidvector;

   for (int i = 0; i < VECTOR_DIM; ++i)
   {
        boidvector.push_back(boid());
        cout<< "Creato boid numero " << boidvector.size();
        cout<< " con valori (x , y , vx , vy) = " <<boidvector.at(i)<<endl;
   }

   cout << "Vettore inizializzato. Nessun errrore ;) \n\n";
   cout << "2) Testando la funzione move() ... \n";

   for (auto itr = boidvector.begin(); itr != boidvector.end(); ++itr)
   {
        cout<< "Muovo boid da posizione ( " << itr->x() << " , " << itr->y() <<" ) " ;
        itr->move();
        cout<< "alla posizione ( " << itr->x() << " , " << itr->y() <<" ) " ;
        cout<< "con vettore di velocità ( " << itr->vx() << " , " << itr->vy() <<" )\n";
   }

   cout << "Nessun errore durante il movimento ;) \n\n";
    
}