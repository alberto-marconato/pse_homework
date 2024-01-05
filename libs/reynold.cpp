#include "reynold.h"

mutex mtx;
condition_variable readyToCalculate;
condition_variable readyToPrint;
condition_variable readyToMove;

void reynold_algorithm(vector<boid>& boidvector , vector<boid>::iterator boiditerator, int framesToRender){

    //unique_lock<mutex> mlock(mtx);

    cout << "Thread numero: " << std::this_thread::get_id() << endl;

    int framesCalculated{0};

    while (framesCalculated < framesToRender)
    {
        //readyToCalculate.wait(mlock);
        mtx.lock();
        cout << "Inizio calcoli" << endl;
        boiditerator->alignment(boidvector);
        boiditerator->separation(boidvector);
        boiditerator->cohesion(boidvector);
        mtx.unlock();
        //readyToCalculate.notify_one();
        framesCalculated++;

        if (boiditerator == boidvector.end() - 1){
            readyToPrint.notify_one();
        }
    }
    

}



void printCoordinates(ofstream file, vector<boid>& boidvector, int framesToRender){

    unique_lock<mutex> mlock(mtx);

    int framesPrinted{0};

    while (framesPrinted < framesToRender)
    {
        readyToPrint.wait(mlock);

        for (auto itr = boidvector.begin(); itr != boidvector.end(); ++itr) //for every boid object
        {
            itr->move();
            file << itr->x() << " " << itr->y() << " "; // write the coordinates on coordinates.txt
        }

        file << "\n";

        framesPrinted++;
    }
    
}