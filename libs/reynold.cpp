#include <vector>
#include "boid.h"

using namespace std;

void reynold_algorithm(vector<boid>& boidvector){

    for (auto itr = boidvector.begin(); itr != boidvector.end(); ++itr) //for every boid object
        {
            itr->separation(boidvector);
            itr->cohesion(boidvector);
            itr->alignment(boidvector);
            itr->move(); //move the boid
        }
}