#include "reynold.h"


void reynold_algorithm(vector<boid>& boidvector , vector<boid>::iterator boiditerator){

    boiditerator->alignment(boidvector);
    boiditerator->separation(boidvector);
    boiditerator->cohesion(boidvector);
}
