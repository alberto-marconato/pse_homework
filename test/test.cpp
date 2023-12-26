#include "boid.h"
#include <iostream>
#include <fstream>

#define VECTOR_DIM 50

using namespace std;

int main(){

     srand (static_cast <unsigned> (time(0))); // seed generation for boid creation

     ofstream outfile ("test/log.txt");

    cout << "------ TEST ------ \n";

   cout << "1) Inizializzando un vettore di boid ... \n"; // Test 1
   vector<boid> boidvector;

   for (int i = 0; i < VECTOR_DIM; ++i) // Testing generation of a vector of boid
   {
        boidvector.push_back(boid());
        outfile<< "Creato boid numero " << boidvector.size();
        outfile<< " con valori (x , y , vx , vy) = " <<boidvector.at(i)<<endl;
   }

   cout << "Vettore inizializzato. Nessun errrore ;) \n\n";

   cout << "2) Testando la funzione move() ... \n"; // Test 2

   for (auto itr = boidvector.begin(); itr != boidvector.end(); ++itr) // Testing movement for every boid created
   {
        outfile<< "Muovo boid da posizione (" << itr->x() << " , " << itr->y() <<") " ;
        itr->move();
        outfile<< "a posizione (" << itr->x() << " , " << itr->y() <<") " ;
        outfile<< "con vettore di velocità (" << itr->vx() << " , " << itr->vy() <<")" << endl;
   }

   cout << "Nessun errore durante il movimento ;) \n\n";

      cout << "3) Testando la funzione distance() ... \n"; // Test 2

   for (auto itr = boidvector.begin(); itr != boidvector.end(); ++itr) // Testing movement for every boid created
   {
     for (int i = 0; i < VECTOR_DIM; ++i)
     {
          outfile<< "Distanza da (" << itr->x() << " , " << itr->y() <<") " ;
          outfile<< "a (" << boidvector[i].x() << " , " << boidvector[i].y() <<") " ;
          outfile<< "pari a: " << itr->distance(boidvector[i]) << endl;
     }
       
   }

   cout << "Nessun errore durante il calcolo delle distanze ;) \n\n";

   cout << "Test terminato. Nessun PC esploso! ;) \n" ;
   cout << "(Per maggiori dettagli leggere il file log.txt)\n";

   outfile.close();

   return 0;
    
}