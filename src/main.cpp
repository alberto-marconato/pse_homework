#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>

#include "boid.h"
#include "reynold.h"

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
    vector<thread> boidThreads;

    ofstream outfile ("src/coordinates.txt");

    outfile << LEFTMARGIN <<" " << RIGHTMARGIN << " " << BOTTOMARGIN << " " << TOPMARGIN <<"\n"; 

    for (int i = 0; i < NUMBER_OF_BOIDS; ++i) // creation of the boid vector
    {
        boids.push_back(boid());
    }

    cout << "Avviata simulazione di " << NUMBER_OF_BOIDS << " boid per " << NUMBER_OF_FRAMES << " frames\n" ;

    for (auto itr = boids.begin(); itr != boids.end(); ++itr){ //for every boid object
        boidThreads.push_back(thread{reynold_algorithm, ref(boids), itr, NUMBER_OF_FRAMES, NUMBER_OF_BOIDS});
    }

    thread print{printCoordinates, ref(outfile), ref(boids), NUMBER_OF_FRAMES};

    /*for (int calculated_frames = 0; calculated_frames < NUMBER_OF_FRAMES; ++calculated_frames) //for every frames rendered
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
        
    }*/

    for (auto itr = boidThreads.begin(); itr != boidThreads.end(); ++itr){ //for every thread
        itr->join();
    }

    print.join();

    
    
    cout << "Simulazione terminata. Risultati salvati in coordinates.txt .\n ";
    
    
    outfile.close();

    return 0;
}