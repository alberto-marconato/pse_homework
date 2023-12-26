#include "boid.h"
#include <iostream>
#include <fstream>

using namespace std;

#define LEFTMARGIN 0 
#define RIGHTMARGIN 50
#define BOTTOMARGIN 0
#define TOPMARGIN 30

#define NUMBER_OF_BOIDS 20
#define NUMBER_OF_FRAMES 50

int main(){

    srand (static_cast <unsigned> (time(0))); // seed generation for boid creation
    vector<boid> boids;

    ofstream outfile ("src/coordinates.txt");

    outfile << LEFTMARGIN <<" " << RIGHTMARGIN << " " << BOTTOMARGIN << " " << TOPMARGIN <<"\n"; 

    for (int i = 0; i < NUMBER_OF_BOIDS; ++i) // creation of the boid vector
    {
        boids.push_back(boid());
    }

    cout << "Avviata simulazione di " << NUMBER_OF_BOIDS << " boid per " << NUMBER_OF_FRAMES << " frames\n" ;

    for (int i = 0; i < NUMBER_OF_FRAMES; ++i) //for every frames rendered
    {
        for (auto itr = boids.begin(); itr != boids.end(); ++itr) //for every boid object
        {
            itr->separation(boids);
            itr->cohesion(boids);
            itr->alignment(boids);
            outfile << itr->x() << " " << itr->y() << " "; // write the coordinates on coordinates.txt
            itr->move(); //move the boid
        }

        outfile << "\n";
        
    }
    
    cout << "Simulazione terminata. Risultati salvati in coordinates.txt .\n ";
    
    
    outfile.close();

    return 0;
}