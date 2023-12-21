#ifndef BOID_H
#define BOID_H

#include <ostream>
#include <vector>
using namespace std;

class boid{
private:
    int boid_x;  //X component of the boid position (pixel)
    int boid_y;  //Y component of the boid position (pixel)
    int boid_vx; //X component of the boid velocity (pixel/frame)
    int boid_vy; //Y component of the boid velocity (pixel/frame)
public:

    //constructors
    boid(int x, int y, int vx, int vy);
    boid();

    int x() const; //return boid_x
    int y() const; //return boid_y
    int vx() const; //return boid_vx
    int vy() const; //return boid_vy

    void move(); //move the boid throug the screen
    int distance(boid& b); 
    void separation(vector<boid>& boidarray);
};



#endif