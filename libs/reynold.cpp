#include "reynold.h"

mutex mtx;
condition_variable readyToCalculate;
condition_variable readyToPrint;
condition_variable readyToMove;

int calculated = 0; 
int moved = 0;

void reynold_algorithm(vector<boid>& boidvector , vector<boid>::iterator boiditerator, int framesToRender, int boidnumber){
    
    unique_lock<mutex> lock(mtx);
    int framesCalculated{0};

    while (framesCalculated < framesToRender)
    {
        boiditerator->cohesion(boidvector);
        boiditerator->separation(boidvector);
        boiditerator->alignment(boidvector);

        calculated++;

        if (calculated < boidnumber){
            readyToMove.wait(lock);
        }else{
            readyToMove.notify_all();
        }

        boiditerator->move();
        
        moved++;

        if (moved == boidnumber)
        {
            readyToPrint.notify_one();
        }

        framesCalculated++;

        readyToCalculate.wait(lock);
    }

}



void printCoordinates(ofstream& file, vector<boid>& boidvector, int framesToRender){

    unique_lock<mutex> lock(mtx);
    int framesPrinted{0};
    
    while (framesPrinted < framesToRender )
    {
        readyToPrint.wait(lock);

        for (auto itr = boidvector.begin(); itr != boidvector.end(); ++itr) //for every boid object
        {
            file << itr->x() << " " << itr->y() << " "; // write the coordinates on coordinates.txt
        }

        file << "\n";

        framesPrinted++;
        calculated = 0;
        moved = 0;

        readyToCalculate.notify_all();
    }
    
    
}