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

    outfile << BOTTOMARGIN <<" " << TOPMARGIN << " " << LEFTMARGIN << " " << RIGHTMARGIN <<"\n"; 

    for (int i = 0; i < NUMBER_OF_BOIDS; ++i)
    {
        boids.push_back(boid());
    }

    for (int i = 0; i < NUMBER_OF_FRAMES; ++i)
    {
        for (auto itr = boids.begin(); itr != boids.end(); ++itr)
        {
            outfile << itr->x() << " " << itr->y() << " ";
            itr->move();
        }

        outfile << "\n";
        
    }
    
    
    
    
    outfile.close();
}