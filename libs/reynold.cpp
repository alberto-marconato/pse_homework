#include "reynold.h"

mutex mtx;
condition_variable readyToCalculate;
condition_variable readyToPrint;
condition_variable readyToMove;

int calculated = 0;
int moved = 0;
bool toPrint = false;

void reynold_algorithm(vector<boid>& boidvector , vector<boid>::iterator boiditerator, int framesToRender){
    
    unique_lock<mutex> lock(mtx);
    int framesCalculated{0};

    while (framesCalculated < framesToRender)
    {
        if (toPrint == true)
        {
            readyToCalculate.wait(lock);
        }
        

        boiditerator->separation(boidvector);
        boiditerator->cohesion(boidvector);
        boiditerator->alignment(boidvector);

        cout << "Ho calcolato" << endl;

        framesCalculated++;
        calculated++;

        if (calculated < boidvector.size())
        {
            readyToMove.wait(lock);
        }else{
            readyToMove.notify_all();
        }

        boiditerator->move();
        cout << "Ho mosso " << endl;
        moved++;

        if (moved = boidvector.size())
        {
            readyToPrint.notify_one();
            toPrint = true;
        }
        
        framesCalculated++;
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
        toPrint = false;

        readyToCalculate.notify_all();
    }
    
    
}