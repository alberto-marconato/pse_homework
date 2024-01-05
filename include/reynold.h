#ifndef REYNOLD_H
#define REYNOLD_H

#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "boid.h"

using namespace std;

void reynold_algorithm(vector<boid>& boidvector, vector<boid>::iterator boiditerator, int framesToRender);
void printCoordinates(ofstream file, vector<boid>& boidvector, int framesToRender);

#endif