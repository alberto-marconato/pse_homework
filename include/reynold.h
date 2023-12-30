#ifndef REYNOLD_H
#define REYNOLD_H

#include <thread>
#include <mutex>

#include "boid.h"

using namespace std;

void reynold_algorithm(vector<boid>& boidvector, vector<boid>::iterator boiditerator);

#endif